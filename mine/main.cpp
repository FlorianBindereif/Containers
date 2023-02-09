#include <string>
#include <iostream>
#include "vector.hpp"
#include <vector>
#include "map.hpp"
#include "string"

int main(void)
{
	ft::map<int, std::string> test_map;
	test_map.insert(ft::make_pair<int, std::string>(6, std::string("hello")));
	test_map.insert(ft::make_pair<int, std::string>(5, std::string("hello")));
	test_map.insert(ft::make_pair<int, std::string>(10, std::string("hello")));
	test_map.insert(ft::make_pair<int, std::string>(1, std::string("hello")));
	test_map.print_tree();
}


			