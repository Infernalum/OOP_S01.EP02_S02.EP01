#ifndef THE_WORST_CIPHER_H
#define THE_WORST_CIPHER_H

#include <string>
#include "StackLib/Stack.h"

extern const int NMsgs;

namespace Cipher {

	// Шаблон функции проверки ввода числа ввода числа (1 в случае неудачи, и 0 при успехе)
	template <class T>
	int getType(T& a, std::istream& stream) {
		int rc = 0;
		stream >> a;
		if (!std::cin.good())
			rc = -1;				// Обнаружена ошибка ввода
		stream.clear();
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return rc;
	};


	// Шаблон функции для ввода числа из входного потока
	template<class T>
	void inputType(T& p, std::istream& stream) {
		while (getType(p, stream))
			std::cout << "Пожалуйста, введите корректное число: --> ";
	}

	// Организация диалога
	int dialog(const char* msgs[], int);

	// Шифрование строки
	int cipherProcess();

	// Генерация ключа заданного размера; передается ПРАВИЛЬНАЯ строка (последовательность символов без пробелов/табуляции) и возвращается строка выражения (которя будет являться ключом)
	std::string generateKey(const std::string&);

	// Конвертация полученного выражения в постфиксный ключ (тот, который будет служить расшифровкой для результата)
	void convertationKey(const std::string&, const std::string&, std::string&, std::string&);

	// Реверс слова (и для шифровки, и для дешифровки)	
	void reverse(std::string&);

	// Сжатие четверичного постфиксного ключа в 16-тиричный
	std::string quaToHex(std::string&);

	// Распаковка 16-тиричного ключа в постфиксный четверичный
	void hexToQua(std::string&);

	// Дешифровка строки
	int decipherProcess();

	// Расшифровка одного слова
	void decipherWord(const std::string&, std::string&);
}

#endif // !THE_WORST_CIPHER_H
