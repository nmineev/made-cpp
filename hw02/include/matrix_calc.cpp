#include <iostream>
#include <algorithm>
#include <cstddef>
#include <iterator>


template <size_t N, size_t M, typename T = double>
class Matrix {
public:
    static const size_t num_rows_ = N;
    static const size_t num_cols_ = M;

    Matrix(T value) {
        std::for_each_n(array_, N, [value](T* row){ std::fill_n(row, M, value); });
    }

    Matrix(T other_array[N][M]) {
        std::copy(std::make_move_iterator(*other_array),
                  std::make_move_iterator(*other_array + N * M),
                  *array_);
    }

    Matrix(const Matrix<1, M, T>& row_vector) {
        for (size_t row_ind = 0; row_ind < N; ++row_ind)
            for (size_t col_ind = 0; col_ind < M; ++col_ind)
                array_[row_ind][col_ind] = row_vector[0][col_ind];
    }

    Matrix(const Matrix<N, 1, T>& col_vector) {
        for (size_t row_ind = 0; row_ind < N; ++row_ind)
            for (size_t col_ind = 0; col_ind < M; ++col_ind)
                array_[row_ind][col_ind] = col_vector[row_ind][0];
    }


    Matrix<N, M, T>& operator+=(const Matrix<N, M, T>& other) {
        for (size_t row_ind = 0; row_ind < N; ++row_ind)
            for (size_t col_ind = 0; col_ind < M; ++col_ind)
                array_[row_ind][col_ind] += other.array_[row_ind][col_ind];
        return *this;
    }

    Matrix<N, M, T>& operator-=(const Matrix<N, M, T>& other) {
        for (size_t row_ind = 0; row_ind < N; ++row_ind)
            for (size_t col_ind = 0; col_ind < M; ++col_ind)
                array_[row_ind][col_ind] -= other.array_[row_ind][col_ind];
        return *this;
    }

    Matrix<N, M, T>& operator*=(const Matrix<N, M, T>& other) {
        for (size_t row_ind = 0; row_ind < N; ++row_ind)
            for (size_t col_ind = 0; col_ind < M; ++col_ind)
                array_[row_ind][col_ind] *= other.array_[row_ind][col_ind];
        return *this;
    }

    Matrix<N, M, T>& operator*=(T scalar) {
        for (size_t row_ind = 0; row_ind < N; ++row_ind)
            for (size_t col_ind = 0; col_ind < M; ++col_ind)
                array_[row_ind][col_ind] *= scalar;
        return *this;
    }


    T* operator[](size_t row_ind) {
        return array_[row_ind];
    }

    const T* operator[](size_t row_ind) const {
        return array_[row_ind];
    }

    template <size_t ROW_IND_FIRST, size_t ROW_IND_LAST,
            size_t COL_IND_FIRST, size_t COL_IND_LAST>
    Matrix<ROW_IND_LAST - ROW_IND_FIRST,
            COL_IND_LAST - COL_IND_FIRST,
            T> Slice() const {
        T new_array[ROW_IND_LAST - ROW_IND_FIRST][COL_IND_LAST - COL_IND_FIRST];
        for (size_t row_ind = ROW_IND_FIRST; row_ind < ROW_IND_LAST; ++row_ind)
            for (size_t col_ind = COL_IND_FIRST; col_ind < COL_IND_LAST; ++col_ind)
                new_array[row_ind - ROW_IND_FIRST][col_ind - COL_IND_FIRST] =\
                array_[row_ind][col_ind];
        return new_array;
    }

    Matrix<1, std::min(N, M), T> Diagonal() const {
        size_t n_m_min = std::min(N, M);
        T row_vector[1][std::min(N, M)];
        for (size_t ind = 0; ind < n_m_min; ++ind)
            row_vector[0][ind] = array_[ind][ind];
        return row_vector;
    }


    Matrix<M, N, T> Transpose() const {
        T new_array[M][N];
        for (size_t row_ind = 0; row_ind < N; ++row_ind)
            for (size_t col_ind = 0; col_ind <M; ++col_ind)
                new_array[col_ind][row_ind] = array_[row_ind][col_ind];
        return new_array;
    }

    template <size_t X, size_t Y, typename U>
    friend std::ostream& operator<<(std::ostream& out, const Matrix<X, Y, U>& mat);
private:
    T array_[N][M];
};


template <size_t N, typename T>
class Matrix<N, N, T> {
    Matrix<N, N, T> Inverse() const {}
    T Determinant() const {}
};


template <size_t N, typename T = double>
using Vector = Matrix<1, N, T>;

template <size_t N, typename T = double>
using ColVector = Matrix<N, 1, T>;


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

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(const Matrix<N, M, T>& first, T second) {
    Matrix<N, M, T> copy = first;
    copy *= second;
    return copy;
}

template <size_t N, size_t M, typename T>
Matrix<N, M, T> operator*(T first, const Matrix<N, M, T> second) {
    return second * first;
}

template <size_t N, size_t M, size_t X, typename T>
Matrix<X, M, T> operator,(const Matrix<X, N, T>& first, const Matrix<N, M, T>& second) {
    Matrix<X, M, T> result(T(0.));
    for (size_t row_ind_first = 0; row_ind_first < X; ++row_ind_first)
        for (size_t col_ind_second = 0; col_ind_second < M; ++col_ind_second)
            for (size_t ind = 0; ind < N; ++ind)
                result[row_ind_first][col_ind_second] +=\
                first[row_ind_first][ind] * second[ind][col_ind_second];
    return result;
};

template <size_t N, size_t M, typename T, size_t X, size_t Y, typename U>
bool operator==(const Matrix<N, M, T>& first, const Matrix<X, Y, U>& second) {
    if (N != X || M != Y || !std::is_same_v<T, U>)
        return false;
    for (size_t row_ind = 0; row_ind < N; ++row_ind) {
        for (size_t col_ind = 0; col_ind < M; ++col_ind) {
            if (first[row_ind][col_ind] != second[row_ind][col_ind])
                return false;
        }
    }
    return true;
}

template <size_t N, size_t M, typename T, size_t X, size_t Y, typename U>
bool operator!=(const Matrix<N, M, T>& first, const Matrix<X, Y, U>& second) {
    return !(first == second);
}

template <size_t N, size_t M, typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<N, M, T>& mat) {
    std::cout << '{' << '\n';
    for (size_t row_col = 0; row_col < N; ++row_col) {
        std::cout << '{';
        std::copy(mat.array_[row_col], mat.array_[row_col] + M, std::ostream_iterator<T>(out, ", "));
        std::cout << '}' << '\n';
    }
    std::cout << '}' << '\n';
    return out;
}
