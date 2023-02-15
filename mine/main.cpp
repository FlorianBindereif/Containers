#include <string>
#include <iostream>
#include "vector.hpp"
#include <vector>
#include "map.hpp"
#include "string"

int main(void)
{
	ft::map<int, std::string> test_map;
	test_map.insert(ft::make_pair<int, std::string>(1000, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1001, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1004, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1005, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1006, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1007, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1008, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1009, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1011, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1012, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1013, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1014, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1015, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1016, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1017, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(1018, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(23, std::string("hello6")));
	test_map.insert(ft::make_pair<int, std::string>(25, std::string("hello5")));
	test_map.insert(ft::make_pair<int, std::string>(1, std::string("hello10")));
	test_map.insert(ft::make_pair<int, std::string>(2, std::string("hello1")));
	test_map.insert(ft::make_pair<int, std::string>(3, std::string("hello11")));
	test_map.insert(ft::make_pair<int, std::string>(75, std::string("hello12")));
	test_map.insert(ft::make_pair<int, std::string>(30, std::string("hello13")));
	test_map.insert(ft::make_pair<int, std::string>(-22, std::string("hello14")));
	test_map.insert(ft::make_pair<int, std::string>(-23, std::string("hello14")));
	test_map.insert(ft::make_pair<int, std::string>(0, std::string("hello14")));

	for (ft::map<int, std::string>::iterator it = test_map.begin(); it != test_map.end(); ++it)
		std::cout << (*it).first << "  ";
	std::cout << std::endl;
	// test_map.print_tree();
	// std::cout << test_map.size() << std::endl;
	test_map.erase(-23);
	// std::cout << test_map.size() << std::endl;
	for (ft::map<int, std::string>::iterator it = test_map.begin(); it != test_map.end(); ++it)
		std::cout << (*it).first << "  ";
	// test_map.print_tree();

	// test_map.clear();
}