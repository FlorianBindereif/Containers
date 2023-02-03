#pragma once

#include "iterator_traits.hpp"
#include "rbt_iterator.hpp"
#include "mynullptr.hpp"

namespace ft
{
	template <typename T, typename DIFFTYPE>
	class rbt_iterator
	{
		public:
			typedef	T													value_type;
			typedef T*													pointer;
			typedef T&													reference;
			typedef DIFFTYPE											difference_type;
			typedef bidirectional_iterator_tag							iterator_category;

		private:
			typedef typename Node<value_type>::pointer					node_pointer;

		protected:
			node_pointer current_;

		public:
			/***********************************************
				Constructors
			***********************************************/

			/*Default Constructor*/
			rbt_iterator()
			:current_(mynullptr){}

			/*Constructor initialized with a @node_pointer*/
			rbt_iterator(node_poiner pointer)
			:current_(pointer){}

			/*Copy Constructor*/
			rbt_iterator(const rbt_iterator& other)
			:current_(other.current_){}

			/***********************************************
				DESTRUCTORS
			***********************************************/
			
			/*default destructor*/
			~rbt_iterator(){}

			/***********************************************
				FORWARD ITERATOR REQUIREMENTS
			***********************************************/

			rbt_iterator& operator++()
			{
				current_ = rbt_next<node_pointer>(current_);
				return *this;
			}

			rbt_iterator operator++(int)
			{
				rbt_iterator tmp = *this;
				current_ = rbt_next<node_pointer>(current_)
				return tmp;
			}

			node_pointer base()
			{ return current_};

			/***********************************************
				BIDIRECTIONAL ITERATOR REQUIREMENTS
			***********************************************/

			rbt_iterator& operator--()
			{
				current_ = rbt_previous<node_pointer>(current_);
				return *this;
			}

			rbt_iterator operator--(int)
			{
				rbt_iterator tmp = *this;
				current_ = rbt_previous<node_pointer>(current_)
				return tmp;
			}

			reference operator*()
			{ return current_->value;}

			pointer operator->()
			{ return &(operator*());}

			/***********************************************
				ITERATOR COMPARISON REQUIREMENTS
			***********************************************/

			bool operator==(const rbt_iterator& other) { return current_ == other.base()}

			bool operator!=(const rbt_iterator& other) { return current_ != other.base()}
	};



}
