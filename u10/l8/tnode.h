#ifndef THEDILLETANTE_TNODE
#define THEDILLETANTE_TNODE

#include <iostream>
#include <string>

class Tnode
{
public:
	Tnode( const std::string& );
	~Tnode();

	Tnode& insert( const std::string& );
	
	friend std::ostream& operator<<( std::ostream&, const Tnode& );

private:
	std::string name;
	int count;
	Tnode* right;
	Tnode* left;

	Tnode* append( Tnode* , const std::string& );
};

//inline
inline Tnode::Tnode( const std::string& n )
	: name(n), count(1), right(0), left(0) {}

inline Tnode* Tnode::append( Tnode* dst, const std::string& n ) {
	if ( dst ) dst->insert( n );
	else dst = new Tnode( n );
	return dst;
}

inline Tnode& Tnode::insert( const std::string& n ) {
	if ( n == name ) ++count;
	else if ( n < name ) left = append( left, n );
	else right = append( right, n );
	return *this;
}

inline Tnode::~Tnode() {
	if ( right ) delete right;
	if ( left ) delete left;
}

inline std::ostream& operator<<( std::ostream& os, const Tnode& a) {
	if (a.left) os << *(a.left);
	os << a.name << ":" << a.count << "\n";
	if (a.right) os << *(a.right);
	return os;
}

#endif // THEDILLETANTE_TNODE