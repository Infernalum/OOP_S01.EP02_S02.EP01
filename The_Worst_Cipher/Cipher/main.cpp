#include <QCoreApplication>

#include <Windows.h>
#include <ctime>

#include "cipher.h"

extern const char* msgs[];

int (*fptr[])() = {nullptr, Cipher::cipherProcess, Cipher::decipherProcess};

int main(int argc, char* argv[]) {
  QCoreApplication a(argc, argv);

  srand(time(nullptr));
  int rc;
  while (rc = Cipher::dialog(msgs, NMsgs))
    if (!fptr[rc]())
      break;
  return a.exec();
}
