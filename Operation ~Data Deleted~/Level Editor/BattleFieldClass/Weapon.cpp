#include "pch.h"

namespace XCom {

	Weapon::Weapon(const std::string& name, const Ammo& amm, int up, int dam, int scat, double pen, int rad, int maxclip, double weight) : Item(ITEMID_WEAPON, up) {
		if (dam < 0)
			throw std::invalid_argument("���� �� ������ �� ����� ���� �������������. ���������� ��� ���.");
		if (scat < 0)
			throw std::invalid_argument("���������� �������� �� ����� ���� �������������. ���������� ��� ���.");
		if (scat > dam)
			throw std::invalid_argument("���������� �������� �� ����� ���� ������ �������� �����. ���������� ��� ���.");
		if (pen < 0)
			throw std::invalid_argument("����� � ��������� �� ��������� �� ����� ���� �������������. ���������� ��� ���.");
		if (rad < 0)
			throw std::invalid_argument("������ �������� ������ �� ����� ���� �������������. ���������� ��� ���.");
		if (maxclip < 0)
			throw std::invalid_argument("��������������� ������ �� ����� ���� �������������. ���������� ��� ���.");
		if (weight < 0)
			throw std::invalid_argument("��� ������ �� ����� ���� �������������. ���������� ��� ���.");
		classifier = name;
		damage = dam;
		scatter = scat;
		penalty = pen;
		radius = rad;
		maxClip = maxclip;
		clip = maxclip;
		weaponWeight = weight;
		ammo = amm;
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
		if (scat > damage)
			throw std::invalid_argument("���������� �������� �� ����� ���� ������ �������� �����. ���������� ��� ���.");
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


	Weapon& Weapon::set_maxClip(int mclip) {
		if (mclip < 0)
			throw std::invalid_argument("��������������� �� ����� ���� ��������������. ���������� ��� ���.");
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


	Weapon& Weapon::set_weaponWeight(double w) {
		if (w < 0)
			throw std::invalid_argument("��� ������ �� ����� ���� �������������. ���������� ��� ���.");
		weaponWeight = w;
		return *this;
	}

	void Weapon::set_weight(double frictious) {
		if (maxClip)
			Item::set_weight(weaponWeight + ammo.get_weight() * clip);
		else
			Item::set_weight(weaponWeight);
	}


	/********************************************************/
	/*					��������� ������					*/
	/********************************************************/


	Weapon& Weapon::reloading(AmmoBox& ammobox) {
		if (!maxClip)
			throw std::logic_error("������ ������������ ������ �������� ���. ���������� ��� ���.");
		if (ammobox.get_ammo() != ammo)
			throw std::invalid_argument("������������ ��� �����������. ���������� ��� ���.");
		int res = ammobox.using_item(maxClip - clip);
		set_clip(get_clip() + res);
		return *this;
	}


	int Weapon::using_item(int fictitious) {
		int res = (damage - scatter) + rand() % (damage + scatter);
		if (res < 0)
			res = 0;
		if (res > 95)
			res = 95;
		return res;
	}

	std::pair<double, int> Weapon::calculate_the_hit(int distance) {
		std::pair<double, int> res;
		double chance = 95;
		for (int i = 0; i < distance; ++i)
			chance *= (double)((100 - penalty) / 100);
		res.second = using_item(0);
		res.first = chance;
		return res;
	}

	std::ostream& Weapon::print(std::ostream& os) const noexcept {
		os << classifier;
		if (maxClip)
			os << " (" << clip << "\\" << maxClip << "); ";
		else
			os << "; ";
		os << "����: " << damage - scatter << " - " << damage + scatter << "; ����� � ����������: " << penalty << "%; ������: " << radius << "; ";
		if (maxClip)
			os << ammo;
		Item::print(os);
		return os;
	}


	std::ostream& Weapon::save(std::ostream& os) const noexcept {
		Item::save(os) << damage << ' ' << scatter << ' ' << penalty << ' ' << radius << ' ' << maxClip << ' ' << clip << ' ' << weaponWeight << ' ' << classifier << '\n';
		if (maxClip)
			ammo.save(os);
		return os;
	}

	std::istream& Weapon::load(std::istream& is) noexcept {
		Item::load(is) >> damage;
		is.ignore() >> scatter;
		is.ignore() >> penalty;
		is.ignore() >> radius;
		is.ignore() >> maxClip;
		is.ignore() >> clip;
		is.ignore() >> weaponWeight;
		is.ignore();
		std::getline(is, classifier);
		if (maxClip)
			ammo.load(is);
		set_weight(0);
		return is;
	}




}
