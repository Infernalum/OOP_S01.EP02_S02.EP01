#ifndef CHRYSSALID_H
#define CHRYSSALID_H



namespace Battlefield {

	// ����� "����� ��������" (��������)
	/* � ���������� ��� �� ���������, �� ������ (������� ������ � ������� ���),
	 �� ���������� ���������� ���������, ������ � ����������
	*/
	class Chryssalid : public Creature {
	private:
		int damage;			// ���� � ������� ���

	protected:
		virtual std::ostream& print(std::ostream&) const;

	public:

		virtual const char name() const { return marking; };

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		Chryssalid(int d = 1) : Creature(5, 50, 8), damage(d) { set_accuracy(100); };


		/********************************************************/
		/*						�������							*/
		/********************************************************/

		int get_damage() { return damage; };


		/********************************************************/
		/*						�������							*/
		/********************************************************/

		virtual Chryssalid& set_damage(int);


		virtual Chryssalid* clone() const { return new Chryssalid(*this); };

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/



		friend std::ostream& operator << (std::ostream& os, const Chryssalid& ch) { return ch.print(os); };

	};

}
#endif CHRYSSALID_H
