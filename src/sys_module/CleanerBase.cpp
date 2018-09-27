#include "Environment.h"
#include "sys_module/CleanerBase.h"
#include "sys_module/ReaderBase.h"
#include "sys_module/RecorderBase.h"
#include "sys_module/models/BarBase.h"
#include "utils/arrow.h"
#include "utils/utils.h"
#include <iostream>

OP_NAMESPACE_START
using utils::arrow;
using utils::Stl;

CleanerBase::CleanerBase(const string &name,
                         const int rolling_window,
                         int buffer_day,
                         const string &frequency)
    : env(Environment::get_instance()),
      name(name),
      rolling_window(rolling_window), //设定数据长度
      buffer_day(buffer_day),         //设定数据初始化长度
      frequency(frequency){};

void CleanerBase::run() {
    _append_data_to_buffer();
};

//设置frequency，如果没有指定的话就默认为系统frequency
void CleanerBase::_settle_frequency(const string &ticker) {
    if (frequency != env->sys_frequency)
        _save_cleaners_feeds(ticker);
    else
        const_cast<string &>(frequency) = env->sys_frequency;
}

//保存cleaners的专有数据feeds
void CleanerBase::_save_cleaners_feeds(const string &ticker) {
    static const string temp = "_";
    auto key = ticker + temp + frequency;
    auto value = env->recorder->bar_class(ticker, frequency);

    if (value->initialize(7))
        env->cleaners_feeds[key] = value;
}

void CleanerBase::_save_data(const string &ticker,
                             const string &key,
                             shared_ptr<BarBase> cleaners_ohlc) {

    data[key].date.emplace_back(cleaners_ohlc->date());
    data[key].open.emplace_back(cleaners_ohlc->open());
    data[key].high.emplace_back(cleaners_ohlc->high());
    data[key].low.emplace_back(cleaners_ohlc->low());
    data[key].close.emplace_back(cleaners_ohlc->close());
    data[key].volume.emplace_back(cleaners_ohlc->volume());

    data[key].date.pop_front();
    data[key].open.pop_front();
    data[key].high.pop_front();
    data[key].low.pop_front();
    data[key].close.pop_front();
    data[key].volume.pop_front();
}

void CleanerBase::_append_data_to_buffer() {
    for (auto &elem : data) {
        const string &key = elem.first;
        const string &ticker = elem.second.ticker;
        if (!Stl::is_elem_in_vector(env->cur_suspended_tickers,
                                    ticker)) {
            if (frequency == env->sys_frequency) {
                _save_data(ticker, key, env->feeds[ticker]);
            } else {
                auto &cleaners_ohlc = env->cleaners_feeds[key];
                if (!cleaners_ohlc->is_bar_series_end()) {
                    while (arrow::str_to_sec(cleaners_ohlc->next_date()) <=
                           arrow::str_to_sec(env->sys_date)) {
                        cleaners_ohlc->next_directly();
                        if (!cleaners_ohlc->is_bar_series_end())
                            _save_data(ticker, key, cleaners_ohlc);
                        else
                            break;
                    }
                }
            }
        }
    }
}

void CleanerBase::_remove_redudent(const string &key) {
    int useless_size = data[key].date.size() - rolling_window;
    data[key].date.erase(data[key].date.cbegin(),
                         data[key].date.cbegin() + useless_size);
    data[key].open.erase(data[key].open.cbegin(),
                         data[key].open.cbegin() + useless_size);
    data[key].high.erase(data[key].high.cbegin(),
                         data[key].high.cbegin() + useless_size);
    data[key].low.erase(data[key].low.cbegin(),
                        data[key].low.cbegin() + useless_size);
    data[key].close.erase(data[key].close.cbegin(),
                          data[key].close.cbegin() + useless_size);
    data[key].volume.erase(data[key].volume.cbegin(),
                           data[key].volume.cbegin() + useless_size);
};

void CleanerBase::initialize_buffer_data(const string &ticker) {
    _check_is_name_overloaded();
    _settle_frequency(ticker);

    //初始化data,若已存在则什么都不做
    static const string temp = "_";
    auto key = ticker + temp + frequency;
    data.emplace(key, ticker);

    //假如时间太长没有load到，就删除
    if (buffer_day > 500) {
        std::cout << key
                  << " is not enough for cleaners. Deleted!!!!"
                  << std::endl;
        data.erase(key);
        auto tickers_ref = const_cast<vector<string> &>(env->tickers);
        tickers_ref.erase(std::find(tickers_ref.cbegin(),
                                    tickers_ref.cend(),
                                    ticker));
    }

    auto &reader = env->readers[ticker];
    auto buffer_start_date = arrow::shift_days_to_str(env->sys_date, -buffer_day);
    auto buffer_end_date = arrow::shift_seconds_to_str(env->sys_date, -1);
    auto buffer_data = reader->load_by_cleaner(buffer_start_date,
                                               buffer_end_date,
                                               frequency);
    for (auto &value : *buffer_data) {
        data[key].date.emplace_back(value.date);
        data[key].open.emplace_back(value.open);
        data[key].high.emplace_back(value.high);
        data[key].low.emplace_back(value.low);
        data[key].close.emplace_back(value.close);
        data[key].volume.emplace_back(value.volume);
    }

    //检查buffer数据是否足够，否则递归重新load
    int useless_size = data[key].date.size() - rolling_window;

    if (useless_size < 0) {
        buffer_day += 2;
        data[key].clear();
        initialize_buffer_data(ticker);
        std::cout << "Retry "
                  << name
                  << "! Perfect bufer_day is "
                  << buffer_day << std::endl;

    } else { //控制长度
        _remove_redudent(key);
    }
};

void CleanerBase::_check_is_name_overloaded() {
    if (!name.size())
        throw std::logic_error("Cleaner's name should be overloaded!");
}

CleanerBase::~CleanerBase() {
    delete _data_ptr;
}

OP_NAMESPACE_END
