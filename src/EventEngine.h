#pragma once
#include "constants.h"
#include <queue>

class EventEngine {
  public:
    void put(EVENT);
    EVENT get(void);
    int size(void) const;
    bool is_core_empty(void) const;

  private:
    std::queue<EVENT> _core;
    void _check_core_empty(void) const;
};
