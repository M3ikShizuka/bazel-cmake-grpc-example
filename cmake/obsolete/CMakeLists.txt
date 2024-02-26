# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Fix cmake compile test "is not able to compile a simple test program."
# set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")
# set(CMAKE_C_COMPILER_WORKS 1)
# set(CMAKE_CXX_COMPILER_WORKS 1)

## Verbose Ninja, Makefile, etc.
## or just use argument -v on build: cmake.exe --build ...mybuild/x64-win-debug-mingw --target all -j 6 -v
# set(CMAKE_VERBOSE_MAKEFILE ON)
# set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON")
# set(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "ON" FORCE)

# Common
set(COMMON_PROJECT_CPP_STANDARD 17 CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD ${COMMON_PROJECT_CPP_STANDARD})
set(COMMON_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/src/common" ON CACHE BOOL "" FORCE)
set(TEST_DATA_DIRECTORY "${CMAKE_SOURCE_DIR}/tests")

#if (MSVC)
#  add_compile_options(/permissive)
#endif()

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

################################################
# include FetchContent
include(FetchContent)
# Set common folder for dependencies.
set(FETCHCONTENT_QUIET off)
get_filename_component(deps_dir "../../external"
        REALPATH BASE_DIR "${CMAKE_BINARY_DIR}")
set(FETCHCONTENT_BASE_DIR ${deps_dir})
################################################
## Fetch GoogleTest
# GoogleTest requires at least C++14
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  #create gt build directory in binary tree
  add_subdirectory(${googletest_SOURCE_DIR} gt)
endif()

################################################
## Fetch gRPC
set(protobuf_INSTALL OFF)
set(utf8_range_ENABLE_INSTALL OFF)
# Use CMake's FetchContent module to clone gRPC at
# configure time. This makes gRPC's source code available to your project,
# similar to a git submodule.
FetchContent_Declare(
        gRPC
        GIT_REPOSITORY https://github.com/grpc/grpc
        GIT_TAG        v1.60.1  # e.g v1.28.0
)
set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(gRPC)

FetchContent_GetProperties(gRPC)
if(NOT googletest_POPULATED)
  FetchContent_Populate(gRPC)
  #create gr build directory in binary tree
  add_subdirectory(${gRPC_SOURCE_DIR} gr)
endif()

# Since FetchContent uses add_subdirectory under the hood, we can use
# the grpc targets directly from this build.
set(_PROTOBUF_LIBPROTOBUF libprotobuf)
set(_REFLECTION grpc++_reflection)
set(_PROTOBUF_PROTOC $<TARGET_FILE:protoc>)
set(_GRPC_GRPCPP grpc++)
if(CMAKE_CROSSCOMPILING)
  find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
  set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:grpc_cpp_plugin>)
endif()

set(PROTO_FILES_DIR "../../common/protobuf")

################################################
# Include header directories. (old method)
#include_directories(${INCLUDE_COMMON_DIR})

################################################
project("gRPC")
# Enable tests.
enable_testing()
# Include sub-projects.
add_subdirectory("src/server")
add_subdirectory("src/client")
