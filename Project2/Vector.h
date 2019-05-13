#pragma once
#include <iostream>
#include <vector>
#include "Vector.h"

// 自定義的 Vector
class Vector
{
public:
    Vector();
    Vector(double);
    Vector(std::string);

    std::string Name;
    std::vector<double> Data;

    std::string output();
    // set precision
    std::string output(int precision);

    /*
     * Access Function
     */
    double& operator [](int index) { return this->Data[index]; }
    void push_back(double data) { this->Data.push_back(data); }
    int size() const { return this->Data.size(); }

    // Conversion
    operator std::vector<double>() const { return this->Data; }

    /*
     * 以下為 Vector 能操作的行為
     * 皆可能會 throw
     * - DIMENSION_NON_EQUIVALENT
     */
    /*
     * Negative Sign
     */
    Vector operator -();

    /*
     * Addition
     */
    Vector operator +(const Vector& v);

    /*
     * Subtraction
     */
    Vector operator -(const Vector& v);

    /*
     * Dot or Scalar multiplication
     */
    Vector operator *(const Vector& v);

    double norm() const;
};

// 定義相關錯誤
enum class VECTOR_ERROR {
    DIMENSION_NON_EQUIVALENT
};