#pragma once

namespace op {
enum class ActionType {
    Buy,
    Sell,
    Short,
    Cover,
    Exit_all,
    Cancel,
};

enum class OrderType {

    Market,
    Limit,
    Stop,
    Trailing_stop,
    Limit_pct,
    Stop_pct,
    Trailing_stop_pct,
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
} // namespace op
