#include <sstream>
#include <iomanip>
#include <string>
#include "Vector.h"

using namespace std;

Vector::Vector()
{
}

Vector::Vector(double d)
{
    this->Data.push_back(d);
}

Vector::Vector(string s)
{
    istringstream iss(s);
    double temp;
    while (iss >> temp)
    {
        this->Data.push_back(temp);
    }
}

string Vector::output()
{
    stringstream stream;
    string result;
    stream << "[";
    for (int i = 0; i < Data.size(); ++i)
    {
        stream << Data[i];
        if (i != Data.size() - 1)
        {
            stream << ",\n";
        }
    }
    stream << "]";
    result = stream.str();
    return result;
}

string Vector::output(int precision)
{
    stringstream stream;
    string result;
    stream << "[";
    for (int i = 0; i < Data.size(); ++i)
    {
        stream << fixed << setprecision(precision) << Data[i];
        if (i != Data.size() - 1)
        {
            stream << ",\n";
        }
    }
    stream << "]";
    result = stream.str();
    return result;
}

Vector Vector::operator -()
{
    Vector result = *this;
    for (unsigned int i = 0; i < result.size(); ++i)
    {
        result.Data[i] = -result.Data[i];
    }

    return result;
}

Vector Vector::operator+(const Vector & v)
{
    // �P�_�O�_�i�H�ۥ[ --> ���ץ����ۦP
    if (this->Data.size() != v.Data.size())
    {
        throw VECTOR_ERROR::DIMENSION_NON_EQUIVALENT;
    }

    Vector result = *this;

    for (unsigned int i = 0; i < result.Data.size(); ++i)
    {
        result.Data[i] += v.Data[i];
    }

    return result;
}

Vector Vector::operator-(const Vector & v)
{
    // �P�_�O�_�i�H�۴� --> ���ץ����ۦP
    if (this->Data.size() != v.Data.size())
    {
        throw VECTOR_ERROR::DIMENSION_NON_EQUIVALENT;
    }

    Vector result = *this;

    for (unsigned int i = 0; i < result.Data.size(); ++i)
    {
        result.Data[i] -= v.Data[i];
    }

    return result;
}

Vector Vector::operator*(const Vector & v)
{
    // �P�_�O�_�i�H�D dot --> ���ץ����ۦP
    // �Ψ䤤�@�謰 scalar --> �䤤�@����ץ������� 1
    if (this->Data.size() != 1 && v.Data.size() != 1 && this->Data.size() != v.Data.size())
    {
        throw VECTOR_ERROR::DIMENSION_NON_EQUIVALENT;
    }

    Vector result;

    if (this->Data.size() == 1)
    {
        result = v;

        for (unsigned int i = 0; i < result.Data.size(); ++i)
        {
            result.Data[i] *= this->Data[0];
        }

    }
    else if (v.Data.size() == 1)
    {
        result = *this;

        for (unsigned int i = 0; i < result.Data.size(); ++i)
        {
            result.Data[i] *= v.Data[0];
        }
    }
    else
    {
        double dot = 0;

        for (unsigned int i = 0; i < this->Data.size(); ++i)
        {
            dot += this->Data[i] * v.Data[i];
        }

        result.Data.push_back(dot);
    }

    return result;
}

double Vector::norm() const
{
    double mag = 0.0;
    for (unsigned int i = 0; i < this->Data.size(); i++)
    {
        mag += pow(this->Data[i], 2);
    }
    return sqrt(mag);
}