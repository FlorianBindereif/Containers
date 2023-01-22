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
}