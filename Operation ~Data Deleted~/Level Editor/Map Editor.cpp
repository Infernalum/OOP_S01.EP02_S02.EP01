#include "Map Editor.h"

extern const int numCr, numMenu;

namespace Editor {

	// ������ ������������� (������� ������� ����� � ��������� ���� ������)
	XCom::Level Initialization() {
		Level lvl;
		short n, m;
		while (true) {
			try {
				system("cls");
				std::cout << "������� ����� ����� (� ��������): ";
				inputType(n, std::cin, std::cout);
				std::cout << "������� ������ ����� (� ��������): ";
				inputType(m, std::cin, std::cout);
				lvl.set_proportions(n, m);
				break;
			}
			catch (const std::exception& ex) {
				std::cout << ex.what() << '\n';
			}
		}
		int rc = 0;
		std::cout << "������� ������ ����� �������������� (1), ��� ������ ������������� � ����� ���� (2)?\n --> ";
		do
			inputType(rc, std::cin, std::cout);
		while (rc < 1 || rc > 2);
		if (rc == 1) {
			std::cout << "������� �����:\n";
			inputType(lvl, std::cin, std::cout);
			std::cout << "������� �����:\n" << lvl;
		}
		return lvl;
	}


	/*
	���� ���������:
	1) �������� ������ (�������� ��� ������, �������� ������� �� ������, ������� ������� � ������)
	2) �������� ����� ��������;
	3) �������� �����-����������;
	*/
	int Menu(Level& lvl) {
		getState(lvl);
		int rc = 0;
		std::cout << "�������� ��������:\n 1 - �������� ������ (�������� ���, ��������/������� ��������, �������� �������);\n 2 - �������� ����� ��������;\n 3 - �������� �����-�� �������� (�������� ���-��, �����������, �������);\n 0 - �����;\n --> ";
		do
			inputType(rc, std::cin, std::cout);
		while (rc > 3 || rc < 0);
		switch (rc) {
		case 0:
			return rc;
			break;
		case 1:
			changeCell(lvl);
			break;
		case 2:
			createCreature(lvl);
			break;
		case 3:
			changeCreature(lvl);
			break;
		}
		system("cls");
		return rc;
	}


	// ��������� ������
	void changeCell(Level& lvl) {
		int rc;
		int x, y, type;
		while (true) {
			std::cout << "������� ���������� x ������: ";
			inputType(x, std::cin, std::cout);
			std::cout << "������� ���������� y ������: ";
			inputType(y, std::cin, std::cout);
			std::cout << "��������:\n 1 - �������� ��� ������;\n 2 - ��������/��������/������� �������;\n 0 - ��������� � ����;\n --> ";
			do
				inputType(rc, std::cin, std::cout);
			while (rc < 0 || rc > 2);
			switch (rc) {
			case 0:
				break;
			case 1:
				try {
					std::cout << "�������� ��� ������: \n 1: ���;\n 2: �����;\n 3: ������;\n 4: �����������;\n 5: ��������� �����;\n --> ";
					inputType(type, std::cin, std::cout);
					lvl.set_cell(x, y, type);
					getState(lvl);
					std::cout << lvl;
				}
				catch (const std::exception& ex) {
					std::cout << ex.what() << '\n';
				}
				break;
			case 2:
				break;
			}
		}
	}


	// �������� ������ �������� � �������� ��� � ����
	void createCreature(Level& lvl) {
		Creature* ptr = nullptr;
		//ptr = answer_1(Cr, numCr, ptr);
		if (!ptr)
			return;
		//int ans_2 = answer_2(ptr, lvl);
		/*while (ans_3 != 3) {
			std::cout << "������ �������� ��������������, �������� ������� ���� ��������:\n";
			switch (ans) {
			case 1:
				std::cout << " 1 - ���� � ������� ���;\n 2 - ��������� �����;\n 3 - ������� ������;\n 0 - ������� �������� � ����� � ������� ����;\n";
				int i;
				do
					inputType(i, std::cin, std::cout);
				while (i < 0 || i > 3);
				switch (i) {
				case 1:
					try {
						ptr->set_damage(5);
						close(lvl);
						std::cout << "���� �������� ������� ��������.\n";
					}
					catch (const std::exception& ex) {
						close(lvl);
						std::cout << ex.what() << '\n';
					}
					break;
				case 2:


				}*/
				//}
	}


	// ����� ��������
	/*Creature* answer_1(const std::string msgs[], int N, Creature* ptr, Level& lvl) {
		getState(lvl);
		std::cout << "����������, �������� ��� ��������:\n";
		for (int i = 0; i < N; ++i)
			std::cout << msgs[i] << '\n';
		std::cout << " --> ";
		int ans;
		do
			inputType(ans, std::cin, std::cout);
		while (ans < 0 || ans > N);
		switch (ans) {
		case 0:
			ptr = nullptr;
			break;
		case 1:
			ptr = new Chryssalid;
			break;

		}
		return ptr;
	}*/

	// ��������� ������� ������������� �������� (1 - ���� ������; 0 - ������� ��������)
	int answer_2(Creature* ptr, Level& lvl) {
		int ans;
		std::cout << "������� " << *ptr << "\n �������� ������� ��������������:\n 1 - �������� ��������;\n 2 - �������� ���� �������;\n 3 - �������� ������ ������;\n 4 - ������� ������;\n 0 - ������� �������� � ��������� � ����;\n --> ";
		do inputType(ans, std::cin, std::cout);
		while (ans < 0 || ans > 4);
		if (!ans) {
			delete ptr;
			system("cls");
			return ans;
		}
		if (ans == 4)
			return 1;
		std::cout << "������� ����� �������� ���������: --> ";
		int par;
		inputType(par, std::cin, std::cout);
		switch (ans) {
		case 1:
			try {
				ptr->set_maxHP(par);
				close(lvl);
				std::cout << "�������������� �������� ������� ��������.\n";
			}
			catch (const std::exception& ex) {
				close(lvl);
				std::cout << ex.what() << '\n';
			}
			break;
		case 2:
			try {
				ptr->set_maxTP(par);
				close(lvl);
				std::cout << "�������������� �������� ������� ��������.\n";
			}
			catch (const std::exception& ex) {
				close(lvl);
				std::cout << ex.what() << '\n';
			}
			break;
		case 3:
			try {
				ptr->set_sight(par);
				close(lvl);
				std::cout << "�������������� �������� ������� ��������.\n";
			}
			catch (const std::exception& ex) {
				close(lvl);
				std::cout << ex.what() << '\n';
			}
			break;
		}
		return ans;
	}


	// ��������� ��������
	void changeCreature(Level& lvl) {


	}


	// ��������� ������ ���������� �� �����
	void getState(const Level& lvl) {
		std::cout << "���� �����:\n" << lvl << '\n';


	}


	void close(Level& lvl) {
		system("cls");
		getState(lvl);
	}


}