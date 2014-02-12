#ifndef THEDILLETANTE_TTREE
#define THEDILLETANTE_TTREE

#include <iostream>
#include <vector>
#include "tnode.h"

class Ttree
{
public:
	Ttree( const std::vector< std::string >& );
	~Ttree();

	friend std::ostream& operator<<( std::ostream&, const Ttree& );

private:
	Tnode* root;
};

// inline 
inline Ttree::Ttree( const std::vector< std::string >& init ) 
	: root(0) {
	size_t size = init.size();
	if ( size ) {
		root = new Tnode( init[0] );
		for ( size_t i = 1; i < size; ++i ) root->insert( init[i] );
	}
}

inline Ttree::~Ttree() {
	if ( root ) delete root;
}

inline std::ostream& operator<<( std::ostream& os, const Ttree& t) { return os << *t.root; }

#endif // THEDILLETANTE_TTREE