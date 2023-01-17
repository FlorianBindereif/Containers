#pragma once

namespace ft
{
	//defines of true/false type
	struct true_type
	{
		static const bool equality = true;
		typedef true_type type;
	};

	struct false_type
	{
		static const bool equality = false;
		typedef false_type type;
	};

	//enable_if
	template <bool B, typename T = void>
	struct enable_if{};

	template <typename T>
	struct enable_if<true, T>
	{typedef T type; };

	//Integer types
	template<typename T>
	struct is_integer : public false_type {};

	template<>
	struct is_integer <bool>: public true_type {};

	template<>
	struct is_integer <signed char>: public true_type {};
	
	template<>
	struct is_integer <char>: public true_type {};

	template<>
	struct is_integer <short int>: public true_type {};
	
	template<>
	struct is_integer <int>: public true_type {};
	
	template<>
	struct is_integer <long int>: public true_type {};
	
	template<>
	struct is_integer <unsigned int>: public true_type {};

	template<>
	struct is_integer <unsigned long int>: public true_type {};
	
	// Comparison of equality of types
	template <typename, typename>
	struct are_same: public false_type {};

	template<typename Tp>
	struct are_same<Tp, Tp>:public true_type {};
}