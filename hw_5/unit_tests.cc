#include "utilities.h"
#include <gtest/gtest.h>
#include <cmath>
#include <fstream>
#include <map>
#include <string>

namespace {
    TEST(SortByMagnitudeTest, SortsCorrectly) {
        vector<double> vec = {3.0, -1.0, -2.0, 1.5};
        sort_by_magnitude(vec);
        EXPECT_DOUBLE_EQ(vec[0], -1.0);
        EXPECT_DOUBLE_EQ(vec[1], 1.5);
        EXPECT_DOUBLE_EQ(vec[2], -2.0);
        EXPECT_DOUBLE_EQ(vec[3], 3.0);
    }

    TEST(UtilitiesTest, ReadMatrixCsv) {
        const string path = "myfile.csv";
        TypedArray<TypedArray<double>> expected_matrix;

        TypedArray<double> row1;
        row1.set(0, 1.0);
        row1.set(1, 2.0);
        row1.set(2, 3.0);
        expected_matrix.set(0, row1);

        TypedArray<double> row2;
        row2.set(0, 2.7);
        row2.set(1, 3.8);
        row2.set(2, 5.3);
        expected_matrix.set(1, row2);

        TypedArray<double> row3;
        row3.set(0, 3.5);
        row3.set(1, 7.7);
        row3.set(2, 8.1);
        expected_matrix.set(2, row3);


        TypedArray<TypedArray<double>> actual_matrix = read_matrix_csv(path);
        ASSERT_EQ(expected_matrix.size(), actual_matrix.size());
        for (int i = 0; i < expected_matrix.size(); ++i) {
            ASSERT_EQ(expected_matrix.get(i).size(), actual_matrix.get(i).size());
            for (int j = 0; j < expected_matrix.get(i).size(); ++j) {
                ASSERT_DOUBLE_EQ(expected_matrix.get(i).get(j), actual_matrix.get(i).get(j));
            }
        }
    }

    TEST(UtilitiesTest, WriteMatrixCsv) {
        const string path = "test.csv";
        TypedArray<TypedArray<double>> matrix;

        for (int i = 0; i < 3; ++i) {
            TypedArray<double> row;
            for (int j = 0; j < 3; ++j) {
                row.set(j, i * 3.0 + j);
            }
            matrix.set(i, row);
        }

        write_matrix_csv(matrix, path);

        ifstream file(path);
        ASSERT_TRUE(file.is_open());

        for (int i = 0; i < matrix.size(); ++i) {
            string line;
            ASSERT_TRUE(getline(file, line));

            stringstream ss(line);
            for (int j = 0; j < matrix.get(i).size(); ++j) {
                string field;
                ASSERT_TRUE(getline(ss, field, ','));

                double value = stod(field);
                ASSERT_DOUBLE_EQ(matrix.get(i).get(j), value);
            }
        }

        file.close();
    }

    TEST(UtilitiesTest, OccurrenceMapTest_Sentence) {
        const string path = "ascii.txt";  // Make sure this file contains the sentence
        map<string, int> result = occurrence_map(path);
        EXPECT_EQ(result["this"], 1);
        EXPECT_EQ(result["is"], 2);
        EXPECT_EQ(result["sentence"], 1);
        EXPECT_EQ(result["don't"], 1);
        EXPECT_EQ(result["think"], 1);
        EXPECT_EQ(result["of"], 1);
        EXPECT_EQ(result["strings"], 1);
        EXPECT_EQ(result["as"], 1);
        EXPECT_EQ(result["words"], 1);
        EXPECT_EQ(result["really"], 1);
        EXPECT_EQ(result["123"], 1);
        EXPECT_EQ(result["a"], 2);
        EXPECT_EQ(result["nice"], 1);
        EXPECT_EQ(result["number"], 1);
        EXPECT_EQ(result.count("wier_d"), 0);  // "wier_d" is not a valid word
    }


}
