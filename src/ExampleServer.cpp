#include <utility>
#include "XConfig.h"
#include "Router.h"

#include <proxygen/httpserver/ResponseBuilder.h>

auto peopleHandler = [](XrpcRequest xrpcRequest) {

  return proxygen::ResponseBuilder(xrpcRequest.getHandler())
      .status(200, "OK")
      .body(folly::IOBuf::copyBuffer(std::string("OK")))
      .sendWithEOM();
};

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);
  google::InitGoogleLogging(argv[0]);
  google::InstallFailureSignalHandler();
  LOG(INFO) << "Starting Server";

  XConfig config;

  Router router(std::move(config));

  router.addRoute("/people", peopleHandler, XHttpMethod::GET);
  router.listenAndServe();
  return 0;
}
