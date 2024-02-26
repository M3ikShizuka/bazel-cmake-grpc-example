#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <grpcpp/security/server_credentials.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include "src/lib_grpc/rpc.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;
using myroute::MyRoute;
using myroute::RouteMessage;
using std::chrono::system_clock;

class MyRouteImpl final : public MyRoute::Service {
public:
    explicit MyRouteImpl()
    {
    }

    Status SetScore(::grpc::ServerContext* context,
            const ::myroute::ScoreRequest* request,
            ::myroute::ScoreReply* response) override {
        const auto score = request->score();
        if (score > 0) {
            response->set_message("Score received");
        }
        else {
            response->set_message("Negative score");
        }

        return Status::OK;
    }

    Status RouteChat(ServerContext* context,
                     ServerReaderWriter<RouteMessage, RouteMessage>* stream) override {
        RouteMessage note;
        while (stream->Read(&note)) {
            const auto& str_message = note.message();
            const auto reply = str_message + " reply from server";
            RouteMessage new_message;
            new_message.set_message(reply);
            stream->Write(new_message);
        }

        return Status::OK;
    }
};

class GRPCServer {
public:
    void Run() {
        std::string server_address("0.0.0.0:50051");
        MyRouteImpl service{};

        ServerBuilder builder;
        builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
        builder.RegisterService(&service);
        std::unique_ptr<Server> server(builder.BuildAndStart());
        std::cout << "Server listening on " << server_address << std::endl;
        server->Wait();
    }
};

int main(int argc, char** argv) {
    try {
        const auto rpc_server = std::make_unique<GRPCServer>();
        rpc_server->Run();
    }
    catch(...)
    {
        std::cerr << "An unhandled exception was caught!\n";
        return 1;
    }

    return 0;
}