#ifndef CHRYSSALID_H
#define CHRYSSALID_H



namespace XCom {

	// ����� ��������� "����� ��������"
	/* � ���������� ��� �� ���������, �� ������ (������� ������ � ������� ���),
	 �� ���������� ���������� ���������, ������ � ����������
	*/
	class Chryssalid : public Creature {

		// ���� � ������� ���
		int damage;
		// ������� �����
		int scatter;

	protected:
		virtual std::ostream& print(std::ostream&) const override;

	public:

		virtual const char name() const override { return marking; };

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		Chryssalid() : Creature(5, 50, 8, 0), damage(20), scatter(10) { marking = 'c'; };

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
		virtual Chryssalid* clone() const override { return new Chryssalid(*this); };

		// ����� ����������:����� ��������� 8 ������ ������ ����
		virtual int get_damage(Creature*) override;

		/*
	���������� ����������� � ����������: Creature::save+'damage'_'scatter'
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// �������� ���������� � ���������� �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept override;

		// ����� ���������� � ���������� �� ������� �����
		friend std::ostream& operator << (std::ostream& os, const Chryssalid& ch) { return ch.print(os); };

	};

}
#endif CHRYSSALID_H
