#include "../src/environment.h"
#include <gtest/gtest.h>

class EnvironmentTest : public ::testing::Test {
  public:
    Environment *first = Environment::getInstance();
    Environment *second = Environment::getInstance();
};

TEST_F(EnvironmentTest, Singleton) {
    first->instrument = "Chandler is pretty cool!";
    ASSERT_EQ(second->instrument, first->instrument);
    ASSERT_EQ(second->instrument, "Chandler is pretty cool!");
};
