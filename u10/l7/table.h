#ifndef THEDILLETANTE_TABLE
#define THEDILLETANTE_TABLE

#include "name.h"

class Table
{
public:
	Table() {};
	Table(const Table&);
	Table& operator=(const Table&);
	~Table();

	Name* lookup(const char*);
	bool insert(Name*);

private:
	Name* p;
	size_t sz;
};

inline Table::Table(const Table& t) : sz(t.sz), p(new Name[t.sz]) {
	for (int i = 0; i < sz; ++i) p[i] = t.p[i];
}
inline Table& Table::operator=(const Table& t) {
	if (this != &t) {
		delete[] p;
		p = new Name[ sz = t.sz ];
		for (int i = 0; i < sz; ++i) p[i] = t.p[i];
	}
	return *this;
}

inline Table::~Table() { delete[] p; }

#endif // THEDILLETANTE_TABLE