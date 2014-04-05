#ifndef THEDILLETANTE_INTSET
#define THEDILLETANTE_INTSET

#include <set>
#include <iostream>
#include "node.h"

class Intset
{
public:
	
	Intset& insert(const Node&);

	// 
	Intset operator+(const Intset&) const;
	Intset operator*(const Intset&) const;
	Intset operator-(const Intset&) const;

	Intset& operator+=(const Intset&);
	Intset& operator*=(const Intset&);
	Intset& operator-=(const Intset&);

	friend std::ostream& operator<<(std::ostream&, const Intset&);

private:
	std::set< Node > c;
};

// inline
inline Intset& Intset::insert(const Node& elem) { c.insert(elem); return *this; }

inline std::ostream& operator<<(std::ostream& os, const Intset& rhs) {
	os << "[";
	typedef std::set< Node >::const_iterator iter;
	bool first = true;
	for (iter i = rhs.c.begin(), end = rhs.c.end(); i != end; ++i ) {
		if ( first ) first = false;
		else os << ",";
		os << *i;
	}
	return os << "]";
}

#endif // THEDILLETANTE_INTSET