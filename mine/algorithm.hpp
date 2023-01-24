namespace ft
{
	template <typename ForwardIterator, typename T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}

	template <typename OutputIterator, typename Size, typename T>
	void fill_n(OutputIterator first, Size count, const T& value)
	{
		if (count > 0)
		{
			for (int filled = 0; filled < count; ++filled, ++first)
			{ *first = value;}
		}
	}

	template <typename T>
	const T& min(const T& first, const T& second)
	{
		if (second < first)
			return second;
		return first;
	}

	template <typename T>
	const T& max(const T& first, const T& second)
	{
		if (second > first)
			return second;
		return first;
	}

	template <typename T>
	void swap(T& first, T& second)
	{
		T tmp = first;
		first = second;
		second = tmp;
	}


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

	template <typename InputIterator_lhs, typename InputIterator_rhs>
	bool lexicographical_compare(
		InputIterator_lhs first, 
		InputIterator_lhs last,
		InputIterator_rhs to_compare_first,
		InputIterator_rhs to_compare_last)
	{
		for (; first != last && to_compare_first != to_compare_last; ++first, ++to_compare_first)
		{
			if (*first < *to_compare_first)
				return true;
			if (*to_compare_first < *first)
				return false;
		}
		return first == last && to_compare_first != to_compare_last;
	}

	template <typename BidirIterator>
	BidirIterator move_backward(BidirIterator first, BidirIterator last, BidirIterator d_last)
	{
		while (last != first) 
		{
			--last;
			--d_last;
			*d_last = *last;
    	}
    	return d_last;
	}

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
}


}