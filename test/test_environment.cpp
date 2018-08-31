#include "Environment.h"
#include <gtest/gtest.h>

using namespace sys;

class EnvironmentTest : public ::testing::Test {
  public:
    Environment *first = Environment::get_instance();
    Environment *second = Environment::get_instance();
};

TEST_F(EnvironmentTest, Singleton) {
    first->instrument = "Chandler is pretty cool!";
    ASSERT_EQ(second->instrument, first->instrument);
    ASSERT_EQ(second->instrument, "Chandler is pretty cool!");
};
