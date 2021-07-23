

#include "lab1_2.h"
#include <iomanip>

const char* msgs[] = {
    "0. Выйти\n",
    "1. Ввести новые координаты вершины\n",
    "2. Ввести новые границы цепи\n",
    "3. Вернуть ординату цепной линии по значению абсциссы\n",
    "4. Вернуть длину дуги цепной линии от ее проекции на оси абсцисс\n",
    "5. Вернуть радиус кривизны цепной линии относительно координаты по оси"
    "абсцисс\n",
    "6. Вернуть координаты центра кривизны цепной линии в декартовой системе"
    "координат относительно координаты по оси абсцисс\n",
    "7. Вернуть площадь криволинейной трапеции, образованной цепной линией и "
    "ее проекцией на ось абсцисс (длина проекции = разности абсцисс границ)\n"};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

void qtConsole(const QString& str) {
  QTextStream outStream(stdout);
  outStream.setCodec(QTextCodec::codecForName("cp866"));
  outStream << QString(str) << flush;
}

namespace Lab1_2 {

// Просто за(кря)бался одно и то же писать
void input_Type(Type& p) {
  while (Lab1_2::getNum(p))
    qtConsole("Пожалуйста, введите корректное число: --> ");
}

// Первая инициализация состояни класса "Цепная линия"
Class::Catenary Input() {
  Class::Point p;
  qtConsole("Введите абсциссу вершины цепи: --> ");
  input_Type(p.x);
  while (1) {
    qtConsole("Введите ординату вершины цепи (строго положительна): --> ");
    input_Type(p.y);
    try {
      Class::Catenary line(p, 0, 0);
      Type x1, x2;
      qtConsole("Введите абсциссу первой границы цепи: --> ");
      input_Type(x1);
      qtConsole("Введите абсциссу второй границы цепи: --> ");
      input_Type(x2);
      line.setL(x1, x2);
      return line;
    } catch (const std::exception& ex) {
      qtConsole(ex.what());
      std::cout << std::endl;
    }
  }
}

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
  } while (getNum(rc) < 0 || rc >= N);
  return rc;
}

// Получение информации о состоянии класса
int D_GetStatus(const Class::Catenary& line) {
  qtConsole(
      "-----------------------------------------------\nТекущее "
      "состояние класса: \n");
  qtConsole("Координаты вершины: ");
  std::cout << std::fixed << std::setprecision(2) << line.getP().x << "/"
            << std::fixed << std::setprecision(2) << line.getP().y << ";\n";
  qtConsole("Координаты левой граничной точки: ");
  std::cout << std::fixed << std::setprecision(2) << line.getL_limit().x << "/"
            << std::fixed << std::setprecision(2) << line.getL_limit().y
            << ";\n";
  qtConsole("Координаты правой граничной точки: ");
  std::cout << std::fixed << std::setprecision(2) << line.getR_limit().x << "/"
            << std::fixed << std::setprecision(2) << line.getR_limit().y
            << ";\n-----------------------------------------------\n";
  return 1;
}

// "1. Ввести новые координаты вершины"
int D_SetVertex(Class::Catenary& line) {
  Class::Point p;
  qtConsole("Введите абсциссу вершины цепи: --> ");
  input_Type(p.x);
  while (1) {
    qtConsole("Введите ординату вершины цепи (строго положительна): --> ");
    input_Type(p.y);
    try {
      line.setP(p);
      qtConsole("Вершина цепи успешно изменена\n");
      return 1;
    } catch (const std::exception& ex) {
      qtConsole(ex.what());
      std::cout << std::endl;
    }
  }
}

// "2. Ввести новые границы цепи"
int D_SetBorders(Class::Catenary& line) {
  Type x1, x2;
  qtConsole("Введите абсциссу первой границы цепи: --> ");
  input_Type(x1);
  qtConsole("Введите абсциссу второй границы цепи: --> ");
  input_Type(x2);
  line.setL(x1, x2);
  return 1;
}

// "3. Вернуть ординату цепной линии по значению абсциссы",
int D_GetOrdinate(Class::Catenary& line) {
  Type x;
  qtConsole("Введите значение абсциссы: --> ");
  input_Type(x);
  qtConsole("Координаты точки, пренадлежащей цепи с выбранной абсциссой: ");
  std::cout << std::fixed << std::setprecision(2) << x << "/" << std::fixed
            << std::setprecision(2) << line.ordinate(x) << ";\n";
  return 1;
}

// "4. Вернуть длину дуги цепной линии от ее проекции на оси абсцисс"
int D_GetLength(Class::Catenary& line) {
  qtConsole(
      "Длина дуги цепной линии от ее проекции на оси абсцисс между "
      "граничными точками: ");
  std::cout << line.length() << "\n";
  return 1;
}

// "5. Вернуть радиус кривизны цепной линии относительно координаты по оси
// абсцисс"
int D_GetRadius(Class::Catenary& line) {
  Type x;
  qtConsole("Введите значение абсциссы: --> ");
  input_Type(x);
  qtConsole(
      "Радиус кривизны цепной линии относительно координаты по оси абсцисс: ");
  std::cout << std::fixed << std::setprecision(2) << line.radius(x) << ";\n";
  return 1;
}

// "6. Вернуть координаты центра кривизны цепной линии в декартовой системе
// координат относительно координаты по оси абсцисс"
int D_GetCenter(Class::Catenary& line) {
  Type x;
  qtConsole("Введите значение абсциссы: --> ");
  input_Type(x);
  Class::Point center = line.center(x);
  qtConsole(
      "Координаты центра кривизны цепной линии в декартовой системе "
      "координат относительно координаты по оси абсцисс: ");
  std::cout << std::fixed << std::setprecision(2) << center.x << "/"
            << std::fixed << std::setprecision(2) << center.y << ";\n";
  return 1;
}

//"7. Вернуть площадь криволинейной трапеции, образованной цепной линией и ее
//проекцией на ось абсцисс (длина проекции = разности абсцисс границ)"
int D_GetArea(Class::Catenary& line) {
  qtConsole(
      "Площадь криволинейной трапеции, образованной цепной линией и ее "
      "проекцией на ось абсцисс (длина проекции = разности абсцисс границ): ");
  std::cout << std::fixed << std::setprecision(2) << line.area() << ";\n";
  return 1;
}

}  // namespace Lab1_2
