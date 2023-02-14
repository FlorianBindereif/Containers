#include <string>
#include <iostream>
#include "vector.hpp"
#include <vector>
#include "map.hpp"
#include "string"

int main(void)
{
	ft::map<int, std::string> test_map;
	test_map.insert(ft::make_pair<int, std::string>(6, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(5, std::string("hello5")));
	test_map.insert(ft::make_pair<int, std::string>(10, std::string("hello10")));
	test_map.insert(ft::make_pair<int, std::string>(1, std::string("hello1")));
	test_map.insert(ft::make_pair<int, std::string>(11, std::string("hello11")));
	test_map.insert(ft::make_pair<int, std::string>(12, std::string("hello12")));
	test_map.insert(ft::make_pair<int, std::string>(13, std::string("hello13")));
	test_map.insert(ft::make_pair<int, std::string>(14, std::string("hello14")));
	// std::cout << test_map.at(1212) << std::endl;
	ft::map<int, std::string> test_map2(test_map);

	// test_map2.insert(ft::make_pair<int, std::string>(15, std::string("hello15")));

	// test_map.clear();
}


			