#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Examples,Complex) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Examples,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

    TEST(TypedArray, PushPopTest) {
        TypedArray<int> arr;

        // Test push
        arr.push(5);
        EXPECT_EQ(arr.size(), 1);
        EXPECT_EQ(arr.get(arr.size() - 1), 5);

        // Test pop
        int popped = arr.pop();
        EXPECT_EQ(popped, 5);
        EXPECT_EQ(arr.size(), 0);

        // Test pop on empty array
        EXPECT_THROW(arr.pop(), std::range_error);
    }

    TEST(TypedArray, PushFrontPopFrontTest) {
        TypedArray<int> arr;

        // Test push_front
        arr.push(10);
        arr.push_front(5);
        EXPECT_EQ(arr.size(), 2);
        EXPECT_EQ(arr.get(0), 5);

        // Test pop_front
        int popped = arr.pop_front();
        EXPECT_EQ(popped, 5);
        EXPECT_EQ(arr.size(), 1);
        EXPECT_EQ(arr.get(0), 10);

        popped = arr.pop_front();
        EXPECT_EQ(popped, 10);
        EXPECT_EQ(arr.size(), 0);

        // Test pop_front on empty array
        EXPECT_THROW(arr.pop_front(), std::range_error);
    }

    TEST(TypedArray, ConcatTest) {
        TypedArray<int> a;
        a.set(0, 0);
        a.set(1, 1);

        TypedArray<int> b = a.concat(a).concat(a);

        // Check that b contains [0,1,0,1,0,1]
        EXPECT_EQ(b.size(), 6);
        EXPECT_EQ(b.get(0), 0);
        EXPECT_EQ(b.get(1), 1);
        EXPECT_EQ(b.get(2), 0);
        EXPECT_EQ(b.get(3), 1);
        EXPECT_EQ(b.get(4), 0);
        EXPECT_EQ(b.get(5), 1);

        // Check that a is unchanged
        EXPECT_EQ(a.size(), 2);
        EXPECT_EQ(a.get(0), 0);
        EXPECT_EQ(a.get(1), 1);
    }

    TEST(TypedArray, ReverseTest) {
        TypedArray<int> a;
        for (int i = 0; i < 5; i++) {
            a.set(i, i);
        }

        a.reverse();

        // Check that a contains [4,3,2,1,0]
        EXPECT_EQ(a.size(), 5);
        EXPECT_EQ(a.get(0), 4);
        EXPECT_EQ(a.get(1), 3);
        EXPECT_EQ(a.get(2), 2);
        EXPECT_EQ(a.get(3), 1);
        EXPECT_EQ(a.get(4), 0);
    }

    TEST(TypedArray, PlusOperatorTest) {
        TypedArray<int> a;
        a.set(0, 0);
        a.set(1, 1);

        TypedArray<int> b = a + a + a;

        // Check that b contains [0,1,0,1,0,1]
        EXPECT_EQ(b.size(), 6);
        EXPECT_EQ(b.get(0), 0);
        EXPECT_EQ(b.get(1), 1);
        EXPECT_EQ(b.get(2), 0);
        EXPECT_EQ(b.get(3), 1);
        EXPECT_EQ(b.get(4), 0);
        EXPECT_EQ(b.get(5), 1);

        // Check that a is unchanged
        EXPECT_EQ(a.size(), 2);
        EXPECT_EQ(a.get(0), 0);
        EXPECT_EQ(a.get(1), 1);
    }

    TEST(ComplexTest, BasicOperations) {
        Complex a(3, 4);
        Complex b(1, 2);

        EXPECT_EQ(a.re(), 3);
        EXPECT_EQ(a.im(), 4);
        EXPECT_EQ(a.conjugate(), Complex(3, -4));
        EXPECT_EQ(a + b, Complex(4, 6));
        EXPECT_EQ(a * b, Complex(-5, 10));
        EXPECT_EQ(a, Complex(3, 4));
    }
}