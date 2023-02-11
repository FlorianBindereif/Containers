#pragma once

#include "iterator_traits.hpp"
#include "rbt_node.hpp"
#include "mynullptr.hpp"

namespace ft
{
	template <typename NodePointer>
	NodePointer rbt_leftmost(NodePointer node)
	{
		while (node->left != node->nil)
			node = node->left;
		return node;
	}

	template <typename NodePointer>
	NodePointer rbt_rightmost(NodePointer node)
	{
		while (node->right != node->nil)
			node = node->right;
		return node;
	}

	template <typename NodePointer>
	NodePointer rbt_next(NodePointer node)
	{
		if (node->right != node->nil)
			return rbt_leftmost(node->right);
		while (node->_parent != node->_nil && node == node->parent->right)
			node = node->parent;
		return node->parent;
	}

	template <typename NodePointer>
	NodePointer rbt_previous(NodePointer node)
	{
		if (node->left != mynullptr)
			return rbt_rightmost(node->left);
		while (node->_parent != node->_nil && node == node->parent->left)
			node = node->parent;
		return node->parent;
	}

	template <typename T, typename DIFFTYPE>
	class const_rbt_iterator;

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
			typedef rbt_iterator<value_type, DIFFTYPE>					rbt_iter;
			typedef const_rbt_iterator<value_type, DIFFTYPE>			const_rbt_iter;

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
			rbt_iterator(node_pointer pointer)
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

			rbt_iter& operator++()
			{
				current_ = rbt_next<node_pointer>(current_);
				return *this;
			}

			rbt_iter operator++(int)
			{
				rbt_iter tmp = *this;
				current_ = rbt_next<node_pointer>(current_);
				return tmp;
			}

			node_pointer base()
			{ return current_;}

			/***********************************************
				BIDIRECTIONAL ITERATOR REQUIREMENTS
			***********************************************/

			rbt_iter& operator--()
			{
				current_ = rbt_previous<node_pointer>(current_);
				return *this;
			}

			rbt_iter operator--(int)
			{
				rbt_iter tmp = *this;
				current_ = rbt_previous<node_pointer>(current_);
				return tmp;
			}

			reference operator*()
			{ return current_->value;}

			pointer operator->()
			{ return &(operator*());}

			/***********************************************
				ITERATOR COMPARISON REQUIREMENTS
			***********************************************/

			bool operator==(const rbt_iter& other) { return current_ == other.base();}

			bool operator==(const const_rbt_iter& other) {return current_ == other.base();}

			bool operator!=(const rbt_iter& other) { return current_ != other.base();}

			bool operator!=(const const_rbt_iter& other) { return current_ != other.base();}
	};
	

	template <typename T, typename DIFFTYPE>
	class const_rbt_iterator
	{
		public:
			typedef	T													value_type;
			typedef T*													pointer;
			typedef T&													reference;
			typedef DIFFTYPE											difference_type;
			typedef bidirectional_iterator_tag							iterator_category;

		private:
			typedef typename Node<value_type>::pointer					node_pointer;
			typedef typename Node<value_type>::const_pointer			const_node_pointer;
			typedef const_rbt_iterator<value_type, DIFFTYPE>			const_rbt_iter;
			typedef rbt_iterator<value_type, DIFFTYPE>					rbt_iter;

		protected:
			const_node_pointer current_;

		public:
			/***********************************************
				Constructors
			***********************************************/

			/*Default Constructor*/
			const_rbt_iterator()
			:current_(mynullptr){}

			/*Constructor initialized with a @node_pointer*/
			const_rbt_iterator(const_node_pointer pointer)
			:current_(pointer){}

			/*Constructor that allows iterator to const_iterator conversion*/
			const_rbt_iterator(rbt_iter& other)
			:current_(other.base()){}

			/*Copy Constructor*/
			const_rbt_iterator(const const_rbt_iter& other)
			:current_(other.current_){}

			/***********************************************
				DESTRUCTORS
			***********************************************/
			
			/*default destructor*/
			~const_rbt_iterator(){}

			/***********************************************
				FORWARD ITERATOR REQUIREMENTS
			***********************************************/

			const_rbt_iter& operator++()
			{
				current_ = rbt_next<node_pointer>(current_);
				return *this;
			}

			const_rbt_iter operator++(int)
			{
				const_rbt_iter tmp = *this;
				current_ = rbt_next<node_pointer>(current_);
				return tmp;
			}

			node_pointer base()
			{ return current_;}

			/***********************************************
				BIDIRECTIONAL ITERATOR REQUIREMENTS
			***********************************************/

			const_rbt_iter& operator--()
			{
				current_ = rbt_previous<node_pointer>(current_);
				return *this;
			}

			const_rbt_iter operator--(int)
			{
				const_rbt_iter tmp = *this;
				current_ = rbt_previous<node_pointer>(current_);
				return tmp;
			}

			reference operator*()
			{ return current_->value;}

			pointer operator->()
			{ return &(operator*());}

			/***********************************************
				ITERATOR COMPARISON REQUIREMENTS
			***********************************************/

			bool operator==(const const_rbt_iter& other) { return current_ == other.base();}

			bool operator!=(const const_rbt_iter& other) { return current_ != other.base();}

			bool operator==(const rbt_iter &other) { return current_ == other.base();}

			bool operator!=(const rbt_iter &other) { return current_ != other.base();}
	};

}
