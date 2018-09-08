#include "OP_DECLARE.h"
//#include "OrderStruct.h"
//#include "SignalStruct.h"

#pragma once

OP_NAMESPACE_START

enum class ActionType;
class ReaderBase;
class BarBase;
class BarBase;
class CleanerBase;
class StrategyBase;
class BrokerBase;
class RiskManagerBase;
class RecorderBase;
class EventEngine;
class SignalBase;
class Signal;
class SignalForPending;
class SignalByTrigger;
class SignalCancel;
class SignalCancelTST;
class SignalCancelPending;
class OrderBase;
class MarketOrder;
class PendingOrder;
class CancelTSTOrder;
class CancelPendingOrder;

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

//using SignalNormalPtr = unique_ptr<SignalNormalStruct>;
//using SignalForPendingPtr = unique_ptr<SignalForPendingStruct>;
//using SignalByTriggerPtr = unique_ptr<SignalByTriggerStruct>;
//using SignalCancelTSTPtr = unique_ptr<SignalForPendingStruct>;
//using SignalCancelPendingPtr = unique_ptr<SignalByTriggerStruct>;

using MarketOrderPtr = shared_ptr<MarketOrder>;
using SignalBasePtr = shared_ptr<SignalBase>;
using SignalPtr = shared_ptr<Signal>;
using SignalForPendingPtr = shared_ptr<SignalForPending>;
using SignalByTriggerPtr = shared_ptr<SignalByTrigger>;
using SignalCancelTSTPtr = shared_ptr<SignalCancelTST>;
using SignalCancelPendingPtr = shared_ptr<SignalCancelPending>;

using PendingOrderPtr = shared_ptr<PendingOrder>;
using CancelTSTOrderPtr = shared_ptr<CancelTSTOrder>;
using CancelPendingOrderPtr = shared_ptr<CancelPendingOrder>;

using OhlcVector = vector<OhlcStruct>;

template <typename value, typename key = string>
using ModuleMap = map<key, shared_ptr<value>>;

template <typename T>
using PtrBox = vector<T>;

using Cash_func_ptr_type = double (*)(const MarketOrderPtr &order);

//struct ChildOfMktStruct {
//ChildOfMktStruct(
//const int mkt_id,
//LimitOrderPtr &&limit_order,
//StopOrderPtr &&stop_order,
//TrailingStopOrderPtr &&trailingstop_order)
//: mkt_id(mkt_id),
//limit_order(std::move(limit_order)),
//stop_order(std::move(stop_order)),
//trailingstop_order(std::move(trailingstop_order)){};
//const int mkt_id;
//const LimitOrderPtr limit_order;
//const StopOrderPtr stop_order;
//const TrailingStopOrderPtr trailingstop_order;
//};

//using ChildOfMktPtr = unique_ptr<ChildOfMktStruct>;

OP_NAMESPACE_END
