#ifndef FIRSTAIDKIT_H
#define FIRSTAIDKIT_H

namespace XCom {

	class FirstAidKit : public Item {
		
		int qty;				// ���������� ���-�� �������������
		int maxQty;				// ���-�� �������������
		int rec;				// ���-�� ������������������ ��������
		double weightOfOne;		// ��� ������ "������" �������

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// �����������, ��������� ������ ������� � 3-�� ���������������, ����������������� 2 HP � �������� �� ������������� 2 TP
		FirstAidKit(int up = 2, int hp = 2, double w = 0.5, int maxqty = 3);

		// copy- move- ������������ �� ���������

		// ����������� ����������
		virtual ~FirstAidKit() override {};

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		int get_qty() const noexcept { return qty; };
		int get_maxQty() const noexcept { return maxQty; };
		int get_rec() const noexcept { return rec; };
		double get_weightOfOne() const noexcept { return weightOfOne; };

		// �������� ������� �� �������
		bool empty() const noexcept;


		/********************************************************/
		/*						�������							*/
		/********************************************************/

		FirstAidKit& set_qty(int);
		FirstAidKit& set_max_qty(int);
		FirstAidKit& set_rec(int);
		FirstAidKit& set_weight_of_one(double);
		
		// �������� ���� �������
		virtual void set_weight(double) override { Item::set_weight(weightOfOne * qty); };


		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/

		// ������������� �������: ��������� ���� ����� � ������� ���-�� ���������� HP. ���� ������� �����, �� ������ �� ���������� (������������ 0)
		virtual int using_item(int) override;

		/*
			���������� ���������� �� ������� � ��������/�������� ������:
		����������: '���� �������������'_'���-�� �������������'_'����. ���-�� �������������'_'���-�� ������������������ ��'_'��� ������ �������������'
		��� ������������� ��������
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// �������� ���������� �� ������� �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept override;

		// �������� ����� �������
		virtual FirstAidKit* clone() const noexcept override { return new FirstAidKit(*this); };

		// ����� ���������� �� ������� � �������� �����
		friend std::ostream& operator << (std::ostream& os, const FirstAidKit& c) noexcept { return c.print(os); };
		// �������� ���������� �� ������� �� ��������/���������
		friend std::istream& operator >>(std::istream& is, FirstAidKit& fak) noexcept { return fak.load(is); };
	};


}

#endif // !FIRSTAIDKIT_H




