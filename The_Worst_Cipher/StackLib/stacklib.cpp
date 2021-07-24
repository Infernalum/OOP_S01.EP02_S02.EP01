#include "stacklib.h"
#include <string.h>
#include <stdexcept>

namespace StackClass {

std::istream& operator>>(std::istream& c, elem_of_stack& a) {
  std::cout << "Enter your key" << std::endl;
  c >> a.key;
  std::cout << "Enter your string" << std::endl;
  c >> a.str;
  return c;
}

Stack::Stack(elem_of_stack elem, int k) {
  top = 0;
  size = 0;
  for (int i = 0; i < (k / 10 + 1); i++)
    size += SZ;
  mas = new elem_of_stack[SZ];
  for (int i = 0; i < k; i++)
    mas[top++] = elem;
}

Stack::Stack(elem_of_stack* elem, int n) {
  top = 0;
  size = n;
  mas = new elem_of_stack[n];
  for (int i = 0; i < n; i++)
    mas[top++] = elem[i];
}

Stack::Stack(const Stack& a) {
  top = a.top;
  size = a.size;
  mas = new elem_of_stack[size];
  for (int i = 0; i < top; i++)
    mas[i] = a.mas[i];
}

Stack::Stack(Stack&& a) {
  top = a.top;
  size = a.size;
  mas = a.mas;
  a.mas = nullptr;
}

Stack& Stack::operator=(const Stack& a) {
  if (this != &a) {
    top = a.top;
    size = a.size;
    delete[] mas;
    mas = new elem_of_stack[size];
    for (int i = 0; i < top; i++)
      mas[i] = a.mas[i];
  }
  return *this;
}

Stack& Stack::operator=(Stack&& a) {
  int tmp = top;
  top = a.top;
  a.top = tmp;
  tmp = size;
  size = a.size;
  a.size = tmp;
  elem_of_stack* el = mas;
  mas = a.mas;
  a.mas = el;
  return *this;
}

std::istream& operator>>(std::istream& c, Stack& a) {
  elem_of_stack elem;
  c >> elem;
  if (a.top > a.size - 1) {
    a.size += a.SZ;
    elem_of_stack* old = a.mas;
    a.mas = new elem_of_stack[a.size];
    for (int i = 0; i < a.top; i++)
      a.mas[i] = old[i];
    delete[] old;
  }
  a += elem;
  return c;
}

std::ostream& operator<<(std::ostream& c, Stack& a) {
  if (a.top == 0)
    throw std::invalid_argument("Stack is empty");
  int g = a.top;
  while (--g >= 0) {
    elem_of_stack elem;
    elem = a.mas[g];
    c << elem;
  }
  return c;
}

Stack& Stack::operator+=(elem_of_stack& elem) {
  if (top >= size) {
    size += SZ;
    elem_of_stack* old = mas;
    mas = new elem_of_stack[size];
    for (int i = 0; i < size; i++)
      mas[i] = old[i];
    delete[] old;
  }
  mas[top++] = elem;
  return *this;
}

Stack& Stack::operator+=(const Stack& st) {
  Stack tmp(st);
  elem_of_stack el;
  while (tmp.top > 0) {
    tmp(el);
    *this += el;
  }
  return *this;
}

elem_of_stack& Stack::show_first() const {
  if (top == 0)
    throw std::invalid_argument("Stack is empty");
  return mas[top - 1];
}

Stack& Stack::operator()(elem_of_stack& elem) {
  if (top == 0)
    throw std::invalid_argument("Stack is empty");
  elem = mas[--top];
  return *this;
}

Stack& Stack::operator()(Stack& st) {
  elem_of_stack el;
  while (st.top > 0) {
    st(el);
    *this += el;
  }
  return *this;
}

int Stack::empty() const {
  if (!top)
    return 1;  // пуст
  else
    return 0;  // не пуст
}
}  // namespace StackClass
