# CMakeList.txt : CMake project for Heap, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.25)

# Build executable.
add_executable(
		grpc_server
		main.cpp)
target_link_libraries(
		grpc_server
		lib_grpc_proto
		absl::flags
		absl::flags_parse
		${_REFLECTION}
		${_GRPC_GRPCPP}
		${_PROTOBUF_LIBPROTOBUF})

## Include header directories. (new method)
#target_include_directories(${PROJECT_NAME} PRIVATE ${COMMON_INCLUDE_DIR})
#
#if (CMAKE_VERSION VERSION_GREATER 3.12)
#  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD ${COMMON_PROJECT_CPP_STANDARD})
#endif()
#
## GoogleTests
#set(CURRENT_TEST_PROJECT_NAME grpc_server_test)
#project(${CURRENT_TEST_PROJECT_NAME})
#add_executable (${CURRENT_TEST_PROJECT_NAME} main.test.cpp)
#
#if (CMAKE_VERSION VERSION_GREATER 3.12)
#	set_property(TARGET ${CURRENT_TEST_PROJECT_NAME} PROPERTY CXX_STANDARD ${COMMON_PROJECT_CPP_STANDARD})
#endif()
#
## GoogleTest requires at least C++14
#target_link_libraries(
#		${CURRENT_TEST_PROJECT_NAME}
#		GTest::gtest_main
#)
#
#include(GoogleTest)
#gtest_discover_tests(${CURRENT_TEST_PROJECT_NAME})
