#pragma once

namespace ft
{
	/* ft::pair is a class template that provides a way to store two heterogeneous objects as a single unit.*/
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1			first_type;
		typedef T2			second_type;

		first_type			first;
		second_type			second;

		/***********************************************
			Constructors
		***********************************************/
		
		/*Default constructor. Value-initializes both elements of the pair, first and second.*/
		pair(): first(T1()), second(T2()) {}

		/*Constructor that initializes @first with @x and @second with @y.*/
		pair(const T1& x, const T2& y): first(x), second(y) {}

		/*Copy Constructor initializes @first with @p.first and @second with @p.second.*/
		template <typename U1, typename U2>
		pair(const pair<U1, U2>& p): first(p.first), second(p.second) {}

		/***********************************************
			DESTRUCTORS
		***********************************************/
		/* Destructs the pair.*/
		~pair() {}

		/***********************************************
			ASSIGNMENT
		***********************************************/
		
		/*Copy assignment operator. Replaces the contents with a copy of the contents of @other.*/
		pair& operator=(const pair& other)
		{
			first = other.first;
			second = other.second;
			return *this;
		}
	};
	
	/***********************************************
		NON-MEMBER FUNCTIONS
	***********************************************/

	/*Creates a pair object of type, defined by the argument types */
	template <typename T1, typename T2>
	pair<T1, T2> make_pair(T1 t, T2 u)
	{ return pair<T1, T2>(t, u); }

	/*Checks if the contents of lhs and rhs are equal*/
	template <typename T1, typename T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first == rhs.first && lhs.first == rhs.first; }

	/*Checks if the contents of lhs and rhs are not equal*/
	template <typename T1, typename T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first != rhs.first || lhs.first != rhs.first; }

	/*Compares the contents of lhs and rhs lexicographically.*/
	template <typename T1, typename T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first < rhs.first && lhs.first < rhs.first; }

	/*Compares the contents of lhs and rhs lexicographically.*/
	template <typename T1, typename T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first > rhs.first && lhs.first > rhs.first; }

	/*Compares the contents of lhs and rhs lexicographically.*/
	template <typename T1, typename T2>
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first <= rhs.first && lhs.first <= rhs.first; }

	/*Compares the contents of lhs and rhs lexicographically.*/
	template <typename T1, typename T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{ return lhs.first >= rhs.first && lhs.first >= rhs.first; }
}