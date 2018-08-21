#include "../../Constants.h"
#include <string>
#include <vector>

#pragma once
namespace sys {

using std::shared_ptr;
using std::string;
using std::vector;
class Environment;
class OrderBase;

class SignalBase {

  public:
    SignalBase(const string &strategy_name,
               const ActionType &action_type,
               const double size,
               const string &ticker,
               const double price,
               const double takeprofit,
               const double takeprofit_pct,
               const double stoploss,
               const double stoploss_pct,
               const double trailingstop,
               const double trailingstop_pct);

    Environment *env;

    const string strategy_name;
    const ActionType action_type;
    const double size;
    const string ticker;

    const double price;
    const double takeprofit;
    const double takeprofit_pct;
    const double stoploss;
    const double stoploss_pct;
    const double trailingstop;
    const double trailingstop_pct;

    const int signal_id;
    const string datetime;
    const string next_datetime;

  protected:
    static int _counter;
    void _check_all_conflict();
    void _check_size();
    void _check_conflict(const double obj,
                         const double obj_pct,
                         const string &name);

    virtual void _save_signals() = 0;
};

class Signal : public SignalBase {
  public:
    Signal(const string &strategy_name,
           const ActionType &action_type,
           const double size,
           const string &ticker,
           const double price,
           const double takeprofit,
           const double takeprofit_pct,
           const double stoploss,
           const double stoploss_pct,
           const double trailingstop,
           const double trailingstop_pct);

  private:
    void _save_signals() override;
};

class SignalForPending : public SignalBase {
  public:
    SignalForPending(const string &strategy_name,
                     const ActionType &action_type,
                     const double size,
                     const string &ticker,
                     const double price,
                     const double takeprofit,
                     const double takeprofit_pct,
                     const double stoploss,
                     const double stoploss_pct,
                     const double trailingstop,
                     const double trailingstop_pct);

  private:
    void _save_signals() override;
};

class SignalByTrigger : public SignalBase {
  public:
    SignalByTrigger(
        const OrderType &order_type,
        const int mkt_id,
        const string &trigger_key,
        const double execute_price,
        const double first_cur_price,
        const shared_ptr<OrderBase> &parent_order,
        const string &strategy_name,
        const ActionType &action_type,
        const double size,
        const string &ticker,
        const double price,
        const double takeprofit,
        const double takeprofit_pct,
        const double stoploss,
        const double stoploss_pct,
        const double trailingstop,
        const double trailingstop_pct);

    const OrderType order_type;
    const int mkt_id;
    const string trigger_key;
    const double execute_price;
    const double first_cur_price;
    const shared_ptr<OrderBase> parent_order;

    const int signal_id; // 触发信号重新计数
    static int _counter;

  private:
    void _save_signals() override;
};

int SignalBase::_counter = 1;
int SignalByTrigger::_counter = 1;
} // namespace sys
