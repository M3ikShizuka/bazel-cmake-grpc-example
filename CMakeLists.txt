# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.25)
project("gRPC-test-project")
# Enable tests.
enable_testing()
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

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

################################################
# Dependencies
################################################
include("cmake/grpc.cmake")

################################################
# Targets
################################################
# Include sub-projects.
add_subdirectory("src/lib_grpc")
add_subdirectory("src/server")
add_subdirectory("src/client")
