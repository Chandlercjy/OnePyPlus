#include "../../Constants.h"
#include <map>
#include <string>
#include <vector>

#pragma once
namespace sys {

using std::map;
using std::shared_ptr;
using std::string;
using std::vector;
class Environment;
class OrderBase;

class SignalBase {

  public:
    SignalBase(const map<string, double> &info,
               const string &ticker,
               const string &strategy_name,
               const ActionType &action_type);

    Environment *env;

    map<string, double> info;
    const string ticker;

    const string strategy_name;
    const ActionType action_type;

    double size;
    double price;
    double takeprofit;
    double takeprofit_pct;
    double stoploss;
    double stoploss_pct;
    double trailingstop;
    double trailingstop_pct;

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
    void _record_info(map<string, double> info);

    virtual void _save_signals() = 0;
};

class Signal : public SignalBase {
  public:
    Signal(const map<string, double> &info,
           const string &ticker,
           const string &strategy_name,
           const ActionType &action_type);

  private:
    void _save_signals() override;
};

class SignalForPending : public SignalBase {
  public:
    SignalForPending(const map<string, double> &info,
                     const string &ticker,
                     const string &strategy_name,
                     const ActionType &action_type);

  private:
    void _save_signals() override;
};

class SignalByTrigger : public SignalBase {
  public:
    SignalByTrigger(const map<string, double> &info,
                    const string &ticker,
                    const string &strategy_name,
                    const ActionType &action_type,
                    const OrderType &order_type,
                    const int mkt_id,
                    const string &trigger_key,
                    const double execute_price,
                    const double first_cur_price,
                    const double parent_order_difference);

    const OrderType order_type;
    const int mkt_id;
    const string trigger_key;
    const double execute_price;
    const double first_cur_price;
    const double parent_order_difference;

    const int signal_id; // 触发信号重新计数

  private:
    void _save_signals() override;
    static int _counter;
};

int SignalBase::_counter = 1;
int SignalByTrigger::_counter = 1;
} // namespace sys
