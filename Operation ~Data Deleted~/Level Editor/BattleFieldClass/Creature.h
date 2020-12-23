#ifndef CREATURE_H
#define CREATURE_H


namespace XCom {

	// ������� ����������� ����� "��������"
	class Creature {

		//static const std::string fraction;	// "���" �������� (� ����� ������� ����������� - "Alien" ��� "Operative")"
		std::pair<int, int> coords;				// ���������� ������, �� ������� ����� ��������
		int HP, maxHP;							// ������� \ ������������ ���-�� ����� ��������
		int evasion;							// �������� ��������� ��������: ������� ���� ��������� (����������� �� 0 - ��� ������, �� 100% - ��������� ���� � 2 ����)
		int accuracy;							// �������� �������� ��������: ����������, ����� ���� ������� ���� �� ������������ ����� �������. 0 - ������ ��� (��������), 100 - ������� ��������
		int TP, maxTP;							// ������� \ ������������ ���-�� ����� �������
		int sight;								// ������ ������ ��������

	protected:

		// ������, ������� ����� ������������ ������ ����� ������� �� �����
		char marking;



		/* � protected ������� ��������� ������� ������, ����� ������ � ��� ����� � �������� ������,
		�� �������� ���������� � ��� ���� ������, �.�. ����� ���������� ������ ����� ������������� ��������
		�� ����, ��� ������ �������������� ��������� ������ � �������� ������� ����� ���������� �� ����� print,
		� ��� ������������� � ��� ������ ��� ������������ ������, ����� �������������� ����� print �������� ������.
		*/
		virtual std::ostream& print(std::ostream&) const;

		/*
	���������� ������� ���������� � ��������:
	'x'_'y'_'HP'_'maxHP'_'evasion'_'accuracy'_'TP'_'maxTP'_'sight'
		*/
		virtual std::ostream& save(std::ostream&) const noexcept;

		// �������� ������� ���������� � �������� �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept;


	public:

		virtual const char name() const = 0;



		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// ����������� �������� �� ���������; ������ ������������ ���-�� ����� ����� �������
		Creature(int s = 1, int mh = 1, int mtp = 1, int mw = 1)
			: coords{ -1,-1 }, evasion(0), accuracy(100) { set_sight(s); set_HP(mh), set_maxHP(mh), set_TP(mtp), set_maxTP(mtp); };


		// ����������� ������� �������� ����� ��������
		virtual Creature* clone() const = 0;

		// ����������� ����������
		virtual ~Creature() {};

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		// ��������� ������� ������������� ������������ ������

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
		std::pair<int, int>& change_coords() { return coords; };

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/

		// ����� ����������� ������� �������� ��������� �� ��������: ����������� ��������� �� ��������� �������� � ������������ ���-�� ����������� �����
		virtual int get_damage(Creature*) = 0;


		// �������� ������� ���������� � �������� �� ��������/��������� ������
		friend std::istream& operator >>(std::istream& is, Creature& ammobox) noexcept { return ammobox.load(is); };



	};

}
#endif // !_CREATURE_H_


