#include "sys_module/models/Counter.h"

namespace op {

int Counter::update_signal_id() {
    static int signal_id = 1;
    return signal_id++;
}

int Counter::update_signal_by_trigger_id() {
    static int signal_by_trigger_id = 1;
    return signal_by_trigger_id++;
}

int Counter::update_signal_cancel_id() {
    static int signal_cancel_id = 1;
    return signal_cancel_id++;
}

int Counter::update_order_id() {
    static int order_id = 1;
    return order_id++;
};

int Counter::update_mkt_id() {
    static int mkt_id = 1;
    return mkt_id++;
};

} // namespace op
