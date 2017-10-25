#include <iostream>
#include <math.h>

unsigned int unsinteger_input();

int main()
{
	unsigned int NN, i, j;
	//take maximum number from input (it must be integer and positive)
	NN = unsinteger_input();

	//initialize boolean vector of length max_number
	bool *vec = new bool[NN];
	for(i=0;i<NN;i++)
		vec[i] = true;

	//cycle from 2 up to sqrt(NN)
	for(i=2;i<=sqrt(NN);i++)
	{
		//cycle over j, and check i^2, i^2 + i, ... up to the closest to NN
		for(j=i*i;j<=NN;j=j+i)
		{
			//turn every element to false
			vec[j-1] = false;
		}
	}

	//print only the numbers for true elements
	std::cout << "Prime numbers up to " << NN << ":\n";
	for(i=1;i<NN;i++)
	{
		if(vec[i])
			std::cout << i+1 << "  ";
	}
	std::cout << std::endl;

	//delete the allocated vectors in the heap
	delete[] vec;

	return 0;
}

/*-----------------------------------------------------
   function to take a positive integer number in input
  -----------------------------------------------------*/
unsigned int unsinteger_input()
{
	double val;
	
  std::cout << "Write the array length: ";
  //cycle until a positive integer number is given in input
  while( !(std::cin >> val) || (val != int(val)) || (val <= 0) ) {
	std::cout << "Please write a positive integer: ";
	std::cin.clear();
	std::cin.ignore(1000, '\n'); }

	return (unsigned int)val;
}
