#include <QCoreApplication>
#include "lab2_c.h"

extern const char* msgs[];

int (*fptr[])(CardDeckClass::CardDeck&) = {NULL,
                                           Lab2_C::D_GetDeck,
                                           Lab2_C::D_AddNewCard,
                                           Lab2_C::D_GetCurrentCard,
                                           Lab2_C::D_Sort,
                                           Lab2_C::D_ChooseSuit};

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  qtConsole(
      "Добро пожаловать в тестирующую программу для класса "
      "\"Карточная колода\" ");
  // CardDeckClass::CardDeck p1(10, 5);
  // std::cout << p1;
  // CardDeckClass::CardDeck p2(p1);
  // std::cout << p2;
  CardDeckClass::CardDeck deck = Lab2_C::Input();
  int rc;
  while (rc = Lab2_C::dialog(msgs, NMsgs))
    if (!fptr[rc](deck))
      break;

  return a.exec();
}
