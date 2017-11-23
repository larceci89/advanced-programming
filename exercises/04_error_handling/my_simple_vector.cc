#include <iostream>

template <typename T>
class Vector {

	unsigned int _size;
	T* vec;

public:
	explicit Vector( const unsigned int l ) : _size{l}, vec{ new T[l]{} }

	unsigned int size() { return _size; }
	
	T& operator[]( const unsigned int n ) { return &(vec + n); }

	


}
