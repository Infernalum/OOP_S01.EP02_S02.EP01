#ifndef LAB2_B_H_
#define LAB2_B_H_

#include "CardDeckLib.h"

extern const int NMsgs;

namespace Lab2_A {

	// ������ ������������� ����
	CardDeckClass::CardDeck Input();

	// ����������� �������
	int dialog(const char* msgs[], int);

	// ����� ������� ����
	int D_GetDeck(CardDeckClass::CardDeck&);

	// �������� ����� ������, �������� ������� ���������� � ������� ���������� ��������� �����
	int D_AddNewCard(CardDeckClass::CardDeck&);

	// �������� ����� � ���� ����� �� �� ������ � ������
	int D_GetCurrentCard(CardDeckClass::CardDeck&);

	// ����������� ����� �� ����� � �������� �����
	int D_Sort(CardDeckClass::CardDeck&);

	// �������� �� ������ ��������� ���� �������� �����
	int D_ChooseSuit(CardDeckClass::CardDeck&);

}


#endif // !LAB2_A_H


