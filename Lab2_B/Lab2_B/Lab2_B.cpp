#include "Lab2_B.h"



const char* msgs[] = { "0. Выйти",
"1. Вывести колоду",
"2. Добавить карту к группе, значение которой получается с помощью генератора случайных чисел",
"3. Получить масть и ранг карты по ее номеру в группе",
"4. Упорядочить карты по масти и убыванию ранга",
"5. Выделить из колоды подгруппу карт заданной масти" };

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);


const char* Rang[] = { "Двойка", "Тройка", "Четвёрка", "Пятёрка", "Шестёрка", "Семёрка", "Восьмёрка", "Девятка", "Десятка", "Валет", "Дама", "Король", "Туз" };
const char* Suit[] = { "Бубе", "Червей", "Пики", "Крести" };

namespace Lab2_A {


	// Выбор номера альтернативы
	int dialog(const char* msgs[], int N) {
		const char* errmsgs = "";
		int rc, i;
		do {
			puts(errmsgs);
			errmsgs = "Ошибка! Повторите ввод!";
			for (i = 0; i < N; ++i)					// Вывод списка альтернатив
				puts(msgs[i]);
			printf("Выберите: --> ");
		} while (CardDeckClass::getNum(rc, std::cin) < 0 || rc >= N);
		return rc;
	}




	// Первая инициализация деки
	CardDeckClass::CardDeck Input() {
		std::cout << "Пожалуйста, выберите способ инициализации Вашей колоды:\n1. Пустая колода\n2. Колода с n кол-вом случайных карт (число n задается пользователем)\n3. Колода с начальной инициализацией одной карты\n4. Ручное создание колоды (И ввод кол-ва карт, и их состояний, в случае необходимости)\n";
		int res;
		CardDeckClass::input_Type(res);
		while (res < 1 || res > 4) {
			std::cout << "Пожалуйста, выберите число от 1 до 4: ==> ";
			CardDeckClass::input_Type(res);
		}
		if (res == 1) {
			CardDeckClass::CardDeck p;
			std::cout << "Колода успешно инициализирована.";
			return p;
		}
		if (res == 2) {
			while (true) {
				std::cout << "Пожалуйста, введите кол-во карт в колоде: ==> ";
				int size;
				CardDeckClass::input_Type(size);
				try {
					CardDeckClass::CardDeck p(size);
					std::cout << "Колода успешно инициализирована.";
					return p;
				}
				catch (const std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			}
		}
		if (res == 3) {
			std::cout << "Пожалуйста, выберите ранг карты: 2 - 10; либо 11 - Валет, 12 - Дама, 13 - Король, 14 - Туз: --> ";
			int rang;
			CardDeckClass::input_Type(rang);
			while (rang < 1 || rang > 14) {
				std::cout << "Пожалуйста, выберите существующий ранг: -->";
				CardDeckClass::input_Type(rang);
			}
			std::cout << "Пожалуйста, выберите масть карты: 1 - Бубе, 2 - Черви, 3 - Пики, 4 - Крести: --> ";
			int suit;
			CardDeckClass::input_Type(suit);
			while (suit < 1 || suit > 4) {
				std::cout << "Пожалуйста, выберите существующую масть: -->";
				CardDeckClass::input_Type(suit);
			}
			CardDeckClass::CardDeck p(rang + 47, suit + 48);
			std::cout << "Колода успешно инициализирована.";
			return p;
		}
		else {
			CardDeckClass::CardDeck p;
			while (true) {
				try {
					std::cout << "1 число: кол-во карт в колоде.\n Далее для каждой карты выберите\n-- > 1. Добавить случайную карту\n-- > 2. Ввести карту самостоятельно\n Если самостоятельно, то:\n ранг карты: 2 - 10; либо 11 - Валет, 12 - Дама, 13 - Король, 14 - Туз; \n масть карты: 1 - Бубе, 2 - Черви, 3 - Пики, 4 - Крести:\n --> \n";
					std::cin >> p;
					std::cout << "Колода успешно инициализирована.";
					return p;
				}
				catch (const std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			}
		}
	}

	// Вывод текущей деки
	int D_GetDeck(CardDeckClass::CardDeck& deck) {
		std::cout << deck;
		return 1;
	}


	// Добавить карту колоде, значение которой получается с помощью генератора случайных чисел
	int D_AddNewCard(CardDeckClass::CardDeck& deck) {
		try {
			++deck;
			std::cout << "Случайная карта успешно добавлена";
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
		return 1;
	}


	// Получить масть и ранг карты по ее номеру в колоде
	int D_GetCurrentCard(CardDeckClass::CardDeck& deck) {
		try {
			int card;
			std::cout << "Пожалуйста, введите номер карты из текущей колоды: --> ";
			CardDeckClass::input_Type(card);
			int suit = deck(card);
			int rang = deck[card];
			std::cout << "Ваша карта: " << Rang[rang - 49] << ' ' << Suit[suit - 49] << std::endl;
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
		return 1;
	}

	// Упорядочить карты по масти и убыванию ранга
	int D_Sort(CardDeckClass::CardDeck& deck) {
		deck.DefaultSort();
		std::cout << "Колода успешно упорядочена.";
		return 1;
	}


	// Выделить из колоды подгруппу карт заданной масти
	int D_ChooseSuit(CardDeckClass::CardDeck& deck) {
		int suit;
		while (true) {
			std::cout << "Пожалуйста, выберите масть карты: 1 - Бубе, 2 - Черви, 3 - Пики, 4 - Крести  ==> ";
			CardDeckClass::input_Type(suit);
			try {
				CardDeckClass::CardDeck res = deck.GetSuitDeck(suit);
				std::cout << "Колода успешно выделена\n";
				std::cout << res;
				return 1;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
		}
	}
}