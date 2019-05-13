#include "Matrix.h"

#ifdef _DEBUG
#include <iostream>
#endif

constexpr int THRESHOLD = 10E-12;

Matrix::Matrix()
{
}

Matrix::Matrix(Vector v)
{
    // Initial as column vector
    this->Data.push_back(v.Data);
    *this = this->trans();
}

Matrix Matrix::operator+(const Matrix & m)
{
    // 判斷是否可以相加
    // A(r1 x c1) * B(r2 x c2)
    // --> r1 必須等於 r2, c1 必須等於 c2
    if (this->Data.size() != m.Data.size() || this->Data[0].size() != m.Data[0].size())
    {
        throw MATRIX_ERROR::DIMENSION_NON_EQUIVALENT;
    }

    Matrix result = *this;

    for (unsigned int y = 0; y < result.Data.size(); ++y)
    {
        for (unsigned int x = 0; x < result.Data[y].size(); ++x)
        {
            result.Data[y][x] += m.Data[y][x];
        }
    }

    return result;
}

Matrix Matrix::operator-(const Matrix & m)
{
    // 判斷是否可以相減
    // A(r1 x c1) * B(r2 x c2)
    // --> r1 必須等於 r2, c1 必須等於 c2
    if (this->Data.size() != m.Data.size() || this->Data[0].size() != m.Data[0].size())
    {
        throw MATRIX_ERROR::DIMENSION_NON_EQUIVALENT;
    }

    Matrix result = *this;

    for (unsigned int y = 0; y < result.Data.size(); ++y)
    {
        for (unsigned int x = 0; x < result.Data[y].size(); ++x)
        {
            result.Data[y][x] -= m.Data[y][x];
        }
    }

    return result;
}

Matrix Matrix::operator*(const Matrix & m)
{
    // 判斷是否可以相乘
    // A(r1 x c1) * B(r2 x c2)
    // --> c1 必須等於 r2
    if (this->Data[0].size() != m.Data.size())
    {
        throw MATRIX_ERROR::DIMENSION_NON_EQUIVALENT;
    }

    Matrix result;

    for (unsigned int y = 0; y < this->Data.size(); ++y)
    {
        std::vector<double> rowVectorTemp;
        for (unsigned int x = 0; x < m.Data[0].size(); ++x)
        {
            double sumTemp = 0;
            for (unsigned int i = 0; i < this->Data[0].size(); ++i)
            {
                sumTemp += (this->Data[y][i] * m.Data[i][x]);
            }
            rowVectorTemp.push_back(sumTemp);
        }
        result.Data.push_back(rowVectorTemp);
    }

    return result;
}

Matrix Matrix::solve(const Matrix & m)
{
    // Solving Ax = B, A.rows must equal B.rows, A must be square matrix
    if (this->Data.size() != m.Data.size())
    {
        throw MATRIX_ERROR::ROW_DIMENSION_NON_EQUIVALENT;
    }
    else if (this->Data.size() != this->Data[0].size())
    {
        throw MATRIX_ERROR::NON_SQUARE;
    }

    Matrix A = *this;
    Matrix B = m;

    // Gaussian elimination to get r.e.f.
    for (unsigned int current = 0; current < A.Data[0].size(); ++current)
    {
        // Search for maximum in this column
        double maxNum = abs(A.Data[current][current]);
        unsigned int maxRow = current;
        for (unsigned int r = current + 1; r < A.Data.size(); ++r)
        {
            if (abs(A.Data[r][current]) > maxNum)
            {
                maxNum = abs(A.Data[r][current]);
                maxRow = r;
            }
        }

        if (!maxNum)
            throw MATRIX_ERROR::SINGULAR;

        // Swap maxRow to current row
        for (unsigned int c = current; c < A.Data[0].size(); ++c)
        {
            double temp = A.Data[current][c];
            A.Data[current][c] = A.Data[maxRow][c];
            A.Data[maxRow][c] = temp;
        }
        for (unsigned int c = 0; c < B.Data[0].size(); ++c)
        {
            double temp = B.Data[current][c];
            B.Data[current][c] = B.Data[maxRow][c];
            B.Data[maxRow][c] = temp;
        }

        // Doing elimination
        for (unsigned int r = current + 1; r < A.Data.size(); ++r)
        {
            if (!A.Data[r][current])
            {
                continue;
            }
            for (unsigned int c = current + 1; c < A.Data[0].size(); ++c)
            {
                A.Data[r][c] -= (A.Data[current][c] * A.Data[r][current] / A.Data[current][current]);
            }
            for (unsigned int c = 0; c < B.Data[0].size(); ++c)
            {
                B.Data[r][c] -= (B.Data[current][c] * A.Data[r][current] / A.Data[current][current]);
            }
            A.Data[r][current] = 0;
        }
    }

    // Get result by solving upper triangular matrix
    for (int current = A.Data.size() - 1; current >= 0; --current)
    {
        for (unsigned int c = 0; c < B.Data[0].size(); ++c)
        {
            B.Data[current][c] /= A.Data[current][current];
        }

        for (int r = current - 1; r >= 0; --r)
        {
            for (unsigned int c = 0; c < B.Data[0].size(); ++c)
            {
                B.Data[r][c] -= (A.Data[r][current] * B.Data[current][c]);
            }
        }
    }

    return B;
}

Matrix Matrix::trans() const
{
    Matrix result;
    for (unsigned int x = 0; x < this->Data[0].size(); ++x)
    {
        std::vector<double> rowVectorTemp;
        for (unsigned int y = 0; y < this->Data.size(); ++y)
        {
            rowVectorTemp.push_back(this->Data[y][x]);
        }
        result.Data.push_back(rowVectorTemp);
    }
    return result;
}

double Matrix::det()
{
    // Solving det(A), A must be square matrix.
    if (this->Data.size() != this->Data[0].size())
    {
        throw MATRIX_ERROR::NON_SQUARE;
    }

    Matrix A = *this;
    double result;
    int sign = true;

    // Gaussian elimination to get upper triangle matrix
    for (unsigned int current_y = 0, current_x = 0; \
        current_y < A.Data.size() && current_x < A.Data[0].size(); \
        ++current_y, ++current_x)
    {
        // Search for maximum in this column
        double maxNum = abs(A.Data[current_y][current_x]);
        unsigned int maxRow = current_y;
        for (unsigned int r = current_y + 1; r < A.Data.size(); ++r)
        {
            if (abs(A.Data[r][current_x]) > maxNum)
            {
                maxNum = abs(A.Data[r][current_x]);
                maxRow = r;
            }
        }

        // If there is a zero in diagonal line, det(A) = 0
        if (!maxNum)
        {
            return 0;
        }

        // Swap maxRow to current row
        if (current_y != maxRow)
        {
            for (unsigned int c = current_x; c < A.Data[0].size(); ++c)
            {
                double temp = A.Data[current_y][c];
                A.Data[current_y][c] = A.Data[maxRow][c];
                A.Data[maxRow][c] = temp;
            }
            sign = !sign;
        }

        // Doing elimination
        for (unsigned int r = current_y + 1; r < A.Data.size(); ++r)
        {
            if (!A.Data[r][current_x])
            {
                continue;
            }

            for (unsigned int c = current_x + 1; c < A.Data[0].size(); ++c)
            {
                A.Data[r][c] -= (A.Data[current_y][c] * A.Data[r][current_x] / A.Data[current_y][current_x]);
            }
            A.Data[r][current_x] = 0;
        }
    }

    // Calculate det(A)
    result = A.Data[0][0];
    for (unsigned int i = 1; i < A.Data.size(); ++i)
    {
        result *= A.Data[i][i];
    }
    result *= sign ? 1 : -1;
    return result;
}

Matrix Matrix::inverse()
{
    // Solving inverse(A), A must be square matrix.
    if (this->Data.size() != this->Data[0].size())
    {
        throw MATRIX_ERROR::NON_SQUARE;
    }

    Matrix A = *this;
    Matrix B, result;

    // Making a identity matrix
    for (unsigned r = 0; r < A.Data.size(); ++r)
    {
        std::vector<double> tempRowVector;
        for (unsigned c = 0; c < A.Data.size(); ++c)
        {
            if (r == c)
                tempRowVector.push_back(1);
            else
                tempRowVector.push_back(0);
        }
        B.Data.push_back(tempRowVector);
    }

    // Solving Ax=B
    try
    {
        result = A.solve(B);
    }
    catch (...)
    {
        throw;
    }

    return result;
}

Matrix leastsquare(const Matrix & A, const Matrix & B)
{
    if (A.Data.size() != B.Data.size())
    {
        throw MATRIX_ERROR::ROW_DIMENSION_NON_EQUIVALENT;
    }

    // Ax = B
    // The best solution of x is :
    // (A(T) * A)^(-1) * A(T) * B
    try
    {
        return (A.trans() * A).inverse() * A.trans() * B;
    }
    catch (...)
    {
        throw;
    }
}

void Matrix::ref(double threshold)
{
    // Gaussian elimination to get r.e.f.
    for (unsigned int current_y = 0, current_x = 0; \
        current_y < this->Data.size() && current_x < this->Data[0].size(); \
        ++current_y, ++current_x)
    {
        // Search for maximum in this column
        double maxNum = abs(this->Data[current_y][current_x]);
        unsigned int maxRow = current_y;
        for (unsigned int r = current_y + 1; r < this->Data.size(); ++r)
        {
            if (abs(this->Data[r][current_x]) > maxNum)
            {
                maxNum = abs(this->Data[r][current_x]);
                maxRow = r;
            }
        }

        if (!maxNum)
        {
            --current_y;
            continue;
        }

        // Swap maxRow to current row
        for (unsigned int c = current_x; c < this->Data[0].size(); ++c)
        {
            double temp = this->Data[current_y][c];
            this->Data[current_y][c] = this->Data[maxRow][c];
            this->Data[maxRow][c] = temp;
        }

        // Doing elimination
        for (unsigned int r = current_y + 1; r < this->Data.size(); ++r)
        {
            if (!this->Data[r][current_x])
            {
                continue;
            }

            for (unsigned int c = current_x + 1; c < this->Data[0].size(); ++c)
            {
                this->Data[r][c] -= (this->Data[current_y][c] * this->Data[r][current_x] / this->Data[current_y][current_x]);
            }
            this->Data[r][current_x] = 0;
        }
    }

    for (unsigned int y = 0; y < this->Data.size(); ++y)
    {
        for (unsigned int x = 0; x < this->Data[0].size(); ++x)
        {
            // threshold
            if (abs(this->Data[y][x]) < threshold)
            {
                this->Data[y][x] = 0;
            }
        }
    }
}