#pragma once
#include "date.h"
#include <string>

namespace utils {

using namespace date;
using namespace std::chrono;
using std::string;

class arrow {
  public:
    typedef time_point<system_clock, duration<long long, std::ratio<1, 1>>> seconds_type;

    static seconds_type str_to_sec(const string &date_str) {
        char *pBeginPos = (char *) date_str.c_str();
        char *pPos = strstr(pBeginPos, "-");
        if (pPos == nullptr) {
            printf("date_str[%s] err \n", date_str.c_str());
            throw std::logic_error("Date_str is not accepted");
        }
        unsigned iYear = std::strtoul(pBeginPos, 0, 0);
        unsigned iMonth = std::strtoul(pPos + 1, 0, 0);
        pPos = strstr(pPos + 1, "-");
        if (pPos == nullptr) {
            printf("date_str[%s] err \n", date_str.c_str());
            throw std::logic_error("Date_str is not accepted");
        }
        unsigned iDay = std::strtoul(pPos + 1, 0, 0);
        unsigned iHour = 0;
        unsigned iMin = 0;
        unsigned iSec = 0;
        pPos = strstr(pPos + 1, " ");
        //为了兼容有些没精确到时分秒的
        if (pPos != nullptr) {
            iHour = std::strtoul(pPos + 1, 0, 0);
            pPos = strstr(pPos + 1, ":");
            if (pPos != nullptr) {
                iMin = std::strtoul(pPos + 1, 0, 0);
                pPos = strstr(pPos + 1, ":");
                if (pPos != nullptr) {
                    iSec = std::strtoul(pPos + 1, 0, 0);
                }
            }
        }
        return sys_days{year(iYear) / iMonth / iDay} +
               hours(iHour) + minutes(iMin) + seconds(iSec);
    };

    static string sec_to_str(const seconds_type &total_seconds) {
        auto date_temp = floor<days>(total_seconds);
        auto date_part = year_month_day(date_temp);
        auto time_part = make_time(total_seconds - date_temp);
        char chTmp[128];

        snprintf(chTmp, sizeof(chTmp), "%04d-%02d-%02d %02d:%02d:%02d",
                 date_part.year().count(),
                 date_part.month().count(),
                 date_part.day().count(),
                 static_cast<int>(time_part.hours().count()),
                 static_cast<int>(time_part.minutes().count()),
                 static_cast<int>(time_part.seconds().count()));
        return chTmp;
    }

    static seconds_type shift_days(const seconds_type &total_seconds, const int value) {
        return total_seconds + days(value);
    }

    static seconds_type shift_days(const string &date_str, const int value) {
        return str_to_sec(date_str) + days(value);
    }

    static string shift_days_to_str(const seconds_type &total_seconds, const int value) {
        return sec_to_str(shift_days(total_seconds, value));
    }

    static string shift_days_to_str(const string date_str, const int value) {
        return sec_to_str(shift_days(date_str, value));
    }

    static seconds_type shift_seconds(const seconds_type &total_seconds, const int value) {
        return total_seconds + seconds(value);
    }

    static seconds_type shift_seconds(const string &date_str, const int value) {
        return str_to_sec(date_str) + seconds(value);
    }

    static string shift_seconds_to_str(const seconds_type &total_seconds, const int value) {
        return sec_to_str(shift_seconds(total_seconds, value));
    }

    static string shift_seconds_to_str(const string date_str, const int value) {
        return sec_to_str(shift_seconds(date_str, value));
    }

    static bool is_gte(const string &lval, const string &rval) {
        return str_to_sec(lval) >= str_to_sec(rval) ? true : false;
    }

    static bool is_gte(const seconds_type &lval, const seconds_type &rval) {
        return lval >= rval ? true : false;
    }

    static bool is_lte(const string &lval, const string &rval) {
        return str_to_sec(lval) <= str_to_sec(rval) ? true : false;
    }

    static bool is_lte(const seconds_type &lval, const seconds_type &rval) {
        return lval <= rval ? true : false;
    }

    static bool is_gt(const string &lval, const string &rval) {
        return str_to_sec(lval) > str_to_sec(rval) ? true : false;
    }

    static bool is_gt(const seconds_type &lval, const seconds_type &rval) {
        return lval > rval ? true : false;
    }

    static bool is_lt(const string &lval, const string &rval) {
        return str_to_sec(lval) < str_to_sec(rval) ? true : false;
    }

    static bool is_lt(const seconds_type &lval, const seconds_type &rval) {
        return lval < rval ? true : false;
    }
    static int _get_isoweek_func(const int days) {
        int result = days >= -4 ? (days + 4) % 7 : (days + 5) % 7 + 6;
        return result == 0 ? 7 : result;
    }

    static int get_isoweek(const string &date_str) { // 周一~周日 1-7
        char *pBeginPos = (char *) date_str.c_str();
        char *pPos = strstr(pBeginPos, "-");
        if (pPos == nullptr) {
            printf("date_str[%s] err \n", date_str.c_str());
            throw std::logic_error("Date_str is not accepted");
        }
        unsigned iYear = std::strtoul(pBeginPos, 0, 0);
        unsigned iMonth = std::strtoul(pPos + 1, 0, 0);
        pPos = strstr(pPos + 1, "-");
        if (pPos == nullptr) {
            printf("date_str[%s] err \n", date_str.c_str());
            throw std::logic_error("Date_str is not accepted");
        }
        unsigned iDay = std::strtoul(pPos + 1, 0, 0);

        auto day_obj = sys_days{year(iYear) / iMonth / iDay};
        return _get_isoweek_func(day_obj.time_since_epoch().count());
    }

    static int get_isoweek(const seconds_type &total_seconds) {
        auto day_obj = floor<days>(total_seconds);
        return _get_isoweek_func(day_obj.time_since_epoch().count());
    }
};

} // namespace utils
