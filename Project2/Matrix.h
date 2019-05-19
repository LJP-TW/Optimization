#pragma once
#include <iostream>
#include <vector>
#include "Vector.h"

// �۩w�q�� Matrix
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

// �w�q�������~
enum class MATRIX_ERROR {
    DIMENSION_NON_EQUIVALENT, // A �P B ���פ��P
    EIGEN_DIMENSION_ERROR, // �ثe eigen() �u�䴩 2x2 �� 3x3 Matrix
    MULTIPLICATION_DIMENSION_ERROR, // A �P B ���వ���k
    NON_DIAGONALIZABLE, // Matrix ���O diagonalizable matrix
    NON_SQUARE, // Matrix ���O square matrix
    ROW_DIMENSION_NON_EQUIVALENT, // A �P B Row �����פ��P
    SINGULAR // Matrix �O singular matrix
};