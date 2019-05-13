#pragma once
#include <sstream>
#include "EquationManager.h"
#include "DotNetUtilities.h"

namespace Project2
{
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;

    /// <summary>
    /// �D�n����
    /// </summary>
    public ref class MyForm : public System::Windows::Forms::Form
    {
    public:
        MyForm(void)
        {
            InitializeComponent();
            equationManager = new EquationManager();
            AlgorithmComboBox->SelectedIndex = 0;
        }

    protected:
        /// <summary>
        /// �M������ϥΤ����귽�C
        /// </summary>
        ~MyForm()
        {
            if (components)
            {
                delete components;
            }
        }
    private: System::Windows::Forms::MenuStrip^  menuStrip1;
    protected:
    private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
    private: System::Windows::Forms::ToolStripMenuItem^  loadEquationsToolStripMenuItem;
    private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
    private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
    private: System::Windows::Forms::GroupBox^  EquationGroupBox;
    private: System::Windows::Forms::ListBox^  EquationlistBox;
    private: System::Windows::Forms::GroupBox^  OutputGroupBox;
    private: System::Windows::Forms::TextBox^  OutputTextBox;
    private: System::Windows::Forms::GroupBox^  ParameterGroupBox;
    private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel3;
    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::TextBox^  InitialTextBox;
    private: System::Windows::Forms::TextBox^  RangeLeftTextBox;
    private: System::Windows::Forms::TextBox^  RangeRightTextBox;
    private: System::Windows::Forms::Button^  ComputeButton;
    private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;
    private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel4;
    private: System::Windows::Forms::Label^  label3;
    private: System::Windows::Forms::ComboBox^  AlgorithmComboBox;
    private:
        /// <summary>
        /// �]�p�u��һݪ��ܼơC
        /// </summary>
        System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
        /// <summary>
        /// �����]�p�u��䴩�һݪ���k - �ФŨϥε{���X�s�边�ק�
        /// �o�Ӥ�k�����e�C
        /// </summary>
        void InitializeComponent(void)
        {
            this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
            this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->loadEquationsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
            this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
            this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->OutputGroupBox = (gcnew System::Windows::Forms::GroupBox());
            this->OutputTextBox = (gcnew System::Windows::Forms::TextBox());
            this->EquationGroupBox = (gcnew System::Windows::Forms::GroupBox());
            this->EquationlistBox = (gcnew System::Windows::Forms::ListBox());
            this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->ComputeButton = (gcnew System::Windows::Forms::Button());
            this->ParameterGroupBox = (gcnew System::Windows::Forms::GroupBox());
            this->tableLayoutPanel3 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->label2 = (gcnew System::Windows::Forms::Label());
            this->InitialTextBox = (gcnew System::Windows::Forms::TextBox());
            this->RangeLeftTextBox = (gcnew System::Windows::Forms::TextBox());
            this->RangeRightTextBox = (gcnew System::Windows::Forms::TextBox());
            this->tableLayoutPanel4 = (gcnew System::Windows::Forms::TableLayoutPanel());
            this->label3 = (gcnew System::Windows::Forms::Label());
            this->AlgorithmComboBox = (gcnew System::Windows::Forms::ComboBox());
            this->menuStrip1->SuspendLayout();
            this->tableLayoutPanel1->SuspendLayout();
            this->OutputGroupBox->SuspendLayout();
            this->EquationGroupBox->SuspendLayout();
            this->tableLayoutPanel2->SuspendLayout();
            this->ParameterGroupBox->SuspendLayout();
            this->tableLayoutPanel3->SuspendLayout();
            this->tableLayoutPanel4->SuspendLayout();
            this->SuspendLayout();
            // 
            // menuStrip1
            // 
            this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
            this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->fileToolStripMenuItem });
            this->menuStrip1->Location = System::Drawing::Point(0, 0);
            this->menuStrip1->Name = L"menuStrip1";
            this->menuStrip1->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
            this->menuStrip1->Size = System::Drawing::Size(1152, 27);
            this->menuStrip1->TabIndex = 0;
            this->menuStrip1->Text = L"menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->loadEquationsToolStripMenuItem });
            this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
            this->fileToolStripMenuItem->Size = System::Drawing::Size(45, 23);
            this->fileToolStripMenuItem->Text = L"File";
            // 
            // loadEquationsToolStripMenuItem
            // 
            this->loadEquationsToolStripMenuItem->Name = L"loadEquationsToolStripMenuItem";
            this->loadEquationsToolStripMenuItem->Size = System::Drawing::Size(192, 26);
            this->loadEquationsToolStripMenuItem->Text = L"Load Equations";
            this->loadEquationsToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::loadEquationsToolStripMenuItem_Click);
            // 
            // openFileDialog1
            // 
            this->openFileDialog1->FileName = L"openFileDialog1";
            this->openFileDialog1->FileOk += gcnew System::ComponentModel::CancelEventHandler(this, &MyForm::openFileDialog1_FileOk);
            // 
            // tableLayoutPanel1
            // 
            this->tableLayoutPanel1->ColumnCount = 1;
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                50)));
            this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                50)));
            this->tableLayoutPanel1->Controls->Add(this->OutputGroupBox, 0, 2);
            this->tableLayoutPanel1->Controls->Add(this->EquationGroupBox, 0, 0);
            this->tableLayoutPanel1->Controls->Add(this->tableLayoutPanel2, 0, 1);
            this->tableLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tableLayoutPanel1->Location = System::Drawing::Point(0, 27);
            this->tableLayoutPanel1->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
            this->tableLayoutPanel1->RowCount = 3;
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 49.79757F)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50.20243F)));
            this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 343)));
            this->tableLayoutPanel1->Size = System::Drawing::Size(1152, 591);
            this->tableLayoutPanel1->TabIndex = 1;
            // 
            // OutputGroupBox
            // 
            this->OutputGroupBox->Controls->Add(this->OutputTextBox);
            this->OutputGroupBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->OutputGroupBox->Location = System::Drawing::Point(4, 251);
            this->OutputGroupBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->OutputGroupBox->Name = L"OutputGroupBox";
            this->OutputGroupBox->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->OutputGroupBox->Size = System::Drawing::Size(1144, 336);
            this->OutputGroupBox->TabIndex = 1;
            this->OutputGroupBox->TabStop = false;
            this->OutputGroupBox->Text = L"Output";
            // 
            // OutputTextBox
            // 
            this->OutputTextBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->OutputTextBox->Location = System::Drawing::Point(4, 22);
            this->OutputTextBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->OutputTextBox->Multiline = true;
            this->OutputTextBox->Name = L"OutputTextBox";
            this->OutputTextBox->ReadOnly = true;
            this->OutputTextBox->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
            this->OutputTextBox->Size = System::Drawing::Size(1136, 310);
            this->OutputTextBox->TabIndex = 0;
            // 
            // EquationGroupBox
            // 
            this->EquationGroupBox->Controls->Add(this->EquationlistBox);
            this->EquationGroupBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->EquationGroupBox->Location = System::Drawing::Point(4, 4);
            this->EquationGroupBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->EquationGroupBox->Name = L"EquationGroupBox";
            this->EquationGroupBox->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->EquationGroupBox->Size = System::Drawing::Size(1144, 115);
            this->EquationGroupBox->TabIndex = 0;
            this->EquationGroupBox->TabStop = false;
            this->EquationGroupBox->Text = L"Equations";
            // 
            // EquationlistBox
            // 
            this->EquationlistBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->EquationlistBox->FormattingEnabled = true;
            this->EquationlistBox->ItemHeight = 15;
            this->EquationlistBox->Location = System::Drawing::Point(4, 22);
            this->EquationlistBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->EquationlistBox->Name = L"EquationlistBox";
            this->EquationlistBox->Size = System::Drawing::Size(1136, 89);
            this->EquationlistBox->TabIndex = 0;
            // 
            // tableLayoutPanel2
            // 
            this->tableLayoutPanel2->ColumnCount = 2;
            this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                92.42424F)));
            this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                7.575758F)));
            this->tableLayoutPanel2->Controls->Add(this->ComputeButton, 1, 0);
            this->tableLayoutPanel2->Controls->Add(this->ParameterGroupBox, 0, 0);
            this->tableLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tableLayoutPanel2->Location = System::Drawing::Point(4, 127);
            this->tableLayoutPanel2->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
            this->tableLayoutPanel2->RowCount = 1;
            this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel2->Size = System::Drawing::Size(1144, 116);
            this->tableLayoutPanel2->TabIndex = 3;
            // 
            // ComputeButton
            // 
            this->ComputeButton->Location = System::Drawing::Point(1061, 4);
            this->ComputeButton->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->ComputeButton->Name = L"ComputeButton";
            this->ComputeButton->Size = System::Drawing::Size(79, 101);
            this->ComputeButton->TabIndex = 2;
            this->ComputeButton->Text = L"Compute";
            this->ComputeButton->UseVisualStyleBackColor = true;
            this->ComputeButton->Click += gcnew System::EventHandler(this, &MyForm::ComputeButton_Click);
            // 
            // ParameterGroupBox
            // 
            this->ParameterGroupBox->Controls->Add(this->tableLayoutPanel3);
            this->ParameterGroupBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->ParameterGroupBox->Location = System::Drawing::Point(4, 4);
            this->ParameterGroupBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->ParameterGroupBox->Name = L"ParameterGroupBox";
            this->ParameterGroupBox->Padding = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->ParameterGroupBox->Size = System::Drawing::Size(1049, 108);
            this->ParameterGroupBox->TabIndex = 0;
            this->ParameterGroupBox->TabStop = false;
            this->ParameterGroupBox->Text = L"Parameter";
            // 
            // tableLayoutPanel3
            // 
            this->tableLayoutPanel3->ColumnCount = 3;
            this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                13.33333F)));
            this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                86.66666F)));
            this->tableLayoutPanel3->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
                515)));
            this->tableLayoutPanel3->Controls->Add(this->label1, 0, 0);
            this->tableLayoutPanel3->Controls->Add(this->label2, 0, 1);
            this->tableLayoutPanel3->Controls->Add(this->InitialTextBox, 1, 0);
            this->tableLayoutPanel3->Controls->Add(this->RangeLeftTextBox, 1, 1);
            this->tableLayoutPanel3->Controls->Add(this->RangeRightTextBox, 2, 1);
            this->tableLayoutPanel3->Controls->Add(this->tableLayoutPanel4, 2, 0);
            this->tableLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tableLayoutPanel3->Location = System::Drawing::Point(4, 22);
            this->tableLayoutPanel3->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->tableLayoutPanel3->Name = L"tableLayoutPanel3";
            this->tableLayoutPanel3->RowCount = 2;
            this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel3->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel3->Size = System::Drawing::Size(1041, 82);
            this->tableLayoutPanel3->TabIndex = 0;
            // 
            // label1
            // 
            this->label1->Anchor = System::Windows::Forms::AnchorStyles::Left;
            this->label1->AutoSize = true;
            this->label1->Location = System::Drawing::Point(4, 13);
            this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(41, 15);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Initial";
            // 
            // label2
            // 
            this->label2->Anchor = System::Windows::Forms::AnchorStyles::Left;
            this->label2->AutoSize = true;
            this->label2->Location = System::Drawing::Point(4, 54);
            this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label2->Name = L"label2";
            this->label2->Size = System::Drawing::Size(42, 15);
            this->label2->TabIndex = 1;
            this->label2->Text = L"Range";
            // 
            // InitialTextBox
            // 
            this->InitialTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
            this->InitialTextBox->Location = System::Drawing::Point(74, 8);
            this->InitialTextBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->InitialTextBox->Name = L"InitialTextBox";
            this->InitialTextBox->Size = System::Drawing::Size(447, 25);
            this->InitialTextBox->TabIndex = 2;
            // 
            // RangeLeftTextBox
            // 
            this->RangeLeftTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
            this->RangeLeftTextBox->Location = System::Drawing::Point(74, 49);
            this->RangeLeftTextBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->RangeLeftTextBox->Name = L"RangeLeftTextBox";
            this->RangeLeftTextBox->Size = System::Drawing::Size(447, 25);
            this->RangeLeftTextBox->TabIndex = 3;
            // 
            // RangeRightTextBox
            // 
            this->RangeRightTextBox->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Left | System::Windows::Forms::AnchorStyles::Right));
            this->RangeRightTextBox->Location = System::Drawing::Point(529, 49);
            this->RangeRightTextBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->RangeRightTextBox->Name = L"RangeRightTextBox";
            this->RangeRightTextBox->Size = System::Drawing::Size(508, 25);
            this->RangeRightTextBox->TabIndex = 4;
            // 
            // tableLayoutPanel4
            // 
            this->tableLayoutPanel4->ColumnCount = 2;
            this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                16.57609F)));
            this->tableLayoutPanel4->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
                83.42391F)));
            this->tableLayoutPanel4->Controls->Add(this->label3, 0, 0);
            this->tableLayoutPanel4->Controls->Add(this->AlgorithmComboBox, 1, 0);
            this->tableLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
            this->tableLayoutPanel4->Location = System::Drawing::Point(529, 4);
            this->tableLayoutPanel4->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->tableLayoutPanel4->Name = L"tableLayoutPanel4";
            this->tableLayoutPanel4->RowCount = 1;
            this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel4->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
            this->tableLayoutPanel4->Size = System::Drawing::Size(508, 33);
            this->tableLayoutPanel4->TabIndex = 5;
            // 
            // label3
            // 
            this->label3->Anchor = System::Windows::Forms::AnchorStyles::Left;
            this->label3->AutoSize = true;
            this->label3->Location = System::Drawing::Point(4, 9);
            this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
            this->label3->Name = L"label3";
            this->label3->Size = System::Drawing::Size(66, 15);
            this->label3->TabIndex = 0;
            this->label3->Text = L"Algorithm";
            // 
            // AlgorithmComboBox
            // 
            this->AlgorithmComboBox->Dock = System::Windows::Forms::DockStyle::Fill;
            this->AlgorithmComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
            this->AlgorithmComboBox->FormattingEnabled = true;
            this->AlgorithmComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(5) {
                L"Powell\'s Method", L"Newton Method",
                    L"Steep Descent Algorithm", L"Quasi-Newton Method", L"Conjugate Gradient Method"
            });
            this->AlgorithmComboBox->Location = System::Drawing::Point(88, 4);
            this->AlgorithmComboBox->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->AlgorithmComboBox->Name = L"AlgorithmComboBox";
            this->AlgorithmComboBox->Size = System::Drawing::Size(416, 23);
            this->AlgorithmComboBox->TabIndex = 1;
            // 
            // MyForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(8, 15);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(1152, 618);
            this->Controls->Add(this->tableLayoutPanel1);
            this->Controls->Add(this->menuStrip1);
            this->MainMenuStrip = this->menuStrip1;
            this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
            this->Name = L"MyForm";
            this->Text = L"Optimization";
            this->menuStrip1->ResumeLayout(false);
            this->menuStrip1->PerformLayout();
            this->tableLayoutPanel1->ResumeLayout(false);
            this->OutputGroupBox->ResumeLayout(false);
            this->OutputGroupBox->PerformLayout();
            this->EquationGroupBox->ResumeLayout(false);
            this->tableLayoutPanel2->ResumeLayout(false);
            this->ParameterGroupBox->ResumeLayout(false);
            this->tableLayoutPanel3->ResumeLayout(false);
            this->tableLayoutPanel3->PerformLayout();
            this->tableLayoutPanel4->ResumeLayout(false);
            this->tableLayoutPanel4->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }
#pragma endregion
    private:
        EquationManager* equationManager;
        System::Void loadEquationsToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
        System::Void openFileDialog1_FileOk(System::Object^  sender, System::ComponentModel::CancelEventArgs^  e);
        System::Void ComputeButton_Click(System::Object^  sender, System::EventArgs^  e);
        System::Void printToOutputTextBox(std::stringstream& ss);

        // 5 Optimization Method
        System::Void Powell(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight);
        System::Void Newton(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight);
        System::Void SteepDescent(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight);
        System::Void QuasiNewton(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight);
        System::Void ConjugateGradient(Equation& equation, Vector initial, Vector rangeLeft, Vector rangeRight);

    };
}
