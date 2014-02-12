#ifndef THEDILLETANTE_HISTOGRAM
#define THEDILLETANTE_HISTOGRAM

#include <vector>
#include <iostream>

class Histogram
{
public:
	class Bad_interval {};
	class Out_of_range {};

	// constructors
	Histogram( int _min, int _max );

	// getters
	int size() const;

	// manipulate
	Histogram& add( int x );
	Histogram& operator+( int x ) { return add(x); }

	friend std::ostream& operator<<( std::ostream& os, const Histogram& hist );


private:
	int min;
	int max;
	std::vector< int > container;

};

inline std::istream& operator>>( std::istream& is, Histogram& hist ) {
	int x;
	while ( is >> x ) hist.add( x );
}

// inline realization

inline Histogram::Histogram( int _min, int _max )
	: min( _min ), max( _max ) {
	if ( min > max ) throw Bad_interval();
}

inline Histogram& Histogram::add( int x ) {
	if ( x < min || x > max ) throw Out_of_range();
	container.push_back( x );
	return *this;
}

inline int Histogram::size() const { return container.size(); }

inline std::ostream& operator<<( std::ostream& os, const Histogram& hist ) {
	std::cout << hist.min << " [\t";
	for (std::vector<int>::const_iterator iter = hist.container.begin(), end = hist.container.end();
			iter != end; ++iter ) {
		std::cout << *iter << "\t";
	}
	std::cout << "] " << hist.max;
	return os;
}

#endif // THEDILLETANTE_HISTOGRAM