#include "DataStruct.hpp"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

enum class ActionType;
enum class OrderType;
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

using CleanerData = map<string, CleanerDataStruct>;

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

using TradeLogPtr = shared_ptr<TradeLogStruct>;

using OhlcVector = vector<OhlcStruct>;
using OhlcVectorPtr = shared_ptr<OhlcVector>;

template <typename value, typename key = string>
using ModuleMap = map<key, shared_ptr<value>>;

template <typename T>
using PtrBox = vector<T>;

using Cash_func_ptr_type = double (*)(const MarketOrderPtr &order);

using SeriesVector = vector<SeriesStruct>;
using SeriesDict = map<string, SeriesVector>;

OP_NAMESPACE_END
