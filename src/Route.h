
//

#pragma once

#include <re2/re2.h>
#include <string>
#include <assert.h>

#define VARIABLE_PATTERN "\\{(\\w+)(?::([^\\{\\}]+))?\\}";

class Route {
 public:
  Route build(std::string path) {

  };

 private:
  RE2 re(VARIABLE_PATTERN);

  Route() {
    assert(re.ok());
  }


};