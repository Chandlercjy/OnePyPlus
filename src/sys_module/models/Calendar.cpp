#include "../../Environment.h"
#include "../../Exceptions.h"
#include "../../utils/arrow.h"
#include "../../utils/easy_func.h"
#include "Calendar.h"
#include <string>

namespace sys {
using namespace utils;
using std::string;


Calendar::Calendar()
    : env(Environment::get_instance()){};

void Calendar::initialize(const string &instrument) {
    if (instrument == "A_shares")
        this->_is_trading_time = &Calendar::_is_A_shares_trading_time;
    else if (instrument == "Forex")
        this->_is_trading_time = &Calendar::_is_forex_trading_time;
};

bool Calendar::_is_forex_trading_time(string date_str) {
    int weekday = arrow::get_isoweek(date_str);
    auto now = arrow::str_to_sec(date_str);
    if (weekday <= 4)
        return true;

    switch (weekday) {
        case 5:
            date_str.replace(date_str.find(" "), 9, " 22:00:00");
            if (now < arrow::str_to_sec(date_str)) return true;
            break;
        case 7:
            date_str.replace(date_str.find(" "), 9, " 21:00:00");
            if (now >= arrow::str_to_sec(date_str)) return true;
            break;
    }
    return false;
};

bool Calendar::_is_A_shares_trading_time(string date_str) {
    int weekday = arrow::get_isoweek(date_str);
    auto now = arrow::str_to_sec(date_str);
    if (weekday <= 5) {
        if (env->sys_frequency == "D") {
            return true;
        } else {
            string left_1 = date_str.replace(date_str.find(" "), 9, " 09:30:00");
            string right_1 = date_str.replace(date_str.find(" "), 9, " 11:30:00");
            string left_2 = date_str.replace(date_str.find(" "), 9, " 13:00:00");
            string right_2 = date_str.replace(date_str.find(" "), 9, " 15:00:00");

            if ((arrow::str_to_sec(left_1) < now && now < arrow::str_to_sec(right_1)) ||
                (arrow::str_to_sec(left_2) < now && now < arrow::str_to_sec(right_2)))
                return true;
        };
    }
    return false;
};

void Calendar::update_calendar() {

    if (env->is_live_trading) {
        assert(1 < 2); //TODO: format sys_date
    } else {
        do {
            _check_todate();
            env->sys_date = arrow::shift_seconds_to_str(
                env->sys_date, get_second_ratio(env->sys_frequency));
        } while (!(this->*_is_trading_time)(env->sys_date));
    };
}; // namespace sys
void Calendar::_check_todate() {
    static arrow::seconds_type todate = arrow::str_to_sec(env->todate);
    if (arrow::str_to_sec(env->sys_date) >= todate)
        throw except::BacktestFinished();
};
} // namespace sys
