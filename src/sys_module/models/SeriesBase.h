#include "../../DataType.h"
#include <map>
#include <string>
#include <vector>

#pragma once

namespace sys {
using std::map;
using std::string;
using std::vector;
class Environment;

class SeriesBase {
  public:
    SeriesBase();
    Environment *env;

    virtual const string get_name() = 0;
    virtual void update_order() = 0;

    void change_initial_value(const string &ticker,
                              const double value,
                              const string &long_or_short);
    double latest(const string &ticker,
                  const string &long_or_short,
                  const int value) const;
    double total_value() const;

  private:
    map<string, vector<SeriesStruct>> _data;

    void _initialize_data();
    void _append_value(const string &ticker,
                       const double value,
                       const string &long_or_short);
    double get_barly_cur_price(const string &ticker,
                               const bool order_executed);
};

} // namespace sys
