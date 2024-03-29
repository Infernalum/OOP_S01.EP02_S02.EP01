// Определение класса "Цепная линия"

#ifndef _CATENARY_H_
#define _CATENARY_H_

#include <math.h>
#include <string>

typedef double Type;

namespace Class {

// Структура точки на плоскости (конкретно для данного класса)
struct Point {
  Type x, y;
  Point()
      : x(0),
        y(1){};  // Пустой конструктор, который задает точку координатами (0,1)
  Point(Type x0, Type y0)
      : x(x0), y(y0){};  // Инициализирующий конструктор, который не ПРИСВАЕВАЕТ
                         // значения, если вызван по умолчанию, а ИНИЦИАЛИЗИРУЕТ
                         // переменные при создании
  bool check() const;  // Функция проверки корректности введенной вершины
};

// Класс "Цепная линия". Задается вершиной цепи. Параметр равен смещению вершины
// относительно начала координат по Oy (Ограничение: > 0).
class Catenary {
 private:
  Point p;        // Координаты вершины
  Point l_limit;  // Левая граница цепи (Задается абсцисса, затем считается
                  // ордината)
  Point r_limit;  // Правая граница цепи (Границы нужны для п.4, 7)
 public:
  Catenary()
      : p(0, 1),
        l_limit(0, 1),
        r_limit(0, 1){};  // Пустой конструктор; по умолчанию определяет цепь с
                          // вершиной в точке (0,1)
  Catenary(const Point&,
           Type,
           Type);  // Инициализирующий конструктор (без доп иниц. конструкторов)
  // Сеттеры - set'теры
  // Сеттер возвращает ссылку на обьект для возможности последовательного
  // доступа и копирующего конструктора
  void setP(const Point& p0);  // Сеттер для задания вершины цепи
  Catenary& setL(Type, Type);  // Сеттер для задания границ
  // Геттеры - get'теры (чисто для тестирования)
  // const обусловлен тем, что геттеры являются разновидностью селекторов и НЕ
  // изменяют состояние объекта
  Point getP() const { return p; };
  Point getL_limit() const { return l_limit; };
  Point getR_limit() const { return r_limit; };
  // Другие методы
  Type ordinate(
      Type) const;  // Возвращает значение ординаты по значению абсциссы
  Type length()
      const;  // п.4: длина дуги цепной линии от ее проекции на оси абсцисс
  Type radius(Type) const;  // п.5: радиус кривизны цепной линии относительно
                            // координаты по оси абсцисс
  Point center(Type) const;  // п.6: координаты центра кривизны цепной динии в
                             // ДСК относительно координаты по оси абсцисс
  Type area() const;  // п.7: площадь криволинейной трапеции, образованной
                      // цепной линией и ее проекцией на ось абсцисс
  ~Catenary(){};      // Деструктор по умолчанию
};

}  // namespace Class

#endif  // !_CATENARY_H_
