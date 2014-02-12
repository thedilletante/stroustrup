#ifndef THEDILLETANTE_NODE
#define THEDILLETANTE_NODE

#include <iostream>
#include <string>

class Node
{
public:
	Node( const std::string& );

	bool operator<( const Node& rhs) const;

	friend std::ostream& operator<<( std::ostream&, const Node& );

private:
	std::string s;
};

inline Node::Node( const std::string& str ) : s(str) {}

inline std::ostream& operator<<( std::ostream& os, const Node& n) { return os << n.s; }

inline bool Node::operator<(const Node& rhs) const { return s < rhs.s; }

#endif // THEDILLETANTE_NODE