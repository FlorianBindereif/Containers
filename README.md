# Containers

## Description
My personal implementation of some of the container class templates from the C++ standard template library (STL). This also included the corresponding iterator systems as well as the required utilities. 

The goal was to get a better understanding of the internal functionality of the different holder objects and the tradeoffs in complexity involved. 
 
Containers:
[`vector`],  [`map`],  [`stack`], [`set`]

Utils :
[`iterator_traits`], [`iterators`], [`reverse_iterator`], [`enable_if`], [`is_integral`], [`equal`], [`lexicographical_compare`], [`pair`],  [`make_pair`]

## Implementation

To facilitate full interoperability between my containers and the STL algorithms I was following the original implementation of the STL source code closely. A good overview over the required member functions and their declarations was provided by [cplusplus.com]. To guarantee time complexity comparable to the STL containers an auto-balancing [Red-Black Tree] was chosen as the underlying data structure for map and set. The  entire code is written in accordance to the C++98 standard.
  
## Testing
To check my own implementation against the original STL version, a test file, which tests for runtime and memory leaks was included. The Makefile automates the comparison between the `ft` and the `std` namespaces.

The rule `run` compiles the test file into two binaries, ownContainerTest and stlContainerTest, using the containers from both namespaces and runs the test. A small benchmark output is provided into the terminal and the output is put into ownData and stlData respecively. The Makefile rule `diff` then provides a diff on both data files. With identical output only the benchmark times are stated.

[container]: https://en.cppreference.com/w/cpp/container

[`vector`]: https://cplusplus.com/reference/vector/vector/

[`map`]: https://cplusplus.com/reference/map/map/

[`stack`]: https://cplusplus.com/reference/stack/stack/

[`set`]: https://cplusplus.com/reference/set/set/

[`iterator_traits`]: https://cplusplus.com/reference/iterator/iterator_traits/

[`iterators`]: https://cplusplus.com/reference/iterator/

[`reverse_iterator`]: https://cplusplus.com/reference/iterator/reverse_iterator/

[`enable_if`]: https://cplusplus.com/reference/type_traits/enable_if/

[`is_integral`]: https://cplusplus.com/reference/type_traits/is_integral/

[`equal`]: https://cplusplus.com/reference/algorithm/equal/

[`lexicographical_compare`]: https://cplusplus.com/reference/algorithm/lexicographical_compare/

[`pair`]: https://cplusplus.com/reference/utility/pair/

[`make_pair`]: https://cplusplus.com/reference/utility/make_pair/

[red-black tree]: https://en.wikipedia.org/wiki/Red-black_tree

[cplusplus.com]: https://cplusplus.com/reference/

[Red-Black Tree]: https://www.codesdope.com/course/data-structures-red-black-trees/
