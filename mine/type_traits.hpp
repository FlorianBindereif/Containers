#pragma once

namespace ft
{
	/***********************************************
		TRUE/FALSE TYPE
	***********************************************/

	struct true_type
	{
		static const bool value = true;
		typedef true_type type;
	};

	struct false_type
	{
		static const bool value = false;
		typedef false_type type;
	};

	/***********************************************
		ENABLE IF
	***********************************************/

	template <bool B, typename T = void>
	struct enable_if{};

	template <typename T>
	struct enable_if<true, T>
	{typedef T type; };

	/***********************************************
		QUALIFIER HELPER FUNCTIONS
	***********************************************/

	template <typename T>
	struct remove_const 
	{ typedef T type; };

	template <typename T>
	struct remove_const<const T> 
	{ typedef T type; };

	template <typename T>
	struct remove_volatile 
	{ typedef T type; };

	template <typename T>
	struct remove_volatile<volatile T> 
	{ typedef T type; };

	template <typename T>
	struct remove_cv 
	{ typedef typename remove_volatile<typename remove_const<T>::type>::type type; };


	/***********************************************
		INTEGER TYPES
	***********************************************/	

	/* Base template for integer_type checking*/
	template<typename T>
	struct is_integral_spec : public false_type {};

	/* Specialisation templates for integer_type checking*/
	template<>
	struct is_integral_spec <bool>: public true_type {};

	template<>
	struct is_integral_spec <signed char>: public true_type {};
	
	template<>
	struct is_integral_spec <unsigned char>: public true_type {};

	template<>
	struct is_integral_spec <char>: public true_type {};

	template<>
	struct is_integral_spec <short int>: public true_type {};
	
	template<>
	struct is_integral_spec <unsigned short int>: public true_type {};

	template<>
	struct is_integral_spec <int>: public true_type {};
	
	template<>
	struct is_integral_spec <unsigned int>: public true_type {};
	
	template<>
	struct is_integral_spec <long int>: public true_type {};

	template<>
	struct is_integral_spec <unsigned long int>: public true_type {};

	template <typename T>
	struct is_integral : is_integral_spec <typename remove_cv<T>::type> {};

	/***********************************************
		COMPARISON OF VALUE TYPES
	***********************************************/
		
	template <typename, typename>
	struct are_same: public false_type {};

	template<typename Tp>
	struct are_same<Tp, Tp>:public true_type {};
}