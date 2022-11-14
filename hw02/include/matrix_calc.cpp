#include "matrix_calc.h"
#include <algorithm>

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(T value) {
    std::for_each_n(array_, N, [value](T* row){ std::fill_n(row, M, value); });
}

//template <size_t N, size_t M, typename T>
//Matrix<N, M, T>::Matrix(const Matrix<N, M, T>& other) {
//    array_ = other.array_;
//}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const Matrix<1, M, T>& row_vector) {
    std::for_each_n(array_, N,
                    [&row_vector](T* row){ std::copy_n(*row_vector.array_, M, row); });
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>::Matrix(const Matrix<N, 1, T>& col_vector) {
    for (uint row_ind = 0; row_ind < N; ++row_ind)
        for (uint col_ind = 0; col_ind < M; ++col_ind)
            array_[row_ind][col_ind] = col_vector.array_[0][row_ind];
}

//template <size_t N, size_t M, typename T>
//Matrix<N, M, T>::Matrix(T** array, size_t num_rows, size_t num_cols) {
//    Matrix<N, M, T> new_matrix = {array, num_rows, num_cols};
//}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator+=(const Matrix<N, M, T>& other) {
    for (uint row_ind = 0; row_ind < N; ++row_ind)
        for (uint col_ind = 0; col_ind < M; ++col_ind)
            array_[row_ind][col_ind] += other.array_[row_ind][col_ind];
    return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator-=(const Matrix<N, M, T>& other) {
    for (uint row_ind = 0; row_ind < N; ++row_ind)
        for (uint col_ind = 0; col_ind < M; ++col_ind)
            array_[row_ind][col_ind] -= other.array_[row_ind][col_ind];
    return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T>& Matrix<N, M, T>::operator*=(const Matrix<N, M, T>& other) {
    for (uint row_ind = 0; row_ind < N; ++row_ind)
        for (uint col_ind = 0; col_ind < M; ++col_ind)
            array_[row_ind][col_ind] *= other.array_[row_ind][col_ind];
    return *this;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator+(const Matrix<N, M, T>& first, const Matrix<N, M, T>& second) {
    Matrix<N, M, T> copy = first;
    copy += second;
    return copy;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator-(const Matrix<N, M, T>& first, const Matrix<N, M, T>& second) {
    Matrix<N, M, T> copy = first;
    copy -= second;
    return copy;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& first, const Matrix<N, M, T>& second) {
    Matrix<N, M, T> copy = first;
    copy *= second;
    return copy;
}

template <size_t N, size_t M, size_t X, typename T>
Matrix<X, M, T> operator,(const Matrix<X, N, T>& first, const Matrix<N, M, T>& second) {
    Matrix<X, N, T> result = first;
    for (uint row_ind_first = 0; row_ind_first < X; ++row_ind_first)
        for (uint col_ind_second = 0; col_ind_second < M; ++col_ind_second)
            for (uint ind = 0; ind < N; ++ind)
                result = first[row_ind_first][ind] * second[ind][col_ind_second];
    return result;
};

//template <size_t N, size_t M, typename T>
//template <size_t X, size_t Y>
//Matrix<X, Y, T> Matrix<N, M, T>::operator()(int row_ind, int col_ind) {
//    if (row_ind < 0) {
//
//    } else if (col_ind < 0) {
//        T col_vector[row_ind][1];
//        for (uint row_ind = 0; row_ind < N; ++row_ind)
//            col_vector[row_ind][0] = array_[row_ind][row_ind];
//        return
//    }
//    return array_[row_ind][col_ind];
//}

template <size_t N, size_t M, typename T>
T* Matrix<N, M, T>::operator[](size_t row_ind) {
    return array_[row_ind];
}

template <size_t N, size_t M, typename T>
template <size_t ROW_IND_FIRST, size_t ROW_IND_LAST,
        size_t COL_IND_FIRST, size_t COL_IND_LAST>
Matrix<ROW_IND_LAST - ROW_IND_FIRST,
       COL_IND_LAST - COL_IND_FIRST,
       T> Matrix<N, M, T>::Slice() {
    size_t new_num_rows = ROW_IND_LAST - ROW_IND_FIRST;
    size_t new_num_cols = COL_IND_LAST - COL_IND_FIRST;
    T new_array[new_num_rows][new_num_cols];
    for (uint row_ind = ROW_IND_FIRST; row_ind < ROW_IND_LAST; ++row_ind)
        for (uint col_ind = COL_IND_FIRST; col_ind < COL_IND_LAST; ++col_ind)
            new_array[row_ind][col_ind] = array_[row_ind][col_ind];
    return {new_array, new_num_rows, new_num_cols};
}

//template <size_t N, size_t M, typename T>
//template <size_t X, size_t Y>
//Matrix<X, Y, T> Matrix<N, M, T>::operator()(int row_ind_first, int row_ind_last,
//                                            int col_ind_first, int col_ind_last) {
//    size_t new_num_rows = row_ind_last - row_ind_first;
//    size_t new_num_cols = col_ind_last - col_ind_first;
//    T new_array[new_num_rows][new_num_cols];
//    for (uint row_ind = row_ind_first; row_ind < row_ind_last; ++row_ind)
//        for (uint col_ind = col_ind_first; col_ind < col_ind_last; ++col_ind)
//            new_array[row_ind][col_ind] = array_[row_ind][col_ind];
//    return {new_array, new_num_rows, new_num_cols};
//}

template <size_t N, size_t M, typename T>
template <size_t N_M_MIN>
Matrix<1, N_M_MIN, T> Matrix<N, M, T>::Diagonal() {
    T row_vector[1][N_M_MIN];
    for (uint ind = 0; ind < N_M_MIN; ++ind)
        row_vector[0][ind] = array_[ind][ind];
    return {row_vector, 1, N_M_MIN};
}

template <size_t N, size_t M, typename T>
Matrix<M, N, T> Matrix<N, M, T>::Transpose() {
    T new_array[M][N];
    for (uint row_ind = 0; row_ind < N; ++row_ind)
        for (uint col_ind = 0; col_ind <M; ++col_ind)
            std::swap(new_array[col_ind][row_ind], array_[row_ind][col_ind]);
    array_ = new_array;
    return {array_, M, N};
}

template <size_t N, typename T>
Matrix<N, N, T> Matrix<N, N, T>::Inverse() {}

template <size_t N, typename T>
T Matrix<N, N, T>::Determinant() {}
