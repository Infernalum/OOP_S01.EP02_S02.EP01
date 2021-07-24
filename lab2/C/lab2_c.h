#ifndef LAB2_C_H_
#define LAB2_C_H_

#include <QCoreApplication>
#include <QTextCodec>
#include <QTextStream>
#include "../CardDeckLib_c/carddecklib_c.h"

extern const int NMsgs;

// Вывод русского текста в консоль QT
void qtConsole(const QString&);

namespace Lab2_C {

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

}  // namespace Lab2_C

#endif  // !LAB2_C_H
