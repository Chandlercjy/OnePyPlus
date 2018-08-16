
#pragma once

namespace sys {
class Environment;
class RecorderBase {
  public:
    RecorderBase() = default;
    RecorderBase(const RecorderBase &) = default;
    RecorderBase &operator=(const RecorderBase &) = default;

    Environment *env;
    void run();
    virtual ~RecorderBase() = default;

  protected:
    template <typename recorder_name>
    void save_to_env(const recorder_name *self_ptr);
};
} // namespace sys
