#ifndef WEAPON_H
#define WEAPON_H

namespace XCom {

	// Класс "Оружие"
	class Weapon : public Item	{
		// Индивидуальное "имя" оружия: можно использовать, например, для указания вида оружия
		std::string classifier;	
		// Урон от оружия
		int damage;	
		// "Разброс" оружия: урон от выстрела/удара варьируется от damage - scatter до damage + scatter
		int scatter;	
		// Процентный штраф попадания на увеличение дистанции на одну клетку (линейная зависимость); изначальный шанс попадания (при расстоянии 0 клеток) - 95%
		double penalty;	
		// Радиус стрельбы (для ближнего боя radius = 1 или 2, чтобы можно было атаковать вокруг себя)
		int radius;	
		// Тип использвуемых патронов (для ближнего боя неважно, ибо не используется)
		Ammo type;	
		// Вместительность обоимы (для оружия ближнего боя maxClip/clip = 0)
		int maxClip;	
		// Текущее кол-во патронов в обоиме
		int clip;	
		// Вес самого оружия; полный вес, это вес оружия + патроны
		double weaponWeight;			

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		// Конструктор, создающий автомат с хар-ками по умолчанию и полным магазином
		Weapon(const std::string& name = "Автомат", int up = 2,int dam = 30,int scat = 10, double pen = 10, int rad = 9, const Ammo& ammo = Ammo::_default ,int maxClip = 6, double weight = 4.5);

		// copy- move- конструкторы по умолчанию

		// Виртуальный деструктор
		virtual ~Weapon() override {};

		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		std::string get_classifier() const noexcept { return classifier; };
		int get_damage() const noexcept { return damage; };
		int get_scatter() const noexcept { return scatter; };
		double get_penalty() const noexcept { return penalty; };
		int get_radius() const noexcept { return radius; };
		Ammo get_ammo() const noexcept { return type; };
		int get_clip() const noexcept { return clip; };
		int get_max_clip() const noexcept { return maxClip; };
		double get_weapon_weight() const noexcept { return weaponWeight; };


		// Проверка магазина на пустоту
		bool empty() const noexcept;

		/********************************************************/
		/*						Сеттеры							*/
		/********************************************************/

		Weapon& set_classifier(const std::string& name) noexcept { classifier = name; return *this; };
		Weapon& set_damage(int);
		Weapon& set_scatter(int);
		Weapon& set_penalty(double);
		Weapon& set_radius(int);
		Weapon& set_type(const Ammo& ammo) noexcept { type = ammo; return *this; };
		Weapon& set_clip(int);
		Weapon& set_max_clip(int);
		Weapon& set_weapon_weight(double);

		// Позволяет получить доступ к типу патронов
		Ammo& access_to_type() noexcept { return type; };

		// Пересчет веса оружия
		virtual void set_weight(double fictitious) override { Item::set_weight(weaponWeight + type.get_weight() * clip); };

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/

		// Использование предмета: возвращается гипотетический урон от оружия (damage - scatter; damage + scatter)
		virtual int using_item(int) override;

		// Перезарядить оружие: принимается ящик, из которого мы пытаемся вытащить патроны
		Weapon& reloading(AmmoBox&);

		// Расститать шанс попадания из данного оружия при заданном расстоянии; возвращает процентный шанс попадания и наносимый урон
		std::pair<double, int> calculate_the_hit(int);


		/*
			Сохранение информации об оружии в выходном/файловом потоке:
		Информация: 'damage'_'scatter'_'penalty'_'radius'_'maxClip'_'clip'_'weaponWeight'_"classifier"\n'type'
		Вес высчитывается отдельно
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// Загрузка информации об оружии из входного/файлового потока
		virtual std::istream& load(std::istream&) noexcept override;

		// Создание копии оружия
		virtual Weapon* clone() const noexcept override { return new Weapon(*this); };

		// Вывод информации об оружии в выходной поток
		friend std::ostream& operator << (std::ostream& os, const Weapon& c) noexcept { return c.print(os); };
		// Загрузка информации об оружии из входного/файлового
		friend std::istream& operator >>(std::istream& is, Weapon& weapon) noexcept { return weapon.load(is); };


	};


}

#endif // !WEAPON_H



