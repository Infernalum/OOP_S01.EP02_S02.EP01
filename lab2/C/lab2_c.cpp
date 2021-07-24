#include "lab2_c.h"

const char* msgs[] = {"0. Выйти\n",
                      "1. Вывести колоду\n",
                      "2. Добавить карту к группе, значение которой получается "
                      "с помощью генератора случайных чисел\n",
                      "3. Получить масть и ранг карты по ее номеру в группе\n",
                      "4. Упорядочить карты по масти и убыванию ранга\n",
                      "5. Выделить из колоды подгруппу карт заданной масти\n"};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

void qtConsole(const QString& str) {
  QTextStream outStream(stdout);
  outStream.setCodec(QTextCodec::codecForName("cp866"));
  outStream << QString(str) << flush;
}

namespace Lab2_C {

// Выбор номера альтернативы
int dialog(const char* msgs[], int N) {
  const char* errmsgs = "";
  int rc, i;
  do {
    qtConsole(errmsgs);
    errmsgs = "Ошибка! Повторите ввод!";
    for (i = 0; i < N; ++i)  // Вывод списка альтернатив
      qtConsole(msgs[i]);
    qtConsole("Выберите: --> ");
  } while (CardDeckClass::getNum(rc, std::cin) < 0 || rc >= N);
  return rc;
}

// Первая инициализация деки
CardDeckClass::CardDeck Input() {
  qtConsole(
      "Пожалуйста, выберите способ инициализации Вашей колоды:\n1. "
      "Пустая колода\n2. Колода с n кол-вом случайных карт (число n "
      "задается пользователем)\n3. Колода с начальной инициализацией "
      "одной карты\n4. Ручное создание колоды (И ввод кол-ва карт, и "
      "их состояний, в случае необходимости)\n");
  int res;
  CardDeckClass::input_Type(res);
  while (res < 1 || res > 4) {
    qtConsole("Пожалуйста, выберите число от 1 до 4: ==> ");
    CardDeckClass::input_Type(res);
  }
  if (res == 1) {
    CardDeckClass::CardDeck* p = new CardDeckClass::CardDeck();
    qtConsole("Колода успешно инициализирована.\n");
    return *p;
  }
  if (res == 2) {
    while (true) {
      qtConsole(
          "Пожалуйста, введите максимальный (на данный момент) размер "
          "колоды: ==> ");
      int size;
      CardDeckClass::input_Type(size);
      qtConsole("Пожалуйста, введите кол-во карт в колоде: ==> ");
      int n;
      CardDeckClass::input_Type(n);
      try {
        CardDeckClass::CardDeck* p = new CardDeckClass::CardDeck(size, n);
        qtConsole("Колода успешно инициализирована.\n");
        return *p;
      } catch (const std::exception& ex) {
        qtConsole(ex.what());
        std::cout << std::endl;
      }
    }
  }
  if (res == 3) {
    qtConsole(
        "Пожалуйста, введите максимальный (на данный момент) размер "
        "колоды: ==> ");
    int size;
    CardDeckClass::input_Type(size);
    qtConsole(
        "Пожалуйста, выберите ранг карты: 2 - 10; либо 11 - Валет, 12 "
        "- Дама, 13 - Король, 14 - Туз: --> ");
    int rang;
    CardDeckClass::input_Type(rang);
    while (rang < 2 || rang > 14) {
      qtConsole("Пожалуйста, выберите существующий ранг: -->");
      CardDeckClass::input_Type(rang);
    }
    qtConsole(
        "Пожалуйста, выберите масть карты: 1 - Бубе, 2 - Черви, 3 - "
        "Пики, 4 - Крести: --> ");
    int suit;
    CardDeckClass::input_Type(suit);
    while (suit < 1 || suit > 4) {
      qtConsole("Пожалуйста, выберите существующую масть: -->");
      CardDeckClass::input_Type(suit);
    }
    CardDeckClass::CardDeck* p =
        new CardDeckClass::CardDeck(size, rang + 47, suit + 48);
    qtConsole("Колода успешно инициализирована.");
    return *p;
  } else {
    CardDeckClass::CardDeck* p = new CardDeckClass::CardDeck();
    while (true) {
      try {
        qtConsole(
            " 1 число: начальный максимальный размер колоды.\n 2 "
            "число: кол-во карт в колоде.\n Далее для каждой карты "
            "выберите\n-- > 1. Добавить случайную карту\n-- > 2. "
            "Ввести карту самостоятельно\n Если самостоятельно, то:\n "
            "ранг карты: 2 - 10; либо 11 - Валет, 12 - Дама, 13 - "
            "Король, 14 - Туз; \n масть карты: 1 - Бубе, 2 - Черви, 3 "
            "- Пики, 4 - Крести:\n --> \n");
        std::cin >> *p;
        qtConsole("Колода успешно инициализирована.\n");
        return *p;
      } catch (const std::exception& ex) {
        qtConsole(ex.what());
        std::cout << std::endl;
      }
    }
  }
}

// Вывод текущей деки
int D_GetDeck(CardDeckClass::CardDeck& deck) {
  std::cout << deck;
  return 1;
}

// Добавить карту колоде, значение которой получается с помощью генератора
// случайных чисел
int D_AddNewCard(CardDeckClass::CardDeck& deck) {
  ++deck;
  qtConsole("Случайная карта успешно добавлена");
  return 1;
}

// Получить масть и ранг карты по ее номеру в колоде
int D_GetCurrentCard(CardDeckClass::CardDeck& deck) {
  try {
    int card;
    qtConsole("Пожалуйста, введите номер карты из текущей колоды: --> ");
    CardDeckClass::input_Type(card);
    int suit = deck(card);
    int rang = deck[card];
    qtConsole("Ваша карта: ");
    qtConsole(CardDeckClass::CardDeck::Rangs[rang - 49]);
    std::cout << ' ';
    qtConsole(CardDeckClass::CardDeck::Suits[suit - 49]);
    std::cout << std::endl;
  } catch (const std::exception& ex) {
    qtConsole(ex.what());
    std::cout << std::endl;
  }
  return 1;
}

// Упорядочить карты по масти и убыванию ранга
int D_Sort(CardDeckClass::CardDeck& deck) {
  deck.DefaultSort();
  qtConsole("Колода успешно упорядочена.");
  return 1;
}

// Выделить из колоды подгруппу карт заданной масти
int D_ChooseSuit(CardDeckClass::CardDeck& deck) {
  int suit;
  while (true) {
    qtConsole(
        "Пожалуйста, выберите масть карты: 1 - Бубе, 2 - Черви, 3 - "
        "Пики, 4 - Крести  ==> ");
    CardDeckClass::input_Type(suit);
    try {
      CardDeckClass::CardDeck res = deck.GetSuitDeck(suit);
      qtConsole("Колода успешно выделена\n");
      std::cout << res;
      return 1;
    } catch (const std::exception& ex) {
      qtConsole(ex.what());
      std::cout << std::endl;
    }
  }
}
}  // namespace Lab2_C
