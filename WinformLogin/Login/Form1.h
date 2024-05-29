#pragma once
#include "../Singup/Form2.h"
#include "../SearchId/Form3.h"
#include "../SearchPassword/Form4.h"

namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ SearchId;

	private: System::Windows::Forms::Button^ SearchPassword;


	private: System::Windows::Forms::Button^ Singup;

	private: System::Windows::Forms::Label^ label3;



	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->SearchId = (gcnew System::Windows::Forms::Button());
			this->SearchPassword = (gcnew System::Windows::Forms::Button());
			this->Singup = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(116, 80);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(253, 21);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(116, 107);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(253, 21);
			this->textBox2->TabIndex = 1;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &Form1::textBox2_TextChanged);
			// 
			// button1
			// 
			this->button1->ForeColor = System::Drawing::SystemColors::ControlText;
			this->button1->Location = System::Drawing::Point(116, 134);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(253, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"로그인";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(94, 83);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(16, 12);
			this->label1->TabIndex = 3;
			this->label1->Text = L"ID";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click_1);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(38, 110);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 12);
			this->label2->TabIndex = 4;
			this->label2->Text = L"PASSWORD";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click_1);
			// 
			// SearchId
			// 
			this->SearchId->AutoSize = true;
			this->SearchId->Location = System::Drawing::Point(116, 184);
			this->SearchId->Name = L"SearchId";
			this->SearchId->Size = System::Drawing::Size(79, 23);
			this->SearchId->TabIndex = 5;
			this->SearchId->Text = L"아이디 찾기";
			this->SearchId->UseVisualStyleBackColor = true;
			this->SearchId->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// SearchPassword
			// 
			this->SearchPassword->AutoSize = true;
			this->SearchPassword->Location = System::Drawing::Point(197, 184);
			this->SearchPassword->Name = L"SearchPassword";
			this->SearchPassword->Size = System::Drawing::Size(91, 23);
			this->SearchPassword->TabIndex = 6;
			this->SearchPassword->Text = L"비밀번호 찾기";
			this->SearchPassword->UseVisualStyleBackColor = true;
			this->SearchPassword->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// Singup
			// 
			this->Singup->Location = System::Drawing::Point(294, 184);
			this->Singup->Name = L"Singup";
			this->Singup->Size = System::Drawing::Size(75, 23);
			this->Singup->TabIndex = 7;
			this->Singup->Text = L"회원가입";
			this->Singup->UseVisualStyleBackColor = true;
			this->Singup->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Showcard Gothic", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(179, 32);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(128, 23);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Game / Chat";
			this->label3->Click += gcnew System::EventHandler(this, &Form1::label3_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->ClientSize = System::Drawing::Size(474, 251);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->Singup);
			this->Controls->Add(this->SearchPassword);
			this->Controls->Add(this->SearchId);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->ForeColor = System::Drawing::SystemColors::ControlText;
			this->Name = L"Form1";
			this->Text = L"Game/Chat";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label2_Click_1(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	Form2^ form2 = gcnew Form2();
	form2->Show();
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	Form4^ form4 = gcnew Form4();
	form4->Show();
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	Form3^ form3 = gcnew Form3();
	form3->Show();
}


private: System::Void Form1_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
