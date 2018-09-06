#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

enum class ActionType {
    Buy,
    Sell,
    Short,
    Cover,
    Cancel,
};

enum class OrderType {
    Market,
    Limit,
    Stop,
    Trailing_stop,
};

enum class OrderStatus {
    Created,
    Submitted,
    Partial,
    Completed,
    Canceled,
    Expired,
    Margin,
    Rejected,
    Triggered,
};

enum class EVENT {
    Market_updated,
    Data_cleaned,
    Signal_generated,
    Submit_order,
    Record_result,
    None,
};

enum class MODULES {
    Cleaners,
    Strategies,
    Risk_managers,
    Brokers,
    Recorders,
};

OP_NAMESPACE_END
