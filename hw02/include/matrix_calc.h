#include <cstddef>

template <size_t N, size_t M, typename T = float>
class Matrix {
public:
    Matrix(T);
//    Matrix(const Matrix<N, M, T>&);
    Matrix(const Matrix<1, M, T>&);
    Matrix(const Matrix<N, 1, T>&);

    Matrix<N, M, T>& operator+=(const Matrix<N, M, T>&);
    Matrix<N, M, T>& operator-=(const Matrix<N, M, T>&);
    Matrix<N, M, T>& operator*=(const Matrix<N, M, T>&);

//    template <size_t X, size_t Y>
//    Matrix<X, Y, T> operator()(int row_ind, int col_ind);

    T* operator[](size_t row_ind);

    template <size_t ROW_IND_FIRST, size_t ROW_IND_LAST,
              size_t COL_IND_FIRST, size_t COL_IND_LAST>
    Matrix<ROW_IND_LAST - ROW_IND_FIRST,
           COL_IND_LAST - COL_IND_FIRST,
           T> Slice();

    template <size_t N_M_MIN>
    Matrix<1, N_M_MIN, T> Diagonal();

    Matrix<M, N, T> Transpose();

private:
    static const size_t num_rows_ = N;
    static const size_t num_cols_ = M;
    T array_[N][M];

//    Matrix(T**, size_t num_rows, size_t num_cols);
};

template <size_t N, typename T>
class Matrix<N, N, T> {
    Matrix<N, N, T> Inverse();
    T Determinant();
};

template <size_t N, typename T>
using Vector = Matrix<1, N, T>;


template <size_t N, size_t M, size_t X, typename T>
Matrix<X, M, T> operator+(const Matrix<X, N, T>&, const Matrix<N, M, T>&);

template <size_t N, size_t M, size_t X, typename T>
Matrix<X, M, T> operator-(const Matrix<X, N, T>&, const Matrix<N, M, T>&);

template <size_t N, size_t M, size_t X, typename T>
Matrix<X, M, T> operator*(const Matrix<X, N, T>&, const Matrix<N, M, T>&);

template <size_t N, size_t M, size_t X, typename T>
Matrix<X, M, T> operator,(const Matrix<X, N, T>&, const Matrix<N, M, T>&);
