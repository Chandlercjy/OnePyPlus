#include "DataType.h"
#include "OP_DECLARE.h"

#pragma once

OP_NAMESPACE_START

class Environment;

class CleanerBase {

  public:
    CleanerBase(const string &name,
                const int rolling_window,
                int buffer_day,
                const string &frequency);

    virtual ~CleanerBase();

    Environment *env;

    const string name;
    const int rolling_window;
    int buffer_day;
    const string frequency;

    void initialize_buffer_data(const string &ticker);
    virtual double calculate(const string &ticker) = 0;
    void run();

  private:
    void _save_cleaners_feeds(const string &ticker);
    void _settle_frequency(const string &ticker);
    void _save_data(const string &ticker,
                    const string &key,
                    shared_ptr<BarBase> cleaners_ohlc);
    void _append_data_to_buffer();
    void _remove_redudent(const string &key);
    void _check_is_name_overloaded();

  protected:
    CleanerData *_data_ptr = new CleanerData;//需要在子类中删除

  public:
    CleanerData &data = *_data_ptr;
};

OP_NAMESPACE_END
