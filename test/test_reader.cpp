#include "builtin_module/CsvReader.h"
#include "builtin_module/backtest_stock/StockRecorder.h"
#include "setting_for_test.hpp"
#include "sys_module/components/MarketMaker.h"
#include "sys_module/models/BarBase.h"
#include "utils/arrow.h"
#include <gtest/gtest.h>

using namespace op;

class CSVReaderTest : public ::testing::Test {
  public:
    void test_load(
        const string &start,
        const string &end,
        const shared_ptr<OhlcVector> &iter_data);
};

void CSVReaderTest::test_load(const string &start,
                              const string &end,
                              const shared_ptr<OhlcVector> &iter_data) {
    using namespace utils;
    auto data_ptr = iter_data->cbegin();
    auto first_date = data_ptr->date;
    double shift_num = 0;

    if (FREQUENCY == "H1")
        shift_num = 1.0 / 24; //TODO 设置成符合下面变换的
    else if (FREQUENCY == "D")
        shift_num = 1;
    auto next_date = arrow::shift_days_to_str(first_date, shift_num);
    ASSERT_EQ((++data_ptr)->date, next_date);

    auto last_date = (--iter_data->cend())->date;

    ASSERT_LE(last_date, arrow::shift_days_to_str(end, 0));
};

TEST_F(CSVReaderTest, CSV) {
    using namespace utils;
    SettingFunc::set_easy_context();

    CsvReader csv_reader("../data/", TICKER, TICKER);

    StockRecorder stock_recorder;
    auto test_iter_data = csv_reader.load(START, END, FREQUENCY);
    test_load(START, END, test_iter_data);
    MarketMaker market_maker;
    market_maker.initialize();
    ASSERT_EQ(TICKER, csv_reader.env->feeds[TICKER]->ticker);
};
