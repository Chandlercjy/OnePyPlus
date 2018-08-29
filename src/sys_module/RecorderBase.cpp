#include "../Environment.h"
#include "RecorderBase.h"
#include "models/SeriesBase.h"

namespace sys {
using std::make_shared;

RecorderBase::RecorderBase()
    : env(Environment::get_instance()){};

void RecorderBase::run() {
    _record_order();
};

void RecorderBase::update(const bool &order_executed) {
    market_value->update_barly(order_executed);
    holding_pnl->update_barly(order_executed);
    margin->update_barly();
    _update_balance(env->sys_date);
    _update_cash(env->sys_date);
};

void RecorderBase::_update_balance(const string &trading_date){

};

void RecorderBase::_record_order(){};

template <typename T>
void RecorderBase::save_to_env(const T *self_ptr, const string &name) {
    env->recorders[name] = make_shared<T>(*self_ptr); //TODO:设置名字
    env->recorder = env->recorders[name];
}
} // namespace sys
