#include <vector>

#ifdef _DEBUG
#include <iostream>
#endif

#include "MyForm.h"

using namespace Project2;
using namespace std;
using namespace System;
using namespace System::IO;

enum OPTIMIZATION_METHOD {
    POWELL,
    NEWTON,
    STEEP_DESCENT,
    QUASI_NEWTON,
    CONJUGATE_GRADIENT
};

System::Void MyForm::ComputeButton_Click(System::Object^  sender, System::EventArgs^  e)
{
    std::string temp;

    // 抓取目前選定的是哪一個 Equation
    MarshalString(EquationlistBox->GetItemText(EquationlistBox->SelectedItem), temp);
    Equation& equation = equationManager->findEquationByString(temp);

    // Initial Value, Range 各是什麼
    MarshalString(InitialTextBox->Text, temp);
    Vector initial(temp);

    MarshalString(RangeLeftTextBox->Text, temp);
    Vector rangeLeft(temp);

    MarshalString(RangeRightTextBox->Text, temp);
    Vector rangeRight(temp);

#ifdef _DEBUG
    {
        using namespace std;
        cout << "Equation: " << equation.get_strF() << endl;
        cout << "Intial Value: " << initial.output() << endl;
        cout << "left range  : " << rangeLeft.output() << endl;
        cout << "right range : " << rangeRight.output() << endl;
        cout << "method: " << AlgorithmComboBox->SelectedIndex << endl;

        Vector test = Vector(initial);
        Vector testOrder[2];
        testOrder[0] = Vector("1");
        testOrder[1] = Vector("2");
        cout << "f(IV): " << equation.evalue(test) << endl; 
        // cout << "df(IV)/dx       : " << equation.diff(test, testOrder[0]) << endl;
        cout << "df(IV)/dx^2     : " << equation.diff(test, testOrder[1]) << endl;
        // 
        // Vector testDirection[3];
        // testDirection[0] = Vector("1");
        // cout << "mixima at Direction (1) : " << equation.getMinima(initial, rangeLeft, rangeRight, testDirection[0]) << endl;
    }
#endif

    // 接下來傳給對應函數
    switch (AlgorithmComboBox->SelectedIndex)
    {
    case POWELL:
        Powell(equation, initial, rangeLeft, rangeRight);
        break;
    case NEWTON:
        Newton(equation, initial, rangeLeft, rangeRight);
        break;
    case STEEP_DESCENT:
        SteepDescent(equation, initial, rangeLeft, rangeRight);
        break;
    case QUASI_NEWTON:
        QuasiNewton(equation, initial, rangeLeft, rangeRight);
        break;
    case CONJUGATE_GRADIENT:
        ConjugateGradient(equation, initial, rangeLeft, rangeRight);
        break;
    default:
        break;
    }
}

System::Void MyForm::printToOutputTextBox(std::stringstream& ss)
{
    std::string s;
    while (getline(ss, s))
    {
        this->OutputTextBox->AppendText(gcnew String(s.c_str()) + Environment::NewLine);
    }
}

System::Void MyForm::loadEquationsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
    openFileDialog1->ShowDialog();
}

System::Void MyForm::exportOutputToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e)
{
    if(saveFileDialog1->ShowDialog() == ::DialogResult::OK)
        File::WriteAllText(saveFileDialog1->FileName, OutputTextBox->Text);
}

System::Void MyForm::openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e)
{
    std::string tempFileName;
    MarshalString(openFileDialog1->FileName, tempFileName);
    equationManager->SetFileName(tempFileName);

    if (equationManager->LoadEquationData())
    {
        EquationlistBox->Items->Clear();

        std::vector<Equation> equations = equationManager->GetEquations();
        for (unsigned int i = 0; i < equations.size(); i++)
        {
            EquationlistBox->Items->Add(gcnew String(equations[i].get_strF().c_str()));
        }
        OutputTextBox->AppendText("- Equations have been loaded" + Environment::NewLine);
    }
}
