#include <ctime>
#include "Date.h"


struct Date::Impl {
	int day;
	std::string month;
	int year;

	Impl(int d, std::string m, int y): day(d), month(m), year(y) {}
};

std::string monthNames[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; //array associating month number to name
int dayArray[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //array associating month number to days in that month


/****************************************************.h
*	Accessors
*****************************************************/

int Date::day() const {
	return pimpl->day;
}
std::string Date::month() const {
	return pimpl->month;
}
int Date::year() const {
	return pimpl->year;
}

/****************************************************
*	Helper Functions
*****************************************************/
namespace help {	
	//Returns whether the given year is a leap year
	bool isLeapYear(int year) {
		if(year % 400 == 0) {
			return true;
		}
		if(year % 100 == 0) {
			return false;
		}
		if(year % 4 == 0) {
			return true;
		}
		return false;
	}

	//Returns the numerical value for the given month, and -1 if it is invalid
	int findMonth(std::string month) {
		for(int i = 0; i < 12; i++) {
			if(monthNames[i] == month) {
				return i;
			}
		}

		return -1;
	}

	//Returns the days in the given month
	int monthDays(int month, int year) {
		if(help::isLeapYear(year) && month == 1) {
			return 29;
		}
		return dayArray[month];
	} 
	//Returns the number of days in the current month of a date
	int monthDays(const Date& d) {
		return help::monthDays(help::findMonth(d.month()), d.year());
	} 
}

/****************************************************
*	Constructors and Destructors
*****************************************************/

Date::~Date() {
	delete pimpl;
}

Date::Date(int day, std::string month, int year): pimpl(new Date::Impl(day, month, year)) {
	if(year < 1900 || year > 2100) {
		throw "Invalid year.";
	}

	if(help::findMonth(month) < 0) {
		throw "Invalid month.";
	}
	if(day < 1 || day > help::monthDays(help::findMonth(month), year)) {
		throw "Invalid day of the month.";
	}
}

Date::Date(const Date& date):pimpl(new Date::Impl(date.day(), date.month(), date.year())) {}

//Returns the current date as a date structure
Date Date::today() {
	time_t t = time(0); 
    struct tm * now = localtime(&t);
    return Date(now->tm_mday, monthNames[now->tm_mon],now->tm_year + 1900);
}

/****************************************************
*	Incrementors
*****************************************************/

Date incDays (const Date& date, long days) {
	Date d = Date(1, date.month(), date.year());
	days += date.day();
	while (days >= 365) {
		d = incYears(date, 1) ;
		days -= (help::isLeapYear(d.year())) ? 366: 365;
	}
	int monDays = help::monthDays(d);
	while (days > monDays) {
		d = incMonths(d, 1);
		days -= monDays;
		monDays = help::monthDays(d);
	}
	return Date(days, d.month(), d.year());
}
Date incMonths (const Date& date, int months) {
	months += help::findMonth(date.month());
	int years = months / 12;
	months -= years * 12;
	years += date.year();
	return Date(std::min(date.day(), help::monthDays(months, years)), monthNames[months], years);
}
Date incYears (const Date& date, int year) {
	if(help::isLeapYear(date.year()) && !help::isLeapYear(date.year() + year) && date.month() == "February" && date.day() == 29) {
		return Date(28, date.month(), date.year() + year);
	}
	return Date(date.day(), date.month(), date.year() + year);
}

/****************************************************
*	Operators
*****************************************************/

Date& Date::operator= (const Date& date) {
	if(*this != date) {
		delete this->pimpl;
		this->pimpl = new Date::Impl(date.day(), date.month(), date.year());
	}
	return (*this);
}

bool operator== (const Date& l, const Date& r) {
	return (l.day() == r.day()) && (l.month() == r.month()) && (l.year() == r.year());
}
bool operator!= (const Date& l, const Date& r) {
	return !(l == r);
}
bool operator< (const Date& l, const Date& r) {
	if(l.year() < r.year()) {
		return true;
	}
	if(l.year() == r.year()) {
		if(help::findMonth(l.month()) < help::findMonth(r.month())) {
			return true;
		}
		if(l.month() == r.month()) {
			if(l.day() < r.day()) {
				return true;
			}
		}
	}
	return false;
}
bool operator<= (const Date& l, const Date& r) {
	return (l == r) || (l < r);
}
bool operator> (const Date& l, const Date& r) {
	return !(l <= r);
}
bool operator>= (const Date& l, const Date& r) {
	return !(l < r);
}

std::ostream& operator<< (std::ostream& o, const Date& d) {
	return o << d.day() << " " << d.month() << ", " << d.year();
}
std::istream& operator>> (std::istream& i, Date& orig) {
	int day, year;
	std::string month;
	i >> day;	
	i >> month;
	i >> year;	
	if(*month.rbegin() != ','|| i.fail()) {
		i.setstate(std::ios::failbit);
		throw "Invalid date value.";
	}
	orig = Date(day, month.substr(0, month.length()-1), year);
	return i;
}
















