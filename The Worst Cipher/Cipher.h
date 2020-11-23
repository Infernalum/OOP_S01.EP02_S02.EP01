#ifndef THE_WORST_CIPHER_H
#define THE_WORST_CIPHER_H

#include <string>
#include "StackLib/Stack.h"

extern const int NMsgs;

namespace Cipher {

	// ������ ������� �������� ����� ����� ����� ����� (1 � ������ �������, � 0 ��� ������)
	template <class T>
	int getType(T& a, std::istream& stream) {
		int rc = 0;
		stream >> a;
		if (!std::cin.good())
			rc = -1;				// ���������� ������ �����
		stream.clear();
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return rc;
	};


	// ������ ������� ��� ����� ����� �� �������� ������
	template<class T>
	void inputType(T& p, std::istream& stream) {
		while (getType(p, stream))
			std::cout << "����������, ������� ���������� �����: --> ";
	}

	// ����������� �������
	int dialog(const char* msgs[], int);

	// ���������� ������
	int cipherProcess();

	// ��������� ����� ��������� �������; ���������� ���������� ������ (������������������ �������� ��� ��������/���������) � ������������ ������ ��������� (������ ����� �������� ������)
	std::string generateKey(const std::string&);

	// ����������� ����������� ��������� � ����������� ���� (���, ������� ����� ������� ������������ ��� ����������)
	void convertationKey(const std::string&, const std::string&, std::string&, std::string&);

	// ������ ����� (� ��� ��������, � ��� ����������)	
	void reverse(std::string&);

	// ������ ������������ ������������ ����� � 16-��������
	std::string quaToHex(std::string&);

	// ���������� 16-��������� ����� � ����������� �����������
	void hexToQua(std::string&);

	// ���������� ������
	int decipherProcess();

	// ����������� ������ �����
	void decipherWord(const std::string&, std::string&);
}

#endif // !THE_WORST_CIPHER_H
