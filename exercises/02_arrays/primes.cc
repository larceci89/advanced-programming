/* ---------------------------------------------------
Enlarging dynamically the size of an array might bring 
to very sparse data on the heap.
I prefer to allocate an array of maximum length = 100,
and then define a shorter one to copy my prime numbers
in. Then I can delete the long array.
   -------------------------------------------------- */
#include <iostream>
#include <string>

int main()
{
	unsigned int const max_length = 100;
	unsigned int pp_length, i, j=0;
	int reminder;
	bool flag_prime;

	// allocate array on the heap for max_length = 100
	int *pp = new int[max_length]{0};

	// start from 2
	pp[0] = 2;
	pp_length = 1;
	// seek for numbers up to 100 
	for(i=3;i<=100;i++)
	{
		flag_prime = true;
		// test the candidate against all smaller prime numbers
		for(j=0;j<pp_length;j++)
		{
			reminder = i % pp[j];
			if(reminder == 0)
			{
				flag_prime = false;
				break;
			}
		}
		if(flag_prime)
		{
			pp[pp_length] = i;
			pp_length++;
		}
	}

	//define a resized array, to free some memory on the heap
	int *ppnew = new int[pp_length]{0};
	//copy the primes into the resized array
	std::copy(pp, pp+pp_length, ppnew);
	//delete the exceedingly long array
	delete[] pp;

	//print the elements
	for(i=0;i<pp_length;i++)
		std::cout << *(ppnew+i) << "  ";
	std::cout << std::endl;

	delete[] ppnew;

	return 0;
}
