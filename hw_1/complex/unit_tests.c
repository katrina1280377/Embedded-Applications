#include "complex.h"
#include "gtest/gtest.h"

namespace {

  TEST(ComplexTest, Add) {
    Complex a = {1.0, 2.0};
    Complex b = {3.0, 4.0};
    Complex result = add(a, b);
    EXPECT_DOUBLE_EQ(result.real, 4.0);
    EXPECT_DOUBLE_EQ(result.im, 6.0);
  }

  TEST(ComplexTest, Negate) {
    Complex a = {1.0, 2.0};
    Complex result = negate(a);
    EXPECT_DOUBLE_EQ(result.real, -1.0);
    EXPECT_DOUBLE_EQ(result.im, -2.0);
  }

  TEST(ComplexTest, Multiply) {
    Complex a = {1.0, 2.0};
    Complex b = {3.0, 4.0};
    Complex result = multiply(a, b);
    EXPECT_DOUBLE_EQ(result.real, -5.0);
    EXPECT_DOUBLE_EQ(result.im, 10.0);
  }

  TEST(ComplexTest, Magnitude) {
    Complex a = {3.0, 4.0};
    double result = magnitude(a);
    EXPECT_DOUBLE_EQ(result, 5.0);
  }

}  // namespace