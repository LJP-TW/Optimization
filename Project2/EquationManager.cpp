#include <string>
#include "EquationManager.h"

using namespace std;

EquationManager::EquationManager()
{
    EquationIndex = 0;
}

bool EquationManager::LoadEquationData()
{
    fstream fin;
    fin.open(FileName, std::ios::in);

    // Ū�����Ѧ^��false
    if (!fin)
    {
        return false;
    }
    else
    {
        string tempSring;
        // ���M���� Equation ���
        Equations.clear();
        EquationIndex = 0;

        while (!fin.eof())
        {
            getline(fin, tempSring);
            Equations.push_back(tempSring);
            EquationIndex++;

        }
        return true;
    }
}

std::vector<Equation> EquationManager::GetEquations()
{
    return Equations;
}

void EquationManager::SetFileName(string fileName)
{
    FileName = fileName;
}

Equation& EquationManager::findEquationByString(string target)
{
    for (int i = 0; i < Equations.size(); ++i)
    {
        if (Equations[i].get_strF() == target)
        {
            return Equations[i];
        }
    }

    throw EQUATION_MANAGER_ERROR::EQUATION_NOT_FOUND;
}