load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

##################################################################################
#### rules_proto
##################################################################################
http_archive(
    name = "rules_proto",
    strip_prefix = "rules_proto-5.3.0-21.7",
    urls = [
        "https://github.com/bazelbuild/rules_proto/archive/refs/tags/5.3.0-21.7.tar.gz",
    ],
)
load("@rules_proto//proto:repositories.bzl", "rules_proto_dependencies", "rules_proto_toolchains")
rules_proto_dependencies()
rules_proto_toolchains()

##################################################################################
#### rules_proto_grpc
##################################################################################
http_archive(
    name = "rules_proto_grpc",
    strip_prefix = "rules_proto_grpc-4.6.0",
    urls = ["https://github.com/rules-proto-grpc/rules_proto_grpc/releases/download/4.6.0/rules_proto_grpc-4.6.0.tar.gz"],
)

load("@rules_proto_grpc//:repositories.bzl", "rules_proto_grpc_toolchains", "rules_proto_grpc_repos")
rules_proto_grpc_toolchains()
rules_proto_grpc_repos()

##################################################################################
#### com_github_grpc_grpc
##################################################################################
http_archive(
    name = "com_github_grpc_grpc",
    strip_prefix = "grpc-1.52.1",
    urls = [
        "https://github.com/grpc/grpc/archive/refs/tags/v1.52.1.tar.gz",
    ],
)

load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
grpc_deps()

load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
grpc_extra_deps()