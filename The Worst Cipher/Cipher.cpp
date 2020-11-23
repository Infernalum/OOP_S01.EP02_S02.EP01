#include "Cipher.h"

const char* msgs[] = {
	"0. Выйти",
	"1. Зашифровать строку",
	"2. Расшифровать строку" };


const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

namespace Cipher {


	// Выбор номера альтернативы 
	int dialog(const char* msgs[], int N) {
		const char* errmsgs = "";
		int rc, i;
		do {
			puts(errmsgs);
			errmsgs = "Ошибка! Повторите ввод:";
			for (int i = 0; i < N; ++i)
				puts(msgs[i]);
			printf("Выберите: --> ");
		} while (getType(rc, std::cin) < 0 || rc >= N);
		return rc;
	}


	// Шифрование строки 
	int cipherProcess() {
	std::cout << "Введите строку, которую желаете зашифровать.\n \"Правила\" шифровки:\n - словом считается любая непрерывная последовательность символов до первого пробельного символа\n - Знаки препинания отсутсвуют в строке, иначе они буду обрабатываться вместе сос словами или как отдельные слова\n --> ";
	std::string origin, resultKey, resultWord;
	std::getline(std::cin, origin);
	// Обрабатываем каждое слово по отдельности
	while (!origin.empty()) {
		// Убираем лишние символы с начала и с конца строки
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
	std::cout << "Зашифрованная строка: " << resultWord << "\n Ключ к строке: " << quaToHex(resultKey);
	return 1;
	}


	// Генерация ключа заданного размера; передается ПРАВИЛЬНАЯ строка (последовательность символов без пробелов/табуляции) и возвращается строка выражения (которя будет являться ключом)
	std::string generateKey(const std::string& str) {
		/*
		0 - число;
		1 - знак низкого приоритета (по типу "+" или "-");
		2 - знак высокого приоритета (по типу "*" или "/");
		3 - стоп знак (для каждого ключа в конце стоит стоп-знак, для того, чтобы можно было склеивать ключи, а => и слова, иначе при склейке будет неопределенность, ибо ключ может кончаться и на 0, и на 1, и на 2, и х*й пойми, где че)
		4,5 - скобки; в самом зашифрованном ключе присутсвовать не будут, но можно использовать для разнообразной постфиксной записи
		*/

		// Кол-во букв в слове
		int SZ = str.size();
		// Флаги информации о предыдущих символах. Если bktFlag (скобка) true, то есть открытая скобка и ее надо открыть
		// После закрытия очередной пары скобок он снова false
		bool digitFlag = false, bktFlag = false;
		// Строка-выражение без скобок
		std::string convert;
		for (int i = 0; i < SZ; ++i) {
			// Если предыдущий символ был числом
			if (digitFlag) {
				// Выбираем рандомно знак
				int p = rand() % 2 + 1;
				// Дообавляем знак в строку
				convert += p + 48;
			}
			// Иначе предыдущий символ знак
			else
				convert += '0';
			digitFlag = !digitFlag;
		}
		// Результирующая строка
		std::string res;
		// Добавление скобок
		if (convert.size() > 2) {
			int tmpSize = convert.size();
			int tmpI = 0;
			while (tmpSize > 2) {
				// Тут вообще можно зафигачить какую-то мудреную формулу с разными зависимостями от типа знаков, оставшегося кол-ва цифр и тд., но мне влом
				int chance = rand() % 2;
				// "Размер" скобок
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
		// Помещаем знак конца слова
		res += '3';
		return res;
	}

	// Конвертация ключа в постфиксную запись
	void convertationKey(const std::string& key, const std::string& word, std::string& resultKey, std::string& resultWord) {
		// Индексы соответствующих строк
		int iWord = 0, iKey = 0;
		// Фактический размер выражения в ключе ( с учетом четности-нечетности)
		int SZ;
		if (word.size() % 2)
			SZ = key.size() - 1; // Один стоп-знак в конце
		else
			SZ = key.size() - 2; // Последний символ - операнд, который добавим в начало шифра, + стоп-знак
		// Преобразованная (зашифрованная) строка
		std::string cipherWord;
		// Преобразованный (зашифрованный) ключ
		std::string cipherKey;
		// Стек для хранения операндов операций
		StackClass::Stack opStack;
		// Сканируем список токенов
		while (iKey != SZ) {
			// 1. Если токен является операндом, то добавить его эквивалент (символ) из слова в конец зашифрованного слова
			if (key[iKey] == '0') {
				cipherWord += word[iWord++];
				cipherKey += key[iKey];
			}
			else
				// 2. Если операнд является левой скобкой, то положить его в opStack
				if (key[iKey] == '4') {
					StackClass::elem_of_stack now(4);	// Так как в зашифрованной строке не будет скобок, => ей в соотвествие не ставится ничего из строки
					opStack += now;
				}
				else
					// 3. Если токен является правой скобкой, то выталкивать элементы из opStack пока не будет найдена
					// соответствующая левая скобка. Каждый оператор добавлять в конец зашифрованных строк
					if (key[iKey] == '5') {
						StackClass::elem_of_stack now(-1);
						while (now.get_key() != 4) {
							opStack(now);
							if (now.get_key() != 4) {
								cipherWord += now.get_string()[0];	// Костыль на костыле костылем погоняет
								cipherKey += now.get_key() + 48;
							}
						}
					}
			// 4. Если токен является оператором высокого или низкого приоритетов, то поместить его в opStack.
			// Однако перед этим вытолкнуть любой из операторов, уже находящихся в opStack,
			// если он имеет больший или равный приоритет, и добавить его в результирующие строки.
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
		// Проверяем стек на наличие операндов; все операнды, которые находятся в нем, помещаем в конец шифров
		if (!opStack.empty()) {
			while (!opStack.empty()) {
				StackClass::elem_of_stack now;
				opStack(now);
				cipherWord += now.get_string()[0];
				cipherKey += now.get_key() + 48;
			}
		}
		cipherKey += '3';
		// Добавляем в начале последний операнд, если он есть (слово четное)
		if (!(word.size() % 2)) {
			cipherKey.insert(0, 1, key[key.size() - 2]);
			cipherWord.insert(0, 1, word[word.size() - 1]);
		}
		reverse(cipherWord);
		resultWord += cipherWord;
		resultKey += cipherKey;
	}


	// Реверс слова (и для шифровки, и для дешифровки)
	void reverse(std::string& str) {
		int n = str.size();
		for (int i = 0; i < n / 2; i++)
			std::swap(str[i], str[n - i - 1]);
	}


	// Сжатие четверичного постфиксного ключа в 16-тиричный 
	std::string quaToHex(std::string& key) {
		std::string result;
		while (key.size() > 1) {
			std::string tmp;
			std::string num[4] = { "00", "01", "10", "11" };
			for (int i = 1; i < 3; i++) {
				tmp += num[key[0] - 48];
				key.erase(0, 1);
			}
			// Переводим в 10-тичную
			int dec = 0;
			for (int i = 3; i > -1; i--) {
				if (tmp[i] == '1')
					dec += pow(2, 3 - i);
			}
			std::string hex[16] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F" };
			result += hex[dec];
		}
		// Если в строке остался еще один не переведенный стоп-знак, то переводим его как 30
		if (!key.empty())
			result += 'C';
		return result;
	}


	// "Распаковка" 16-тиричного ключа в постфиксный четверичный
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


	// Расшифровка одного слова
	void decipherWord(const std::string& key, std::string& word) {
		reverse(word);
		// Индексы зашифрованных слова и ключа
		int iKey = 0, iWord = 0;
		// Стек для хранения операндов
		StackClass::Stack opStack;
		int SZ = word.size();
		// Временные переменные
		StackClass::elem_of_stack now;
		char tmpSymbol = 0;
		// Проверяем, четно слово, или нет; если четно, то ставим первый символ в конец
		if (!(SZ % 2)) {
			tmpSymbol = word[0];
			word.erase(0, 1);
			iKey++;
			SZ--;
		}
		while (iWord < SZ) {
			// 1. Если токен является операндом, помещаем его в opStack
			if (key[iKey] == '0') {
				now = 0;
				std::string str;
				str = word[iWord];
				now = str;
				opStack += now;
			}
			// 2. Либо токен оператор, => нуждается в двух операторах, которые должны находиться в opStack
			else {
				// Строка для нового операнда, который будет лежать в opStack
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
		// Когда выражение полностью обработано, его результат находится в стеке. Выталкиваем его из opStack
		opStack(now);
		word = now.get_string();
		if (tmpSymbol)
			word += tmpSymbol;
	}


	// Дешифровка строки
	int decipherProcess() {
		std::cout << "Внимание! В зашифрованной строке/ключе НЕ МОЖЕТ БЫТЬ пробельных символов! Все, что стоит после них, автоматически будет игнорироваться!\nВведите зашифрованную строку\n --> ";
		std::string decipherWord;
		inputType(decipherWord, std::cin);
		std::cout << "Введите зашифрованный ключ\n --> ";
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
			decipherKey.erase(0, endsPos + 1);				// Удаляем вместе со стоп знаком
			Cipher::decipherWord(currentKey, currentWord);
			resultWord += currentWord;
			if ((!decipherKey.empty() || decipherKey != "0"))
				resultWord += ' ';
		}
		std::cout << "Расшифрованная строка: " << resultWord;
		return 1;
	}


}