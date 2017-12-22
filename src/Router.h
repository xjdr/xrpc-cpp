//

#pragma once

#include <string>
#include <map>
#include <proxygen/httpserver/HTTPServer.h>
#include "XConfig.h"
#include "XHttpMethod.h"
#include "XrpcRequest.h"
#include "RouterHandlerFactory.h"

class Router {
 private:
  XConfig _config;
  //std::atomic<std::map<std::string, std::pair<XHttpMethod, std::shared_ptr<std::function<void(XrpcRequest)>>>>> route_list;

 public:
  explicit Router(XConfig &&config) : _config(config) {

  }

  static auto makeShared(std::function<void(XrpcRequest)> handler) {
    return std::make_shared<std::function<void(XrpcRequest)>>(handler);
  }

  void addRoute(std::string route, std::shared_ptr<std::function<void(XrpcRequest)>> handler, XHttpMethod method) {

  }

  void listenAndServe() {
    std::vector<proxygen::HTTPServer::IPConfig> ips = {
        {folly::SocketAddress("0.0.0.0", 11000, true), proxygen::HTTPServer::Protocol::HTTP},
        {folly::SocketAddress("0.0.0.0", 11001, true), proxygen::HTTPServer::Protocol::HTTP2},
    };

    wangle::SSLContextConfig sslCfg;
    sslCfg.isDefault = true;
    sslCfg.setCertificate(
        "certs/xjeffrose.com.crt",
        "certs/xjeffrose.com.key",
        "");

    for (auto cfg : ips) {
      cfg.sslConfigs.push_back(sslCfg);
    }

    proxygen::HTTPServerOptions options;
    options.threads = static_cast<size_t>(sysconf(_SC_NPROCESSORS_ONLN));
    options.idleTimeout = std::chrono::milliseconds(60000);
    options.shutdownOn = {SIGINT, SIGTERM};
    options.enableContentCompression = false;
    options.handlerFactories = proxygen::RequestHandlerChain()
        .addThen<RouterHandlerFactory>()
        .build();

    //options.h2cEnabled = true;
    //options.supportsConnect = true;

    auto server = std::make_unique<proxygen::HTTPServer>(std::move(options));

    server->bind(ips);

    std::thread t([&] () {
      server->start();
    });

    t.join();

  }


};



