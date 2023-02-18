
#pragma once

#include <iterator>

namespace ft
{
	/***********************************************
		ITERATOR TAGS
	***********************************************/

	/*Iterator category tags carry information that can be used to select the most efficient algorithms
	for the specific requirement set that is implied by the category. */
	typedef std::output_iterator_tag        output_iterator_tag;
	typedef std::input_iterator_tag         input_iterator_tag;
	typedef std::forward_iterator_tag       forward_iterator_tag;
	typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag random_access_iterator_tag;

	/***********************************************
		ITERATOR TRAITS
	***********************************************/

	/*Primary template struct for interator_traits is used to obtain information about the properties of an iterator*/
	template <typename Iter>
	struct iterator_traits 
	{
		typedef typename Iter::value_type        value_type;
		typedef typename Iter::difference_type   difference_type;
		typedef typename Iter::pointer           pointer;
		typedef typename Iter::reference         reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	/*Specialization of iterator_traits for pointer types*/
	template <typename T>
	struct iterator_traits<T*> 
	{
		typedef T                          value_type;
		typedef std::ptrdiff_t             difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
		typedef random_access_iterator_tag iterator_category;
	};

	/*Specialization of iterator_traits for pointer to const types*/
	template <typename T>
	struct iterator_traits<const T*> 
	{
		typedef T                          value_type;
		typedef std::ptrdiff_t             difference_type;
		typedef const T*                   pointer;
		typedef const T&                   reference;
		typedef random_access_iterator_tag iterator_category;
	};

	/* helper function that used to determine the category of an iterator passed as an argument.*/
	template <typename Iterator>
	inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&)
	{ return typename iterator_traits<Iterator>::iterator_category();}
}