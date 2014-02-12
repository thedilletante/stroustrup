#include "date.h"

Date Date::default_date(1, Date::January, 2014);

void Date::set_default(int dd, Date::Month mm, int yy ) {
	if ( dd == 0 ) dd = default_date.day();
	if ( mm == 0 ) mm = default_date.month();
	if ( yy == 0 ) yy = default_date.year();

	int max = max_days( mm, yy );

	if ( dd < 1 || max < dd ) throw Bad_date();

	default_date.d = dd;
	default_date.m = Month(mm);
	default_date.y = yy;
}

Date::Date( int dd, Date::Month mm, int yy ) {
	if ( dd == 0 ) dd = default_date.day();
	if ( mm == 0 ) mm = default_date.month();
	if ( yy == 0 ) yy = default_date.year();

	int max = max_days( mm, yy );

	if ( dd < 1 || max < dd ) throw Bad_date();

	y = yy;
	m = mm;
	d = dd;
}

Date& Date::add_year( int n ) {
	if  (n != 0 ) {
		if ( d == 29 && m == February && !leapyear(y + n) ) {
			if ( n > 0 ) {
				d = 1;
				m = March;
			}
			else
				d = 28;
		}
		y += n;
		cache.isCache = false;
	}
	return *this;
}

Date& Date::add_month( int n ) {
	if ( n != 0 ) {
		int sign = (n > 0) ? 1 : -1;
		int mn = (n > 0) ? n : -n;
		int delta_y = n/12;
		int mm = m + sign*(mn % 12);
		if ( mm < 1 || mm > 12 ) {
			mm -= 12*sign;
			delta_y += sign;
		}
		int new_year = y + delta_y;
		int max = max_days( Month(mm), new_year );
		if ( d > max ) d = max;
		y = new_year;
		m = Month(mm);
		cache.isCache = false;
	}
	return *this;
}

Date& Date::add_day( int n ) {
	if ( n != 0 ) {
		// reset to 1 of month;
		n += d - 1;
		d = 1;

		int sign = (n > 0) ? 1 : -1;
		int mn = (n > 0) ? n : -n;

		int delta;
		// add years
		while( (delta = 365 + leapyear(y)) < mn ) {
			y += sign;
			mn -= delta;
		}

		int mm = m;
		while( (delta = max_days(m, y)) < mn + d ) {
			mm += sign;
			mn -= delta;
		}

		d += mn;
		if ( mm < 1 || mm > 12 ) {
			mm -= sign*12;
			y += sign;
		}

		if (d > (delta = max_days( Month(mm), y ))) {
			d -= delta;
			++mm;
		}
		m = Month(mm);
		cache.isCache = false;
	}
	return *this;
}

void Date::calculate_rep() const {
	std::cout << "calculate" << std::endl;
	std::stringstream tmp;
	tmp << d << "." << m << "." << y;
	cache.rep = tmp.str();
	cache.isCache = true;
}

int diff( const Date& a, const Date& b) {
	Date min = (a < b) ? a : b;
	Date max = (a > b) ? a : b;
	int result = 0;
	while( min != max ) {
		min.add_day();
		++result;
	}
	return result;
}