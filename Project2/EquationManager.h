#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "Equation.h"

class EquationManager
{
public:
    EquationManager();
    // Ū�� Equation ���
    bool LoadEquationData();
    // ���o�Ҧ� Equation ���
    std::vector<Equation> GetEquations();
    // �]�m�ɮ׸��|�W��
    void SetFileName(std::string fileName);
    // ���o�S�w Equation ���
    Equation& findEquationByString(std::string);

private:
    // �x�s Equation ���
    std::vector<Equation> Equations;
    // ���� Equation ID�A�Ω󱱺�
    int EquationIndex;
    // �����ɮ׸��|�W��
    std::string FileName;
};

enum class EQUATION_MANAGER_ERROR
{
    EQUATION_NOT_FOUND,
};