#include "intset.h"

Intset& Intset::operator+=( const Intset& rhs ) {
	typedef std::set< Node >::const_iterator iter;
	for ( iter i = rhs.c.begin(), end = rhs.c.end(); i != end; ++i )
		c.insert( *i );
	return *this;
}

Intset& Intset::operator*=( const Intset& rhs ) {
	std::set< Node > tmp = c;
	c.clear();
	typedef std::set< Node >::iterator iter;
	for ( iter i = tmp.begin(), end = tmp.end(); i != end; ++i )
		if ( rhs.c.find( *i ) != rhs.c.end() ) c.insert( *i );
	return *this;
}

Intset& Intset::operator-=( const Intset& rhs ) {
	typedef std::set< Node >::const_iterator iter;
	for ( iter i = rhs.c.begin(), end = rhs.c.end(); i != end; ++i )
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