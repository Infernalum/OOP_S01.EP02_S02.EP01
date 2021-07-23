#ifndef _LAB1_2_
#define _LAB1_2_

#include <QCoreApplication>
#include <QTextCodec>
#include <QTextStream>

#include <../CetaneryLib/cetanerylib.h>
#include <stdio.h>
#include <iostream>
#include <limits>

extern const int NMsgs;

// Вывод русского текста в консоль QT
void qtConsole(const QString&);

namespace Lab1_2 {

// Шаблон функции ввода числа (1 в случае неудачи, и 0 при успехе)
template <class T>
int getNum(T& a) {
  int rc = 0;
  std::cin >> a;
  if (!std::cin.good())
    rc = 1;  // Обнаружена ошибка ввода
  std::cin.clear();
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return rc;
};

// Прототипы остальных функций
Class::Catenary
Input();  // Первая инициализация состояния класса "Цепная линия"
int dialog(const char* msgs[], int N);  // Организация диалога
int D_GetStatus(
    const Class::Catenary&);  // Получение информации о состоянии класса "Цепная
                              // линия": коор-ты вершины и границ
// Диалоговые функции работы с классом "Цепная линия"
int D_SetVertex(Class::Catenary&);  // "1. Ввести новые координаты вершины"
int D_SetBorders(Class::Catenary&);  // "2. Ввести новые границы цепи"
int D_GetOrdinate(Class::Catenary&);  // "3. Вернуть ординату цепной линии по
                                      // значению абсциссы"
int D_GetLength(Class::Catenary&);  // "4. Вернуть длину дуги цепной линии от ее
                                    // проекции на оси абсцисс"
int D_GetRadius(Class::Catenary&);  // "5. Вернуть радиус кривизны цепной линии
                                    // относительно координаты по оси абсцисс"
int D_GetCenter(
    Class::Catenary&);  // "6. Вернуть координаты центра кривизны цепной линии в
                        // декартовой системе координат относительно координаты
                        // по оси абсцисс"
int D_GetArea(
    Class::Catenary&);  // "7. Вернуть площадь криволинейной трапеции,
                        // образованной цепной линией и ее проекцией на ось
                        // абсцисс (длина проекции = разности абсцисс границ)"

}  // namespace Lab1_2

#endif
