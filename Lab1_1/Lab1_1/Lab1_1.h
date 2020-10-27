#ifndef HEADER_LAB1_H
#define HEADER_LAB1_H

#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

extern const int NMsgs;

namespace Lab1 {

	/****************************************************************************************/
	/*		    	Необходимые структуры для описания сильно разряженной матрицы			*/
	/****************************************************************************************/

	// Структура "не пустой" строки матрицы (т. е. в которой есть хотя бы один не нулевой элемент), в которой хранятся только не нулевые элементы этой строки
	struct RowOfSparseMatrix {
		int val;						// Значение элемента
		int j;							// j-тый индекс элемента (номер столбца)
		RowOfSparseMatrix* next;		// Указатель на следующий не нулевой элемент данной строки
	};


	/* Структура списка строк матрицы */
	struct SparseMatrixRowList {
		int i;							// Номер текущей строки
		SparseMatrixRowList* next;		// Указатель на следующую ненулевую строку
		RowOfSparseMatrix* row;			// Указатель на текущую строку
	};


	/* Структура сильно разряженной матрицы - хранит размер матрицы и указатель на список строк */
	struct SparseMatrix {
		int m;							// Кол-во строк матрицы
		int n;							// Кол-во столбцов матрицы
		SparseMatrixRowList* Rowlist;	// Указатель на список не пустых строк
	};

	/****************************************************************************************/
	/*								Прототипы функций										*/
	/****************************************************************************************/

	int getInt(int&);								// Функция ввода целого числа (1 в случае неудачи, и 0 при успехе)
	void Input(SparseMatrix&);						// Ввод размера матрицы
	int dialog(const char* msgs[], int N);			// Организация диалога
	int D_Add(SparseMatrix*);						// Диалоговая функция добавления ненулевого элемента в матрицу
	void AddNewRow(SparseMatrix*, int, int, int);	// Функция добавления новой строки-списка в матрицу по возрастанию
	void AddToRow(RowOfSparseMatrix**, int, int);	// Функция добавления нового не нулевого элемента в строку-список по возрастанию
	int D_Show(SparseMatrix*);						// Функция вывода матрицы
	SparseMatrix* CreateNewMatrix(SparseMatrix *);	// Функция создания новой матрицы
	int ChangeV1(int);								// 1 функция преобразования (число записано задом наперед)
	int ChangeV2(int);								// 2 функция преобразования (число переведено в 16-ричную СЧ)
	int ChangeV3(int);								// 3 функция преобразования (из числа вычтена сумма его цифр, умноженная на последнюю цифру)
	void Delete(SparseMatrix*);						// Функция удаления матрицы


}

#endif // HEADER_LAB1_H
