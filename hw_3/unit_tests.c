#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }

    // TEST CASES FOR HOMEWORK 3 START HERE
    TEST(DynamicArray, Basic) {
        // Part 1 - Mathematical operations
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 5.0);
        DynamicArray_push(da, 6.0);
        DynamicArray_push(da, 2.0);
        DynamicArray_push(da, 7.0);
        DynamicArray_push(da, 3.0);
        printf("Array: %s\n", DynamicArray_to_string(da));
        printf("Min value = %f\n", DynamicArray_min(da));
        ASSERT_EQ(2.0, DynamicArray_min(da));
        printf("Max value = %f\n", DynamicArray_max(da));
        ASSERT_EQ(7.0, DynamicArray_max(da));
        printf("Average value = %f\n", DynamicArray_mean(da));
        ASSERT_EQ(4.6, DynamicArray_mean(da));
        printf("[Test Case 1] Median value = %f\n", DynamicArray_median(da));
        ASSERT_EQ(5.0, DynamicArray_median(da));
        printf("Adding 8.0 to array... \n");
        DynamicArray_push(da, 8.0);
        printf("Array: %s\n", DynamicArray_to_string(da));
        printf("[Test Case 2] Median value = %f\n", DynamicArray_median(da));
        ASSERT_EQ(5.5, DynamicArray_median(da));
        printf("Sum = %f\n", DynamicArray_sum(da));
        ASSERT_EQ(31.0, DynamicArray_sum(da));
        // Part 2  - Write the methods _last and _first return the value at the end 
        // or beginning of the array respectively.
        printf("First value = %f\n", DynamicArray_first(da));
        ASSERT_EQ(5.0, DynamicArray_first(da));
        printf("Last value = %f\n", DynamicArray_last(da));
        ASSERT_EQ(8.0, DynamicArray_last(da));
        // Part 3 - Write a _copy method that produces a copy of an array.
        DynamicArray * copy = DynamicArray_copy(da);
        printf("Copy array: %s\n", DynamicArray_to_string(da));
        ASSERT_EQ(DynamicArray_size(da), DynamicArray_size(copy));
        for (int i = 0; i < DynamicArray_size(da); i++) {
          ASSERT_EQ(DynamicArray_get(da, i), DynamicArray_get(copy, i));
        }
        DynamicArray_destroy(copy);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, Range) {
        // Part 4- Write a method called _range that creates a new dynamic array with values as follows
        printf("Creating array range from 0 to 1... \n");
        DynamicArray * range = DynamicArray_range(0, 1, 0.1);
        printf("The range array: %s\n", DynamicArray_to_string(range));
        double epsilon = 0.00001;  // or whatever small value you consider "close enough"
        for (int i = 0; i < DynamicArray_size(range); i++) {
            ASSERT_TRUE(fabs(DynamicArray_get(range, i) - (i * 0.1)) < epsilon);
        }
        DynamicArray_destroy(range);
    }

    TEST(DynamicArray, Concat) {
        // Part 5- Implement the method _concat, which concatenates two arrays to produce a new array.
        printf("Creating array A range from 0 to 1... \n");
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        printf("Array A %s\n", DynamicArray_to_string(a));
        printf("Creating array B range from 1.1 to 2... \n");
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        printf("Array B: %s\n", DynamicArray_to_string(b));
        printf("Concatenating  array C range from A & B... \n");
        DynamicArray * c = DynamicArray_concat(a, b); /* yeilds [ 0, 0.1, ..., 2.0 ] */
        printf("Array C: %s\n", DynamicArray_to_string(c));
        ASSERT_EQ(21, DynamicArray_size(c));
        double epsilon = 0.00001;  // or whatever small value you consider "close enough"
        for (int i = 0; i < DynamicArray_size(c); i++) {
            ASSERT_TRUE(fabs(DynamicArray_get(c, i) - i * 0.1) < epsilon);
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
    }

    TEST(DynamicArray, Take) {
        DynamicArray * a = DynamicArray_range(1, 5, 1);
        DynamicArray * b = DynamicArray_take(a, 2);
        DynamicArray * c = DynamicArray_take(a, -2);
        DynamicArray * d = DynamicArray_take(a, 7);
        printf("Creating array A range from 1 to 5... \n");
        printf("Array A %s\n", DynamicArray_to_string(a));
        printf("Take(a, 2): %s\n", DynamicArray_to_string(b));
        printf("Take(a, -2): %s\n", DynamicArray_to_string(c));
        printf("Take(a, 1): %s\n", DynamicArray_to_string(d));
        ASSERT_EQ(2, DynamicArray_size(b));
        ASSERT_EQ(2, DynamicArray_size(c));
        ASSERT_EQ(7, DynamicArray_size(d));
        for (int i = 0; i < 2; i++) {
             ASSERT_EQ(1+i, DynamicArray_get(b, i));
        }
        for (int i = 0; i < 2; i++) {
             ASSERT_EQ(4+i, DynamicArray_get(c, i));
        }
        for (int i = 0; i < 5; i++) {
            if(i < 5) ASSERT_EQ(1+i, DynamicArray_get(d, i));
            else ASSERT_EQ(0, DynamicArray_get(d, i));
        }
        DynamicArray_destroy(a);
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
        DynamicArray_destroy(d);
    }

    TEST(DynamicArray, Extra) {
        printf("Creating array A range from 0 to 1... \n");
        DynamicArray * a = DynamicArray_range(0, 1, 0.1);
        printf("Array A %s\n", DynamicArray_to_string(a));
        printf("Creating array B range from 1.1 to 2... \n");
        DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
        printf("Array B: %s\n", DynamicArray_to_string(b));
        printf("Concatenating  array C range from A & B... \n");
        DynamicArray * c = DynamicArray_concat(a, b);
        printf("Array C: %s\n", DynamicArray_to_string(c));
        ASSERT_EQ(DynamicArray_is_valid(a), 1);
        ASSERT_EQ(DynamicArray_num_arrays(), 3);
        DynamicArray_destroy_all();
        ASSERT_EQ(DynamicArray_is_valid(a), 0);
        ASSERT_EQ(DynamicArray_num_arrays(), 0);
        free(a);
        free(b);
        free(c);
    }

}