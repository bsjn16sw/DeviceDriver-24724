#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
  EXPECT_THAT(1, 1);
}