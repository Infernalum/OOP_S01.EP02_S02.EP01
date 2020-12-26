#ifndef CHRYSSALID_H
#define CHRYSSALID_H



namespace XCom {

	// ��� ���������� attack
	class Operative;

	
	/*  
		����� ��������� "����� ��������": � ���������� ��� �� ���������, �� ������ (������� ������ � ������� ���),
	 �� ���������� ���������� ���������, ������ � ����������
	*/
	class Chryssalid : public Creature {

		// ���� � ������� ���
		int damage;
		// ������� �����
		int scatter;

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		Chryssalid() : Creature(CREATUREID_CHRYSSALID, 5, 50, 8, 0), damage(20), scatter(10) {};

		// ����������� ���������� ������ "���������": ������ �� ������, �.�. ������ ����� �����������
		virtual ~Chryssalid() {};

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		int get_damage() const noexcept { return damage; };
		int get_scatter() const noexcept { return scatter; };

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		Chryssalid& set_damage(int);
		Chryssalid& set_scatter(int);

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/


		// �������� ����� ����������
		virtual Chryssalid* clone() const noexcept override { return new Chryssalid(*this); };

		/* 
			����� ����������: ����� ��������� 8 ������ ������ ����. ������������ ������ "����������" (���������, ���) � ��� ���������. 
		���� ���� ���������, ���� ���� ��������� ����� ��, �� ����������� �������� (���� ����) ���������� ��� ������.

		*/
		std::pair<bool, std::string> attack(Operative*);

		/*
			���������� ����������� � ����������: Creature::save+'damage'_'scatter'
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// �������� ���������� � ���������� �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept override;

		// ����� ���������� � ���������� �� ������� �����
		friend std::ostream& operator << (std::ostream& os, const Chryssalid& ch) { return ch.print(os); };
		// �������� ���������� � ���������� �� ��������/��������� ������
		friend std::istream& operator >>(std::istream& is, Chryssalid& ch) noexcept { return ch.load(is); };

	};

}
#endif CHRYSSALID_H
