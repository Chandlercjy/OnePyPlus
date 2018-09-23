#include "OnePiece.h"
#include <gtest/gtest.h>

using namespace op;

class OnePySunnyTest : public ::testing::Test {
  public:
    OnePiece go;
};

TEST_F(OnePySunnyTest, ggg) {
    ASSERT_EQ(1, 1);
};
