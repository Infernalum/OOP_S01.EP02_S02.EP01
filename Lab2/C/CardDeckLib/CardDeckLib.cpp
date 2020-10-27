#include "CardDeckLib.h"
#include <exception>
#include <stdio.h>
#include <ctime>

namespace CardDeckClass {

	const char* CardDeck::Rangs[13] = { "Двойка", "Тройка", "Четвёрка", "Пятёрка", "Шестёрка", "Семёрка", "Восьмёрка", "Девятка", "Десятка", "Валет", "Дама", "Король", "Туз" };

	const char* CardDeck::Suits[] = { "Бубе", "Червей", "Пики", "Крести" };

	/* --------------------------------------------------------- */
	/*				    	  Конструкторы					 	 */
	/* --------------------------------------------------------- */


	/* Пустой конструктор
	 Инициализируется пустая колода */
	CardDeck::CardDeck() {
		SZ = QUOTA;
		cards = new Card[SZ];
		for (int i = 0; i < SZ; ++i)
			cards[i] = { '0', '0' };
	}


	/* Инициализирующий конструктор с заданием количества карт, масть и ранг которых определяются случайно
	Выбрасывается исключение, если n > SZ */
	CardDeck::CardDeck(int size, int n) {
		if (size < n)
			throw std::exception("Кол-во инициализирующихся карт больше максимального размера колоды. Попрообуйте еще раз.");
		SZ = size;
		cards = new Card[SZ];
		srand(time(NULL));
		for (int i = 0; i < n; ++i) {
			int rang = 49 + rand() % 13;
			int suit = 49 + rand() % 4;
			cards[i] = { (char)rang, (char)suit };
		}
		for (int i = n; i < SZ; ++i)
			cards[i] = { '0','0' };
	}


	/* Инициализирующий конструктор с начальной инициализацией одной карты
	Выбрасывается исключение, если n = 0, либо масть или ранг карты не лежит в нужных интервалах */
	CardDeck::CardDeck(int n, int r, int s) {
		if (!n)
			throw std::exception("Начальный размер колоды не может быть пустым. Попробуйте еще раз.");
		if (r > 61 || r < 49 || s > 52 || s < 49)
			throw std::exception("Введены неверный ранг или масть инициализирующей карты. Попробуйте еще раз. ");
		SZ = n;
		cards = new Card[SZ];
		cards[0] = { (char)r, (char)s };
		for (int i = 1; i < SZ; i++)
			cards[i] = { '0','0' };
	}



	// Создание экземпляра класса с его инициализацией другим экземпляром класса (Копирующий конструктор)
	CardDeck::CardDeck(const CardDeck& copy) {
		cards = new Card[copy.SZ];
		(*this) = copy;
	}


	/* --------------------------------------------------------- */
	/*				      Сеттеры - set'теры					 */
	/* --------------------------------------------------------- */


	/* Добавить новую карту в колоду с помощью генератора случайных чисел
	При добавлении карты в переполненную колоду, размер колоды увеличиается на 10*/
	CardDeck& CardDeck::AddNewCard() {
		srand(time(NULL));
		int rang = 49 + rand() % 13;
		int suit = 49 + rand() % 4;
		if (cards[SZ - 1].rang != '0') {
			SZ += 10;
			Card* res = cards;
			cards = new Card[SZ];
			for (int i = 0; i < (SZ - 10); i++)
				cards[i] = { res[i].rang, res[i].suit };
			delete[] res;
			for (int i = SZ - 10; i < SZ; ++i)
				cards[i] = { '0','0' };
		}
		cards[GetCurrentSize()] = { (char)rang, (char)suit };
		return *this;
	}


	// Перегруженный оператор с таким функционалом
	CardDeck& CardDeck::operator ++ () {
		this->AddNewCard();
		return *this;
	}


	/* --------------------------------------------------------- */
	/*	     		      Компараторы для qsort					 */
	/* --------------------------------------------------------- */

	// Сравнение ранга двух карт по рангу
	int CardDeck::CompareRang(const void* x1, const void* x2) {
		return (((Card*)x1)->rang - ((Card*)x2)->rang);
	}


	// Сравнение ранга двух карт по масти
	int CardDeck::CompareSuit(const void* x1, const void* x2) {
		return (((Card*)x1)->suit - ((Card*)x2)->suit);
	}

	/* --------------------------------------------------------- */
	/*															 */
	/* --------------------------------------------------------- */

	// Сортировка деки по масти (Бубе -> Черви -> Пики -> Крести)
	CardDeck& CardDeck::SortSuit() {
		qsort(this->cards, GetCurrentSize(), sizeof(Card), CompareSuit);
		return *this;
	}


	// Сортировка деки по условию лабы (по масти: Бубе -> Черви -> Пики -> Крести, и по убыванию рангу) 
	CardDeck& CardDeck::DefaultSort() {
		SortSuit();
		int suit_ends = 0;
		int suit_beginning = 0;
		for (int i = 49; i < 53; i++) {
			if (suit_beginning == GetCurrentSize())
				return *this;
			while (suit_ends < GetCurrentSize() && (*this)(suit_ends + 1) == i)
				suit_ends++;
			qsort(this->cards + suit_beginning, suit_ends - suit_beginning, sizeof(Card), CompareRang);
			suit_beginning = suit_ends;
		}
		return *this;
	}

	// Переопределение экземпляра класса (Перегруженный оператор присваивания)
	CardDeck& CardDeck::operator = (const CardDeck& copy) {
		SZ = copy.SZ;
		for (int i = 0; i < copy.GetCurrentSize(); ++i)
			cards[i] = copy.cards[i];
		for (int i = copy.GetCurrentSize(); i < SZ; ++i)
			cards[i] = { '0', '0' };
		return *this;
	}


	/* --------------------------------------------------------- */
	/*				      Геттеры - get'теры 					 */
	/* --------------------------------------------------------- */


	// Вернуть текущее кол-во карт в деке
	int CardDeck::GetCurrentSize() const {
		for (int i = 0; i < SZ; ++i)
			if (cards[i].rang == '0')
				return i;
		return SZ;
	}

	// Получить масть карты по ее номеру в группе
	int CardDeck::GetCurrentSuit(int i) const {
		if (i < 1 || i > GetCurrentSize())
			throw std::exception("Неправильный номер карты (либо больший, либо меньший возможного)");
		return cards[i - 1].suit;
	}

	// Получить масть карты по ее номеру в группе
	int CardDeck::operator () (int i) const {
		return this->GetCurrentSuit(i);
	}

	// Получить ранг карты по ее номеру в группе
	int CardDeck::GetCurrentRang(int i) const {
		if (i < 1 || i > GetCurrentSize())
			throw std::exception("Неправильный номер карты (либо больший, либо меньший возможного)");
		return cards[--i].rang;
	}

	// Получить ранг карты по ее номеру в группе
	int CardDeck::operator [] (int i) const {
		return this->GetCurrentRang(i);
	}

	// Получить подгруппу карт заданной масти из текущей деки (Возвращается новый экземпляр класса)
	CardDeck& CardDeck::GetSuitDeck(int s) const {
		if (s < 1 || s > 4)
			throw std::exception("Пожалуйста, выберите существующий ранг: --> ");
		CardDeck* res = new CardDeck(GetCurrentSize(), 0);
		int j = 0;
		for (int i = 0; i < GetCurrentSize(); ++i) {
			if (!(*this)(i + 1))
				return *res;
			if ((*this)(i + 1) == (s + 48))
				(*res).cards[j++] = cards[i];
		}
		return (*res);
	}


	/* --------------------------------------------------------- */
	/*					Деструктор класса						 */
	/* --------------------------------------------------------- */

	CardDeck::~CardDeck() {
		delete[] cards;
	}


	/* --------------------------------------------------------- */
	/*						 Друзья класса 						 */
	/* --------------------------------------------------------- */

	// Ввод состояния деки из входного потока (с возможным выбрасыванием исключения)
	std::istream& operator >> (std::istream& stream, CardDeck& deck) {
		int size;
		getNum(size, stream);
		if (size > deck.SZ || size < 1)
			throw std::exception("Некорректное число карт (либо больше, либо меньше возможного). Попробуйте еще раз.");
		for (int i = 0; i < size; ++i) {
			int rc = 0;
			if (getNum(rc, stream))
				throw std::exception("Было введено неправильное число. Попробуйте еще раз");
			while (rc != 1 && rc != 2) {
				if (getNum(rc, stream))
					throw std::exception("Было введено неправильное число. Попробуйте еще раз");
			}

			if (rc == 1)
				++deck;
			else {
				int rang;
				if (getNum(rang, stream))
					throw std::exception("Было введено неправильное число. Попробуйте еще раз");
				while (rang < 1 || rang > 14) {
					if (getNum(rang, stream))
					throw std::exception("Было введено неправильное число. Попробуйте еще раз");
				}
				int suit;
				if (getNum(suit, stream))
					throw std::exception("Было введено неправильное число. Попробуйте еще раз");
				while (suit < 1 || suit > 4) {
					if (getNum(suit, stream))
						throw std::exception("Было введено неправильное число. Попробуйте еще раз");
				}
				deck.cards[i].rang = rang + 47;
				deck.cards[i].suit = suit + 48;
			}
		}
		return stream;
	}


	// Вывод текущей деки в выходной поток
	std::ostream& operator << (std::ostream& stream, const CardDeck& deck) {
		if (!deck.GetCurrentSize())
			stream << "Колода пуста.";
		else {
			stream << "Маскимальный размер колоды на данный момент: " << deck.GetMaxSize() << '\n' << "Колода:\n";
			for (int i = 0; i < deck.GetCurrentSize(); ++i) {
				stream << i + 1 << ": " << CardDeck::Rangs[deck[i + 1] - 49] << ' ' << CardDeck::Suits[deck(i + 1) - 49] << ' ' << std::endl;
			}
		}
		return stream;
	}
}

