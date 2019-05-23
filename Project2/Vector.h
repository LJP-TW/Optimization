#pragma once
#include <iostream>
#include <vector>
#include "Vector.h"

// �۩w�q�� Vector
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
     * �H�U�� Vector ��ާ@���欰
     * �ҥi��| throw
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

    bool operator <=(const Vector& v);
    bool operator >=(const Vector& v);

    double norm() const;
};

// �w�q�������~
enum class VECTOR_ERROR {
    DIMENSION_NON_EQUIVALENT
};