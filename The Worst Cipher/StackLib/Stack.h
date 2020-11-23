#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <string.h>

namespace StackClass {


	// ������ ������� �������� ����� ������ ���� ������ (1 � ������ �������, � 0 ��� ������)
	template <class T>
	int getType(T& a, std::istream& stream) {
		int rc = 0;
		stream >> a;
		if (!stream.good())
			rc = 1;				// ���������� ������ �����
		stream.clear();
		stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return rc;
	};

	// ������ ������� ��� ����� ����� �� �������� ������
	template<class T>
	void input_Type(T& p, std::istream& istream, std::ostream& ostream) {
		while (getType(p, istream))
			ostream << "����������, ��������� ����: --> ";
	}

	struct elem_of_stack {
	private:
		int key;
		std::string str;
	public:
		elem_of_stack(int k = 0, std::string s = "") : key(k), str(s) {};
		elem_of_stack& set_key(int k) {
			key = k;
			return *this;
		}
		elem_of_stack& operator =(int k) {
			return set_key(k);
		}
		elem_of_stack& operator =(const std::string& str) {
			return set_string(str);
		}
		elem_of_stack& operator +=(int k) {
			return set_key(key += k);
		}
		elem_of_stack& operator +=(const std::string& s) {
			return set_string(str += s);
		}
		elem_of_stack& set_string(const std::string& s) {
			str = s;
			return *this;
		}
		int get_key() { return key; }
		std::string& get_string() { return str; };
		friend std::istream& operator >>(std::istream&, elem_of_stack&);
		friend std::ostream& operator <<(std::ostream& c, elem_of_stack& a) {
			c << "key: " << a.key << " str: " << a.str << ' ' << std::endl;
			return c;
		}
	};
	class Stack {
		static const int SZ = 10; // ������ ��� ���������� �������
		int size;
		int top;
		elem_of_stack* mas;
	public:
		Stack() : top(0), size(SZ) { mas = new elem_of_stack[SZ]; };
		Stack(elem_of_stack, int k = 1);	//������ k ���������� ���������  
		Stack(elem_of_stack*, int);			//�������� �� ������� 
		~Stack() { delete[] mas; };
		Stack(const Stack&);
		Stack(Stack&&);
		int get_size() const { return size; }; // ���������� ������ �������
		int get_top() const { return top; }; //���������� �������(��� ���� �����)
		Stack& operator = (const Stack&); //���������� ������������
		Stack& operator = (Stack&&); //������������ ������������
		Stack& operator +=(elem_of_stack&); //���������� ��������
		Stack& operator +=(const Stack&); //���������� ������������ � �����������
		Stack& operator ()(Stack&); //������������ ������������ � �����������
		friend std::ostream& operator <<(std::ostream& c, Stack& a); //������� ���� ���� � �����
		friend std::istream& operator >>(std::istream&, Stack&); //��������� ������� �� ������
		elem_of_stack& show_first() const; //������ ������� ��������
		Stack& operator ()(elem_of_stack&); //������� �� ����� pop
		int  empty() const; //��������� ���� �� �������������(-1 �������� ��������; 0 ������; 1 ������)
	};
}


#endif // !LAB3_STACK_H
