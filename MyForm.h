#pragma once
#include <cstdlib> 
namespace Project1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	//using namespace System::IO;
	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			srand(time(NULL)); // генерация псевдо случайных чисел 
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button_input_open;
	protected:
	private: System::Windows::Forms::TextBox^ textBox_open;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::GroupBox^ groupBox1;


	private: System::Windows::Forms::Button^ button_input_close;
	private: System::Windows::Forms::Button^ button_input_key;
	private: System::Windows::Forms::Button^ button_output_open;
	private: System::Windows::Forms::Button^ button_output_close;
	private: System::Windows::Forms::Button^ button_output_key;
	private: System::Windows::Forms::Button^ button_gen_key;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::TextBox^ textBox_close;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::TextBox^ textBox_key;
	private: System::Windows::Forms::Button^ button_code_open;
	private: System::Windows::Forms::Button^ button_decode_close;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::TextBox^ textBox_open_hex;
	private: System::Windows::Forms::GroupBox^ groupBox5;
	private: System::Windows::Forms::GroupBox^ groupBox6;
	private: System::Windows::Forms::GroupBox^ groupBox7;
	private: System::Windows::Forms::Button^ button_gen_key_RSA;
	private: System::Windows::Forms::Button^ button_decode_RSA;
	private: System::Windows::Forms::Button^ button_code_RSA;
	private: System::Windows::Forms::Button^ button_output_d;
	private: System::Windows::Forms::Button^ button_input_d;
	private: System::Windows::Forms::Button^ button_output_n;
	private: System::Windows::Forms::Button^ button_input_n;
	private: System::Windows::Forms::TextBox^ textBox_d;
	private: System::Windows::Forms::TextBox^ textBox_e;
	private: System::Windows::Forms::TextBox^ textBox_n;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;





	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_input_open = (gcnew System::Windows::Forms::Button());
			this->textBox_open = (gcnew System::Windows::Forms::TextBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->button_input_close = (gcnew System::Windows::Forms::Button());
			this->button_input_key = (gcnew System::Windows::Forms::Button());
			this->button_output_open = (gcnew System::Windows::Forms::Button());
			this->button_output_close = (gcnew System::Windows::Forms::Button());
			this->button_output_key = (gcnew System::Windows::Forms::Button());
			this->button_gen_key = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox_close = (gcnew System::Windows::Forms::TextBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox_key = (gcnew System::Windows::Forms::TextBox());
			this->button_code_open = (gcnew System::Windows::Forms::Button());
			this->button_decode_close = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox_open_hex = (gcnew System::Windows::Forms::TextBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->button_gen_key_RSA = (gcnew System::Windows::Forms::Button());
			this->button_decode_RSA = (gcnew System::Windows::Forms::Button());
			this->button_code_RSA = (gcnew System::Windows::Forms::Button());
			this->button_output_d = (gcnew System::Windows::Forms::Button());
			this->button_input_d = (gcnew System::Windows::Forms::Button());
			this->button_output_n = (gcnew System::Windows::Forms::Button());
			this->button_input_n = (gcnew System::Windows::Forms::Button());
			this->textBox_d = (gcnew System::Windows::Forms::TextBox());
			this->textBox_e = (gcnew System::Windows::Forms::TextBox());
			this->textBox_n = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox7->SuspendLayout();
			this->SuspendLayout();
			// 
			// button_input_open
			// 
			this->button_input_open->Location = System::Drawing::Point(646, 409);
			this->button_input_open->Name = L"button_input_open";
			this->button_input_open->Size = System::Drawing::Size(155, 23);
			this->button_input_open->TabIndex = 0;
			this->button_input_open->Text = L"Загрузить открытый текст";
			this->button_input_open->UseVisualStyleBackColor = true;
			this->button_input_open->Click += gcnew System::EventHandler(this, &MyForm::button_input_open_Click);
			// 
			// textBox_open
			// 
			this->textBox_open->Location = System::Drawing::Point(2, 19);
			this->textBox_open->Multiline = true;
			this->textBox_open->Name = L"textBox_open";
			this->textBox_open->Size = System::Drawing::Size(332, 263);
			this->textBox_open->TabIndex = 1;
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox_open);
			this->groupBox1->Location = System::Drawing::Point(12, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(340, 288);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Открытый текст";
			// 
			// button_input_close
			// 
			this->button_input_close->Location = System::Drawing::Point(646, 438);
			this->button_input_close->Name = L"button_input_close";
			this->button_input_close->Size = System::Drawing::Size(155, 23);
			this->button_input_close->TabIndex = 4;
			this->button_input_close->Text = L"Загрузить закрытый текст";
			this->button_input_close->UseVisualStyleBackColor = true;
			this->button_input_close->Click += gcnew System::EventHandler(this, &MyForm::button_input_close_Click);
			// 
			// button_input_key
			// 
			this->button_input_key->Location = System::Drawing::Point(6, 19);
			this->button_input_key->Name = L"button_input_key";
			this->button_input_key->Size = System::Drawing::Size(155, 23);
			this->button_input_key->TabIndex = 5;
			this->button_input_key->Text = L"Загрузить ключ";
			this->button_input_key->UseVisualStyleBackColor = true;
			this->button_input_key->Click += gcnew System::EventHandler(this, &MyForm::button_input_key_Click);
			// 
			// button_output_open
			// 
			this->button_output_open->Location = System::Drawing::Point(822, 409);
			this->button_output_open->Name = L"button_output_open";
			this->button_output_open->Size = System::Drawing::Size(155, 23);
			this->button_output_open->TabIndex = 6;
			this->button_output_open->Text = L"Выгрузить открытый текст";
			this->button_output_open->UseVisualStyleBackColor = true;
			this->button_output_open->Click += gcnew System::EventHandler(this, &MyForm::button_output_open_Click);
			// 
			// button_output_close
			// 
			this->button_output_close->Location = System::Drawing::Point(822, 438);
			this->button_output_close->Name = L"button_output_close";
			this->button_output_close->Size = System::Drawing::Size(155, 23);
			this->button_output_close->TabIndex = 7;
			this->button_output_close->Text = L"Выгрузить закрытый текст";
			this->button_output_close->UseVisualStyleBackColor = true;
			this->button_output_close->Click += gcnew System::EventHandler(this, &MyForm::button_output_close_Click);
			// 
			// button_output_key
			// 
			this->button_output_key->Location = System::Drawing::Point(177, 19);
			this->button_output_key->Name = L"button_output_key";
			this->button_output_key->Size = System::Drawing::Size(155, 23);
			this->button_output_key->TabIndex = 8;
			this->button_output_key->Text = L"Выгрузить ключ";
			this->button_output_key->UseVisualStyleBackColor = true;
			this->button_output_key->Click += gcnew System::EventHandler(this, &MyForm::button_output_key_Click);
			// 
			// button_gen_key
			// 
			this->button_gen_key->Location = System::Drawing::Point(19, 375);
			this->button_gen_key->Name = L"button_gen_key";
			this->button_gen_key->Size = System::Drawing::Size(155, 23);
			this->button_gen_key->TabIndex = 9;
			this->button_gen_key->Text = L"Сгенерировать ключ";
			this->button_gen_key->UseVisualStyleBackColor = true;
			this->button_gen_key->Click += gcnew System::EventHandler(this, &MyForm::button_gen_key_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->textBox_close);
			this->groupBox2->Location = System::Drawing::Point(12, 428);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(340, 329);
			this->groupBox2->TabIndex = 3;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Закрытый текст HEX";
			// 
			// textBox_close
			// 
			this->textBox_close->Location = System::Drawing::Point(2, 19);
			this->textBox_close->Multiline = true;
			this->textBox_close->Name = L"textBox_close";
			this->textBox_close->Size = System::Drawing::Size(332, 304);
			this->textBox_close->TabIndex = 1;
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->textBox_key);
			this->groupBox3->Location = System::Drawing::Point(13, 322);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(186, 47);
			this->groupBox3->TabIndex = 10;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Ключ HEX (DES)";
			// 
			// textBox_key
			// 
			this->textBox_key->Location = System::Drawing::Point(6, 19);
			this->textBox_key->Name = L"textBox_key";
			this->textBox_key->Size = System::Drawing::Size(155, 20);
			this->textBox_key->TabIndex = 0;
			// 
			// button_code_open
			// 
			this->button_code_open->Location = System::Drawing::Point(6, 19);
			this->button_code_open->Name = L"button_code_open";
			this->button_code_open->Size = System::Drawing::Size(202, 23);
			this->button_code_open->TabIndex = 11;
			this->button_code_open->Text = L"Закодировать открытый текст";
			this->button_code_open->UseVisualStyleBackColor = true;
			this->button_code_open->Click += gcnew System::EventHandler(this, &MyForm::button_code_open_Click);
			// 
			// button_decode_close
			// 
			this->button_decode_close->Location = System::Drawing::Point(6, 61);
			this->button_decode_close->Name = L"button_decode_close";
			this->button_decode_close->Size = System::Drawing::Size(202, 23);
			this->button_decode_close->TabIndex = 12;
			this->button_decode_close->Text = L"Раскодировать закрытый текст";
			this->button_decode_close->UseVisualStyleBackColor = true;
			this->button_decode_close->Click += gcnew System::EventHandler(this, &MyForm::button_decode_close_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->textBox_open_hex);
			this->groupBox4->Location = System::Drawing::Point(589, 12);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(340, 288);
			this->groupBox4->TabIndex = 3;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Открытый текст HEX";
			// 
			// textBox_open_hex
			// 
			this->textBox_open_hex->Location = System::Drawing::Point(2, 19);
			this->textBox_open_hex->Multiline = true;
			this->textBox_open_hex->Name = L"textBox_open_hex";
			this->textBox_open_hex->Size = System::Drawing::Size(332, 263);
			this->textBox_open_hex->TabIndex = 1;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->button_code_open);
			this->groupBox5->Controls->Add(this->button_decode_close);
			this->groupBox5->Location = System::Drawing::Point(199, 322);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(213, 100);
			this->groupBox5->TabIndex = 13;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"DES";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->button_input_key);
			this->groupBox6->Controls->Add(this->button_output_key);
			this->groupBox6->Location = System::Drawing::Point(427, 322);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(334, 54);
			this->groupBox6->TabIndex = 14;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"DES";
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->button_gen_key_RSA);
			this->groupBox7->Controls->Add(this->button_decode_RSA);
			this->groupBox7->Controls->Add(this->button_code_RSA);
			this->groupBox7->Controls->Add(this->button_output_d);
			this->groupBox7->Controls->Add(this->button_input_d);
			this->groupBox7->Controls->Add(this->button_output_n);
			this->groupBox7->Controls->Add(this->button_input_n);
			this->groupBox7->Controls->Add(this->textBox_d);
			this->groupBox7->Controls->Add(this->textBox_e);
			this->groupBox7->Controls->Add(this->textBox_n);
			this->groupBox7->Controls->Add(this->label3);
			this->groupBox7->Controls->Add(this->label2);
			this->groupBox7->Controls->Add(this->label1);
			this->groupBox7->Location = System::Drawing::Point(370, 476);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(553, 263);
			this->groupBox7->TabIndex = 15;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L"RSA";
			// 
			// button_gen_key_RSA
			// 
			this->button_gen_key_RSA->Location = System::Drawing::Point(6, 25);
			this->button_gen_key_RSA->Name = L"button_gen_key_RSA";
			this->button_gen_key_RSA->Size = System::Drawing::Size(166, 23);
			this->button_gen_key_RSA->TabIndex = 12;
			this->button_gen_key_RSA->Text = L"Сгенерировать ключ RSA";
			this->button_gen_key_RSA->UseVisualStyleBackColor = true;
			this->button_gen_key_RSA->Click += gcnew System::EventHandler(this, &MyForm::button_gen_key_RSA_Click);
			// 
			// button_decode_RSA
			// 
			this->button_decode_RSA->Location = System::Drawing::Point(234, 223);
			this->button_decode_RSA->Name = L"button_decode_RSA";
			this->button_decode_RSA->Size = System::Drawing::Size(166, 23);
			this->button_decode_RSA->TabIndex = 11;
			this->button_decode_RSA->Text = L"Раскодировать RSA";
			this->button_decode_RSA->UseVisualStyleBackColor = true;
			this->button_decode_RSA->Click += gcnew System::EventHandler(this, &MyForm::button_decode_RSA_Click);
			// 
			// button_code_RSA
			// 
			this->button_code_RSA->Location = System::Drawing::Point(57, 223);
			this->button_code_RSA->Name = L"button_code_RSA";
			this->button_code_RSA->Size = System::Drawing::Size(166, 23);
			this->button_code_RSA->TabIndex = 10;
			this->button_code_RSA->Text = L"Закодировать RSA";
			this->button_code_RSA->UseVisualStyleBackColor = true;
			this->button_code_RSA->Click += gcnew System::EventHandler(this, &MyForm::button_code_RSA_Click);
			// 
			// button_output_d
			// 
			this->button_output_d->Location = System::Drawing::Point(306, 75);
			this->button_output_d->Name = L"button_output_d";
			this->button_output_d->Size = System::Drawing::Size(83, 23);
			this->button_output_d->TabIndex = 9;
			this->button_output_d->Text = L"Выгрузить d";
			this->button_output_d->UseVisualStyleBackColor = true;
			this->button_output_d->Click += gcnew System::EventHandler(this, &MyForm::button_output_d_Click);
			// 
			// button_input_d
			// 
			this->button_input_d->Location = System::Drawing::Point(182, 75);
			this->button_input_d->Name = L"button_input_d";
			this->button_input_d->Size = System::Drawing::Size(83, 23);
			this->button_input_d->TabIndex = 8;
			this->button_input_d->Text = L"Загрузить d";
			this->button_input_d->UseVisualStyleBackColor = true;
			this->button_input_d->Click += gcnew System::EventHandler(this, &MyForm::button_input_d_Click);
			// 
			// button_output_n
			// 
			this->button_output_n->Location = System::Drawing::Point(306, 25);
			this->button_output_n->Name = L"button_output_n";
			this->button_output_n->Size = System::Drawing::Size(83, 23);
			this->button_output_n->TabIndex = 7;
			this->button_output_n->Text = L"Выгрузить n";
			this->button_output_n->UseVisualStyleBackColor = true;
			this->button_output_n->Click += gcnew System::EventHandler(this, &MyForm::button_output_n_Click);
			// 
			// button_input_n
			// 
			this->button_input_n->Location = System::Drawing::Point(182, 25);
			this->button_input_n->Name = L"button_input_n";
			this->button_input_n->Size = System::Drawing::Size(83, 23);
			this->button_input_n->TabIndex = 6;
			this->button_input_n->Text = L"Загрузить n";
			this->button_input_n->UseVisualStyleBackColor = true;
			this->button_input_n->Click += gcnew System::EventHandler(this, &MyForm::button_input_n_Click);
			// 
			// textBox_d
			// 
			this->textBox_d->Location = System::Drawing::Point(48, 117);
			this->textBox_d->Name = L"textBox_d";
			this->textBox_d->Size = System::Drawing::Size(93, 20);
			this->textBox_d->TabIndex = 5;
			// 
			// textBox_e
			// 
			this->textBox_e->Location = System::Drawing::Point(48, 156);
			this->textBox_e->Name = L"textBox_e";
			this->textBox_e->Size = System::Drawing::Size(93, 20);
			this->textBox_e->TabIndex = 4;
			// 
			// textBox_n
			// 
			this->textBox_n->Location = System::Drawing::Point(48, 78);
			this->textBox_n->Name = L"textBox_n";
			this->textBox_n->Size = System::Drawing::Size(93, 20);
			this->textBox_n->TabIndex = 3;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(22, 120);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(19, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"d=";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(22, 159);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(19, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"e=";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(22, 81);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(19, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"n=";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(989, 759);
			this->Controls->Add(this->groupBox7);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->button_gen_key);
			this->Controls->Add(this->button_output_close);
			this->Controls->Add(this->button_output_open);
			this->Controls->Add(this->button_input_close);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->button_input_open);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
private: System::Void button_input_open_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_input_close_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_input_key_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_output_open_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_output_close_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_output_key_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_gen_key_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_code_open_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_decode_close_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_gen_key_RSA_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_input_n_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_output_n_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_input_d_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_output_d_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_code_RSA_Click(System::Object^ sender, System::EventArgs^ e);
private: System::Void button_decode_RSA_Click(System::Object^ sender, System::EventArgs^ e);
};
}
