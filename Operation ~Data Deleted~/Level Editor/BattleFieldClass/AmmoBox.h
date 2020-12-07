#ifndef AMMOBOX_H
#define AMMO_BOX


namespace XCom {

	class AmmoBox : public Item {
	private:

		int qty;				// Текущее кол-во патронов в ящике;
		int maxQty;				// Общее кол-во патронов в ящике;
		double weightOfOne;		// Вес одного патрона

	protected:

		virtual std::ostream& print(std::ostream&) const override;

	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		// Конструктор, создающий полный ящик с 40 патронами и тратящий 2 TP на перезарядку
		AmmoBox(int up = 2, double wof = 0.02, int maxqty = 40);

		// copy- move- конструкторы по умолчанию

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		int get_qty() { return qty; };
		int get_max_qty() { return maxQty; };
		double get_weight_of_one() { return weightOfOne; };

		// Проверка ящика на пустоту
		bool empty();

		/********************************************************/
		/*						Сеттеры							*/
		/********************************************************/

		AmmoBox& set_qty(int);
		AmmoBox& set_max_qty(int);
		AmmoBox& set_weight_of_one(double);


		// Пересчет веса ящика с патронами
		virtual const AmmoBox& set_weight() override;

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/

		virtual int using_item(int) override;

		friend std::ostream& operator << (std::ostream& os, const AmmoBox& c) { return c.print(os); };

	};

}
#endif // !AMMOBOX_H



