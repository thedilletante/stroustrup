#include "intset.h"

Intset& Intset::operator+=( const Intset& rhs ) {
	typedef std::set<int>::const_iterator iter;
	for ( iter i = rhs.c.cbegin(), end = rhs.c.cend(); i != end; ++i )
		c.insert( *i );
	return *this;
}

Intset& Intset::operator*=( const Intset& rhs ) {
	std::set<int> tmp = c;
	c.clear();
	typedef std::set<int>::iterator iter;
	for ( iter i = tmp.begin(), end = tmp.end(); i != end; ++i )
		if ( rhs.c.find( *i ) != rhs.c.end() ) c.insert( *i );
	return *this;
}

Intset& Intset::operator-=( const Intset& rhs ) {
	typedef std::set<int>::const_iterator iter;
	for ( iter i = rhs.c.cbegin(), end = rhs.c.cend(); i != end; ++i )
		c.erase( *i );
	return *this;
}

Intset Intset::operator+( const Intset& rhs ) const {
	Intset result = *this;
	return result += rhs;
}

Intset Intset::operator*( const Intset& rhs ) const {
	Intset result = *this;
	return result *= rhs;
}

Intset Intset::operator-( const Intset& rhs ) const {
	Intset result = *this;
	return result -= rhs;
}