#include "lab1_1.h"

const char* msgs[] = {
    "0. Выйти\n",
    "1. Добавить не нулевой элемент (в случае существования)\n"
    "элемента с такими индексами, значение перезаписывается)\n",
    "2. Вывести исходную матрицу и соотвествующий ей вектор\n"};

const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);

const int SZ = 4;

namespace Lab1 {

void qtConsole(const QString& str) {
  QTextStream outStream(stdout);
  outStream.setCodec(QTextCodec::codecForName("cp866"));
  outStream << QString(str) << flush;
}

// Функция ввода целого числа
int getInt(int& a) {
  int rc = 0;
  cin >> a;
  if (!cin.good())
    rc = 1;  // Обнаружена ошибка ввода
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return rc;
}

// Выбор номера альтернативы
int dialog(const char* msgs[], int N) {
  const char* errmsgs = "";
  int rc, i;
  do {
    qtConsole(errmsgs);
    errmsgs = "Ошибка! Повторите ввод:!";
    for (i = 0; i < N; ++i)  // Вывод списка альтернатив
      qtConsole(msgs[i]);
    qtConsole("Выберите: --> ");
  } while (getInt(rc) < 0 || rc >= N);
  return rc;
}

// Функция ввода кол-ва строк и столбцов
void Input(SparseMatrix& matrix) {
  const char* em =
      "Неверное число (Число должно быть натуральным). Попробуйте еще "
      "раз:\n--> ";  // Будущее сообщение об ошибке
  qtConsole("Введите кол-во строк: --> ");
  while (getInt(matrix.m) ||
         (matrix.m < 1))  // Обнаружена ошибка ввода или конец файла
    qtConsole(em);
  qtConsole("Введите кол-во столбцов: --> ");
  while (getInt(matrix.n) ||
         (matrix.n < 1))  // Обнаружена ошибка ввода или конец файла
    qtConsole(em);
}

//Функция добавления новой строки-списка в матрицу по возрастанию
void AddNewRow(SparseMatrix* matrix, int i, int j, int val) {
  SparseMatrixRowList* Rows = matrix->Rowlist;  // Указатель на список строк
  /* 1 случай: список пуст */
  if (!matrix->Rowlist) {
    matrix->Rowlist = new SparseMatrixRowList();
    matrix->Rowlist->i = i;
    matrix->Rowlist->next = nullptr;
    matrix->Rowlist->row = nullptr;
    AddToRow(&(matrix->Rowlist->row), j, val);
  } else {
    /* Перемещаем указатель на тот элемент, который будет стоять после нового*/
    while (Rows && (i > Rows->i))
      Rows = Rows->next;
    /* 2 случай: Такая строка уже существует. Тогда добавляем элемент в данный
     * список */
    if (Rows && (i == Rows->i))
      AddToRow(&(Rows->row), j, val);
    else {
      SparseMatrixRowList* NewElem = new SparseMatrixRowList();
      NewElem->i = i;
      NewElem->row = nullptr;
      SparseMatrixRowList* RowsPrev = matrix->Rowlist;
      while ((RowsPrev->next != Rows) && (RowsPrev != Rows))
        RowsPrev = RowsPrev->next;
      /* 3 случай: элемент добавляется в начало */
      if (RowsPrev == Rows) {
        matrix->Rowlist = NewElem;
        NewElem->next = Rows;
        AddToRow(&(matrix->Rowlist->row), j, val);
      }
      /* 4 случай: обычное добавление */
      else {
        NewElem->next = Rows;
        RowsPrev->next = NewElem;
        AddToRow(&(NewElem->row), j, val);
      }
    }
  }
}

// Функция добавления нового не нулевого элемента в строку-список по возрастанию
void AddToRow(RowOfSparseMatrix** row, int j, int val) {
  /* Проверка существования ненулевого элемента с такими индексами */
  RowOfSparseMatrix* tmp = *row;
  while (tmp) {
    if (tmp->j == j) {
      tmp->val = val;
      return;
    }
    tmp = tmp->next;
  }
  tmp = *row;
  /* 1 случай: список пуст */
  if (!tmp) {
    (*row) = new RowOfSparseMatrix();
    (*row)->j = j;
    (*row)->val = val;
    (*row)->next = nullptr;
  } else {
    /* Перемещаем указатель на тот элемент, который будет стоять после нового*/
    while (tmp && (j > tmp->j))
      tmp = tmp->next;
    /* 2 случай: если элемент с такими индексами уже есть */
    if (tmp && (j == tmp->j))
      tmp->val = val;
    else {
      RowOfSparseMatrix* NewElem = new RowOfSparseMatrix();
      NewElem->j = j;
      NewElem->val = val;
      NewElem->next = nullptr;
      RowOfSparseMatrix* tmpPrev = (*row);
      while ((tmpPrev->next != tmp) && (tmpPrev != tmp))
        tmpPrev = tmpPrev->next;
      /* 3 случай: элемент добавляется в начало */
      if (tmpPrev == tmp) {
        (*row) = NewElem;
        NewElem->next = tmp;
      }
      /* 4 случай: обычное добавление */
      else {
        NewElem->next = tmp;
        tmpPrev->next = NewElem;
      }
    }
  }
}

// Функция добавления нового ненулевого элемента в матрицу
int D_Add(SparseMatrix* matrix) {
  int i, j, val;
  const char* em =
      "Неверный индекс (Число должно быть натуральным и не выходящим за "
      "границы массива). Попробуйте еще раз:\n --> ";
  qtConsole("Введите индекс строки: --> ");
  while ((getInt(i) < 0) || (i >= matrix->m))
    qtConsole(em);
  qtConsole("Введите индекс столбца: --> ");
  while ((getInt(j) < 0) || (j >= matrix->n))
    qtConsole(em);
  qtConsole("Введите значение элемента: --> ");
  while ((getInt(val) < 0) || (!val))
    qtConsole(
        "Ошибка ввода (Число должно быть целым и отличным от нуля). "
        "Попробуйте еще раз:\n --> ");
  AddNewRow(matrix, i, j, val);
  return 1;
}

// Функция вывода матрицы и создания вектора
int D_Show(SparseMatrix* matrix) {
  SparseMatrixRowList* Row = matrix->Rowlist;
  /* Для каждой строки */
  for (int i = 0; i < matrix->m; ++i) {
    if (Row && Row->i == i) {
      RowOfSparseMatrix* now = Row->row;
      for (int j = 0; j < matrix->n; ++j) {
        if (now && now->j == j) {
          cout << setw(4) << right << now->val;
          now = now->next;
        } else
          cout << "   0";
      }
      cout << endl;
      Row = Row->next;
    } else {
      for (int j = 0; j < matrix->n; ++j) {
        cout << "   0";
      }
      cout << endl;
    }
  }
  SparseMatrix* ResultMatrix = CreateNewMatrix(matrix);
  return 1;
}

// 1 функция преобразования (число записано в обратном порядке)
int ChangeV1(int a) {
  int cur = 0, dg = 0, res = 0;
  // Нахождение разряда числа
  cur = a;
  while (cur) {
    cur /= 10;
    dg++;
  }
  do {
    cur = a % 10;
    // Нахождение степени
    int dec = 1;
    for (int i = 1; i < dg; ++i)
      dec *= 10;
    res += dec * cur;
    a /= 10;
    --dg;
  } while (a);
  return res;
}

// 2 функция преобразования (число переведено в 8-ричную СЧ)
int ChangeV2(int a) {
  int cur = 0, dg = 1, res = 0;
  do {
    cur = a % 8;
    res += (cur * dg);
    dg *= 10;
    a /= 8;
  } while (a);
  return res;
}

// 3 функция преобразования (из числа вычтена сумма его цифр, умноженная на
// последнюю цифру)
int ChangeV3(int a) {
  int sum = 0, dup = a, last = a % 10;
  do {
    sum += (dup % 10);
    dup /= 10;
  } while (dup);
  return (a - sum * last);
}

SparseMatrix* CreateNewMatrix(SparseMatrix* matrix) {
  SparseMatrix* ResultMatrix =
      new SparseMatrix;  // Результирующая разряженная матрица
  ResultMatrix->m = matrix->m;
  ResultMatrix->n = matrix->n;
  ResultMatrix->Rowlist = nullptr;
  SparseMatrixRowList* rows = matrix->Rowlist;
  while (rows) {
    RowOfSparseMatrix* now = rows->row;
    while (now) {
      AddNewRow(ResultMatrix, rows->i, now->j, ChangeV3(now->val));
      now = now->next;
    }
    rows = rows->next;
  }
  // Вывод результирующей матрицы
  cout << endl << endl;
  rows = ResultMatrix->Rowlist;
  for (int i = 0; i < matrix->m; ++i) {
    if (rows && rows->i == i) {
      RowOfSparseMatrix* now = rows->row;
      for (int j = 0; j < matrix->n; ++j) {
        if (now && now->j == j) {
          cout << setw(SZ) << right << now->val;
          now = now->next;
        } else
          cout << setw(SZ) << right << "0";
      }
      cout << endl;
      rows = rows->next;
    } else {
      for (int j = 0; j < matrix->n; ++j) {
        cout << setw(SZ) << right << "0";
      }
      cout << endl;
    }
  }
  return ResultMatrix;
}

// Функция удаления
void Delete(SparseMatrix* matrix) {
  SparseMatrixRowList* rows = matrix->Rowlist;
  while (rows) {
    matrix->Rowlist = matrix->Rowlist->next;
    RowOfSparseMatrix* tmp = rows->row;
    while (tmp) {
      rows->row = rows->row->next;
      delete tmp;
      tmp = rows->row;
    }
    rows = matrix->Rowlist;
  }
}
}  // namespace Lab1
