#include <string>
#include <iostream>
#include "vector.hpp"
#include <vector>

int main(void)
{
	std::vector<int>			original(10, 10);
	ft::vector<int>				mine(10, 10);

	std::cout << "original " << original[100] << std::endl;
	// std::cout << "mine " << mine.size() << std::endl;
}
