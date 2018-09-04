#include "OP_DECLARE.h"
#include "OrderStruct.h"
#include "SignalStruct.h"

#pragma once

OP_NAMESPACE_START

class MarketOrder;
enum class ActionType;

struct OhlcStruct {
    OhlcStruct(const string &date, const double open, const double high,
               const double low, const double close, const double volume)
        : date(date),
          open(open),
          high(high),
          low(low),
          close(close),
          volume(volume){};
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

using SignalNormalPtr = unique_ptr<SignalNormalStruct>;
using SignalForPendingPtr = unique_ptr<SignalForPendingStruct>;
using SignalByTriggerPtr = unique_ptr<SignalByTriggerStruct>;

//using MarketOrder = unique_ptr<MarketOrderStruct>;
//using LimitOrder = unique_ptr<LimitOrderStruct>;
//using StopOrder = unique_ptr<StopOrderStruct>;
//using TrailingStopOrder = unique_ptr<TrailingStopOrderStruct>;
//using CancelOrder = unique_ptr<CancelOrderStruct>;
//using CancelOrderPending = unique_ptr<CancelOrderPendingStruct>;

OP_NAMESPACE_END
