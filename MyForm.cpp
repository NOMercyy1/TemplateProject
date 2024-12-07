#include "MyForm.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <msclr\marshal_cppstd.h> // ��� msclr::interop::marshal_as
#include <sstream>
#include <iomanip>
#include <bitset>
#include <array>
#include <string>
#include <random>
#include <vector>
#include <iostream>
using namespace System;
using namespace System::Windows::Forms;
using namespace System::IO;

//[STAThread]
[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Project1::MyForm form;
	Application::Run(% form);
}


// ������� ��� �������� ������ � 16-������ ������
std::string toHex(const std::string& input) {
    std::stringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (unsigned char c : input) {
        hexStream << std::setw(2) << (int)c;
    }
    return hexStream.str();
}

// ������� ��� �������� 16-������� ������� ������� � ������
std::string fromHex(const std::string& hex) {
    std::string result;
    for (size_t i = 0; i < hex.length(); i += 2) {
        std::string byte = hex.substr(i, 2);
        char chr = (char)(int)strtol(byte.c_str(), nullptr, 16);
        result.push_back(chr);
    }
    return result;
}

std::string xorStrings(const std::string& str1, const std::string& str2) {
    std::string result = "";
    for (size_t i = 0; i < str1.length(); ++i) {  //��������������, ��� ��� ������ ����� ���������� �����
        result += (str1[i] == str2[i]) ? '0' : '1'; // ? �������� ���������� �������
    }
    //���� ������� �� ������� ������� ����� �� � ������ result ����������� ������ 0 ����� 1
    return result;
}
//���������� ������������ � �������
std::string permute(const std::string& input, const int* table, int size) { //size ������ �������� ������
    std::string output = "";
    for (int i = 0; i < size; ++i) {
        output += input[table[i] - 1]; //-1 �� � ������� ��������� � 1 � ��� � 0
    }
    return output;
}
//������� ��� ��������� ������������
int IP[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};
//������� ��������� ������������
std::string initialPermutation(const std::string& input) {
    return permute(input, IP, 64);
}
//������� ���������� ������ ����� � 32 ��� �� 48
int E[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};
//������� ���������� ������ ����� � 32 ��� �� 48
std::string expand(const std::string& halfBlock) {
    return permute(halfBlock, E, 48);
}
//������� ������ ����� s �����
std::string sBoxSubstitution(const std::string& input) {
    std::string output = "";

    // ������ ���� S-������
    int S[8][4][16] = {
        {
            {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
            {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
            {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
            {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
        },
        {
            {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
            {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
            {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
            {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
        },
        {
            {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
            {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
            {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
            {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
        },
        {
            {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
            {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
            {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
            {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
        },
        {
            {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
            {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
            {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
            {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
        },
        {
            {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
            {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
            {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
            {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
        },
        {
            {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
            {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
            {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
            {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
        },
        {
            {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
            {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
            {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
            {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
        }
    };

    // ��� ������� �� 8 ������ ������������ �� 6 ���
    for (int i = 0; i < 8; ++i) {
        std::string sixBits = input.substr(i * 6, 6);
        //-'0' ������������ ��� �������������� �������� '0' � '1' � ����� 0 � 1
        int row = 2 * (sixBits[0] - '0') + (sixBits[5] - '0');  // ������ � ��������� ���� ��������� � ����� ������
        int col = 8 * (sixBits[1] - '0') + 4 * (sixBits[2] - '0') +
            2 * (sixBits[3] - '0') + (sixBits[4] - '0');  // ������� 4 ���� ��������� � ����� �������
        int value = S[i][row][col];  // �������� �� ���������������� S-�����
        output += std::bitset<4>(value).to_string();  // ��������� �������� � �������� ������
        //�� ������ 32 ���
    }

    return output;
}

//������� P ������������
int P[] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25
};
//������� P ������������
std::string permutationP(const std::string& input) {
    return permute(input, P, 32);
}
void desRound(std::string& left, std::string& right, const std::string& roundKey) {
    // ���������� ������ �����
    std::string expandedRight = expand(right);

    // XOR � ��������� ������
    std::string xorResult = xorStrings(expandedRight, roundKey);

    // ������ ����� S-�����
    std::string sboxResult = sBoxSubstitution(xorResult);

    // ������������ P
    std::string permuted = permutationP(sboxResult);

    // XOR � ����� ������ � ����������
    std::string newRight = xorStrings(left, permuted);
    left = right;  // ����� ����� ���������� ������
    right = newRight;  // ����� ������ �����
}

int FP[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};
std::string finalPermutation(const std::string& input) {
    return permute(input, FP, 64);
}

//��������������� ������� PC-1 (64-������ ���� -> 56-������)
int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};
//��������������� ������� PC-2 (56 - ������ ����-> 48 - ������)
int PC2[] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};
//������� ����������� ������� ��� ��������� ������
int shiftTable[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};
//������� ��� �������������� ����������������� ������ � �������� �������
std::string hexToBin(const std::string& hex) {
    std::string bin = "";
    for (size_t i = 0; i < hex.size(); ++i) {
        switch (toupper(hex[i])) {
        case '0': bin += "0000"; break;
        case '1': bin += "0001"; break;
        case '2': bin += "0010"; break;
        case '3': bin += "0011"; break;
        case '4': bin += "0100"; break;
        case '5': bin += "0101"; break;
        case '6': bin += "0110"; break;
        case '7': bin += "0111"; break;
        case '8': bin += "1000"; break;
        case '9': bin += "1001"; break;
        case 'A': bin += "1010"; break;
        case 'B': bin += "1011"; break;
        case 'C': bin += "1100"; break;
        case 'D': bin += "1101"; break;
        case 'E': bin += "1110"; break;
        case 'F': bin += "1111"; break;
        }
    }
    return bin;
}

//����������� ����� �����
std::string shiftLeft(const std::string& key, int shifts) {
    std::string shifted = key;
    for (int i = 0; i < shifts; ++i) {
        shifted = shifted.substr(1) + shifted[0];
    }
    return shifted;
}
//��������� ��������� ������
void generateRoundKeys(const std::string& keyHex, std::string roundKeys[16]) {
    // �������������� ��������� ����� � �������� ������
    std::string keyBin = hexToBin(keyHex);
    if (keyBin.length() % 64 != 0) {
        keyBin.insert(0, 64 - (keyBin.length() % 64), '0');  // ��������� ���� '\0' �� 64
    }
    // ���������� ������������ PC-1
    std::string permutedKey = permute(keyBin, PC1, 56);

    // ���������� �� ��� ��������
    std::string left = permutedKey.substr(0, 28);
    std::string right = permutedKey.substr(28, 28);

    // ��������� 16 ��������� ������
    for (int i = 0; i < 16; ++i) {
        // ����� ����� �� �������� ���������� �������
        left = shiftLeft(left, shiftTable[i]);
        right = shiftLeft(right, shiftTable[i]);

        // ����������� ����� �������
        std::string combined = left + right;

        // ���������� ������������ PC-2 ��� ��������� 48-������� ���������� �����
        roundKeys[i] = permute(combined, PC2, 48);
    }
}
std::string desEncrypt(const std::string& plaintextHex, const std::string& keyHex) {
    //������� ��������� ����� ��� � 16�������� �������
    // ����������� ����� � �������� ������
    std::string plaintextBin = hexToBin(plaintextHex);
    if (plaintextBin.length() % 64 != 0) {
        plaintextBin.append(64 - (plaintextBin.length() % 64), '0');  // ��������� ������ '0'  64
    }

    // ��������� ��������� ������������
    std::string permutedPlaintext = initialPermutation(plaintextBin);

    // ��������� �� ����� � ������ �������� �� 32 ����
    std::string left = permutedPlaintext.substr(0, 32);
    std::string right = permutedPlaintext.substr(32, 32);

    // ��������� ��������� ������
    std::string roundKeys[16];
    generateRoundKeys(keyHex, roundKeys);

    // ��������� 16 ������� ����������
    for (int i = 0; i < 16; ++i) {
        desRound(left, right, roundKeys[i]);
    }

    // ��������� ���������  ������ � ����� �����
    std::string combined = right + left;

    // ��������� ��������� ������������
    std::string ciphertextBin = finalPermutation(combined);

    // ����������� �������� ��������� ������� � ����������������� ������
    std::stringstream ciphertextHex;
    for (size_t i = 0; i < ciphertextBin.size(); i += 4) {
        std::bitset<4> bits(ciphertextBin.substr(i, 4));
        ciphertextHex << std::hex << bits.to_ulong();
    }

    return ciphertextHex.str();
}
std::string desDecrypt(const std::string& ciphertextHex, const std::string& keyHex) {
    // ����������� ����� � �������� ������
    std::string ciphertextBin = hexToBin(ciphertextHex);

    // ��������� ��������� ������������
    std::string permutedCiphertext = initialPermutation(ciphertextBin);

    // ��������� �� ����� � ������ �������� �� 32 ����
    std::string left = permutedCiphertext.substr(0, 32);
    std::string right = permutedCiphertext.substr(32, 32);

    // ��������� ��������� ������
    std::string roundKeys[16];
    generateRoundKeys(keyHex, roundKeys);

    // ��������� 16 ������� ������������ � �������� �������� ������
    for (int i = 15; i >= 0; --i) {
        desRound(left, right, roundKeys[i]);
    }

    // ��������� ������ � ����� ����� � �������� �������
    std::string combined = right + left;

    // ��������� ��������� ������������
    std::string plaintextBin = finalPermutation(combined);

    // ����������� �������� ��������� ������� � ����������������� ������
    std::stringstream plaintextHex;
    for (size_t i = 0; i < plaintextBin.size(); i += 4) {
        std::bitset<4> bits(plaintextBin.substr(i, 4));
        plaintextHex << std::hex << bits.to_ulong();
    }

    return plaintextHex.str();
}

System::Void Project1::MyForm::button_input_open_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ Filename_Opentxt = "";
	if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		Filename_Opentxt = openFileDialog1->FileName;
	}
	try
	{
		// ��������� ���� � ������ ��� ����������
		StreamReader^ file = File::OpenText(Filename_Opentxt);
		String^ fileContent = file->ReadToEnd();

		// ������������� ����� � textBox_open
		textBox_open->Text = fileContent;

		// ����������� System::String^ � std::string ��� ����������������� ���������
		std::string fileContentStd = msclr::interop::marshal_as<std::string>(fileContent);

		// ����������� ���������� ����� � ����������������� �������������
		std::string hexOutput = toHex(fileContentStd);

		// ����������� ����������������� ������ ������� � System::String^
		System::String^ hexString = gcnew System::String(hexOutput.c_str());

		// ������������� ����������������� ������������� � textBox_open_hex
		textBox_open_hex->Text = hexString;
	}
	catch (Exception^ e)
	{
		MessageBox::Show(this, "���� �� ��� ������", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void Project1::MyForm::button_input_close_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ Filename_Closetxt = "";
	if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		Filename_Closetxt = openFileDialog1->FileName;
	}
	try
	{
		StreamReader^ file = File::OpenText(Filename_Closetxt);
		textBox_close->Text = file->ReadToEnd();
	}
	catch (Exception^ e)
	{
		MessageBox::Show(this, "���� �� ��� ������", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void Project1::MyForm::button_input_key_Click(System::Object^ sender, System::EventArgs^ e)
{
	String^ Filename_keytxt = "";
	if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
	{
		Filename_keytxt = openFileDialog1->FileName;
	}
	try
	{
		StreamReader^ file = File::OpenText(Filename_keytxt);
		textBox_key->Text = file->ReadToEnd();
	}
	catch (Exception^ e)
	{
		MessageBox::Show(this, "���� �� ��� ������", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void Project1::MyForm::button_output_open_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
	saveFileDialog1->Title = "��������� ��������� ����";
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ Filename_Savetxt = saveFileDialog1->FileName;

		try
		{
			StreamWriter^ file = gcnew StreamWriter(Filename_Savetxt);
			file->Write(textBox_open->Text);
			file->Close();
		}
		catch (Exception^ e)
		{
			MessageBox::Show(this, "�� ������� ��������� ����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

System::Void Project1::MyForm::button_output_close_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
	saveFileDialog1->Title = "��������� ��������� ����";
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ Filename_Savetxt = saveFileDialog1->FileName;

		try
		{
			StreamWriter^ file = gcnew StreamWriter(Filename_Savetxt);
			file->Write(textBox_close->Text);
			file->Close();
		}
		catch (Exception^ e)
		{
			MessageBox::Show(this, "�� ������� ��������� ����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}


System::Void Project1::MyForm::button_output_key_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
	saveFileDialog1->Title = "��������� ��������� ����";
	if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		String^ Filename_Savetxt = saveFileDialog1->FileName;

		try
		{
			StreamWriter^ file = gcnew StreamWriter(Filename_Savetxt);
			file->Write(textBox_key->Text);
			file->Close();
		}
		catch (Exception^ e)
		{
			MessageBox::Show(this, "�� ������� ��������� ����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

System::Void Project1::MyForm::button_gen_key_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string key = "";
	int keyLength = 8;
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //������������� ���������� ��������� ����� � �������������� �������� �������.
	//static_cast<unsigned int> ����������� ��� ����� � ����� ����� ���� unsigned int, ��� ��� std::srand ������� ������ ������ ��������.
	//��� ������� ������ ���, ��� ��������� ��������� ����� �� ������ ������� std::rand() ����� �������� �� ������� ���������� ���������
	//std::time(nullptr) ���������� ������� ����� � �������� � ������ �����
	for (int i = 0; i < keyLength; i++) {
		int randomNumber = std::rand() % 256; //����� ������� � ��������  ��� ����� �� 0 �� 255
		std::stringstream ss; //��� �������� �������������� ������ ����� � ������ � ����������������� �������.
		//���� ������ �������� ������ ��������� �������������� ����� � ������.
		ss << std::hex << randomNumber; //���������� ������ ���������� ����� � ����� ss,
		//��� ���� ��� ����������� � ����������������� ������������� ��������� ����� std::hex
		std::string hexValue = ss.str(); //�� ������ stringstream ����������� ��������� ������������� ����� � ����������� � ���������� hexValue
		if (hexValue.length() < 2) {
			hexValue = "0" + hexValue;
		}
		key += hexValue;
	}

	// ����������� std::string � System::String^
	System::String^ managedKey = gcnew System::String(key.c_str());

	// ������������� �������� � textBox_key
	textBox_key->Text = managedKey;

	return System::Void();
}

System::Void Project1::MyForm::button_code_open_Click(System::Object^ sender, System::EventArgs^ e)
{
	// �������� ����� �� textBox_open
	System::String^ managedString = textBox_open->Text;

	// ����������� System::String^ � std::string
	std::string data = msclr::interop::marshal_as<std::string>(managedString);

	// �������� ���� �� textBox_key
	System::String^ managedkey = textBox_key->Text;

	// ����������� System::String^ � std::string
	std::string key = msclr::interop::marshal_as<std::string>(managedkey);
	//std::string res= xorStrings(data, fromHex(key));
    std::string chunk_des;
    std::string plaintext= toHex(data);

    // ����������� ����������������� ������ ������� � System::String^
    System::String^ hexString = gcnew System::String(plaintext.c_str());

    // ������������� ����������������� ������������� � textBox_open_hex
    textBox_open_hex->Text = hexString;


    for (size_t i = 0; i < plaintext.length(); i += 16) {
        std::string chunk = plaintext.substr(i, 16);

        chunk_des += desEncrypt(chunk, key);

    }
    std::string res;
	res = chunk_des;
	
	System::String^ resulres = gcnew System::String(res.c_str());
	// ������������� ������������ ����� � textBox_close
	textBox_close->Text = resulres;
	
	return System::Void();
}

System::Void Project1::MyForm::button_decode_close_Click(System::Object^ sender, System::EventArgs^ e)
{
	// �������� ����� �� textBox_close
	System::String^ managedString = textBox_close->Text;

	// ����������� System::String^ � std::string
	std::string data = msclr::interop::marshal_as<std::string>(managedString);

	// �������� ���� �� textBox_key
	System::String^ managedkey = textBox_key->Text;

	// ����������� System::String^ � std::string
	std::string key = msclr::interop::marshal_as<std::string>(managedkey);
	//std::string res = xorStrings(fromHex(data), fromHex(key));
	//res = fromHex(res);
    std::string chunk_des= data;
    std::string res;
    std::string decrypted_plaintext;
    for (size_t i = 0; i < chunk_des.length(); i += 16) {
        // ��������� ���� �� 16 ��������
        std::string chunk = chunk_des.substr(i, 16);

        // ���������� ����
        decrypted_plaintext += desDecrypt(chunk, key);
    }
    res = fromHex(decrypted_plaintext);
	System::String^ resulres = gcnew System::String(res.c_str());
	// ������������� ������������ ����� � textBox_open
	textBox_open->Text = resulres;

	return System::Void();
}

// ������ ���������� RCA

// �������� �������
int GCD(unsigned int a, unsigned int b) {
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

// ����������� �������� �������
int ext_GCD(unsigned int a, unsigned int b, int& x, int& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int x1, y1;
    int nod = ext_GCD(b, a % b, x1, y1); //��������
    x = y1;
    y = x1 - y1 * (a / b);
    return nod; 
}

// �������� ���������� � ������� ��� ������������
long long pows(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m; 
    while (b > 0) {
        if (b % 2 == 1) {   //���� b ��������,�� ������ ������� ������ (������� a) ������ �������������� � ����������
            result = (result * a) % m;
        }         //���� b ������, �� ������ ������� ������ �� �����, � �� � ������ ����������
        a = (a * a) % m;
        b /= 2;  //�������� ������� � ����������� ����
    }
    return result;
}

// ���� ����� 
bool Ferma(unsigned int x) {
    if (x == 2)
        return true;
    for (int i = 0; i < 10; i++) {
        unsigned int a = (rand() % (x - 2)) + 2; //��������� a �� 2 �� �-1
        if (GCD(a, x) != 1)
            return false;      //���� � � � ����� ����� ��������, �������� �� 1, �� � ����� �� �������
        if (pows(a, x - 1, x) != 1)
            return false;     //�������� ������� ����� ������� ����� (a^(�-1))mod(�)=1 ������ ��� ������� �
    }
    return true;
}

// ����������� ����� ����� � ��� 16-������ ������������� 
std::string intToHex(int number) {
    std::stringstream ss;
    ss << std::hex << number; // ������������� ����������������� ������ � ��������� ����� � �����
    return ss.str(); // �������� ��������� ������������� ����� � ����������������� �������
}

// ����������� 16-������ ��������� ������������� � ����� ����� 
int hexToInt(const std::string& hexStr) {
    int number;
    std::stringstream ss;
    ss << std::hex << hexStr; // ������������� ����������������� ������ � ��������� ������ � �����
    ss >> number; // ������ �������� �� ������ ��� ����� �����
    return number;
}

System::Void Project1::MyForm::button_gen_key_RSA_Click(System::Object^ sender, System::EventArgs^ e)
{
    // ���� �� 
    unsigned int p, q;
    do {
        p = rand() % (65536);
        if ((p % 2) == 0) 
        { 
            p--; 
        }
    } while ((Ferma(p) == false));

    do {
        q = rand() % (65536);
        if ((q % 2) == 0) 
        { 
            q--; 
        }
    } while ((Ferma(q) == false) || (q == p));  //p �� ������ ���� ����� q 

    unsigned int n, fi, E;
    n = p * q;
    fi = (p - 1) * (q - 1);

    //���������� ����� �
    int x, y;
    do {             
        E = rand() % fi; // ������������� ����� ������ �� 

    } while (ext_GCD(fi, E, x, y) != 1);

    //������� d - ���� ������������ 
    unsigned int d;
    if (y < 0) {
        d = fi + y; 
    }
    else {
        d = y; 
    }
    textBox_d->Text = Convert::ToString(d);
    textBox_e->Text = Convert::ToString(E);
    textBox_n->Text = Convert::ToString(n);
    return System::Void();
}

System::Void Project1::MyForm::button_input_n_Click(System::Object^ sender, System::EventArgs^ e)
{
    String^ Filename_keytxt = "";
    if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
    {
        Filename_keytxt = openFileDialog1->FileName;
    }
    try
    {
        StreamReader^ file = File::OpenText(Filename_keytxt);
        textBox_n->Text = file->ReadToEnd();
    }
    catch (Exception^ e)
    {
        MessageBox::Show(this, "���� �� ��� ������", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void Project1::MyForm::button_output_n_Click(System::Object^ sender, System::EventArgs^ e)
{
    SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
    saveFileDialog1->Filter = "��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
    saveFileDialog1->Title = "��������� ��������� ����";
    if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        String^ Filename_Savetxt = saveFileDialog1->FileName;

        try
        {
            StreamWriter^ file = gcnew StreamWriter(Filename_Savetxt);
            file->Write(textBox_n->Text);
            file->Close();
        }
        catch (Exception^ e)
        {
            MessageBox::Show(this, "�� ������� ��������� ����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}

System::Void Project1::MyForm::button_input_d_Click(System::Object^ sender, System::EventArgs^ e)
{
    String^ Filename_keytxt = "";
    if (openFileDialog1->ShowDialog() == Windows::Forms::DialogResult::OK)
    {
        Filename_keytxt = openFileDialog1->FileName;
    }
    try
    {
        StreamReader^ file = File::OpenText(Filename_keytxt);
        textBox_d->Text = file->ReadToEnd();
    }
    catch (Exception^ e)
    {
        MessageBox::Show(this, "���� �� ��� ������", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void Project1::MyForm::button_output_d_Click(System::Object^ sender, System::EventArgs^ e)
{
    SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
    saveFileDialog1->Filter = "��������� ����� (*.txt)|*.txt|��� ����� (*.*)|*.*";
    saveFileDialog1->Title = "��������� ��������� ����";
    if (saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
    {
        String^ Filename_Savetxt = saveFileDialog1->FileName;

        try
        {
            StreamWriter^ file = gcnew StreamWriter(Filename_Savetxt);
            file->Write(textBox_d->Text);
            file->Close();
        }
        catch (Exception^ e)
        {
            MessageBox::Show(this, "�� ������� ��������� ����", "������", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}
// ���������� 
System::Void Project1::MyForm::button_code_RSA_Click(System::Object^ sender, System::EventArgs^ e)
{
    // �������� ����� �� textBox_open
    System::String^ managedString = textBox_open->Text;

    // ����������� ����������� ������ � ����������� ������
    std::string data = msclr::interop::marshal_as<std::string>(managedString);

    // �������� ����� �� textBox_e 
    System::String^ managedkey = textBox_e->Text;

    // ����������� ����������� ������ � ����������� ������ 
    std::string key = msclr::interop::marshal_as<std::string>(managedkey);

    // ����������� ������ key � ����� ����� �
    unsigned int E = std::stoul(key);

    // �������� ����� �� textBox_n 
    System::String^ managedkey1 = textBox_n->Text;

    // ����������� ����������� ������ � ����������� ������ 
    std::string key1 = msclr::interop::marshal_as<std::string>(managedkey1);

    // ����������� ������ key1 � ����� ����� n
    unsigned int n = std::stoul(key1);

    std::string Str, S;
    for (size_t i = 0; i < data.length(); ++i) {
        int intValue = (int)data[i]; // ����������� ������ � ����� ����� 
        int powValue = pows(intValue, E, n); 
        S = intToHex(powValue);
        Str += S;
        Str += ' ';
    };
    System::String^ resulres = gcnew System::String(Str.c_str()); // ����������� ������ � ����������� ������ 
    textBox_close->Text = resulres; // ���� ���������� ��������� 
    return System::Void();
}
// ������������ 
System::Void Project1::MyForm::button_decode_RSA_Click(System::Object^ sender, System::EventArgs^ e)
{
    // �������� ����� �� textBox_close
    System::String^ managedString = textBox_close->Text;

    // ����������� ����������� ������ � ����������� ������
    std::string Str = msclr::interop::marshal_as<std::string>(managedString);

    // �������� ����� �� textBox_n 
    System::String^ managedkey1 = textBox_n->Text;

    // ����������� ����������� ������ � ����������� ������
    std::string key1 = msclr::interop::marshal_as<std::string>(managedkey1);

    // ����������� ������ key1 � ����� n 
    unsigned int n = std::stoul(key1);

    // �������� ����� �� textBox_d 
    System::String^ managedkey = textBox_d->Text;

    // ����������� ����������� ������ � ����������� ������
    std::string key = msclr::interop::marshal_as<std::string>(managedkey);

    // ����������� ������ key � ����� ����� d 
    unsigned int d = std::stoul(key);
    std::stringstream a(Str); //�����, ������� ��������� ������������ ������ ��� ����� ������. 

    //�������������� ��� ��������� Str, ��� �������� ��� ������ ����� �� ������ �� ������
    std::string hexNum;
    std::string res;

    // �������� �� ������� ����� � ������, ������������ ���������
    while (a >> hexNum) { // � �������� ������������� ������ 
        int decimalValue = hexToInt(hexNum); 
        int powchar = pows(decimalValue, d, n);
        char letter = static_cast<char>(powchar); // ����������� ����� � ������
        res += letter;
    }
    System::String^ resulres = gcnew System::String(res.c_str()); // ����������� res � ����������� 
    textBox_open->Text = resulres; // ���������� ��������� 
    return System::Void();
}