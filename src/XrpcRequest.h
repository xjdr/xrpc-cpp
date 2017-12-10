
//

#pragma once

#include <proxygen/httpserver/ResponseHandler.h>

class XrpcRequest {

 public:
  proxygen::ResponseHandler *getHandler() {

    return handler;
  }

 private:
  proxygen::ResponseHandler *handler;
};



