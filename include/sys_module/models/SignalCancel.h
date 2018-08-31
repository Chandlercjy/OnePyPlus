
#include "../../Constants.h"
#include <string>
#include <vector>

#pragma once
namespace op {

using std::shared_ptr;
using std::string;
using std::vector;
class Environment;
class OrderBase;
class SignalCancelBase {
  public:
    SignalCancelBase(
        const string &strategy_name,
        const string &ticker,
        const string &long_or_short);

    Environment *env;

    const string strategy_name;
    const string ticker;
    const string long_or_short;

    const string datetime;
    const int signal_id;
    static int _counter;

  protected:
    virtual void _check_conflict() = 0;
    virtual void _save_signals() = 0;
};

class SignalCancelTST : public SignalCancelBase {
  public:
    SignalCancelTST(
        const string &strategy_name,
        const string &ticker,
        const string &long_or_short,
        const bool takeprofit,
        const bool stoploss,
        const bool trailingstop);

    const double takeprofit;
    const double stoploss;
    const double trailingstop;

  private:
    void _check_conflict() override;
    void _save_signals() override;
};

class SignalCancelPending : public SignalCancelBase {
  public:
    SignalCancelPending(
        const string &strategy_name,
        const string &ticker,
        const string &long_or_short,
        const double below_price,
        const double above_price);

    const double below_price;
    const double above_price;

  private:
    void _check_conflict() override;
    void _save_signals() override;
};

int SignalCancelBase::_counter = 1;
} // namespace op

