/*!
\file
\brief Заголовочный файл с описанием класса "Оперативник"

Данный файл содержит в себе состояние и методы класса "Оперативник"
*/
#ifndef OPERATIVE_H
#define OPERATIVE_H

namespace XCom {



	/*!
	\brief Класс "Оперативник"

	Является производным классом базового абстрактного класса "Существо"
*/
	class Operative :public Creature {

		/*!
		Позывной оперативника
		*/
		std::string callname;

		// Спрайт оперативника (сами не вводим, менятся в зависимости от создаваемых 
		static char idGenerator;

		char spriteID;

		// Инвентарь оперативника
		mystd::Table<Item*> inventory;

		// Активное оружие оперативника
		Weapon* hand;

	protected:
		/*!
		\brief Вывод информации об оперативнике

		Защищенный виртуальный метод вывода информации об оперативнике

		Находится в protected области, чтобы доступ к ней имели и дочерние классы,
		но напрямую обращаться к ней было нельзя, т.е. вывод происходил только через перегруженный оператор

		То есть, при вызове перегруженного оператора вывода в дочерних классах будет вызываться ИХ метод print,
		а при использовании в них вывода для абстрактного класса, будет использоваться метод print базового класса.
		\see Creature
		*/
		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 Конструкторы						*/
		/********************************************************/

		/*!
		\brief Пустой конструктор преобразования.
		\param [name] Позывной оперативника (по умолчанию "Unknow")
		*/
		Operative(const std::string& name = "Unknow") noexcept : Creature(CREATUREID_OPERATIVE, 1, 1, 1, 20), spriteID(idGenerator++), callname(name), hand(), inventory() {};


		/*!	
		\brief Копирующий конструктор.
		\param [copy] ссылка на экземпляр копирующего оперативника
			*/
		Operative(const Operative& copy) noexcept = default;

		/*! 
		\brief Копирующий оператор присваивания.
		\param [copy] ссылка на экземпляр копирующего оперативника
		\return Ссылка на измененный экземпляр оперативника
		*/
		Operative& operator =(const Operative&) noexcept;

		/*! 
		\brief Перемещающий конструктор.

		Желателен, т.к. и для mystd::Table, и для string предусмотрена семантика перемещения
		\see mystd::Table
		*/
		Operative(Operative&& move) noexcept : callname(std::move(move.callname)), spriteID(move.spriteID), inventory(std::move(move.inventory)), hand(move.hand) {};


		/*! 
		\brief Перемещающий оператор присваивания.
		\param [move] r_value ссылка на экземпляр перемещающего оперативника
		\return Ссылка на измененный экземпляр класса

		Желателен, т.к. и для mystd::Table, и для string предусмотрена семантика перемещения
		\see mystd::Table
		*/
		Operative& operator =(Operative&&) noexcept;

		/*!
		\brief Виртуальный деструктор.
		
		Из-за того, что класс не имеет своих динамических полей, ничего не делает
		*/
		virtual ~Operative() noexcept {};


		/********************************************************/
		/*						Геттеры							*/
		/********************************************************/

		/*! 
		\brief Получить позывной оперативника.
		\return string с позывным
		*/
		std::string get_callname() const noexcept { return callname; };

		/*!
		\brief Получить спрайт оперативника

		 Получить символ, которым данный оперативник отображается на карте.
		\return char, соотвествующий спрайту оперативника на карте
		*/
		char get_spriteID() const noexcept { return spriteID; };

		/*!
		\brief Получение кол-ва вещей в инвентаре.
		\return Кол-во вещей в инвентаре оперативника
		*/
		int size() const noexcept { return inventory.size(); };

		/*! 
		\brief Получение суммарного веса инвентаря.
		\return Суммарный вес инвентаря
		*/
		double total_weight() const noexcept;

		/*! 
		\brief Вывод всего инвентаря.
		\param [os] Ссылка на поток, куда выводить инвентарь
		\return Ссылка на этот же поток
		*/
		std::ostream& show_table(std::ostream&) const noexcept;

		/*!
		\brief Получение константного указателя на оружие в руке.
		\return Указатель на оружие к руке оперативника
		*/
		const Weapon* get_hand() const noexcept { return hand; };


		/********************************************************/
		/*						Сеттеры							*/
		/********************************************************/

		/*! 
		\brief Изменить позывной оперативника.
		\param [str] новое имя оперативника
		\return Ссылка на измененный экземпляр оперативника
		*/
		Operative& set_callname(const std::string& str) noexcept { callname = str; return *this; };

		/*! 
		\brief Выбросить/подобрать оружие.
		\param [weapon] Указатель на оружие, которое нужно поместить в руку 
		\return Указатель на предыдущее оружие, который нужно будет соотвествующим образом обработать
		*/
		Weapon* change_weapon(Weapon*) noexcept;

		/********************************************************/
		/*					Остальные методы					*/
		/********************************************************/


		/*! 
		\brief Добавить новый предмет в инвентарь оперативника.

		\param [item] указатель типа Item на добавляемый предмет
		\return [Operative] ссылка на экземпляр класса
		*/
		Operative& add_item(Item* item) noexcept { inventory.push_back(item); return *this; };

		/*! 
		\brief Выбросить (НЕ УДАЛИТЬ) предмет из инвентаря.

		\param [pos] НОМЕР предмета (не индекс) в инвентаре
		\return указатель на удаляемый предмет
		\throws	Выход за границы размера инвентаря (< 1 или > size)
		*/
		Item* drop_item(int pos);

		/*! 
		\brief Выбрать предмет.

		Обратиться к какому-либо предмету по номеру, не вытаскивая его из инвентаря (например, перезарядиться или захиллиться)
		\param [pos] НОМЕР предмета (не индекс) в инвентаре
		\return Указатель на выбранный предмет
		\throws Выход за границы размера инвентаря (< 1 или > size)
		*/
		Item* select_item(int);

		/*!
		\brief Создание копии оперативника.

		Виртуальный метод создании копии оперативника
		\return Указатель на новый экземпляр оперативника
		*/
		virtual Operative* clone() const noexcept override { return new Operative(*this); };

		/*!
		\brief Вывод информации об оперативнике в выходной поток.
		
		Используется для сохранения конфигурации оперативника в файл
		
		Порядок сохранения: Creature::save + callname + inventory.size() + предметы + hand
		\param [os] Ссылка на выходной поток
		\return Ссылка на тот же поток
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		/*!
		\brief Загрузка информации об оперативнике из входного/файлового потока.

		Используется для загрузки конфигурации оперативника из файла

		Порядок загрузки: Creature::save + callname + inventory.size() + предметы + hand
		\param [is] Ссылка на входной поток
		\return Ссылка на тот же поток
		*/
		virtual std::istream& load(std::istream&) noexcept override;

		/*!
		\brief Вывод информации об оперативнике в выходной поток.
		\param [os] Ссылка на выходной поток
		\param [oper] Ссылка на экземпляр оперативника
		\return Ссылка на тот же выходной поток
		*/
		friend std::ostream& operator << (std::ostream& os, const Operative& oper) { return oper.print(os); };
		/*! 
		\brief Загрузка информации об оперативнике из входного/файлового потока.
		\param [is] Ссылка на входной поток
		\param [oper] Ссылка на экземпляр оперативника
		\return Ссылка на тот же входной поток
		*/
		friend std::istream& operator >>(std::istream& is, Operative& oper) noexcept { return oper.load(is); };

	};




}

#endif // !OPERATIVE_H



