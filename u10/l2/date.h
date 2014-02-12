#ifndef THEDILLETANTE_DATE
#define THEDILLETANTE_DATE

#include <iostream>
#include <string>
#include <sstream>

class Date
{
public:	// open interface

	enum Month{ January = 1, February, 
		March, April, May, 
		June, July, August, 
		September, October, November, 
		December };

	class Bad_date{};

	Date( int dd=0, Month mm = Month(0), int yy = 0 ); // 0 - default value
	Date( const Date& copy );
	Date operator=( const Date& copy );

	// access functions
	int day() const;
	Month month() const;
	int year() const;

	std::string string_rep() const;
	void char_rep( char s[] ) const;

	static void set_default( int dd, Month mm, int yy );

	// modify functions
	Date& add_year( int n = 1 );
	Date& add_month( int n = 1 );
	Date& add_day( int n = 1 );

private:
	int d, y;
	Month m;

	static Date default_date;

	mutable struct Cache_rep {
		std::string rep;
		bool isCache;
		Cache_rep() : isCache(false) {}
	} cache;

	void calculate_rep() const;
};

// helper functions
inline bool leapyear( int y ) {
#define MULT(x, y) (((x) % (y)) == 0)
	return MULT(y,4) ? (MULT(y,400) ? true : (MULT(y,100) ? false : true )) : false; 
}
inline int max_days( Date::Month month, int year ) {
	switch ( month ) {
	case Date::February: return (28 + leapyear(year));
	case Date::April: case Date::June: case Date::September: case Date::November: return 30;
	case Date::January: case Date::March: case Date::May: case Date::July:
	case Date::August: case Date::October: case Date::December: return 31;
	default:
		throw Date::Bad_date();
	}
}
int diff( const Date& a, const Date& b);
//Date next_weekday( const Date& d );
//Date next_saturday( const Date& d );

// overload operations
inline bool operator==( const Date& a, const Date& b ) {
	return ((a.day() == b.day()) && (a.month() == b.month()) && (a.year() == b.year()));
}
inline bool operator!=( const Date& a, const Date& b ) { return (!(a==b)); }
inline bool operator< ( const Date& a, const Date& b ) {
	if (a.year() < b.year()) return true;
	else if (a.year() > b.year()) return false;
	else if (a.month() < b.month()) return true;
	else if (a.month() > b.month()) return false;
	else if (a.day() < b.day()) return true;
	else return false;
}
inline bool operator> ( const Date& a, const Date& b ) {
	if (a.year() > b.year()) return true;
	else if (a.year() < b.year()) return false;
	else if (a.month() > b.month()) return true;
	else if (a.month() < b.month()) return false;
	else if (a.day() > b.day()) return true;
	else return false;
}

inline Date& operator++( Date& d ) { return d.add_day(1); }
inline Date& operator--( Date& d ) { return d.add_day(-1); }

inline Date& operator+=( Date& d, int n ) { return d.add_day(n); }
inline Date& operator-=( Date& d, int n ) { return d.add_day(-n); }

inline Date operator+( const Date& d, int n ) {
	Date result(d);
	return result.add_day(n);
}
inline Date operator-( const Date& d, int n ) {
	Date result(d);
	return result.add_day(-n);
}

inline std::ostream& operator<<( std::ostream& os, const Date& d ) { return os << d.string_rep(); }
//std::istream& operator>>( std::istream& is, Date& d );

// inline members
inline Date::Date( const Date& copy ) :
	d(copy.d), m(copy.m), y(copy.y) {}

inline Date Date::operator=( const Date& copy ) {
	d = copy.d;
	m = copy.m;
	y = copy.y;
	return *this;
}

inline int Date::day() const { return d; }
inline Date::Month Date::month() const { return m; }
inline int Date::year() const { return y; }

inline std::string Date::string_rep() const {
	if ( !cache.isCache ) calculate_rep();
	return cache.rep;
}

inline void Date::char_rep( char s[] ) const {
	if ( !cache.isCache ) calculate_rep();
	memcpy(s, cache.rep.c_str(), cache.rep.size() );
}

#endif // THEDILLETANTE_DATE