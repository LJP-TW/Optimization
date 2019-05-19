#pragma once
#include <iostream>
#include <vector>
#include "Vector.h"

// 自定義的 Matrix
class Matrix
{
public:
    Matrix();
    Matrix(Vector);

    std::string Name;
    std::vector<std::vector<double>> Data;

    std::string output();
    // set precision
    std::string output(int precision);

    // Negative sign
    Matrix operator -();

    /*
     * Return the result of A+B, which A is this matrix, B is m
     * might throw
     * - DIMENSION_NON_EQUIVALENT
     */
    Matrix operator +(const Matrix& m);

    /*
     * Return the result of A-B, which A is this matrix, B is m
     * might throw
     * - DIMENSION_NON_EQUIVALENT
     */
    Matrix operator -(const Matrix& m);

    /*
     * Return the result of A*B, which A is this matrix, B is m
     * might throw
     * - MULTIPLICATION_DIMENSION_ERROR
     */
    Matrix operator *(const Matrix& m);

    // Scalar
    Matrix operator *(double m);

    /*
     * Return the solution of Ax=B, which A is this matrix, B is m
     * might throw
     * - NON_SQUARE
     * - SINGULAR
     * - ROW_DIMENSION_NON_EQUIVALENT
     */
    Matrix solve(const Matrix& m);
    
    /*
     * Return transpose matrix of this matrix
     */
    Matrix trans() const;

    /*
     * Return determinant of this matrix
     * might throw
     * - NON_SQUARE
     */
    double det();

    /*
     * Return inverse of this matrix
     * will call
     * - solve()
     * might throw
     * - NON_SQUARE
     * - ROW_DIMENSION_NON_EQUIVALENT
     * - SINGULAR
     */
    Matrix inverse();
    
    /*
     * Return the best solution of Ax=B
     * might throw
     * - ROW_DIMENSION_NON_EQUIVALENT
     * - SINGULAR
     */
    friend Matrix leastsquare(const Matrix& A, const Matrix& B);

protected:
    /*
     * Change this matrix into r.e.f.
     */
    void ref(double threshold);
};

// 定義相關錯誤
enum class MATRIX_ERROR {
    DIMENSION_NON_EQUIVALENT, // A 與 B 維度不同
    EIGEN_DIMENSION_ERROR, // 目前 eigen() 只支援 2x2 或 3x3 Matrix
    MULTIPLICATION_DIMENSION_ERROR, // A 與 B 不能做乘法
    NON_DIAGONALIZABLE, // Matrix 不是 diagonalizable matrix
    NON_SQUARE, // Matrix 不是 square matrix
    ROW_DIMENSION_NON_EQUIVALENT, // A 與 B Row 的維度不同
    SINGULAR // Matrix 是 singular matrix
};