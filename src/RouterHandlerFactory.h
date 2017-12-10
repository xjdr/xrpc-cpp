
//

#pragma once

#include <proxygen/httpserver/RequestHandlerFactory.h>
#include <folly/ThreadLocal.h>
#include "RouterHandler.h"
using namespace proxygen;

class RouterHandlerFactory : public RequestHandlerFactory {
 private:
  struct TimerWrapper {
    folly::HHWheelTimer::UniquePtr timer;
  };

  folly::ThreadLocalPtr<RouterStats> stats_;
  folly::ThreadLocal<TimerWrapper> timer_;

 public:
  void onServerStart(folly::EventBase *evb) noexcept override {
    stats_.reset(new RouterStats);
    timer_->timer = folly::HHWheelTimer::newTimer(
        evb,
        std::chrono::milliseconds(folly::HHWheelTimer::DEFAULT_TICK_INTERVAL),
        folly::AsyncTimeout::InternalEnum::NORMAL,
        std::chrono::seconds(60));
  }

  void onServerStop() noexcept override {
    stats_.reset();
    timer_->timer.reset();
  }

  RequestHandler *onRequest(RequestHandler *, HTTPMessage *) noexcept override {
    return new RouterHandler(stats_.get(), timer_->timer.get());
  }
};



