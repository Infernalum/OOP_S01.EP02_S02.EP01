#include "Lab2_C.h"



const char* msgs[] = { "0. �����",
"1. ������� ������",
"2. �������� ����� � ������, �������� ������� ���������� � ������� ���������� ��������� �����",
"3. �������� ����� � ���� ����� �� �� ������ � ������",
"4. ����������� ����� �� ����� � �������� �����",
"5. �������� �� ������ ��������� ���� �������� �����" };

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

namespace Lab2_A {


	// ����� ������ ������������
	int dialog(const char* msgs[], int N) {
		const char* errmsgs = "";
		int rc, i;
		do {
			puts(errmsgs);
			errmsgs = "������! ��������� ����!";
			for (i = 0; i < N; ++i)					// ����� ������ �����������
				puts(msgs[i]);
			printf("��������: --> ");
		} while (CardDeckClass::getNum(rc, std::cin) < 0 || rc >= N);
		return rc;
	}




	// ������ ������������� ����
	CardDeckClass::CardDeck Input() {
		std::cout << "����������, �������� ������ ������������� ����� ������:\n1. ������ ������\n2. ������ � n ���-��� ��������� ���� (����� n �������� �������������)\n3. ������ � ��������� �������������� ����� �����\n4. ������ �������� ������ (� ���� ���-�� ����, � �� ���������, � ������ �������������)\n";
		int res;
		CardDeckClass::input_Type(res);
		while (res < 1 || res > 4) {
			std::cout << "����������, �������� ����� �� 1 �� 4: ==> ";
			CardDeckClass::input_Type(res);
		}
		if (res == 1) {
			CardDeckClass::CardDeck* p = new CardDeckClass::CardDeck();
			std::cout << "������ ������� ����������������.";
			return *p;
		}
		if (res == 2) {
			while (true) {
				std::cout << "����������, ������� ������������ (�� ������ ������) ������ ������: ==> ";
				int size;
				CardDeckClass::input_Type(size);
				std::cout << "����������, ������� ���-�� ���� � ������: ==> ";
				int n;
				CardDeckClass::input_Type(n);
				try {
					CardDeckClass::CardDeck* p = new CardDeckClass::CardDeck(size, n);
					std::cout << "������ ������� ����������������.";
					return *p;
				}
				catch (const std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			}
		}
		if (res == 3) {
			std::cout << "����������, ������� ������������ (�� ������ ������) ������ ������: ==> ";
			int size;
			CardDeckClass::input_Type(size);
			std::cout << "����������, �������� ���� �����: 2 - 10; ���� 11 - �����, 12 - ����, 13 - ������, 14 - ���: --> ";
			int rang;
			CardDeckClass::input_Type(rang);
			while (rang < 2 || rang > 14) {
				std::cout << "����������, �������� ������������ ����: -->";
				CardDeckClass::input_Type(rang);
			}
			std::cout << "����������, �������� ����� �����: 1 - ����, 2 - �����, 3 - ����, 4 - ������: --> ";
			int suit;
			CardDeckClass::input_Type(suit);
			while (suit < 1 || suit > 4) {
				std::cout << "����������, �������� ������������ �����: -->";
				CardDeckClass::input_Type(suit);
			}
			CardDeckClass::CardDeck* p = new CardDeckClass::CardDeck(size, rang + 47, suit + 48);
			std::cout << "������ ������� ����������������.";
			return *p;
		}
		else {
			CardDeckClass::CardDeck* p = new CardDeckClass::CardDeck();
			while (true) {
				try {
					std::cout << " 1 �����: ��������� ������������ ������ ������.\n 2 �����: ���-�� ���� � ������.\n ����� ��� ������ ����� ��������\n-- > 1. �������� ��������� �����\n-- > 2. ������ ����� ��������������\n ���� ��������������, ��:\n ���� �����: 2 - 10; ���� 11 - �����, 12 - ����, 13 - ������, 14 - ���; \n ����� �����: 1 - ����, 2 - �����, 3 - ����, 4 - ������:\n --> \n";
					std::cin >> *p;
					std::cout << "������ ������� ����������������.";
					return *p;
				}
				catch (const std::exception& ex) {
					std::cout << ex.what() << std::endl;
				}
			}
		}
	}

	// ����� ������� ����
	int D_GetDeck(CardDeckClass::CardDeck& deck) {
		std::cout << deck;
		return 1;
	}


	// �������� ����� ������, �������� ������� ���������� � ������� ���������� ��������� �����
	int D_AddNewCard(CardDeckClass::CardDeck& deck) {
		++deck;
		std::cout << "��������� ����� ������� ���������";
		return 1;
	}


	// �������� ����� � ���� ����� �� �� ������ � ������
	int D_GetCurrentCard(CardDeckClass::CardDeck& deck) {
		try {
			int card;
			std::cout << "����������, ������� ����� ����� �� ������� ������: --> ";
			CardDeckClass::input_Type(card);
			int suit = deck(card);
			int rang = deck[card];
			std::cout << "���� �����: " << CardDeckClass::CardDeck::Rangs[rang - 49] << ' ' << CardDeckClass::CardDeck::Suits[suit - 49] << std::endl;
		}
		catch (const std::exception& ex) {
			std::cout << ex.what() << std::endl;
		}
		return 1;
	}

	// ����������� ����� �� ����� � �������� �����
	int D_Sort(CardDeckClass::CardDeck& deck) {
		deck.DefaultSort();
		std::cout << "������ ������� �����������.";
		return 1;
	}


	// �������� �� ������ ��������� ���� �������� �����
	int D_ChooseSuit(CardDeckClass::CardDeck& deck) {
		int suit;
		while (true) {
			std::cout << "����������, �������� ����� �����: 1 - ����, 2 - �����, 3 - ����, 4 - ������  ==> ";
			CardDeckClass::input_Type(suit);
			try {
				CardDeckClass::CardDeck res = deck.GetSuitDeck(suit);
				std::cout << "������ ������� ��������\n";
				std::cout << res;
				return 1;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << std::endl;
			}
		}
	}
}