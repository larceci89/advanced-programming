#include <iostream>

struct input_error{ std::string error_msg; };

int main()
{
  bool flag = true;
  double num;

  do
  {
	try
	{
		std::cout << "Enter an integer number: ";
		if( !(std::cin >> num) )
			throw input_error{"This is a word!\n"};
		else if( num != int(num) )
			throw input_error{"This is a rational!\n"};

		flag = false;

	}catch (const input_error& s)
	{
		std::cerr << s.error_msg << std::endl;
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}catch (...)
	{
		std::cerr << "Unknow exception!\nAborting...\n";
		return 1;
	}
  }while(flag);

  std::cout << "\n";
  std::cout << "Number entered correctly: " << num << "\n";

return 0;
}
