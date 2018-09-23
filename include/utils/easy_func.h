
#include <map>
#include <string>
#pragma once

namespace utils {
using std::map;
using std::string;

class Easy {
  public:
    Easy() = delete;

    static int get_second_ratio(const string &frequency) {
        int result = 0;
        if (frequency == "S5")
            result = 5;
        else if (frequency == "S10")
            result = 10;
        else if (frequency == "S30")
            result = 30;
        else if (frequency == "M1")
            result = 60;
        else if (frequency == "M2")
            result = 120;
        else if (frequency == "M4")
            result = 240;
        else if (frequency == "M5")
            result = 300;
        else if (frequency == "M10")
            result = 600;
        else if (frequency == "M15")
            result = 900;
        else if (frequency == "M30")
            result = 1800;
        else if (frequency == "H1")
            result = 3600;
        else if (frequency == "H2")
            result = 7200;
        else if (frequency == "H3")
            result = 10800;
        else if (frequency == "H4")
            result = 14400;
        else if (frequency == "H8")
            result = 28800;
        else if (frequency == "H12")
            result = 43200;
        else if (frequency == "D")
            result = 86400;
        return result;
    };
};

class ForexUtils {
  public:
    ForexUtils() = delete;

    static double
    dollar_per_pips(const string &ticker, const double cur_price) {
        if (ticker.find("USD") == 0)
            return 10 / cur_price;
        else if (ticker.find("USD") == 4)
            return 10;
        else
            throw std::logic_error("Could only backtest in USD currency pairs.");
    };

    static double market_value_multiplyer(const string &ticker,
                                           const double cur_price) {
        if (ticker.find("USD") == 0)
            return 1;
        else if (ticker.find("USD") == 4)
            return cur_price;
        else
            throw std::logic_error("Could only backtest in USD currency pairs.");
    };
};

static map<string, double> Forex_slippage = {{"EUR_USD", 1.5},
                                                   {"AUD_USD", 1.5},
                                                   {"GBP_USD", 2.0},
                                                   {"USD_CAD", 2.0},
                                                   {"USD_JPY", 1.5}};

} // namespace utils
