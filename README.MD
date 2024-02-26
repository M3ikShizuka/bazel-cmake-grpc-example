# Bazel gRPC project
## Build
Build server:
```bash
bazel build //src/server:server
```
Build client:
```bash
bazel build //src/client:client
```
Build gRPC lib:
```bash
bazel build //src/lib_grpc:lib_grpc
```
## Run
```bash
./bazel-bin/src/server/server.exe
```
```bash
./bazel-bin/src/client/client.exe
```