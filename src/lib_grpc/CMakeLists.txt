# CMakeList.txt : CMake project for Heap, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.25)

# Build library.
add_library(
		lib_grpc_proto
		${file_grpc_srcs}
		${file_grpc_hdrs}
		${file_proto_srcs}
		${file_proto_hdrs})
target_link_libraries(
		lib_grpc_proto
		${_REFLECTION}
		${_GRPC_GRPCPP}
		${_PROTOBUF_LIBPROTOBUF})

add_dependencies(lib_grpc_proto ${TARGET_BUILD_PROTO})