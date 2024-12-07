#include "MyForm.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include <msclr\marshal_cppstd.h> // Для msclr::interop::marshal_as
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


// Функция для перевода строки в 16-ричный формат
std::string toHex(const std::string& input) {
    std::stringstream hexStream;
    hexStream << std::hex << std::setfill('0');
    for (unsigned char c : input) {
        hexStream << std::setw(2) << (int)c;
    }
    return hexStream.str();
}

// Функция для перевода 16-ричного формата обратно в строку
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
    for (size_t i = 0; i < str1.length(); ++i) {  //Предполагается, что обе строки имеют одинаковую длину
        result += (str1[i] == str2[i]) ? '0' : '1'; // ? Оператор тернарного условия
    }
    //Если символы на текущей позиции равны то к строке result добавляется символ 0 иначе 1
    return result;
}
//Применение перестановки к массиву
std::string permute(const std::string& input, const int* table, int size) { //size размер выходной строки
    std::string output = "";
    for (int i = 0; i < size; ++i) {
        output += input[table[i] - 1]; //-1 тк в таблице нумервция с 1 а тут с 0
    }
    return output;
}
//таблица для начальной перестановки
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
//функция начальной перестановки
std::string initialPermutation(const std::string& input) {
    return permute(input, IP, 64);
}
//таблица расширения правой части с 32 бит до 48
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
//функция расширения правой части с 32 бит до 48
std::string expand(const std::string& halfBlock) {
    return permute(halfBlock, E, 48);
}
//функция замены через s блоки
std::string sBoxSubstitution(const std::string& input) {
    std::string output = "";

    // Массив всех S-блоков
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

    // Для каждого из 8 блоков обрабатываем по 6 бит
    for (int i = 0; i < 8; ++i) {
        std::string sixBits = input.substr(i * 6, 6);
        //-'0' используется для преобразования символов '0' и '1' в числа 0 и 1
        int row = 2 * (sixBits[0] - '0') + (sixBits[5] - '0');  // Первые и последние биты переводим в номер строки
        int col = 8 * (sixBits[1] - '0') + 4 * (sixBits[2] - '0') +
            2 * (sixBits[3] - '0') + (sixBits[4] - '0');  // Средние 4 бита переводим в номер столбца
        int value = S[i][row][col];  // Значение из соответствующего S-блока
        output += std::bitset<4>(value).to_string();  // Переводим значение в бинарный формат
        //на выходе 32 бит
    }

    return output;
}

//таблица P перестановки
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
//функция P перестановки
std::string permutationP(const std::string& input) {
    return permute(input, P, 32);
}
void desRound(std::string& left, std::string& right, const std::string& roundKey) {
    // Расширение правой части
    std::string expandedRight = expand(right);

    // XOR с раундовым ключом
    std::string xorResult = xorStrings(expandedRight, roundKey);

    // Замена через S-блоки
    std::string sboxResult = sBoxSubstitution(xorResult);

    // Перестановка P
    std::string permuted = permutationP(sboxResult);

    // XOR с левой частью и обновление
    std::string newRight = xorStrings(left, permuted);
    left = right;  // Левая часть становится правой
    right = newRight;  // Новая правая часть
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

//Перестановочная таблица PC-1 (64-битный ключ -> 56-битный)
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
//Перестановочная таблица PC-2 (56 - битный ключ-> 48 - битный)
int PC2[] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
};
//Таблица циклических сдвигов для раундовых ключей
int shiftTable[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};
//Функция для преобразования шестнадцатеричной строки в бинарную строчку
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

//Циклический сдвиг влево
std::string shiftLeft(const std::string& key, int shifts) {
    std::string shifted = key;
    for (int i = 0; i < shifts; ++i) {
        shifted = shifted.substr(1) + shifted[0];
    }
    return shifted;
}
//Генерация раундовых ключей
void generateRoundKeys(const std::string& keyHex, std::string roundKeys[16]) {
    // Преобразование исходного ключа в бинарный формат
    std::string keyBin = hexToBin(keyHex);
    if (keyBin.length() % 64 != 0) {
        keyBin.insert(0, 64 - (keyBin.length() % 64), '0');  // Дополняем слев '\0' до 64
    }
    // Применение перестановки PC-1
    std::string permutedKey = permute(keyBin, PC1, 56);

    // Разделение на две половины
    std::string left = permutedKey.substr(0, 28);
    std::string right = permutedKey.substr(28, 28);

    // Генерация 16 раундовых ключей
    for (int i = 0; i < 16; ++i) {
        // Сдвиг влево на заданное количество позиций
        left = shiftLeft(left, shiftTable[i]);
        right = shiftLeft(right, shiftTable[i]);

        // Объединение обеих половин
        std::string combined = left + right;

        // Применение перестановки PC-2 для получения 48-битного раундового ключа
        roundKeys[i] = permute(combined, PC2, 48);
    }
}
std::string desEncrypt(const std::string& plaintextHex, const std::string& keyHex) {
    //ФУНКЦИЯ ПРИНИМАЕТ ТЕКСТ УЖЕ В 16тиричном формате
    // Преобразуем текст в бинарный формат
    std::string plaintextBin = hexToBin(plaintextHex);
    if (plaintextBin.length() % 64 != 0) {
        plaintextBin.append(64 - (plaintextBin.length() % 64), '0');  // Дополняем справа '0'  64
    }

    // Применяем начальную перестановку
    std::string permutedPlaintext = initialPermutation(plaintextBin);

    // Разделяем на левую и правую половины по 32 бита
    std::string left = permutedPlaintext.substr(0, 32);
    std::string right = permutedPlaintext.substr(32, 32);

    // Генерация раундовых ключей
    std::string roundKeys[16];
    generateRoundKeys(keyHex, roundKeys);

    // Выполняем 16 раундов шифрования
    for (int i = 0; i < 16; ++i) {
        desRound(left, right, roundKeys[i]);
    }

    // Соединяем финальную  правую и левую части
    std::string combined = right + left;

    // Применяем финальную перестановку
    std::string ciphertextBin = finalPermutation(combined);

    // Преобразуем бинарный результат обратно в шестнадцатеричный формат
    std::stringstream ciphertextHex;
    for (size_t i = 0; i < ciphertextBin.size(); i += 4) {
        std::bitset<4> bits(ciphertextBin.substr(i, 4));
        ciphertextHex << std::hex << bits.to_ulong();
    }

    return ciphertextHex.str();
}
std::string desDecrypt(const std::string& ciphertextHex, const std::string& keyHex) {
    // Преобразуем текст в бинарный формат
    std::string ciphertextBin = hexToBin(ciphertextHex);

    // Применяем начальную перестановку
    std::string permutedCiphertext = initialPermutation(ciphertextBin);

    // Разделяем на левую и правую половины по 32 бита
    std::string left = permutedCiphertext.substr(0, 32);
    std::string right = permutedCiphertext.substr(32, 32);

    // Генерация раундовых ключей
    std::string roundKeys[16];
    generateRoundKeys(keyHex, roundKeys);

    // Выполняем 16 раундов дешифрования с обратным порядком ключей
    for (int i = 15; i >= 0; --i) {
        desRound(left, right, roundKeys[i]);
    }

    // Соединяем правую и левую части в обратном порядке
    std::string combined = right + left;

    // Применяем финальную перестановку
    std::string plaintextBin = finalPermutation(combined);

    // Преобразуем бинарный результат обратно в шестнадцатеричный формат
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
		// Открываем файл и читаем его содержимое
		StreamReader^ file = File::OpenText(Filename_Opentxt);
		String^ fileContent = file->ReadToEnd();

		// Устанавливаем текст в textBox_open
		textBox_open->Text = fileContent;

		// Преобразуем System::String^ в std::string для шестнадцатеричной обработки
		std::string fileContentStd = msclr::interop::marshal_as<std::string>(fileContent);

		// Преобразуем содержимое файла в шестнадцатеричное представление
		std::string hexOutput = toHex(fileContentStd);

		// Преобразуем шестнадцатеричную строку обратно в System::String^
		System::String^ hexString = gcnew System::String(hexOutput.c_str());

		// Устанавливаем шестнадцатеричное представление в textBox_open_hex
		textBox_open_hex->Text = hexString;
	}
	catch (Exception^ e)
	{
		MessageBox::Show(this, "Файл не был открыт", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
		MessageBox::Show(this, "Файл не был открыт", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
		MessageBox::Show(this, "Файл не был открыт", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
}

System::Void Project1::MyForm::button_output_open_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
	saveFileDialog1->Title = "Сохранить текстовый файл";
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
			MessageBox::Show(this, "Не удалось сохранить файл", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

System::Void Project1::MyForm::button_output_close_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
	saveFileDialog1->Title = "Сохранить текстовый файл";
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
			MessageBox::Show(this, "Не удалось сохранить файл", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}


System::Void Project1::MyForm::button_output_key_Click(System::Object^ sender, System::EventArgs^ e)
{
	SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
	saveFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
	saveFileDialog1->Title = "Сохранить текстовый файл";
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
			MessageBox::Show(this, "Не удалось сохранить файл", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}
}

System::Void Project1::MyForm::button_gen_key_Click(System::Object^ sender, System::EventArgs^ e)
{
	std::string key = "";
	int keyLength = 8;
	std::srand(static_cast<unsigned int>(std::time(nullptr))); //Инициализация генератора случайных чисел с использованием текущего времени.
	//static_cast<unsigned int> преобразует это время в целое число типа unsigned int, так как std::srand требует именно целого значения.
	//Эта строчка делает так, что генерация случайных чисел на основе функции std::rand() будет зависеть от времени выполнения программы
	//std::time(nullptr) возвращает текущее время в секундах с начала эпохи
	for (int i = 0; i < keyLength; i++) {
		int randomNumber = std::rand() % 256; //берем остаток и получаем  рнд число от 0 до 255
		std::stringstream ss; //для удобного преобразования целого числа в строку в шестнадцатеричном формате.
		//Этот объект временно хранит результат преобразования числа в строку.
		ss << std::hex << randomNumber; //Происходит запись случайного числа в поток ss,
		//при этом оно переводится в шестнадцатеричное представление благодаря флагу std::hex
		std::string hexValue = ss.str(); //из потока stringstream извлекается строковое представление числа и сохраняется в переменную hexValue
		if (hexValue.length() < 2) {
			hexValue = "0" + hexValue;
		}
		key += hexValue;
	}

	// Преобразуем std::string в System::String^
	System::String^ managedKey = gcnew System::String(key.c_str());

	// Устанавливаем значение в textBox_key
	textBox_key->Text = managedKey;

	return System::Void();
}

System::Void Project1::MyForm::button_code_open_Click(System::Object^ sender, System::EventArgs^ e)
{
	// Получаем текст из textBox_open
	System::String^ managedString = textBox_open->Text;

	// Преобразуем System::String^ в std::string
	std::string data = msclr::interop::marshal_as<std::string>(managedString);

	// Получаем ключ из textBox_key
	System::String^ managedkey = textBox_key->Text;

	// Преобразуем System::String^ в std::string
	std::string key = msclr::interop::marshal_as<std::string>(managedkey);
	//std::string res= xorStrings(data, fromHex(key));
    std::string chunk_des;
    std::string plaintext= toHex(data);

    // Преобразуем шестнадцатеричную строку обратно в System::String^
    System::String^ hexString = gcnew System::String(plaintext.c_str());

    // Устанавливаем шестнадцатеричное представление в textBox_open_hex
    textBox_open_hex->Text = hexString;


    for (size_t i = 0; i < plaintext.length(); i += 16) {
        std::string chunk = plaintext.substr(i, 16);

        chunk_des += desEncrypt(chunk, key);

    }
    std::string res;
	res = chunk_des;
	
	System::String^ resulres = gcnew System::String(res.c_str());
	// Устанавливаем обработанный текст в textBox_close
	textBox_close->Text = resulres;
	
	return System::Void();
}

System::Void Project1::MyForm::button_decode_close_Click(System::Object^ sender, System::EventArgs^ e)
{
	// Получаем текст из textBox_close
	System::String^ managedString = textBox_close->Text;

	// Преобразуем System::String^ в std::string
	std::string data = msclr::interop::marshal_as<std::string>(managedString);

	// Получаем ключ из textBox_key
	System::String^ managedkey = textBox_key->Text;

	// Преобразуем System::String^ в std::string
	std::string key = msclr::interop::marshal_as<std::string>(managedkey);
	//std::string res = xorStrings(fromHex(data), fromHex(key));
	//res = fromHex(res);
    std::string chunk_des= data;
    std::string res;
    std::string decrypted_plaintext;
    for (size_t i = 0; i < chunk_des.length(); i += 16) {
        // Извлекаем блок по 16 символов
        std::string chunk = chunk_des.substr(i, 16);

        // Декодируем блок
        decrypted_plaintext += desDecrypt(chunk, key);
    }
    res = fromHex(decrypted_plaintext);
	System::String^ resulres = gcnew System::String(res.c_str());
	// Устанавливаем обработанный текст в textBox_open
	textBox_open->Text = resulres;

	return System::Void();
}

// ДАЛЬШЕ РЕАЛТЗАЦИЯ RCA

// Алгоритм Евклида
int GCD(unsigned int a, unsigned int b) {
    if (b == 0)
        return a;
    return GCD(b, a % b);
}

// Расширенный алгоритм Евклида
int ext_GCD(unsigned int a, unsigned int b, int& x, int& y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    int x1, y1;
    int nod = ext_GCD(b, a % b, x1, y1); //рекурсия
    x = y1;
    y = x1 - y1 * (a / b);
    return nod; 
}

// Алгоритм возведения в степень без переполнения
long long pows(long long a, long long b, long long m) {
    long long result = 1;
    a = a % m; 
    while (b > 0) {
        if (b % 2 == 1) {   //Если b нечётное,то данная степень двойки (текущий a) должна присутствовать в разложении
            result = (result * a) % m;
        }         //Если b чётное, то данная степень двойки не нужна, и мы её просто игнорируем
        a = (a * a) % m;
        b /= 2;  //неполное частное с округлением вниз
    }
    return result;
}

// Тест Ферма 
bool Ferma(unsigned int x) {
    if (x == 2)
        return true;
    for (int i = 0; i < 10; i++) {
        unsigned int a = (rand() % (x - 2)) + 2; //случайное a от 2 до х-1
        if (GCD(a, x) != 1)
            return false;      //если а и х имеют общий делитель, отличный от 1, то х точно не простое
        if (pows(a, x - 1, x) != 1)
            return false;     //проверка условия малой теоремы Ферма (a^(х-1))mod(х)=1 только для простых х
    }
    return true;
}

// преобразуем целое число в его 16-ричное представление 
std::string intToHex(int number) {
    std::stringstream ss;
    ss << std::hex << number; // Устанавливаем шестнадцатеричный формат и добавляем число в поток
    return ss.str(); // Получаем строковое представление числа в шестнадцатеричном формате
}

// преобразуем 16-ричное строковое представление в целое число 
int hexToInt(const std::string& hexStr) {
    int number;
    std::stringstream ss;
    ss << std::hex << hexStr; // Устанавливаем шестнадцатеричный формат и добавляем строку в поток
    ss >> number; // Читаем значение из потока как целое число
    return number;
}

System::Void Project1::MyForm::button_gen_key_RSA_Click(System::Object^ sender, System::EventArgs^ e)
{
    // ищем фи 
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
    } while ((Ferma(q) == false) || (q == p));  //p не должно быть равно q 

    unsigned int n, fi, E;
    n = p * q;
    fi = (p - 1) * (q - 1);

    //генерируем число е
    int x, y;
    do {             
        E = rand() % fi; // сгенерировали число меньше фи 

    } while (ext_GCD(fi, E, x, y) != 1);

    //считаем d - ключ дешифрования 
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
        MessageBox::Show(this, "Файл не был открыт", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void Project1::MyForm::button_output_n_Click(System::Object^ sender, System::EventArgs^ e)
{
    SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
    saveFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
    saveFileDialog1->Title = "Сохранить текстовый файл";
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
            MessageBox::Show(this, "Не удалось сохранить файл", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
        MessageBox::Show(this, "Файл не был открыт", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

System::Void Project1::MyForm::button_output_d_Click(System::Object^ sender, System::EventArgs^ e)
{
    SaveFileDialog^ saveFileDialog1 = gcnew SaveFileDialog();
    saveFileDialog1->Filter = "Текстовые файлы (*.txt)|*.txt|Все файлы (*.*)|*.*";
    saveFileDialog1->Title = "Сохранить текстовый файл";
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
            MessageBox::Show(this, "Не удалось сохранить файл", "Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }
    }
}
// шифрование 
System::Void Project1::MyForm::button_code_RSA_Click(System::Object^ sender, System::EventArgs^ e)
{
    // Получаем текст из textBox_open
    System::String^ managedString = textBox_open->Text;

    // Преобразуем управляемую строку в стандартную строку
    std::string data = msclr::interop::marshal_as<std::string>(managedString);

    // Получаем текст из textBox_e 
    System::String^ managedkey = textBox_e->Text;

    // Преобразуем управляемую строку в стандартную строку 
    std::string key = msclr::interop::marshal_as<std::string>(managedkey);

    // Преобразуем строку key в целое число Е
    unsigned int E = std::stoul(key);

    // Получаем текст из textBox_n 
    System::String^ managedkey1 = textBox_n->Text;

    // Преобразуем управляемую строку в стандартную строку 
    std::string key1 = msclr::interop::marshal_as<std::string>(managedkey1);

    // Преобразуем строку key1 в целое число n
    unsigned int n = std::stoul(key1);

    std::string Str, S;
    for (size_t i = 0; i < data.length(); ++i) {
        int intValue = (int)data[i]; // преобразуем символ в целое число 
        int powValue = pows(intValue, E, n); 
        S = intToHex(powValue);
        Str += S;
        Str += ' ';
    };
    System::String^ resulres = gcnew System::String(Str.c_str()); // преобразуем строку в управляемую строку 
    textBox_close->Text = resulres; // сюда записываем результат 
    return System::Void();
}
// дешифрование 
System::Void Project1::MyForm::button_decode_RSA_Click(System::Object^ sender, System::EventArgs^ e)
{
    // Получаем текст из textBox_close
    System::String^ managedString = textBox_close->Text;

    // Преобразуем управляемую строку в стандартную строку
    std::string Str = msclr::interop::marshal_as<std::string>(managedString);

    // Получаем текст из textBox_n 
    System::String^ managedkey1 = textBox_n->Text;

    // Преобразуем управляемую строку в стандартную строку
    std::string key1 = msclr::interop::marshal_as<std::string>(managedkey1);

    // Преобразуем строку key1 в число n 
    unsigned int n = std::stoul(key1);

    // Получаем текст из textBox_d 
    System::String^ managedkey = textBox_d->Text;

    // Преобразуем управляемую строку в стандартную строку
    std::string key = msclr::interop::marshal_as<std::string>(managedkey);

    // Преобразуем строку key в целое число d 
    unsigned int d = std::stoul(key);
    std::stringstream a(Str); //поток, который позволяет обрабатывать строку как поток данных. 

    //инициализируем его значением Str, что позволит нам читать числа из строки по одному
    std::string hexNum;
    std::string res;

    // Проходим по каждому числу в строке, разделенному пробелами
    while (a >> hexNum) { // а содержит зашифрованные данные 
        int decimalValue = hexToInt(hexNum); 
        int powchar = pows(decimalValue, d, n);
        char letter = static_cast<char>(powchar); // Преобразуем число в символ
        res += letter;
    }
    System::String^ resulres = gcnew System::String(res.c_str()); // преобразуем res в управляемую 
    textBox_open->Text = resulres; // записываем результат 
    return System::Void();
}