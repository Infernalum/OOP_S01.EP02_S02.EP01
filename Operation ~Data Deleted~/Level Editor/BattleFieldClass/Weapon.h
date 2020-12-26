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
		// ��� ������������ �������� (��� ������ �������� ��� �� �����, ��� �� ������������)
		Ammo ammo;
		// ��������������� ������ (��� ������ �������� ��� maxClip\clip = 0)
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
		Weapon(const std::string& name = "�������", const Ammo& ammo = Ammo::_default, int up = 2,int dam = 30,int scat = 10, double pen = 10, int rad = 9,int maxClip = 6, double weight = 4.5);

		// copy- move- ������������ �� ���������

		// ����������� ���������� ������ "������"
		virtual ~Weapon() override {};

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		std::string get_classifier() const noexcept { return classifier; };
		int get_damage() const noexcept { return damage; };
		int get_scatter() const noexcept { return scatter; };
		double get_penalty() const noexcept { return penalty; };
		int get_radius() const noexcept { return radius; };
		const Ammo& get_ammo() const noexcept { return ammo; };
		int get_clip() const noexcept { return clip; };
		int get_maxClip() const noexcept { return maxClip; };
		double get_weaponWeight() const noexcept { return weaponWeight; };


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
		Ammo& change_type() noexcept { return ammo; };
		Weapon& set_clip(int);
		Weapon& set_maxClip(int);
		Weapon& set_weaponWeight(double);


		// �������� ���� ������
		virtual void set_weight(double fictitious) override;

		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/

		// ������������� ��������: ������������ �������������� ���� �� ������ � ���������� [damage - scatter; damage + scatter]
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
		friend std::ostream& operator << (std::ostream& os, const Weapon& weapon) noexcept { return weapon.print(os); };
		// �������� ���������� �� ������ �� ��������/��������� ������
		friend std::istream& operator >>(std::istream& is, Weapon& weapon) noexcept { return weapon.load(is); };


	};


}

#endif // !WEAPON_H



