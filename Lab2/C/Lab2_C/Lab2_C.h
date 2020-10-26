#ifndef LAB2_C_H_
#define LAB2_C_H_

#include "CardDeckLin"

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


#endif // !LAB2_C_H
