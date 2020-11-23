#include "Cipher.h"
#include <Windows.h>
#include <ctime>

extern const char* msgs[];

int (*fptr[])() = { nullptr, Cipher::cipherProcess, Cipher::decipherProcess };


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	srand(time(nullptr));
	int rc;
	while (rc = Cipher::dialog(msgs, NMsgs))
		if (!fptr[rc]())
			break;
	return 0;
}