#include <iostream>
#include <gtest/gtest.h>
#include "matrix_calc.cpp"


TEST(MatrixCalcTest, FillValueConstructorTest) {
    double arr[4][2] = {{5, 5},
                       {5, 5},
                       {5, 5},
                       {5, 5}};
    Matrix<4, 2> true_mat(arr);

    Matrix<4, 2> filled_mat(5);
    EXPECT_EQ(true_mat, filled_mat);
}

TEST(MatrixCalcTest, RowVectorConstructorTest) {
    double arr[3][5] = {{1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}, {1, 2, 3, 4, 5}};
    Matrix<3, 5> true_mat(arr);

    double row_vector_arr[1][5] = {{1, 2, 3, 4, 5}};
    Vector<5> row_vector(row_vector_arr);
    Matrix<3, 5> mat_from_row(row_vector);
    EXPECT_EQ(true_mat, mat_from_row);
}

TEST(MatrixCalcTest, ColVectorConstructorTest) {
    double arr[3][5] = {{1, 1, 1, 1, 1},
                       {2, 2, 2, 2, 2},
                       {3, 3, 3, 3, 3}};
    Matrix<3, 5> true_mat(arr);

    double col_vector_arr[3][1] = {{1}, {2}, {3}};
    ColVector<3> col_vector(col_vector_arr);
    Matrix<3, 5> mat_from_col(col_vector);
    EXPECT_EQ(true_mat, mat_from_col);
}

TEST(MatrixCalcTest, SumTest) {
    double arr[4][8] = {{-154, -91, 26, -11, 87, -194, -69, -34},
                       {44, -33, -24, -75, -166, -106, 158, 73},
                       {-128, -68, -83, 103, -32, -8, 11, 9},
                       {134, -70, 111, 21, -4, 154, -91, -1}};
    Matrix<4, 8> true_mat(arr);

    double first_arr[4][8] = {
            {-81, -5, 86, 36, 18, -98, 21, -54},
            {-42, 61, 76, -98, -95, -89, 82, 90},
            {-87, -13, -22, 94, -36, -49, -32, -47},
            {64, 16, 95, -44, 47, 63, -10, 7}
    };
    Matrix<4, 8> first(first_arr);

    double second_arr[4][8] = {
            {-73, -86, -60, -47, 69, -96, -90, 20},
            {86, -94, -100, 23, -71, -17, 76, -17},
            {-41, -55, -61, 9, 4, 41, 43, 56},
            {70, -86, 16, 65, -51, 91, -81, -8}
    };
    Matrix<4, 8> second(second_arr);

    EXPECT_EQ(true_mat, first + second);
}

TEST(MatrixCalcTest, SubTest) {
    double arr[4][8] = {{-8, 81, 146, 83, -51, -2, 111, -74},
                       {-128, 155, 176, -121, -24, -72, 6, 107},
                       {-46, 42, 39, 85, -40, -90, -75, -103},
                       {-6, 102, 79, -109, 98, -28, 71, 15}};
    Matrix<4, 8> true_mat(arr);

    double first_arr[4][8] = {
            {-81, -5, 86, 36, 18, -98, 21, -54},
            {-42, 61, 76, -98, -95, -89, 82, 90},
            {-87, -13, -22, 94, -36, -49, -32, -47},
            {64, 16, 95, -44, 47, 63, -10, 7}
    };
    Matrix<4, 8> first(first_arr);

    double second_arr[4][8] = {
            {-73, -86, -60, -47, 69, -96, -90, 20},
            {86, -94, -100, 23, -71, -17, 76, -17},
            {-41, -55, -61, 9, 4, 41, 43, 56},
            {70, -86, 16, 65, -51, 91, -81, -8}
    };
    Matrix<4, 8> second(second_arr);

    EXPECT_EQ(true_mat, first - second);
}

TEST(MatrixCalcTest, MulTest) {
    double arr[4][8] = {{5913, 430, -5160, -1692, 1242, 9408, -1890, -1080},
                       {-3612, -5734, -7600, -2254, 6745, 1513, 6232, -1530},
                       {3567, 715, 1342, 846, -144, -2009, -1376, -2632},
                       {4480, -1376, 1520, -2860, -2397, 5733, 810, -56}};
    Matrix<4, 8> true_mat(arr);

    double first_arr[4][8] = {
            {-81, -5, 86, 36, 18, -98, 21, -54},
            {-42, 61, 76, -98, -95, -89, 82, 90},
            {-87, -13, -22, 94, -36, -49, -32, -47},
            {64, 16, 95, -44, 47, 63, -10, 7}
    };
    Matrix<4, 8> first(first_arr);

    double second_arr[4][8] = {
            {-73, -86, -60, -47, 69, -96, -90, 20},
            {86, -94, -100, 23, -71, -17, 76, -17},
            {-41, -55, -61, 9, 4, 41, 43, 56},
            {70, -86, 16, 65, -51, 91, -81, -8}
    };
    Matrix<4, 8> second(second_arr);

    EXPECT_EQ(true_mat, first * second);
}

TEST(MatrixCalcTest, MulScalarTest) {
    double arr[4][8] = {{-1352, -2366, -2418, -1586, -1014, -1742, -2366, -780},
                       {-1326, 1742, 260, 2418, -1768, 858, -156, 416},
                       {1274, 546, 286, 2210, 1118, -1508, 208, -208},
                       {-1846, -1456, -1534, 2522, 520, -2132, -1196, -1456}};
    Matrix<4, 8> true_mat(arr);

    double first_arr[4][8] = {{-52, -91, -93, -61, -39, -67, -91, -30},
                             {-51, 67, 10, 93, -68, 33, -6, 16},
                             {49, 21, 11, 85, 43, -58, 8, -8},
                             {-71, -56, -59, 97, 20, -82, -46, -56}};
    Matrix<4, 8> first(first_arr);

    EXPECT_EQ(true_mat, first * 26.);
    EXPECT_EQ(true_mat, 26. * first);
}

TEST(MatrixCalcTest, SliceTest) {
    double arr[4][2] = {{13, -53},
                       {-97, -16},
                       {-11, -62},
                       {98, 79}};
    Matrix<4, 2> true_mat(arr);

    double first_arr[8][6] = {{22, -88, 7, -57, -93, -73},
                             {40, -74, 9, -38, 13, -53},
                             {66, 65, -28, -11, -97, -16},
                             {-37, 63, 6, 43, -11, -62},
                             {89, -66, -88, -16, 98, 79},
                             {-65, 53, -58, 71, 34, 61},
                             {-90, -98, -53, -80, 32, -71},
                             {-88, -86, 47, 97, 28, 46}};
    Matrix<8, 6> first(first_arr);

    Matrix<4, 2> ans = first.Slice<1, 5, 4, 6>();
    EXPECT_EQ(true_mat, ans);
}

TEST(MatrixCalcTest, DiagonalTest) {
    double arr[1][5] = {{-14, 32, 66, -32, 2}};
    Matrix<1, 5> true_mat(arr);

    double first_arr[5][8] = {{-14, 93, 35, -71, -71, -58, -22, 31},
                             {13, 32, -14, -92, 32, 53, -52, 33},
                             {-7, 45, 66, 47, 56, -10, 48, -76},
                             {99, -21, 61, -32, 48, -22, -9, 39},
                             {-54, 83, 5, -17, 2, -12, 47, 42}};
    Matrix<5, 8> first(first_arr);

    EXPECT_EQ(true_mat, first.Diagonal());
}

TEST(MatrixCalcTest, TransposeTest) {
    double arr[8][3] = {{-74, -19, -71},
                       {-5, 58, -59},
                       {-21, -98, -24},
                       {51, -9, -61},
                       {89, 63, -26},
                       {73, -75, -84},
                       {-47, 5, 19},
                       {-42, 48, 1}};
    Matrix<8, 3> true_mat(arr);

    double first_arr[3][8] = {{-74, -5, -21, 51, 89, 73, -47, -42},
                             {-19, 58, -98, -9, 63, -75, 5, 48},
                             {-71, -59, -24, -61, -26, -84, 19, 1}};
    Matrix<3, 8> first(first_arr);

    EXPECT_EQ(true_mat, first.Transpose());
}

TEST(MatrixCalcTest, DotTest) {
    double arr[3][2] = {{4449, 6699},
                       {-9581, -515},
                       {4733, -1289}};
    Matrix<3, 2> true_mat(arr);

    double first_arr[3][5] = {{-47, 77, -13, 51, 63},
                             {-25, 49, 47, 53, -77},
                             {-64, -47, 68, -39, -34}};
    Matrix<3, 5> first(first_arr);

    double second_arr[5][2] = {{-93, 6},
                              {-27, 90},
                              {-33, 45},
                              {-60, -53},
                              {76, 53}};
    Matrix<5, 2> second(second_arr);

    EXPECT_EQ(true_mat, (first, second));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}