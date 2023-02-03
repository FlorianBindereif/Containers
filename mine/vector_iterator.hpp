#pragma once

#include "type_traits.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	/* Converts iterator that is not a class, e.g. a pointer, into an iterator that is a class.
	@Container exists so that different containers using this template can instantiate different types, 
	even if the Iterator parameter is the same.*/
	template <typename Iterator, typename Container>
	class normal_iterator
	{
		protected:
			Iterator current_;

			public:
			typedef Iterator                                                    iterator_type;
			typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
			typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
			typedef typename ft::iterator_traits<Iterator>::reference           reference;
			typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;

		public:
			/***********************************************
				Constructors
			***********************************************/

			/*constructor initialising with @Iterator type*/
			normal_iterator()
			: current_(iterator_type()){}

			/*constructor takes object of the Iterator type and initializes with the passed Iterator object.*/
			explicit normal_iterator(const iterator_type& iter)
			:current_(iter){}

			/*constructor that allows iterator to const_iterator conversion*/
			template <typename Iter>
			normal_iterator(const normal_iterator<
				Iter, typename ft::enable_if<
				ft::are_same<Iter, typename Container::pointer>::value, Container>::type>& it)
			:current_(it.base()) {}

			/***********************************************
				DESTRUCTORS
			***********************************************/

			/*default destructor*/
			~normal_iterator(){}
			
			/***********************************************
				FORWARD ITERATOR REQUIREMENTS
			***********************************************/

			reference operator*() const
			{return *current_;}
 
			pointer operator->() const
			{return &(operator*());}

			normal_iterator& operator++()
			{
				++current_;
				return *this;
			}

			normal_iterator operator++(int)
			{
				normal_iterator tmp(*this);
				++current_;
				return tmp;
			}

			iterator_type base() const
			{return current_;}

			/***********************************************
				BIDIRECTIONAL ITERATOR REQUIREMENTS
			***********************************************/
			normal_iterator& operator--()
			{
				--current_;
				return *this;
			}

			normal_iterator operator--(int)
			{
				normal_iterator tmp(*this);
				--current_;
				return tmp;
			}

			/***********************************************
				RANDOM ACCESS ITERATOR REQUIREMENTS
			***********************************************/
			reference operator[](const difference_type& n) const
			{return current_[n];}

			normal_iterator operator+(const difference_type& n) const
			{ return normal_iterator(current_ + n);}

			normal_iterator operator-(const difference_type& n) const
			{return normal_iterator(current_ - n);}

			normal_iterator& operator+=(const difference_type& n)
			{
				current_ += n;
				return *this;
			}

			normal_iterator& operator-=(const difference_type& n)
			{
				current_ -= n;
				return *this;
			}
	};

	/***********************************************
		ITERATOR COMPARISON REQUIREMENTS
	***********************************************/
	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool operator==
	(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() == rhs.base();}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool operator!=
	(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() != rhs.base();}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool operator<
	(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() < rhs.base();}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool operator>
	(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() > rhs.base();}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool operator>=
	(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() >= rhs.base();}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool operator<=
	(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() <= rhs.base();}

	/***********************************************
		ITERATOR ARIMETHICS REQUIREMENTS
	***********************************************/

	/*Allows for mixed iterator/const_iterator parameters*/
	template <typename IteratorL, typename IteratorR, typename Container>
	inline typename normal_iterator<IteratorL, Container>::difference_type operator-(
		const normal_iterator<IteratorL, Container>& lhs, 
		const normal_iterator<IteratorR, Container>& rhs)
	{ return lhs.base() - rhs.base();}

	template <typename Iterator, typename Container>
	inline typename normal_iterator<Iterator, Container>::difference_type operator-(
		const normal_iterator<Iterator, Container>& lhs, 
		const normal_iterator<Iterator, Container>& rhs)
	{ return lhs.base() - rhs.base();}

	template <typename Iterator, typename Container>
	inline normal_iterator<Iterator, Container> operator+(
		typename normal_iterator<Iterator, Container>::difference_type n,
		const normal_iterator<Iterator, Container>& it)
		{return normal_iterator<Iterator, Container>(it.base() + n);}

	/* Reverse iterator that iterates through a container in the reverse order. 
	That is, it starts at the last element of the container and moves towards the first element.*/
	template <typename Iterator>
	class reverse_iterator
	{
		protected:
			Iterator current_;

		public:
			typedef Iterator                                                    iterator_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
			typedef typename ft::iterator_traits<Iterator>::reference           reference;
			typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
			typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
			typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;

		public:
			/***********************************************
				Constructors
			***********************************************/

			/*default constructor default initializes @current. If it is a pointer it is zero-initialized*/
			reverse_iterator()
			: current_(){}

			/*takes iterator object and turns it in into a reverse_iterator*/
			explicit reverse_iterator(iterator_type iter)
			:current_(iter) {}

			/*copy Constructor*/
			reverse_iterator(const reverse_iterator& iter)
			:current_(iter.current_){}
			
			/* constructor creates a copy of reverse_iterator with the same base type */
			template <typename Iter>
			reverse_iterator(const reverse_iterator<Iter>& iter)
			:current_(iter.base()) {}

			/***********************************************
				DESTRUCTORS
			***********************************************/

			/*Default Destructor*/
			~reverse_iterator(){}

			/***********************************************
				ASSIGNMENT
			***********************************************/

			template <typename Iter>
			reverse_iterator& operator=(const reverse_iterator<Iter>& other)
			{
				current_ = other.base();
				return *this;
			}

			/***********************************************
				FORWARD ITERATOR REQUIREMENTS
			***********************************************/
			reference operator*() const
			{
				iterator_type tmp = current_;
				return *(--tmp);
			}

			pointer operator->() const
			{ return &(operator*());}

			reverse_iterator& operator++()
			{
				--current_;
				return *this;
			}

			reverse_iterator operator++(int)
			{
				reverse_iterator tmp(*this);
				--current_;
				return tmp;
			}

			/***********************************************
				BIDIRECTIONAL ITERATOR REQUIREMENTS
			***********************************************/
			reverse_iterator& operator--()
			{
				++current_;
				return *this;
			}

			reverse_iterator operator--(int)
			{
				reverse_iterator tmp(*this);
				++current_;
				return tmp;
			}

			/***********************************************
				RANDOM ACCESS ITERATOR REQUIREMENTS
			***********************************************/
			reference operator[](const difference_type& n) const
			{ return *(*this + n);}

			reverse_iterator operator+(const difference_type& n) const
			{ return reverse_iterator(current_ - n);}

			reverse_iterator operator-(const difference_type& n) const
			{ return reverse_iterator(current_ + n);}

			reverse_iterator& operator+=(const difference_type& n)
			{
				current_ -= n;
				return *this;
			}

			reverse_iterator& operator-=(const difference_type& n)
			{
				current_ += n;
				return *this;
			}

			iterator_type base() const
			{ return current_;}
	};


	/***********************************************
		ITERATOR ARIMETHICS REQUIREMENTS
	***********************************************/

	template <typename Iterator>
	inline typename reverse_iterator<Iterator>::difference_type operator- (
		const reverse_iterator<Iterator>& lhs,
		const reverse_iterator<Iterator>& rhs)
	{ return rhs.base() - lhs.base();}

	template <typename Iterator>
	inline reverse_iterator<Iterator> operator+ (
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& iter)
	{ return reverse_iterator<Iterator>(iter.base() - n);}


	/***********************************************
		MIXED ITERATOR COMPARISON REQUIREMENTS
	***********************************************/

	template <typename IteratorL, typename IteratorR>
	inline bool operator==(
		const reverse_iterator<IteratorL>& lhs, 
		const reverse_iterator<IteratorR>& rhs)
	{ return lhs.base() == rhs.base();}

	template <typename IteratorL, typename IteratorR>
	inline bool operator!=(
		const reverse_iterator<IteratorL>& lhs, 
		const reverse_iterator<IteratorR>& rhs)
	{ return lhs.base() != rhs.base();}

	template <typename IteratorL, typename IteratorR>
	inline bool operator<(
		const reverse_iterator<IteratorL>& lhs, 
		const reverse_iterator<IteratorR>& rhs)
	{ return lhs.base() > rhs.base();}

	template <typename IteratorL, typename IteratorR>
	inline bool operator>(
		const reverse_iterator<IteratorL>& lhs, 
		const reverse_iterator<IteratorR>& rhs)
	{ return lhs.base() < rhs.base();}

	template <typename IteratorL, typename IteratorR>
	inline bool operator>=(
		const reverse_iterator<IteratorL>& lhs, 
		const reverse_iterator<IteratorR>& rhs)
	{ return lhs.base() <= rhs.base();}

	template <typename IteratorL, typename IteratorR>
	inline bool operator<=(
		const reverse_iterator<IteratorL>& lhs, 
		const reverse_iterator<IteratorR>& rhs)
	{ return lhs.base() >= rhs.base();}

	template <typename IteratorL, typename IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-(
		const reverse_iterator<IteratorL>& lhs,
		const reverse_iterator<IteratorR>& rhs)
	{ return rhs.base() - lhs.base();}

	/***********************************************
		DISTANCE FUNCTIONS
	***********************************************/

	template <typename InputIterator>
	inline typename ft::iterator_traits<InputIterator>::difference_type iterator_distance_(
		InputIterator first,
		InputIterator last,
		input_iterator_tag)
	{
		typename ft::iterator_traits<InputIterator>::difference_type distance = 0;
		for (;first !=  last; ++first, ++distance){}
		return distance;
	}

	template <typename RandomAccessIterator>
	inline typename ft::iterator_traits<RandomAccessIterator>::difference_type iterator_distance_(
		RandomAccessIterator first,
		RandomAccessIterator last,
		random_access_iterator_tag)
	{ return last - first;}

	template <typename Iterator>
	inline typename ft::iterator_traits<Iterator>::difference_type distance(
		Iterator first,
		Iterator last)
	{ return iterator_distance_(first, last, ft::iterator_category(first));}
}