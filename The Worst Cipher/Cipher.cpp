#include "Cipher.h"

const char* msgs[] = {
	"0. �����",
	"1. ����������� ������",
	"2. ������������ ������" };


const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

namespace Cipher {


	// ����� ������ ������������ 
	int dialog(const char* msgs[], int N) {
		const char* errmsgs = "";
		int rc, i;
		do {
			puts(errmsgs);
			errmsgs = "������! ��������� ����:";
			for (int i = 0; i < N; ++i)
				puts(msgs[i]);
			printf("��������: --> ");
		} while (getType(rc, std::cin) < 0 || rc >= N);
		return rc;
	}


	// ���������� ������ 
	int cipherProcess() {
	std::cout << "������� ������, ������� ������� �����������.\n \"�������\" ��������:\n - ������ ��������� ����� ����������� ������������������ �������� �� ������� ����������� �������\n - ����� ���������� ���������� � ������, ����� ��� ���� �������������� ������ ��� ������� ��� ��� ��������� �����\n --> ";
	std::string origin, resultKey, resultWord;
	std::getline(std::cin, origin);
	// ������������ ������ ����� �� �����������
	while (!origin.empty()) {
		// ������� ������ ������� � ������ � � ����� ������
		while (!origin.find_first_of(" \t"))
			origin.erase(0, 1);
		while (origin.find_last_of(" \t") == origin.size() - 1)
			origin.pop_back();
		int pos = origin.find_first_of(" \t");
		std::string word;
		word.append(origin, 0, pos);
		origin.erase(0, pos);
		std::string key = generateKey(word);
		convertationKey(key, word, resultKey, resultWord);
	}
	std::cout << "������������� ������: " << resultWord << "\n ���� � ������: " << quaToHex(resultKey);
	return 1;
	}


	// ��������� ����� ��������� �������; ���������� ���������� ������ (������������������ �������� ��� ��������/���������) � ������������ ������ ��������� (������ ����� �������� ������)
	std::string generateKey(const std::string& str) {
		/*
		0 - �����;
		1 - ���� ������� ���������� (�� ���� "+" ��� "-");
		2 - ���� �������� ���������� (�� ���� "*" ��� "/");
		3 - ���� ���� (��� ������� ����� � ����� ����� ����-����, ��� ����, ����� ����� ���� ��������� �����, � => � �����, ����� ��� ������� ����� ����������������, ��� ���� ����� ��������� � �� 0, � �� 1, � �� 2, � �*� �����, ��� ��)
		4,5 - ������; � ����� ������������� ����� ������������� �� �����, �� ����� ������������ ��� ������������� ����������� ������
		*/

		// ���-�� ���� � �����
		int SZ = str.size();
		// ����� ���������� � ���������� ��������. ���� bktFlag (������) true, �� ���� �������� ������ � �� ���� �������
		// ����� �������� ��������� ���� ������ �� ����� false
		bool digitFlag = false, bktFlag = false;
		// ������-��������� ��� ������
		std::string convert;
		for (int i = 0; i < SZ; ++i) {
			// ���� ���������� ������ ��� ������
			if (digitFlag) {
				// �������� �������� ����
				int p = rand() % 2 + 1;
				// ���������� ���� � ������
				convert += p + 48;
			}
			// ����� ���������� ������ ����
			else
				convert += '0';
			digitFlag = !digitFlag;
		}
		// �������������� ������
		std::string res;
		// ���������� ������
		if (convert.size() > 2) {
			int tmpSize = convert.size();
			int tmpI = 0;
			while (tmpSize > 2) {
				// ��� ������ ����� ���������� �����-�� �������� ������� � ������� ������������� �� ���� ������, ����������� ���-�� ���� � ��., �� ��� ����
				int chance = rand() % 2;
				// "������" ������
				int format = 0;
				if (chance) {
					format = 3;
					int m[2] = { 3, 5 };
					if (tmpSize > 4)
						format = m[rand() % 2];
					res += '4';
					res.append(convert, tmpI, format);
					res += '5';
					if (tmpI + format <= convert.size())
						res.append(convert, tmpI + format, 1);
					tmpI += (format + 1);
					tmpSize--;
				}
				else {
					res.append(convert, tmpI, 2);
					(++tmpI)++;
					format = 2;
				}
				tmpSize -= format;
				if (convert.size() - tmpI < 3) {
					res.append(convert, tmpI, convert.size() - tmpI);
					break;
				}
			}
		}
		else
			res = convert;
		// �������� ���� ����� �����
		res += '3';
		return res;
	}

	// ����������� ����� � ����������� ������
	void convertationKey(const std::string& key, const std::string& word, std::string& resultKey, std::string& resultWord) {
		// ������� ��������������� �����
		int iWord = 0, iKey = 0;
		// ����������� ������ ��������� � ����� ( � ������ ��������-����������)
		int SZ;
		if (word.size() % 2)
			SZ = key.size() - 1; // ���� ����-���� � �����
		else
			SZ = key.size() - 2; // ��������� ������ - �������, ������� ������� � ������ �����, + ����-����
		// ��������������� (�������������) ������
		std::string cipherWord;
		// ��������������� (�������������) ����
		std::string cipherKey;
		// ���� ��� �������� ��������� ��������
		StackClass::Stack opStack;
		// ��������� ������ �������
		while (iKey != SZ) {
			// 1. ���� ����� �������� ���������, �� �������� ��� ���������� (������) �� ����� � ����� �������������� �����
			if (key[iKey] == '0') {
				cipherWord += word[iWord++];
				cipherKey += key[iKey];
			}
			else
				// 2. ���� ������� �������� ����� �������, �� �������� ��� � opStack
				if (key[iKey] == '4') {
					StackClass::elem_of_stack now(4);	// ��� ��� � ������������� ������ �� ����� ������, => �� � ����������� �� �������� ������ �� ������
					opStack += now;
				}
				else
					// 3. ���� ����� �������� ������ �������, �� ����������� �������� �� opStack ���� �� ����� �������
					// ��������������� ����� ������. ������ �������� ��������� � ����� ������������� �����
					if (key[iKey] == '5') {
						StackClass::elem_of_stack now(-1);
						while (now.get_key() != 4) {
							opStack(now);
							if (now.get_key() != 4) {
								cipherWord += now.get_string()[0];	// ������� �� ������� �������� ��������
								cipherKey += now.get_key() + 48;
							}
						}
					}
			// 4. ���� ����� �������� ���������� �������� ��� ������� �����������, �� ��������� ��� � opStack.
			// ������ ����� ���� ���������� ����� �� ����������, ��� ����������� � opStack,
			// ���� �� ����� ������� ��� ������ ���������, � �������� ��� � �������������� ������.
					else {
						if (!opStack.empty() && key[iKey] <= opStack.show_first().get_key() + 48 && opStack.show_first().get_key() < 3) {
							StackClass::elem_of_stack now(-1);
							opStack(now);
							if (now.get_key() == 4)
								break;
							cipherKey += now.get_key() + 48;
							cipherWord += now.get_string()[0];
						}
						StackClass::elem_of_stack now(key[iKey] - 48);
						std::string str;
						str += (word[iWord++]);
						now = str;
						opStack += now;
					}
			iKey++;
		}
		// ��������� ���� �� ������� ���������; ��� ��������, ������� ��������� � ���, �������� � ����� ������
		if (!opStack.empty()) {
			while (!opStack.empty()) {
				StackClass::elem_of_stack now;
				opStack(now);
				cipherWord += now.get_string()[0];
				cipherKey += now.get_key() + 48;
			}
		}
		cipherKey += '3';
		// ��������� � ������ ��������� �������, ���� �� ���� (����� ������)
		if (!(word.size() % 2)) {
			cipherKey.insert(0, 1, key[key.size() - 2]);
			cipherWord.insert(0, 1, word[word.size() - 1]);
		}
		reverse(cipherWord);
		resultWord += cipherWord;
		resultKey += cipherKey;
	}


	// ������ ����� (� ��� ��������, � ��� ����������)
	void reverse(std::string& str) {
		int n = str.size();
		for (int i = 0; i < n / 2; i++)
			std::swap(str[i], str[n - i - 1]);
	}


	// ������ ������������ ������������ ����� � 16-�������� 
	std::string quaToHex(std::string& key) {
		std::string result;
		while (key.size() > 1) {
			std::string tmp;
			std::string num[4] = { "00", "01", "10", "11" };
			for (int i = 1; i < 3; i++) {
				tmp += num[key[0] - 48];
				key.erase(0, 1);
			}
			// ��������� � 10-������
			int dec = 0;
			for (int i = 3; i > -1; i--) {
				if (tmp[i] == '1')
					dec += pow(2, 3 - i);
			}
			std::string hex[16] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
			result += hex[dec];
		}
		// ���� � ������ ������� ��� ���� �� ������������ ����-����, �� ��������� ��� ��� 30
		if (!key.empty())
			result += 'C';
		return result;
	}


	// "����������" 16-��������� ����� � ����������� �����������
	void hexToQua(std::string& key) {
		std::string qua;
		std::string val[16] = { "00", "01", "02", "03", "10", "11", "12", "13", "20", "21", "22", "23", "30", "31", "32", "33" };
		while (!key.empty()) {
			if (key[0] < 65)
				qua += val[key[0] - 48];
			else
				qua += val[key[0] - 55];
			key.erase(0, 1);
		}
		key = qua;
	}


	// ����������� ������ �����
	void decipherWord(const std::string& key, std::string& word) {
		reverse(word);
		// ������� ������������� ����� � �����
		int iKey = 0, iWord = 0;
		// ���� ��� �������� ���������
		StackClass::Stack opStack;
		int SZ = word.size();
		// ��������� ����������
		StackClass::elem_of_stack now;
		char tmpSymbol = 0;
		// ���������, ����� �����, ��� ���; ���� �����, �� ������ ������ ������ � �����
		if (!(SZ % 2)) {
			tmpSymbol = word[0];
			word.erase(0, 1);
			iKey++;
			SZ--;
		}
		while (iWord < SZ) {
			// 1. ���� ����� �������� ���������, �������� ��� � opStack
			if (key[iKey] == '0') {
				now = 0;
				std::string str;
				str = word[iWord];
				now = str;
				opStack += now;
			}
			// 2. ���� ����� ��������, => ��������� � ���� ����������, ������� ������ ���������� � opStack
			else {
				// ������ ��� ������ ��������, ������� ����� ������ � opStack
				std::string first, second;
				opStack(now);
				second = now.get_string();
				opStack(now);
				first = now.get_string();
				now = ((first += word[iWord]) += second);
				now = 0;
				opStack += now;
			}
			iWord++;
			iKey++;
		}
		// ����� ��������� ��������� ����������, ��� ��������� ��������� � �����. ����������� ��� �� opStack
		opStack(now);
		word = now.get_string();
		if (tmpSymbol)
			word += tmpSymbol;
	}


	// ���������� ������
	int decipherProcess() {
		std::cout << "��������! � ������������� ������/����� �� ����� ���� ���������� ��������! ���, ��� ����� ����� ���, ������������� ����� ��������������!\n������� ������������� ������\n --> ";
		std::string decipherWord;
		inputType(decipherWord, std::cin);
		std::cout << "������� ������������� ����\n --> ";
		std::string decipherKey;
		inputType(decipherKey, std::cin);
		std::string resultWord;
		hexToQua(decipherKey);
		while (!decipherKey.empty() && decipherKey != "0") {
			int endsPos = decipherKey.find_first_of("3");
			std::string currentWord, currentKey;
			currentWord.append(decipherWord, 0, endsPos);
			currentKey.append(decipherKey, 0, endsPos);
			decipherWord.erase(0, endsPos);
			decipherKey.erase(0, endsPos + 1);				// ������� ������ �� ���� ������
			Cipher::decipherWord(currentKey, currentWord);
			resultWord += currentWord;
			if ((!decipherKey.empty() || decipherKey != "0"))
				resultWord += ' ';
		}
		std::cout << "�������������� ������: " << resultWord;
		return 1;
	}


}