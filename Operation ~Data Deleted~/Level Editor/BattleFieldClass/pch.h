// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include <cstdio>
#include <iostream>
#include <exception>
#include <string>
#include <limits>
#include <vector>
#include <list>
#include <locale>
#include <map>


#include "Creature.h"
#include "Chryssalid.h"
#include "Item.h"
#include "Table.h"
#include "ConstTableIt.h"
#include "AmmoBox.h"
#include "Cell.h"
#include "Level.h"

#endif //PCH_H
