#ifndef AMMOBOX_H
#define AMMO_BOX


namespace XCom {

	class AmmoBox : public Item {
	private:

		int qty;				// ������� ���-�� �������� � �����;
		int maxQty;				// ����� ���-�� �������� � �����;
		double weightOfOne;		// ��� ������ �������

	protected:

		virtual std::ostream& print(std::ostream&) const override;

	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// �����������, ��������� ������ ���� � 40 ��������� � �������� 2 TP �� �����������
		AmmoBox(int up = 2, double wof = 0.02, int maxqty = 40);

		// copy- move- ������������ �� ���������

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		int get_qty() { return qty; };
		int get_max_qty() { return maxQty; };
		double get_weight_of_one() { return weightOfOne; };

		// �������� ����� �� �������
		bool empty();

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		AmmoBox& set_qty(int);
		AmmoBox& set_max_qty(int);
		AmmoBox& set_weight_of_one(double);


		// �������� ���� ����� � ���������
		virtual const AmmoBox& set_weight() override;

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/

		virtual int using_item(int) override;

		friend std::ostream& operator << (std::ostream& os, const AmmoBox& c) { return c.print(os); };

	};

}
#endif // !AMMOBOX_H



