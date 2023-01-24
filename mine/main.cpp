#include <string>
#include <iostream>
#include "vector.hpp"
#include <vector>

#ifndef NAMESPACE
#define NAMESPACE ft
#endif

#define INTVEC NAMESPACE::vector<int>
#define STRVEC NAMESPACE::vector<std::string>
#define DBLVEC NAMESPACE::vector<double>

template <typename T>
void vec_print(const T& vec __attribute__((unused)))
{
    std::cout << "size: " << vec.size() << "\n";
    std::cout << "max_size: " << vec.max_size() << "\n";
    std::cout << "capacity: " << vec.capacity() << "\n";
    std::cout << "empty: " << vec.empty() << "\n";
    if (vec.size() > 0)
        std::cout << "vec.front(): " << vec.front() << "vec.back()" << vec.back() << std::endl;
    std::cout << "\ncontent_index: ";
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << "vec[" << i << "]: " << vec[i] << "  ";
    }
    // std::cout << "\ncontent_iter:  ";
    // for (typename T::const_iterator it = vec.begin(); it != vec.end(); it++) {
    //     std::cout << "vec[" << it - vec.begin() << "]: " << *it << "  ";
    // }
    std::cout << std::endl;
}

int main(void)
{
	INTVEC ivec;
    INTVEC ivec_cpy(ivec);
    vec_print(ivec);
    vec_print(ivec_cpy);
	INTVEC ivec2(10, 42);
    INTVEC ivec2_cpy(ivec2);
    vec_print(ivec2);
    vec_print(ivec2_cpy);
    std::vector<int> std_vec(100, 42);
    INTVEC           ivec3(std_vec.begin(), std_vec.end());
    INTVEC           ivec3_cpy(ivec2);
    vec_print(ivec3);
    vec_print(ivec3_cpy);
}

			