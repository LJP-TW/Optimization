#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

// 必須給 main() STAThread 這個屬性
[STAThread]
int main(array<String^>^ argv)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Project2::MyForm windowsForm;
    Application::Run(%windowsForm);
}