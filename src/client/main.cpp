#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "src/lib_grpc/rpc.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
using grpc::Status;
using myroute::MyRoute;
using myroute::RouteMessage;

class MyRouteClient {
private:
    std::unique_ptr<MyRoute::Stub> stub_;

public:
    MyRouteClient(const std::shared_ptr<Channel>& channel)
        : stub_(MyRoute::NewStub(channel))
    {
    }

    [[nodiscard]] std::string SetScore(const int32_t score) const {
        myroute::ScoreRequest request{};
        request.set_score(score);

        myroute::ScoreReply reply{};
        grpc::ClientContext context{};

        const auto status = stub_->SetScore(&context, request, &reply);
        if (!status.ok()) {
            throw std::exception(status.error_message().c_str());
        }

        return reply.message();
    }

    [[nodiscard]] std::vector<std::string> RouteChat(const std::vector<std::string>& messages) const {
        ClientContext context;
        std::shared_ptr<ClientReaderWriter<RouteMessage, RouteMessage>> stream(stub_->RouteChat(&context));

        std::thread writer([stream, &messages]() {
            std::vector<RouteMessage> route_messages(messages.size());

            for (const std::string& message : messages) {
                RouteMessage route_message;
                route_message.set_message(message);
                stream->Write(route_message);
            }

            stream->WritesDone();
        });

        std::vector<std::string> received_messages;
        RouteMessage route_received_message;
        while (stream->Read(&route_received_message)) {
            received_messages.push_back(route_received_message.message());
        }

        // Fix capacity.
        received_messages.shrink_to_fit();

        writer.join();

        Status status = stream->Finish();
        if (!status.ok()) {
            throw std::exception(status.error_message().c_str());
        }

        return received_messages;
    }
};

class Communication {
public:
    void DoWork() {
        try {
            MyRouteClient guide(
                    grpc::CreateChannel("localhost:50051",
                                        grpc::InsecureChannelCredentials())
            );

            const auto message = guide.SetScore(31);
            std::cout << "SetScore() reply: " << message << std::endl;

            const std::vector<std::string> messages {
                    "Client Message 1",
                    "Client Message 2",
                    "Client Message 3",
                    "Client Message 4",
                    "Client Message 5",
            };
            const auto received_messages = guide.RouteChat(messages);
            std::string str_out {"RouteChat() reply:\n"};
            for (const auto& msg : received_messages) {
                str_out += msg + "\n";
            }

            std::cout << str_out;
        }
        catch(const std::exception& except) {
            std::cout << "Communication exception: " << except.what() << std::endl;
        }
    }
};

int main(int argc, char** argv) {
    try {
        const auto communication = std::make_unique<Communication>();
        communication->DoWork();
    }
    catch(...)
    {
        std::cerr << "An unhandled exception was caught!\n";
        return 1;
    }

    return 0;
}