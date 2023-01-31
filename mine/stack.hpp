#pragma once

#include "vector.hpp"

namespace ft
{
	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container										container_type;
			typedef typename container_type::value_type				value_type;
			typedef typename container_type::size_type				size_type;
			typedef typename container_type::reference				reference;
			typedef typename container_type::const_reference		const_reference;
		
		protected:
			container_type	container_;

		public:

			/***********************************************
				Constructors
			***********************************************/

			/*Copy-constructs the underlying container @container_ with the contents of @cont*/
			explicit stack(const container_type& cont = container_type())
			: container_(cont){};

			/*Copy constructor. The adaptor is copy-constructed with the contents of @other.container_.*/
			explicit stack(const stack& other)
			: container_(other.container_){};

			/***********************************************
				DESTRUCTORS
			***********************************************/

			/*Destructs the stack. The destructors of the elements are called and the used storage is deallocated.*/
			~stack() {};

			/***********************************************
				ASSIGNMENT
			***********************************************/

			/*Copy assignment operator. Replaces the contents with a copy of the contents of other.*/
			stack& operator=(const stack& other)
			{
				container_ = other.container_;
				return *this;
			}

			/***********************************************
				ELEMENT ACCESS
			***********************************************/

			/*Returns reference to the top element in the stack. This is the most recently pushed element.*/
			reference top() {return container_.back(); }

			/*Returns read_only reference to the top element in the stack. This is the most recently pushed element.*/
			const_reference top() const {return container_.back(); }

			/***********************************************
				CAPACITY
			***********************************************/

			/*Checks if the underlying container has no elements*/
			bool empty() const { return container_.empty(); }

			/*Returns the number of elements in the underlying container*/
			size_type size() const { return container_.size(); }

			/***********************************************
				MODIFIERS
			***********************************************/

			/*Pushes the given element value to the top of the stack.*/
			void push(const value_type& value) {container_.push_back(value);}

			/*Removes the top element from the stack*/
			void pop() {container_.pop_back();}

			/***********************************************
				FRIEND DECLARATIONS
			***********************************************/

			template <typename T1, typename C1>
			friend bool operator==(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

			template <typename T1, typename C1>
			friend bool operator!=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

			template <typename T1, typename C1>
			friend bool operator>(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

			template <typename T1, typename C1>
			friend bool operator<(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

			template <typename T1, typename C1>
			friend bool operator>=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);

			template <typename T1, typename C1>
			friend bool operator<=(const stack<T1, C1>& lhs, const stack<T1, C1>& rhs);
	};

	/***********************************************
		NON-MEMBER FUNCTIONS
	***********************************************/

	/*Check if the contents of the underlying container adaptors are equal.*/
	template< typename T, typename Container >
	inline bool operator==(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{return lhs.container_ == rhs.container_;};

	/*Check if the contents of the underlying container adaptors are not equal.*/
	template< typename T, typename Container >
	inline bool operator!=(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{return lhs.container_ != rhs.container_;};

	/*Compares the contents of the underlying containers of two container adaptors lexicographically.*/
	template< typename T, typename Container >
	inline bool operator<(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{return lhs.container_ < rhs.container_;};

	/*Compares the contents of the underlying containers of two container adaptors lexicographically.*/
	template< typename T, typename Container >
	inline bool operator>(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{return lhs.container_ > rhs.container_;};

	/*Compares the contents of the underlying containers of two container adaptors lexicographically.*/
	template< typename T, typename Container >
	inline bool operator<=(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{return lhs.container_ <= rhs.container_;};

	/*Compares the contents of the underlying containers of two container adaptors lexicographically.*/
	template< typename T, typename Container >
	inline bool operator>=(const stack<T, Container>& lhs, const stack<T,Container>& rhs)
	{return lhs.container_ >= rhs.container_;};

}