COPTS = select({
    "@bazel_tools//src/conditions:windows": ["/std:c++17"],
    "//conditions:default": ["--std=c++17"],
})

cc_binary(
    name = "server",
    srcs = glob(["*.cpp"]),
    deps = [
        "@com_github_grpc_grpc//:grpc++",
        "//src/lib_grpc:lib_grpc",
    ],
    copts = COPTS,
)
