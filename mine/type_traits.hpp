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
		INTEGER TYPES
	***********************************************/	

	/* Base template for integer_type checking*/
	template<typename T>
	struct is_integer : public false_type {};

	/* Specialisation templates for integer_type checking*/
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
	
	/***********************************************
		COMPARISON OF VALUE TYPES
	***********************************************/
		
	template <typename, typename>
	struct are_same: public false_type {};

	template<typename Tp>
	struct are_same<Tp, Tp>:public true_type {};
}