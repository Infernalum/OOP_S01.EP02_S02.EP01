#ifndef LAB2_B_H_
#define LAB2_B_H_

#include "CardDeckLib.h"

extern const int NMsgs;

namespace Lab2_A {

	// Первая инициализация деки
	CardDeckClass::CardDeck Input();

	// Организация диалога
	int dialog(const char* msgs[], int);

	// Вывод текущей деки
	int D_GetDeck(CardDeckClass::CardDeck&);

	// Добавить карту колоде, значение которой получается с помощью генератора случайных чисел
	int D_AddNewCard(CardDeckClass::CardDeck&);

	// Получить масть и ранг карты по ее номеру в колоде
	int D_GetCurrentCard(CardDeckClass::CardDeck&);

	// Упорядочить карты по масти и убыванию ранга
	int D_Sort(CardDeckClass::CardDeck&);

	// Выделить из колоды подгруппу карт заданной масти
	int D_ChooseSuit(CardDeckClass::CardDeck&);

}


#endif // !LAB2_A_H


