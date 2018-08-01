#include "../src/OnePy.h"
#include <gtest/gtest.h>

class OnePySunnyTest : public ::testing::Test {
  public:
    OnePiece go;
};

TEST_F(OnePySunnyTest, ggg) {
    ASSERT_EQ(1, 1);
};
