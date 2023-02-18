#pragma once

namespace ft
{
	/***********************************************
		MODIFYING OPERATIONS
	***********************************************/

	/*Assigns the given @value to the elements in the range [first, last).*/
	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}

	/*Assigns the given @value to the first @count elements in the range beginning at @first*/
	template <typename OutputIterator, typename Size, typename T>
	void fill_n(OutputIterator first, Size count, const T& value)
	{
		if (count > 0)
		{
			for (Size filled = 0; filled < count; ++filled, ++first)
			{ *first = value;}
		}
	}

	/*swaps the values of two objects*/
	template <typename T>
	void swap(T& first, T& second)
	{
		T tmp = first;
		first = second;
		second = tmp;
	}

	/*Copies a range of elements in backwards order*/
	template <typename BidirIterator>
	BidirIterator copy_backward(BidirIterator first, BidirIterator last, BidirIterator d_last)
	{
		while (last != first) 
		{
			--last;
			--d_last;
			*d_last = *last;
    	}
    	return d_last;
	}

	/*copies a range of elements to a new location*/
	template <typename InputIterator, typename OutputIterator>
	OutputIterator copy(
		InputIterator first, 
		InputIterator last,
        OutputIterator result)
	{
		for (; first != last; ++result, ++first)
        	*result = *first;
    	return result;
    }
	
	/***********************************************
		COMPARISON OPERATIONS
	***********************************************/
	
	/*Returns the smaller of the given values.*/
	template <typename T>
	const T& min(const T& first, const T& second)
	{
		if (second < first)
			return second;
		return first;
	}

	/*Returns the greater of the given values.*/
	template <typename T>
	const T& max(const T& first, const T& second)
	{
		if (second > first)
			return second;
		return first;
	}

	/*Determines if two sets of elements are the same*/
	template <typename InputIterator_lhs, typename InputIterator_rhs>
	bool equal(
		InputIterator_lhs first, 
		InputIterator_lhs last,
		InputIterator_rhs to_compare_first)
	{
		for (; first != last; ++first, ++to_compare_first)
			if (!(*first == *to_compare_first))
				return false;
		return true;
	}

	/*Returns true if one range is lexicographically less than another*/
	template <typename InputIterator_lhs, typename InputIterator_rhs>
	bool lexicographical_compare(
		InputIterator_lhs first, 
		InputIterator_lhs last,
		InputIterator_rhs to_compare_first,
		InputIterator_rhs to_compare_last)
	{
		for (; (first != last) && (to_compare_first != to_compare_last); ++first, ++to_compare_first)
		{
			if (*first < *to_compare_first)
				return true;
			if (*to_compare_first < *first)
				return false;
		}
		return (first == last) && (to_compare_first != to_compare_last);
	}
}