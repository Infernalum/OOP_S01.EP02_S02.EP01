#ifndef AMMOBOX_H
#define AMMO_BOX


namespace XCom {

	// Класс "Ящик с патронами"
	class AmmoBox : public Item {

		// Тип хранящегося патрона
		Ammo type;
		// Текущее кол-во патронов в ящике;
		int qty;
		// Общее кол-во патронов в ящике;
		int maxQty;


	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		// Конструктор, создающий полный ящик с 40 стандартными патронами и тратящий 2 TP на перезарядку
		AmmoBox(int up = 2, int maxqty = 40, const Ammo& ammo = Ammo::_default);

		// copy- move- конструкторы по умолчанию

		// Виртуальный деструктор
		virtual ~AmmoBox() override {};

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		int get_qty() const noexcept { return qty; };
		int get_max_qty() const noexcept { return maxQty; };
		Ammo get_type() const noexcept { return type; };

		// Проверка ящика на пустоту
		bool empty() const noexcept;

		/********************************************************/
		/*						Сеттеры							*/
		/********************************************************/

		AmmoBox& set_qty(int);
		AmmoBox& set_max_qty(int);
		// Позволяет получить доступ к типу патронов
		Ammo& access_to_type() noexcept { return type; };

		AmmoBox& set_name(const std::string& name) noexcept { type.set_type(name); return *this; };
		AmmoBox& set_weight_of_one(double);

		// Пересчет веса ящика с патронами
		virtual void set_weight(double fictitious) override { Item::set_weight(type.get_weight() * qty); };

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/

		// Использование предмета: вытащить и вернуть count патронов из ящика. Если в ящике меньше count патронов, то вытаскивается, сколько есть (либо 0, если ящик пустой)
		virtual int using_item(int) override;

		/*
			Сохранение информации о ящике в выходном/файловом потоке:
		Информация: 'очки использования'_'кол-во патронов'_'макс.кол-во патронов'_'вес одного патрона'
		Вес высчитывается отдельно
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// Загрузка информации о ящике из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept override;

		// Создание копии ящика
		virtual AmmoBox* clone() const noexcept override { return new AmmoBox(*this); };

		// Вывод информации о ящике в выходной поток
		friend std::ostream& operator << (std::ostream& os, const AmmoBox& c) noexcept { return c.print(os); };
		// Загрузка информации о ощике из входного/файлового
		friend std::istream& operator >>(std::istream& is, AmmoBox& ammobox) noexcept { return ammobox.load(is); };
	
	};


}
#endif // !AMMOBOX_H



