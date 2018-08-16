
#pragma once

namespace sys {
class Environment;

class CleanerBase {

  public:
    CleanerBase() = default;
    CleanerBase(const CleanerBase &) = default;
    CleanerBase &operator=(const CleanerBase &) = default;
    Environment *env;
    void run();
    virtual ~CleanerBase() = default;

  protected:
    template <typename cleaner_name>
    void save_to_env(const cleaner_name *self_ptr);
};
} // namespace sys
