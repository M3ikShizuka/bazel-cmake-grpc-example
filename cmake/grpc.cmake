cmake_minimum_required (VERSION 3.8)
# gRPC
# CMake Error: install(EXPORT "protobuf-targets" ...) includes target "libprotobuf-lite" which requires target "absl_absl_check" that is not in any export set.
set(protobuf_INSTALL OFF)
set(utf8_range_ENABLE_INSTALL OFF)

add_subdirectory("external/grpc" EXCLUDE_FROM_ALL)
message(STATUS "Using gRPC via add_subdirectory.")

# After using add_subdirectory, we can now use the grpc targets directly from
# this build.
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_ORCA_SERVICE grpcpp_orca_service)
if(CMAKE_CROSSCOMPILING)
  find_program(_PROTOBUF_PROTOC protoc)
else()
  set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()
set(_GRPC_GRPCPP grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

set(PROTO_FILES_DIR "src/gprc_lib")

# Proto file
get_filename_component(proto_idl_file "${PROTO_FILES_DIR}/rpc.proto" ABSOLUTE)
get_filename_component(proto_idl_file_path ${proto_idl_file} PATH)

# Generated sources
set(file_proto_srcs "${proto_idl_file_path}/rpc.pb.cc")
set(file_proto_hdrs "${proto_idl_file_path}/rpc.pb.h")
set(file_grpc_srcs "${proto_idl_file_path}/rpc.grpc.pb.cc")
set(file_grpc_hdrs "${proto_idl_file_path}/rpc.grpc.pb.h")

set(TARGET_BUILD_PROTO "proto-compile-idl")
project(${TARGET_BUILD_PROTO})
add_custom_target(${TARGET_BUILD_PROTO} DEPENDS "${file_proto_srcs}" "${file_proto_hdrs}" "${file_grpc_srcs}" "${file_grpc_hdrs}")
add_custom_command(
        OUTPUT "${file_proto_srcs}" "${file_proto_hdrs}" "${file_grpc_srcs}" "${file_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${proto_idl_file_path}"
        --cpp_out "${proto_idl_file_path}"
        -I "${proto_idl_file_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${proto_idl_file}"
        DEPENDS ${proto_idl_file}
)

# Include generated *.pb.h files
include_directories("${proto_idl_file_path}")