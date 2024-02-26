load("@rules_proto//proto:defs.bzl", "proto_library")
load("@com_github_grpc_grpc//bazel:cc_grpc_library.bzl", "cc_grpc_library")
load("@com_github_grpc_grpc//bazel:grpc_build_system.bzl", "grpc_proto_library")
load("@com_github_grpc_grpc//bazel:python_rules.bzl", "py_grpc_library", "py_proto_library")

package(default_visibility = ["//visibility:public"])

# The following three rules demonstrate the usage of the cc_grpc_library rule in
# in a mode compatible with the native proto_library and cc_proto_library rules.
proto_library(
    name = "lib_grpc_proto",
    srcs = ["rpc.proto"],
)

cc_proto_library(
    name = "lib_grpc_cc_proto",
    deps = [":lib_grpc_proto"],
)

cc_grpc_library(
    name = "lib_grpc",
    srcs = [":lib_grpc_proto"],
    grpc_only = True,
    deps = [":lib_grpc_cc_proto"],
)

##################################################################################
#### Golang
##################################################################################
load("@io_bazel_rules_go//go:def.bzl", "go_library")
load("@io_bazel_rules_go//proto:def.bzl", "go_proto_library")

go_proto_library(
    name = "lib_grpc_go_proto",
    compilers = ["@io_bazel_rules_go//proto:go_grpc"],
    importpath = "example.com/repo/foo",
    proto = ":lib_grpc_proto",
    deps = ["//bar:bar_go_proto"],
)

go_library(
    name = "lib_grpc_go",
    embed = [":lib_grpc_go_proto"],
    importpath = "libgrpc",
)
