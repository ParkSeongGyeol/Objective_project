#pragma once
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "../Login/Form1.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace MySql::Data::MySqlClient;

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
	public ref class Form2 : public System::Windows::Forms::Form
	{
	public:
		Form2(void)
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
		~Form2()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;





	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Button^ singup;

	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;


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
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->singup = (gcnew System::Windows::Forms::Button());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(120, 49);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(193, 21);
			this->textBox1->TabIndex = 0;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(120, 103);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(193, 21);
			this->textBox2->TabIndex = 1;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(120, 76);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(193, 21);
			this->textBox3->TabIndex = 2;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(120, 130);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(193, 21);
			this->textBox4->TabIndex = 3;
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(120, 157);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(193, 21);
			this->textBox5->TabIndex = 4;
			// 
			// textBox6
			// 
			this->textBox6->Location = System::Drawing::Point(120, 184);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(193, 21);
			this->textBox6->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(98, 52);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(16, 12);
			this->label1->TabIndex = 6;
			this->label1->Text = L"ID";
			this->label1->Click += gcnew System::EventHandler(this, &Form2::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(42, 79);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(72, 12);
			this->label2->TabIndex = 7;
			this->label2->Text = L"PASSWORD";
			this->label2->Click += gcnew System::EventHandler(this, &Form2::label2_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(76, 106);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(37, 12);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Email";
			this->label3->Click += gcnew System::EventHandler(this, &Form2::label3_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(76, 133);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(29, 12);
			this->label4->TabIndex = 9;
			this->label4->Text = L"이름";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(27, 160);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(87, 12);
			this->label5->TabIndex = 10;
			this->label5->Text = L"생년월일 8자리";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(61, 187);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(53, 12);
			this->label6->TabIndex = 11;
			this->label6->Text = L"전화번호";
			this->label6->Click += gcnew System::EventHandler(this, &Form2::label6_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(76, 216);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(29, 12);
			this->label7->TabIndex = 17;
			this->label7->Text = L"성별";
			// 
			// singup
			// 
			this->singup->Location = System::Drawing::Point(120, 240);
			this->singup->Name = L"singup";
			this->singup->Size = System::Drawing::Size(193, 23);
			this->singup->TabIndex = 16;
			this->singup->Text = L"회원가입";
			this->singup->UseVisualStyleBackColor = true;
			this->singup->Click += gcnew System::EventHandler(this, &Form2::button5_Click);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(120, 214);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(47, 16);
			this->radioButton1->TabIndex = 18;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"남자";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(266, 214);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(47, 16);
			this->radioButton2->TabIndex = 19;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"여자";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &Form2::radioButton2_CheckedChanged);
			// 
			// Form2
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(7, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(423, 318);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->singup);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Name = L"Form2";
			this->Text = L"회원가입";
			this->Load += gcnew System::EventHandler(this, &Form2::Form2_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label8_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e) {
	// MySQL 연결 문자열 설정
	String^ connStr = "server=221.140.173.236;user=root;database=GameChat;port=3306;password=Q!w2e3r4";

	// MySQL 연결 생성
	MySqlConnection^ conn = gcnew MySqlConnection(connStr);

	try
	{
		// 연결 열기
		conn->Open();

		// 중복 확인을 위한 쿼리 작성
		String^ query = "SELECT COUNT(*) FROM users WHERE UserId = @UserId OR Email = @Email OR PhoneNumber = @PhoneNumber";

		// 쿼리 실행을 위한 커맨드 생성
		MySqlCommand^ cmd = gcnew MySqlCommand(query, conn);
		cmd->Parameters->AddWithValue("@UserId", textBox1->Text);
		cmd->Parameters->AddWithValue("@Email", textBox3->Text);
		cmd->Parameters->AddWithValue("@PhoneNumber", textBox6->Text);

		// 결과 가져오기
		int count = Convert::ToInt32(cmd->ExecuteScalar());

		// 중복 확인
		if (count > 0)
		{
			MessageBox::Show("중복된 정보가 있습니다.");
		}
		else
		{
			// 중복되지 않았으므로 회원가입 처리
			query = "INSERT INTO users (UserId, UserPassword, Email, Name, Birthday, PhoneNumber, Sex) VALUES (@UserId, @UserPassword, @Email, @Name, @Birthday, @PhoneNumber, @Sex)";
			cmd = gcnew MySqlCommand(query, conn);
			cmd->Parameters->AddWithValue("@UserId", textBox1->Text);
			cmd->Parameters->AddWithValue("@UserPassword", textBox2->Text);
			cmd->Parameters->AddWithValue("@Email", textBox3->Text);
			cmd->Parameters->AddWithValue("@Name", textBox4->Text);
			cmd->Parameters->AddWithValue("@Birthday", textBox5->Text);
			cmd->Parameters->AddWithValue("@PhoneNumber", textBox6->Text);
			cmd->Parameters->AddWithValue("@Sex", radioButton1->Checked ? (Object^)"남자" : (Object^)"여자");


			// 쿼리 실행
			cmd->ExecuteNonQuery();

			MessageBox::Show("회원가입 성공!");
			// Form1으로 이동
			Form1^ form1 = gcnew Form1();
			form1->Show();
			this->Hide();
		}
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
	}
	finally
	{
		// 연결 닫기
		conn->Close();
	}
}
private: System::Void Form2_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
};