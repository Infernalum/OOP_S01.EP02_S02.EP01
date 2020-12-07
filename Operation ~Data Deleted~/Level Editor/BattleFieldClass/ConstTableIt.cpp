#include "pch.h"


namespace XCom {

	bool ConstTableIt::operator!= (const ConstTableIt& it) const {
		return cur != it.cur;
	}

	bool ConstTableIt::operator== (const ConstTableIt& it) const {
		return cur == it.cur;
	}

	const std::pair<int, Item*>& ConstTableIt::operator*() {
		return *cur;
	}

	const std::pair<const int, Item*>* ConstTableIt::operator->() {
		return &*cur;
	}

	ConstTableIt& ConstTableIt::operator++() {
		++cur;
		return *this;
	}

	ConstTableIt& ConstTableIt::operator++(int) {
		ConstTableIt res(*this);
		++cur;
		return res;
	}

}
