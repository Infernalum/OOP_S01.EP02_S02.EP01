#include "pch.h"

#include "gtest/gtest.h"
#include "CardDeckLib/CardDeckLib.h"

/* --------------------------------------------------------- */
/*				    	  ������������					 	 */
/* --------------------------------------------------------- */

// ������ �����������
// ���������������� ������ ������
TEST(Constuctors, EmptyConstructor) {
	CardDeckClass::CardDeck deck;
	EXPECT_EQ(10, deck.GetMaxSize());
	EXPECT_EQ(0, deck.GetCurrentSize());
	for (int i = 0; i < deck.GetCurrentSize(); i++) {
		EXPECT_EQ('0', deck[i + 1]);
		EXPECT_EQ('0', deck(i + 1));
	}
}


// ���������������� ����������� � �������� ���������� ����, ����� � ���� ������� ������������ ��������
TEST(Constructors, DefaultConstructor1) {
	CardDeckClass::CardDeck deck(36, 6);
	EXPECT_EQ(36, deck.GetMaxSize());
	EXPECT_EQ(6, deck.GetCurrentSize());
	for (int i = 0; i < deck.GetCurrentSize(); ++i) {
		EXPECT_LE(49, deck[i + 1]);
		EXPECT_GE(61, deck[i + 1]);
		EXPECT_LE(49, deck(i + 1));
		EXPECT_GE(52, deck(i + 1));
	}
}

// ���������������� ����������� � �������� ���������� ����, ����� � ���� ������� ������������ ��������
// ������������ ���������� ��� n > SZ
TEST(Constructors, DefaultConstructor1_Exception) {
	EXPECT_ANY_THROW(CardDeckClass::CardDeck deck(36, 37));
}


// ���������������� ����������� � ��������� �������������� ����� �����
TEST(Constructors, DefaultConstructor2) {
	CardDeckClass::CardDeck deck(6, 61, 49);
	EXPECT_EQ(6, deck.GetMaxSize());
	EXPECT_EQ(1, deck.GetCurrentSize());
	EXPECT_EQ(61, deck[1]);
	EXPECT_EQ(49, deck(1));
}

// ���������������� ����������� � ��������� �������������� ����� �����
// ������������ ���������� ��� ������������ ����� ����� ��� �����
TEST(Constructors, DefaultConstructors2_Exception) {
	EXPECT_ANY_THROW(CardDeckClass::CardDeck deck(6, 62, 49));
}


// �������� ���������� ������ � ��� �������������� ������ ����������� ������ (���������� �����������)
TEST(Constructors, CopyConstructor) {
	CardDeckClass::CardDeck copy(36, 6);
	CardDeckClass::CardDeck deck(copy);
	EXPECT_EQ(deck.GetMaxSize(), copy.GetMaxSize());
	EXPECT_EQ(deck.GetCurrentSize(), copy.GetCurrentSize());
	for (int i = 0; i < deck.GetCurrentSize(); ++i) {
		EXPECT_EQ(deck[i + 1], copy[i + 1]);
		EXPECT_EQ(deck(i + 1), copy(i + 1));
	}
}


/* --------------------------------------------------------- */
/*				      ������� - set'����					 */
/* --------------------------------------------------------- */

// ���������� ����� ����� � ������ (������������� ���������� �������� "++")
TEST(Setters, _operatorPlusPlus) {
	CardDeckClass::CardDeck deck(10, 4);
	++deck;
	EXPECT_EQ(5, deck.GetCurrentSize());
	EXPECT_LE(49, deck[5]);
	EXPECT_GE(61, deck[5]);
	EXPECT_LE(49, deck(5));
	EXPECT_GE(52, deck(5));
}

// ���������� ����� ����� � ������ (������������� ���������� �������� "++")
// ������ ���������� ������� ����
TEST(Setters, _operatorPlusPlus_Quota) {
	CardDeckClass::CardDeck deck(12, 12);
	++deck;
	EXPECT_EQ(22, deck.GetMaxSize());
	EXPECT_LE(49, deck[13]);
	EXPECT_GE(61, deck[13]);
	EXPECT_LE(49, deck(13));
	EXPECT_GE(52, deck(13));
}

// ���������� �� ������� ����
TEST(Setters, Sorting) {
	CardDeckClass::CardDeck deck(36, 36);
	deck.DefaultSort();
	for (int i = 0; i < deck.GetCurrentSize() - 1; i++) {
		EXPECT_LE(deck(i + 1), deck(i + 2));
		if (deck(i + 1) == deck(i + 2))
			EXPECT_LE(deck[i + 1], deck[i + 2]);
	}
}