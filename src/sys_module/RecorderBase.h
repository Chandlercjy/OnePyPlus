#include <string>
#pragma once

namespace sys {
using std::string;
class Environment;
class BarBase;

class RecorderBase {
  public:
    RecorderBase();
    RecorderBase(const RecorderBase &) = default;
    RecorderBase &operator=(const RecorderBase &) = default;

    Environment *env;
    virtual std::shared_ptr<BarBase> bar_class(const string &ticker,
                                               const string &frequency) = 0;

    void initialize();
    void run();
    void update(const bool &order_executed);
    virtual ~RecorderBase() = default;

  protected:
    template <typename recorder_name>
    void save_to_env(const recorder_name *self_ptr);
};
} // namespace sys
