#include <iostream>
#include <string>

enum class monthtype {jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};

class Date{
	unsigned int day;
	monthtype month;
	unsigned int year;

public:
	//constructor
	Date(unsigned int _day, unsigned int _month, unsigned int _year) : day{_day} , month{monthtype(_month)} , year{_year} {}
	//basic functions
	unsigned int fday() const { return day; }
	monthtype fmonth() const { return month; }
	unsigned int fyear() const { return year; }
	//function that adds n days
	Date add_day(Date date, const unsigned int n) {
		unsigned int i;
		for(i=1; i<=n; i++)
			date = add_oneday(date);
		return date; }
	//function that adds one single day
	Date add_oneday(Date date);
};

/*	logical operation to assess whether a year is leap or not
	NOTE: it is defined before the function add_oneday, since this function
	uses it	*/
bool is_leap(const unsigned int y){
	if (y % 4 == 0)
		return true;
	else
		return false;
}

//	operation that adds one day at a time
Date Date::add_oneday(Date date) {
	unsigned int day = date.fday();
	monthtype month = date.fmonth();
	unsigned int year = date.fyear();
	unsigned int day_threshold;

	switch (month)
	{
		case monthtype::feb:
			if ( is_leap(year) )
				day_threshold = 29;
			else
				day_threshold = 28;
			break;
		case monthtype::apr:
		case monthtype::jun:
		case monthtype::sep:
		case monthtype::nov:
			day_threshold = 30;
			break;
		default:
			day_threshold = 31;
			break;
	}

	if(day == day_threshold)
	{
		day = 1;
		if(month == monthtype::dec)
		{
			month = monthtype::jan;
			year++;
		}else
			month = monthtype( int(month)+1 );
	}else
		day++;

	date.day = day;
	date.month = month;
	date.year = year;

	return date;
}

//	logical equal operation between class elements
bool operator == (const Date& lhs, const Date& rhs){
	if ( lhs.fday() == rhs.fday() )
	{
	   if ( lhs.fmonth() == rhs.fmonth() )
	   {
		if ( lhs.fyear() == rhs.fyear() )
			return true;
	   }
	}
	return false;
}

bool operator != (const Date& lhs, const Date& rhs){
	if (lhs == rhs)
		return false;
	else
		return true;
}

//	operator that describes how to print a Date element with <<
std::ostream& operator << (std::ostream& os, const Date& d){
	return os << d.fday() << "/" << int(d.fmonth()) << "/" << d.fyear();
}


int main() {

	unsigned int dd, mm, yy, numdays;
	bool flag_stop = true;

	// get the date in input
	std::cout << "Insert the day: ";
	std::cin >> dd;
	std::cout << "\nInsert the month (number): ";
	std::cin >> mm;
	std::cout << "\nInsert the year: ";
	std::cin >> yy;
	std::cout << std::endl << std::endl;
	
	Date date(dd,mm,yy);

	// writes the input date
	std::cout << "You have inserted the date: " << date << std::endl << std::endl;

	// check and write if the year is leap or not
	if ( is_leap(date.fyear()) )
		std::cout << "This year is leap\n\n";
	else
		std::cout << "This year is not leap\n\n";

	// ask for a number of days to add and compute the new date
	// stops when 0 is entered
	while(flag_stop){
		std::cout << "Insert the number of days to add (insert 0 to stop): ";
		std::cin >> numdays;
		if(numdays == 0)
			flag_stop = false;
		else{
			date = date.add_day(date, numdays);
			std::cout << "New date: " << date.fday() << "/" << int(date.fmonth()) << "/" << date.fyear() << std::endl << std::endl;
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
	}

	return 0;
}
