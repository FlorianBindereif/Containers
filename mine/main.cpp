#include <string>
#include <iostream>
// #include "vector.hpp"
#include <vector>

int main(void)
{
	std::vector<int>			original(1, 1);
	// ft::vector<int>				mine(10, 10);

	original[0] = 5;
	original.resize(1000);

	std::cout << original[0] << std::endl;
}
