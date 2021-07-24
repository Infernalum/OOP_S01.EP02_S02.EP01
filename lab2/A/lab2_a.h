#ifndef LAB2_A_H_
#define LAB2_A_H_

#include <../CardDeckLib_a_b/carddecklib_a_b.h>
#include <QCoreApplication>
#include <QTextCodec>
#include <QTextStream>

extern const int NMsgs;

// Вывод русского текста в консоль QT
void qtConsole(const QString&);

namespace Lab2_B {

// Первая инициализация деки
CardDeckClass::CardDeck Input();

// Организация диалога
int dialog(const char* msgs[], int);

// Вывод текущей деки
int D_GetDeck(CardDeckClass::CardDeck&);

// Добавить карту колоде, значение которой получается с помощью генератора
// случайных чисел
int D_AddNewCard(CardDeckClass::CardDeck&);

// Получить масть и ранг карты по ее номеру в колоде
int D_GetCurrentCard(CardDeckClass::CardDeck&);

// Упорядочить карты по масти и убыванию ранга
int D_Sort(CardDeckClass::CardDeck&);

// Выделить из колоды подгруппу карт заданной масти
int D_ChooseSuit(CardDeckClass::CardDeck&);

}  // namespace Lab2_B

#endif  // !LAB2_A_H
