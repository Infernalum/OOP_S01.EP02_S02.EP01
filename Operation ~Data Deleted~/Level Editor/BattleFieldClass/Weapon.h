#ifndef WEAPON_H
#define WEAPON_H

namespace XCom {

	// ����� "������"
	class Weapon : public Item	{
		// �������������� "���" ������: ����� ������������, ��������, ��� �������� ���� ������
		std::string classifier;	
		// ���� �� ������
		int damage;	
		// "�������" ������: ���� �� ��������/����� ����������� �� damage - scatter �� damage + scatter
		int scatter;	
		// ���������� ����� ��������� �� ���������� ��������� �� ���� ������ (�������� �����������); ����������� ���� ��������� (��� ���������� 0 ������) - 95%
		double penalty;	
		// ������ �������� (��� �������� ��� radius = 1 ��� 2, ����� ����� ���� ��������� ������ ����)
		int radius;	
		// ��� ������������� �������� (��� �������� ��� �������, ��� �� ������������)
		Ammo type;	
		// ��������������� ������ (��� ������ �������� ��� maxClip/clip = 0)
		int maxClip;	
		// ������� ���-�� �������� � ������
		int clip;	
		// ��� ������ ������; ������ ���, ��� ��� ������ + �������
		double weaponWeight;			

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		// �����������, ��������� ������� � ���-���� �� ��������� � ������ ���������
		Weapon(const std::string& name = "�������", int up = 2,int dam = 30,int scat = 10, double pen = 10, int rad = 9, const Ammo& ammo = Ammo::_default ,int maxClip = 6, double weight = 4.5);

		// copy- move- ������������ �� ���������

		// ����������� ����������
		virtual ~Weapon() override {};

		/********************************************************/
		/*						�������							*/
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


		// �������� �������� �� �������
		bool empty() const noexcept;

		/********************************************************/
		/*						�������							*/
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

		// ��������� �������� ������ � ���� ��������
		Ammo& access_to_type() noexcept { return type; };

		// �������� ���� ������
		virtual void set_weight(double fictitious) override { Item::set_weight(weaponWeight + type.get_weight() * clip); };

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/

		// ������������� ��������: ������������ �������������� ���� �� ������ (damage - scatter; damage + scatter)
		virtual int using_item(int) override;

		// ������������ ������: ����������� ����, �� �������� �� �������� �������� �������
		Weapon& reloading(AmmoBox&);

		// ���������� ���� ��������� �� ������� ������ ��� �������� ����������; ���������� ���������� ���� ��������� � ��������� ����
		std::pair<double, int> calculate_the_hit(int);


		/*
			���������� ���������� �� ������ � ��������/�������� ������:
		����������: 'damage'_'scatter'_'penalty'_'radius'_'maxClip'_'clip'_'weaponWeight'_"classifier"\n'type'
		��� ������������� ��������
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// �������� ���������� �� ������ �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept override;

		// �������� ����� ������
		virtual Weapon* clone() const noexcept override { return new Weapon(*this); };

		// ����� ���������� �� ������ � �������� �����
		friend std::ostream& operator << (std::ostream& os, const Weapon& c) noexcept { return c.print(os); };
		// �������� ���������� �� ������ �� ��������/���������
		friend std::istream& operator >>(std::istream& is, Weapon& weapon) noexcept { return weapon.load(is); };


	};


}

#endif // !WEAPON_H



