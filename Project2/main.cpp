#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

// ������ main() STAThread �o���ݩ�
[STAThread]
int main(array<String^>^ argv)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Project2::MyForm windowsForm;
    Application::Run(%windowsForm);
}