#include "Constants.h"
#include "EventEngine.h"
#include <gtest/gtest.h>

using namespace op;

class EventEngineTest : public ::testing::Test {
  public:
    op::EventEngine engine;
};

TEST_F(EventEngineTest, put_and_get) {
    engine.put(EVENT::Data_cleaned);
    const int before_length = engine.size();
    EVENT result = engine.get();
    const int after_length = engine.size();

    ASSERT_EQ(before_length, 1);
    ASSERT_EQ(result, EVENT::Data_cleaned);
    ASSERT_EQ(after_length, 0);
};
