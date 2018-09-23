#include "Environment.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/components/TradeLogGenerator.h"
#include "sys_module/models/GeneralOrder.h"
#include "utils/easy_func.h"

OP_NAMESPACE_START
using utils::ForexUtils;

TradeLogGenerator::TradeLogGenerator()
    : env(Environment::get_instance()),
      action_type_map({{ActionType::Buy, "Buy"},
                       {ActionType::Sell, "Sell"},
                       {ActionType::Short, "Short"},
                       {ActionType::Cover, "Cover"}}),
      order_type_map({{OrderType::Market, "Market "},
                      {OrderType::Limit, "Limit "},
                      {OrderType::Stop, "Stop "},
                      {OrderType::Trailing_stop, "Trailing_stop "}}){};

void TradeLogGenerator::initialize(const string &instrument) {
    if (instrument == "A_shares") {
        this->_make_log_ptr = &TradeLogGenerator::_make_log_A_shares;
        this->_settle_left_trade_ptr =
            &TradeLogGenerator::_settle_left_trade_A_shares;
    } else if (instrument == "Forex") {
        this->_make_log_ptr = &TradeLogGenerator::_make_log_Forex;
        this->_settle_left_trade_ptr =
            &TradeLogGenerator::_settle_left_trade_Forex;
    } else {
        throw std::logic_error("Instrument should be A_shares or Forex!");
    }
};

shared_ptr<TradeLogStruct>
TradeLogGenerator::make_log(MarketOrderPtr &buy_order,
                            MarketOrderPtr &sell_order,
                            const double size) {
    return (this->*_make_log_ptr)(buy_order, sell_order, size);
}

shared_ptr<TradeLogStruct> TradeLogGenerator::settle_left_trade(
    MarketOrderPtr &unfinished_order, const double size) {
    return (this->*_settle_left_trade_ptr)(unfinished_order, size);
}

// A股生成交易记录的函数
shared_ptr<TradeLogStruct>
TradeLogGenerator::_make_log_A_shares(MarketOrderPtr &buy_order,
                                      MarketOrderPtr &sell_order,
                                      const double size) {
    const double per_comm_pct = env->recorder->per_comm_pct;
    const double per_comm = env->recorder->per_comm;

    const string &ticker = buy_order->ticker;
    const string &entry_date = buy_order->trading_date;
    const string &exit_date = sell_order->trading_date;

    const double entry_price = buy_order->execute_price;
    const double exit_price = sell_order->execute_price;

    const string &entry_type = order_type_map[buy_order->from_order_type] +
                               action_type_map[buy_order->action_type];
    const string &exit_type = order_type_map[sell_order->from_order_type] +
                              action_type_map[sell_order->action_type];

    const int direction = buy_order->action_type == ActionType::Buy ? 1 : -1;

    const double pl_points = (exit_price - entry_price) * direction;
    const double re_pnl = pl_points * size;

    const double commission =
        (per_comm_pct != 0) ? (per_comm_pct * size * entry_price)
                            : (per_comm * size / 100);

    return make_shared<TradeLogStruct>(ticker,
                                       entry_date,
                                       exit_date,
                                       entry_price,
                                       exit_price,
                                       entry_type,
                                       exit_type,
                                       pl_points,
                                       size,
                                       re_pnl,
                                       commission);
}

shared_ptr<TradeLogStruct> TradeLogGenerator::_settle_left_trade_A_shares(
    MarketOrderPtr &unfinished_order, const double size) {
    const double per_comm_pct = env->recorder->per_comm_pct;
    const double per_comm = env->recorder->per_comm;

    const string &ticker = unfinished_order->ticker;
    const string &entry_date = unfinished_order->trading_date;
    const string &exit_date = "";

    const double entry_price = unfinished_order->execute_price;
    const double exit_price = env->feeds[ticker]->execute_price();

    const string &entry_type = order_type_map[unfinished_order->from_order_type] +
                               action_type_map[unfinished_order->action_type];
    const string &exit_type = "";

    const int direction = unfinished_order->action_type == ActionType::Buy ? 1 : -1;

    const double pl_points = (exit_price - entry_price) * direction;
    const double re_pnl = pl_points * size;

    const double commission =
        (per_comm_pct != 0) ? (per_comm_pct * size * entry_price)
                            : (per_comm * size / 100);

    return make_shared<TradeLogStruct>(ticker,
                                       entry_date,
                                       exit_date,
                                       entry_price,
                                       exit_price,
                                       entry_type,
                                       exit_type,
                                       pl_points,
                                       size,
                                       re_pnl,
                                       commission);
}

// Forex生成交易记录的函数
shared_ptr<TradeLogStruct>
TradeLogGenerator::_make_log_Forex(MarketOrderPtr &buy_order,
                                   MarketOrderPtr &sell_order,
                                   const double size) {
    const double slippage = utils::Forex_slippage[buy_order->ticker];

    const string &ticker = buy_order->ticker;
    const string &entry_date = buy_order->trading_date;
    const string &exit_date = sell_order->trading_date;

    const double entry_price = buy_order->execute_price;
    const double exit_price = sell_order->execute_price;

    const string &entry_type = order_type_map[buy_order->from_order_type] +
                               action_type_map[buy_order->action_type];
    const string &exit_type = order_type_map[sell_order->from_order_type] +
                              action_type_map[sell_order->action_type];

    const int direction = buy_order->action_type == ActionType::Buy ? 1 : -1;

    const double pl_points = (exit_price - entry_price) * direction;
    const double re_pnl = pl_points *
                          size *
                          ForexUtils::dollar_per_pips(ticker, exit_price);

    const double commission = slippage * size / 1e5 *
                              ForexUtils::dollar_per_pips(ticker, entry_price);
    return make_shared<TradeLogStruct>(ticker,
                                       entry_date,
                                       exit_date,
                                       entry_price,
                                       exit_price,
                                       entry_type,
                                       exit_type,
                                       pl_points,
                                       size,
                                       re_pnl,
                                       commission);
}

shared_ptr<TradeLogStruct> TradeLogGenerator::_settle_left_trade_Forex(
    MarketOrderPtr &unfinished_order, const double size) {
    const double slippage = utils::Forex_slippage[unfinished_order->ticker];

    const string &ticker = unfinished_order->ticker;
    const string &entry_date = unfinished_order->trading_date;
    const string &exit_date = "";

    const double entry_price = unfinished_order->execute_price;
    const double exit_price = env->feeds[ticker]->execute_price();

    const string &entry_type = order_type_map[unfinished_order->from_order_type] +
                               action_type_map[unfinished_order->action_type];
    const string &exit_type = "";

    const int direction = unfinished_order->action_type == ActionType::Buy ? 1 : -1;

    const double pl_points = (exit_price - entry_price) * direction;
    const double re_pnl = pl_points *
                          size *
                          ForexUtils::dollar_per_pips(ticker, exit_price);

    const double commission = slippage * size / 1e5 *
                              ForexUtils::dollar_per_pips(ticker, entry_price);

    return make_shared<TradeLogStruct>(ticker,
                                       entry_date,
                                       exit_date,
                                       entry_price,
                                       exit_price,
                                       entry_type,
                                       exit_type,
                                       pl_points,
                                       size,
                                       re_pnl,
                                       commission);
}

OP_NAMESPACE_END
