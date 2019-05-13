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
    // 讀取 Equation 資料
    bool LoadEquationData();
    // 取得所有 Equation 資料
    std::vector<Equation> GetEquations();
    // 設置檔案路徑名稱
    void SetFileName(std::string fileName);
    // 取得特定 Equation 資料
    Equation& findEquationByString(std::string);

private:
    // 儲存 Equation 資料
    std::vector<Equation> Equations;
    // 紀錄 Equation ID，用於控管
    int EquationIndex;
    // 紀錄檔案路徑名稱
    std::string FileName;
};

enum class EQUATION_MANAGER_ERROR
{
    EQUATION_NOT_FOUND,
};