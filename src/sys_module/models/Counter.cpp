#include "sys_module/models/Counter.h"

namespace op {

int Counter::update_signal_id() {
    return signal_id++;
}

int Counter::update_signal_by_trigger_id() {
    return signal_by_trigger_id++;
}

int Counter::update_signal_cancel_id() {
    return signal_cancel_id++;
}

int Counter::update_order_id(){
    return order_id++;

};
int Counter::update_mkt_id(){
    return mkt_id++;
};

} // namespace op
