#include <iostream>
#include <string>

/* ---------------------------------------------------
     template declaration (specified at the bottom)
   -------------------------------------------------- */
// --- datatype is generic, and specified when I call the function from the main in <double>
// --- note that it returns a pointer, so it is datatype*
template <typename datatype>
datatype* array_init(unsigned int n);

template <typename T>
void print_array(T* vec, unsigned int n);


int main()
{
  unsigned int length;
  double *pp;

  /* take array length */
  std::cout << "Write the array length: ";
  //cycle until a number is given in input
  while( !(std::cin >> length) ) {
	std::cout << "Please write a positive integer: ";
	std::cin.clear();
	std::cin.ignore(1000, '\n'); }

/* ---------------------------------------------------
       initialize the array + read and store data
   -------------------------------------------------- */
  // here pp is the address of the array of doubles
  pp = array_init<double>(length);

/* ---------------------------------------------------
		print in reverse order
   -------------------------------------------------- */
  print_array<double>(pp, length);


  delete[] pp;


return 0;
}

/* ---------------------------------------------------
		templates instantiation
   -------------------------------------------------- */

// it returns the pointer to the first element of the array
template <typename datatype>
datatype* array_init(unsigned int n)
{
  unsigned int i;
  datatype val;

  // array definition
  datatype *vec = new datatype[n]{0};

  std::cout << "Write the array elements:\n";
  //array elements initialization
  for(i=0; i<n; i++)
  {
	std::cin >> val;
	*(vec+i) = val;
  }

  return vec;
}

// print the vector in reverse order
template <typename T>
void print_array(T* vec, unsigned int n)
{
  unsigned int i;

  std::cout << "\nArray reversed:\n\n";
  for(i=0; i<n; i++)
  {
	std::cout << *(vec+n-i-1) << "  ";
  }
  std::cout << "\n\n";
}



