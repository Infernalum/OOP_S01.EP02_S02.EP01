#ifndef PORTER_H
#define PORTER_H

namespace XCom {

	// ����� ��������� "�������": �� ����� ���������, �� ������ � ����� ������������� � �*���� ���� �����, ��� �����
	class Porter :public Creature{
		mystd::Table<Item*> items;

	protected:
		virtual std::ostream& print(std::ostream&) const override;

	public:

		virtual const char name() const override { return marking; };


		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		Porter() : Creature(5, 50, 8, 20), items() { marking = 'p'; };

		// ???
		virtual ~Porter();

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		mystd::Table<Item*>& access_to_table() { return items; };


		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/

		// �������� ����� ����������
		virtual Porter* clone() const override { return new Porter(*this); };

		// ����� ����������: ����������
		virtual int get_damage(Creature*) override { throw std::invalid_argument("���������� ��������� �� �����; � ��� �����, � ��� ����� ������ ������!"); };

		/*
	���������� ����������� � ����������: Creature::save + items.size() + ��������
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// �������� ���������� � ���������� �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept override;

		// ����� ���������� � ���������� �� ������� �����
		friend std::ostream& operator << (std::ostream& os, const Porter& por) { return por.print(os); };


	};

}


#endif // !PORTAER_H



