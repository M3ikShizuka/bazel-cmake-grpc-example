build-all: build-server build-client

run-all: run-server run-client

build-lib:
	bazel build //src/lib_grpc:lib_grpc

build-server:
	bazel build //src/server:server

build-client:
	bazel build //src/client:client

run-server:
	./bazel-bin/src/server/server.exe

run-client:
	./bazel-bin/src/client/client.exe