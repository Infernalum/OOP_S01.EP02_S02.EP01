#ifndef CONSTTABLEIT_H
#define CONSTTABLEIT_H

namespace XCom {

	// ����� ������������ ��������� ��� ������ � ������ ��������� �������
	class ConstTableIt {
	private:
		std::map<int, Item*>::const_iterator cur;
	public:

		/********************************************************/
		/*					 ������������						*/
		/********************************************************/

		ConstTableIt() : cur() {};
		ConstTableIt(std::map<int, Item*>::iterator it) : cur(it) {};
		ConstTableIt(std::map<int, Item*>::const_iterator it) : cur(it) {};

		/********************************************************/
		/*				�������� � ����������					*/
		/********************************************************/

		bool operator == (const ConstTableIt&) const;
		bool operator != (const ConstTableIt&) const;

		const std::pair<int, Item*>& operator *();

		// ������?
		const std::pair<const int, Item*>* operator ->();

		// ���������
		ConstTableIt& operator ++();
		
		// ���������
		ConstTableIt& operator ++(int);

	};
}

#endif // !CONSTMYTABLEIT_H



