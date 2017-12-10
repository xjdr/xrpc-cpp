#pragma once

#include <proxygen/lib/http/session/HTTPUpstreamSession.h>

class SessionWrapper : public proxygen::HTTPSession::InfoCallback {
 private:
  proxygen::HTTPUpstreamSession* session_{nullptr};

 public:
  explicit SessionWrapper(proxygen::HTTPUpstreamSession* session)
      : session_(session) {
    session_->setInfoCallback(this);
  }

  ~SessionWrapper() override {
    if (session_) {
      session_->drain();
    }
  }

  proxygen::HTTPUpstreamSession* operator->() const {
    return session_;
  }

  // Note: you must not start any asynchronous work from onDestroy()
  void onDestroy(const proxygen::HTTPSessionBase&) override {
    session_ = nullptr;
  }
};
