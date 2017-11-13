/* about error handling:
	get_date() provides checks on input and throws errors until a good input is given.
	Still, one can enter a day not compatible with a certain month, say 31-11-****.
	This is done to test the function check_Date(), which uses "assert" to check this incompatibilities.
	
	It would be nice to put the check inside the constructor or somewhere in the class... */
#include <iostream>
#include <string>
#include <assert.h>

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

//	determines the number of days in a specific month
unsigned int fday_threshold( monthtype month, unsigned int year ){
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

	return day_threshold;
}


//	operation that adds one day at a time
Date Date::add_oneday(Date date) {
	unsigned int day = date.fday();
	monthtype month = date.fmonth();
	unsigned int year = date.fyear();
	unsigned int day_threshold;

	day_threshold = fday_threshold(month, year);

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

//	check the validity of Date type
bool check_Date(Date d){
	unsigned int day = d.fday();
	monthtype month = d.fmonth();
	unsigned int year = d.fyear();
	unsigned int day_threshold;
	// if ok, check the day according to the month
	day_threshold = fday_threshold(month, year);
	assert(day>=1 && day<=day_threshold);

	return true;
}

// type that contains the possible input error message
struct input_error{ std::string err_string; };

/* function to get input date, which throws exceptions if input is not valid */
unsigned int get_date(const unsigned int n){
	int val;
	std::string s, msg;
	int lowlimit, uplimit;
	bool flag_stop = true;

	// choose the parameters depending on if I input day, month or year
	switch (n){
	   case 1:
		s = "day";
		lowlimit = 1;
		uplimit = 31;
		break;
	   case 2:
		s = "month";
		lowlimit = 1;
		uplimit = 12;
		break;
	   case 3:
		s = "year";
		lowlimit = 0;
		uplimit = 0;
		break;
	}

	//cycle until I get a good input value
	while (flag_stop){
	   try{
		std::cout << "Insert the " << s << ": ";
		// throw an exception if it is a word
		if ( !(std::cin >> val) )
			throw input_error{"This is a word, not a number!\n"};
		// for uplimit == 0, I consider the year, which has no upper limit
		else if (uplimit != 0)
		{
		   if (val < lowlimit || val > uplimit) {
			msg = "This is not a valid " + s + "!\n";
			throw input_error{msg}; }
		}else{
		   if (val < lowlimit)
			throw input_error{"This is not a valid year!\n"};
		}

		flag_stop = false;

	   }catch(const input_error& e){
	   // in case of exception, I write an error message and reset the cin buffer
		std::cerr << e.err_string << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	   }
	}
	return (unsigned int) val;
}


int main() {
	unsigned int dd, mm, yy, numdays;
	bool flag_stop = true;

	// get day, month and year in input
	dd = get_date(1);
	mm = get_date(2);
	yy = get_date(3);

	Date date(dd,mm,yy);
	if (!check_Date(date)){
		std::cout << "Invalid date! Aborting...\n";
		return 1; }

	// writes the input date, exploiting the "<<" operator defined before
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
