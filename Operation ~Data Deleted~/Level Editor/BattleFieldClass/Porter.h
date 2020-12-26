#ifndef PORTER_H
#define PORTER_H

namespace XCom {

	// ����� ��������� "�������": �� ����� ���������, �� ������ � ����� ������������� � �*���� ���� �����, ��� �����
	class Porter : public Creature {

		// ��������� ��������
		mystd::Table<Item*> inventory;

		// ������ ������� �������� ���������� �������. �.�. ���� ��������� ��������� �� ��������, � ������� ���� ������ �� ���� ������
		std::vector<std::pair<int, int>> starages;

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		Porter() : Creature(CREATUREID_PORTER, 5, 50, 8, 20), inventory(), starages() {};

		// ���������� �����������
		Porter(const Porter& copy) noexcept : inventory(copy.inventory), starages(copy.starages) {};

		// ���������� �������� ������������
		Porter& operator =(const Porter&) noexcept;

		// ������������ ����������� (�.�. � ��� �������, � ��� ������� ������������� ��������� �����������)
		Porter(Porter&& move) noexcept : inventory(std::move(move.inventory)), starages(std::move(move.starages)) {};
		
		// ������������ �������� ������������
		Porter& operator =(Porter&&) noexcept;


		// ���������� ���������� ������ �������� "�������"
		virtual ~Porter() {};

		/********************************************************/
		/*						�������							*/
		/********************************************************/


		// ��������� ���-�� ����� � ���������
		int size() const noexcept { return inventory.size(); };

		// ��������� ���������� ���� ���������
		double total_weight() const noexcept;

		// ����� ����� ���������
		std::ostream& show_table(std::ostream&) const noexcept;

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/

		// �������� ����� ������� � ���������
		Porter& add_item(Item* item) noexcept { inventory.push_back(item); return *this; };

		// ��������� (�� �������) ������� �� ��������� (����������� ����� ��������)
		Item* drop_item(int);

		// ���������� � ������-���� �������� �� ������
		Item* select_item(int);


		// �������� ����� ��������
		virtual Porter* clone() const noexcept override { return new Porter(*this); };

		/*
	���������� ����������� � ��������: Creature::save + inventory.size() + ��������
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// �������� ���������� � �������� �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept override;

		// ����� ���������� � �������� �� ������� �����
		friend std::ostream& operator << (std::ostream& os, const Porter& por) { return por.print(os); };
		// �������� ���������� � �������� �� ��������/��������� ������
		friend std::istream& operator >>(std::istream& is, Porter& por) noexcept { return por.load(is); };

	};

}


#endif // !PORTAER_H



