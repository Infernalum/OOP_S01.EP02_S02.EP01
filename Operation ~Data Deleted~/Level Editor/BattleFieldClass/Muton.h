#ifndef MUTON_H 
#define MUTON_H

namespace XCom {


	/*!
	\brief ����� ��������� "�������� ��������"

	�������� ����������� ������� �������� ������������ ������ "��������"; �� ����� ���������, �� ����� ������� � ����� ������, ���������� ��� � ��������� �����
	*/
	class Muton : public Creature {

		// �������� ������
		Weapon* hand;

	protected:

		virtual std::ostream& print(std::ostream&) const noexcept override;

	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		Muton(Weapon* wp = nullptr) noexcept : Creature(CREATUREID_MUTON, 5, 50, 8, 20), hand(wp) {};

		// ����������� ���������� ������ �������� "�������� ��������"
		virtual ~Muton() {};

		/********************************************************/
		/*						�������							*/
		/********************************************************/

		// ��������� ������������ ��������� �� ������ � ����
		const Weapon* get_hand() const noexcept { return hand; };


		/********************************************************/
		/*					��������� ������					*/
		/********************************************************/


		// ���������/��������� ������ (� �������� ���������� ������������ ��������� �� ����������� ������)
		Weapon* change_weapon(Weapon*) noexcept;

		// �������� ����� ��������� ��������
		virtual Muton* clone() const noexcept override { return new Muton(*this); };

		/*
	���������� ����������� � �������� ��������: Creature::save + hand
		*/
		virtual std::ostream& save(std::ostream&) const noexcept override;

		// �������� ���������� � �������� �������� �� ��������/��������� ������
		virtual std::istream& load(std::istream&) noexcept override;

		// ����� ���������� � �������� �������� �� ������� �����
		friend std::ostream& operator << (std::ostream& os, const Muton& por) { return por.print(os); };
		// �������� ���������� � �������� �������� �� ��������/��������� ������
		friend std::istream& operator >>(std::istream& is, Muton& mut) noexcept { return mut.load(is); };


	};

}

#endif // !MUTON_H 



