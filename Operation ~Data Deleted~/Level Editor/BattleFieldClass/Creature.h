#ifndef CREATURE_H
#define CREATURE_H


namespace XCom {


	/*
		������������ ����� �������. � ������� ������������ ���� �������������� ��� �������,
	� ��� ��������� ������ ���� �� ������ ���� �� ����� ���������� (�������� � ����, ����� ���������� � �������� ���������� �������� ��������)
	*/
	enum CreatureID {
		CREATUREID_OPERATIVE = -1,
		CREATUREID_PORTER,
		CREATUREID_CHRYSSALID,
		CREATUREID_MUTON,
	};


	// ������� ����������� ����� "��������"
	class Creature {

		// ���������� ������, �� ������� ����� ��������
		std::pair<int, int> coords;
		// ������� \ ������������ ���-�� ����� ��������
		int HP, maxHP;
		// �������� ��������� ��������: ������� ���� ��������� (����������� �� 0 - ��� ������, �� 100% - ��������� ���� � 2 ����)
		int evasion;
		// �������� �������� ��������: ����������, ����� ���� ������� ���� �� ������������ ����� �������. 0 - ������ ��� (��������), 100 - ������� ��������
		int accuracy;
		// ������� \ ������������ ���-�� ����� �������
		int TP, maxTP;
		// ������ ������ ��������
		int sight;

	protected:

		// ������������� �������� (��. enum CreatureID)
		int ID;

		/*
			� protected ������� ��������� ������� ������, ����� ������ � ��� ����� � �������� ������,
		�� �������� ���������� � ��� ���� ������, �.�. ����� ���������� ������ ����� ������������� ��������
		�� ����, ��� ������ �������������� ��������� ������ � �������� ������� ����� ���������� �� ����� print,
		� ��� ������������� � ��� ������ ��� ������������ ������, ����� �������������� ����� print �������� ������.
		*/
		virtual std::ostream& print(std::ostream&) const noexcept;


	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// ����������� �������� �� ���������; ������ ������������ ���-�� ����� ����� �������
		Creature(int t = -1, int s = 1, int mh = 1, int mtp = 1, int mw = 1)
			: ID(t), coords{ -1,-1 }, evasion(0), accuracy(100) { set_sight(s); set_maxHP(mh), set_HP(mh), set_maxTP(mtp), set_TP(mtp); };


		// ����������� ������� �������� ����� ��������
		virtual Creature* clone() const noexcept = 0;

		// ����������� ����������
		virtual ~Creature() {};

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		// ��������� ������� ������������� ������������ ������

		int get_ID() const noexcept { return ID; };
		int get_x() const noexcept { return coords.first; };
		int get_y() const noexcept { return coords.second; };
		int get_HP() const noexcept { return HP; };
		int get_TP() const noexcept { return TP; };
		int get_maxTP() const noexcept { return maxTP; };
		int get_maxHP() const noexcept { return maxHP; };
		int get_sight() const noexcept { return sight; };
		int get_evasion() const noexcept { return evasion; };
		int get_accurany() const noexcept { return accuracy; };



		/********************************************************/
		/*						�������							*/
		/********************************************************/

		/* ��������� ����������� ���-� ��������: ��� ������� ��������� ������� ���-� �� ��������,
		����������� ������������, ��������� ��������������� �� ������������ ��������.
		   � ������ ��������� ������������� �������� �� ��, ������� ������ ��������, ������� ��������
		�������� �� ������������
			������� ���-�� �������� ������ ������ ��� ������; ��� �� �������
		�� �������� ��� �� ���� ����� ��������� � ������������� */

		void set_x(int);
		void set_y(int);
		void set_HP(int);
		void set_TP(int);
		void set_maxHP(int);
		void set_maxTP(int);
		void set_sight(int);
		void set_evasion(int);
		void set_accuracy(int);

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/

		/*
			���������� ������� ���������� � ��������:
		'x'_'y'_'HP'_'maxHP'_'evasion'_'accuracy'_'TP'_'maxTP'_'sight'
		*/
		virtual std::ostream& save(std::ostream&) const noexcept;

		// �������� ������� ���������� � �������� �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept;

		// ����� ������� ���������� � �������� (�� ��� ���������� � ����)
		friend std::ostream& operator <<(std::ostream& os, const Creature& cr) noexcept { return cr.print(os); };

	};

}
#endif // !_CREATURE_H_


