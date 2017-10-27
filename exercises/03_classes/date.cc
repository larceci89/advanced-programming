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

Date Date::add_oneday(Date date) {
	unsigned int day = date.fday();
	monthtype month = date.fmonth();
	unsigned int year = date.fyear();
	unsigned int day_threshold;

	switch (month)
	{
		case monthtype::feb:
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

int main() {

	unsigned int dd, mm, yy, numdays;
	bool flag_stop = true;

	std::cout << "Insert the day: ";
	std::cin >> dd;
	std::cout << "\nInsert the month (number): ";
	std::cin >> mm;
	std::cout << "\nInsert the year: ";
	std::cin >> yy;
	std::cout << std::endl << std::endl;
	
	Date date(dd,mm,yy);

	std::cout << "You have inserted the date: " << date.fday() << "/" << int(date.fmonth()) << "/" << date.fyear() << std::endl << std::endl;

	while(flag_stop){
		std::cout << "Insert the number of days to add: ";
		std::cin >> numdays;
		date = date.add_day(date, numdays);
		std::cout << "New date: " << date.fday() << "/" << int(date.fmonth()) << "/" << date.fyear() << std::endl << std::endl;
		if(numdays == 0)
			flag_stop = false;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}

	return 0;
}
