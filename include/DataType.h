#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class MarketOrder;
enum class ActionType;

struct OhlcStruct {
    const string date;
    const double open;
    const double high;
    const double low;
    const double close;
    const double volume;
};

struct SeriesStruct {
    const string date;
    double value;
};

using OhlcVector = vector<OhlcStruct>;

template <typename value, typename key = string>
using ModuleMap = map<key, shared_ptr<value>>;

template <typename T>
using SignalBox = vector<shared_ptr<T>>;

template <typename T>
using OrderBox = vector<shared_ptr<T>>;

using Cash_func_ptr_type = double (*)(const shared_ptr<MarketOrder> &order);

OP_NAMESPACE_END
