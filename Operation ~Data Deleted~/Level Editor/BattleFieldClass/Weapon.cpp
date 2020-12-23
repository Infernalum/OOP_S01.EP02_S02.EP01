#include "pch.h"

namespace XCom {

	Weapon::Weapon(const std::string& name, int up, int dam, int scat, double pen, int rad, const Ammo& ammo, int maxclip, double weight): Item(up) {
		if (dam < 0)
			throw std::invalid_argument("���� �� ������ �� ����� ���� �������������. ���������� ��� ���.");
		if (scat < 0)
			throw std::invalid_argument("���������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		if (pen < 0)
			throw std::invalid_argument("����� � ��������� �� ��������� �� ����� ���� �������������. ���������� ��� ���.");
		if (rad < 0)
			throw std::invalid_argument("������ �������� ������ �� ����� ���� �������������. ���������� ��� ���.");
		if (maxclip < 0)
			throw std::invalid_argument("��������������� ������ �� ����� ���� �������������. ���������� ��� ���.");
		if (weight < 0)
			throw std::invalid_argument("��� ������ �� ����� ���� �������������. ���������� ��� ���.");
		marking = 'W';
		damage = dam;
		penalty = pen;
		radius = rad;
		maxClip = maxclip;
		clip = maxClip;
		weaponWeight = weight;
		set_weight(0);

	}

	/********************************************************/
	/*						�������							*/
	/********************************************************/

	bool Weapon::empty() const noexcept {
		if (!clip)
			return true;
		else
			return false;
	}


	/********************************************************/
	/*						�������							*/
	/********************************************************/


	Weapon& Weapon::set_damage(int dam) {
		if (dam < 0)
			throw std::invalid_argument("���� �� ������ �� ����� ���� �������������. ���������� ��� ���.");
		damage = dam;
		return *this;
	}


	Weapon& Weapon::set_scatter(int scat) {
		if (scat < 0)
			throw std::invalid_argument("���������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		scatter = scat;
		return *this;
	}


	Weapon& Weapon::set_penalty(double pen) {
		if (pen < 0)
			throw std::invalid_argument("����� � ��������� �� ��������� �� ����� ���� �������������. ���������� ��� ���.");
		penalty = pen;
		return *this;
	}


	Weapon& Weapon::set_radius(int rad) {
		if (rad < 0)
			throw std::invalid_argument("������ �������� ������ �� ����� ���� �������������. ���������� ��� ���.");
		radius = rad;
		return *this;
	}


	Weapon& Weapon::set_max_clip(int mclip) {
		if (mclip <= 0)
			throw std::invalid_argument("��������������� ������ ���� �������������. ���������� ��� ���.");
		maxClip = mclip;
		if (clip > maxClip) {
			clip = maxClip;
			set_weight(0);
		}
		return *this;
	}


	Weapon& Weapon::set_clip(int cl) {
		if (cl < 0)
			throw std::invalid_argument("���-�� �������� � ������ �� ����� ���� �������������. ���������� ��� ���.");
		if (cl > maxClip)
			clip = maxClip;
		clip = cl;
		set_weight(0);
		return *this;
	}


	Weapon& Weapon::set_weapon_weight(double w) {
		if (w < 0)
			throw std::invalid_argument("��� ������ �� ����� ���� �������������. ���������� ��� ���.");
		weaponWeight = w;
		return *this;
	}

	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/


	Weapon& Weapon::reloading(AmmoBox& ammobox) {
		int res = ammobox.using_item(maxClip - clip);
		set_clip(get_clip() + res);
		return *this;
	}


	int Weapon::using_item(int fictitious) {
		srand(time(0));
		int res = (damage - scatter) + rand() % (damage + scatter);
		if (res < 0)
			res = 0;
		if (res > 95)
			res = 95;
		return res;
	}

	std::pair<double, int> Weapon::calculate_the_hit(int distance) {
		srand(time(0));
		std::pair<double, int> res;
		double chance = 95;
		for (int i = 0; i < distance; ++i)
			chance *= (double)((100 - penalty) / 100);
		res.second = using_item(0);
		res.first = chance;
		return res;
	}

	std::ostream& Weapon::print(std::ostream& os) const noexcept {
		os << "������: " << classifier << "; ������� ����: " << damage << "; ������� �����: " << scatter << "; ����� � ���������: " << penalty << "; ������: " << radius << "; ";
		if (maxClip)
			os << "�������: " << clip << "\\" << maxClip << "; ��� ��������: " << type << "; ��� ������ (��� �����������): " << weaponWeight << "; ";
		Item::print(os);
		return os;
	}


	std::ostream& Weapon::save(std::ostream& os) const noexcept {
		os << get_uP() << ' ' << damage << ' ' << scatter << ' ' << penalty << ' ' << radius << ' ' << maxClip << ' ' << clip << ' ' << weaponWeight << ' ' << classifier << '\n';
		os << type;
		return os;
	}

	std::istream& Weapon::load(std::istream& is) noexcept {
		int _int;
		double _double;
		std::string str;
		is >> _int;
		set_usedPoint(_int);
		is.ignore();
		is >> _int;
		set_scatter(_int);
		is.ignore();
		is >> _int;
		set_penalty(_int);
		is.ignore();
		is >> _int;;
		set_radius(_int);
		is.ignore();
		is >> _int;;
		set_max_clip(_int);
		is.ignore(); 
		is >> _int;
		set_clip(_int);
		is.ignore();
		is >> _double;
		set_weapon_weight(_double);
		set_weight(0);
		is.ignore();
		std::getline(is, str);
		set_classifier(str);
		is >> type;
		// ���������� ��� ���������� ������, ���, �� ������
		is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return is;
	}




}
