#pragma once

#include "iterator_traits.hpp"
#include "rbt_node.hpp"
#include "mynullptr.hpp"
#include "algorithm.hpp"

namespace ft
{
	template <class NodePointer>
	NodePointer rbt_leftmost(NodePointer node)
	{
		while (node->left != node->nil)
			node = node->left;
		return node;
	}

	template <class NodePointer>
	NodePointer rbt_rightmost(NodePointer node)
	{
		while (node->right != node->nil)
			node = node->right;
		return node;
	}

	template <class NodePointer>
	NodePointer rbt_next(NodePointer node)
	{
		if (node->right != node->nil)
			return rbt_leftmost(node->right);
		while (node->parent != node->nil && node == node->parent->right)
			node = node->parent;
		return node->parent;
	}

	template <class NodePointer>
	NodePointer rbt_previous(NodePointer node)
	{
		if (node == node->nil)
			return node->parent;
		if (node->left != node->nil)
			return rbt_rightmost(node->left);
		while (node->parent != node->nil && node == node->parent->left)
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
			typedef const_rbt_iterator<value_type, DIFFTYPE>			const_iterator;
			typedef rbt_iterator<value_type, DIFFTYPE>					iterator;

		private:
			typedef typename Node<value_type>::pointer					node_pointer;
			typedef typename Node<value_type>::const_pointer			const_node_pointer;

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
			rbt_iterator(const iterator& other)
			:current_(other.current_){}

			/***********************************************
				DESTRUCTORS
			***********************************************/
			
			/*default destructor*/
			~rbt_iterator(){}

			/***********************************************
				FORWARD ITERATOR REQUIREMENTS
			***********************************************/

			iterator& operator++()
			{
				current_ = rbt_next<node_pointer>(current_);
				return *this;
			}

			iterator operator++(int)
			{
				iterator tmp = *this;
				current_ = rbt_next<node_pointer>(current_);
				return tmp;
			}

			node_pointer base() const
			{ return current_;}

			/***********************************************
				BIDIRECTIONAL ITERATOR REQUIREMENTS
			***********************************************/

			iterator& operator--()
			{
				current_ = rbt_previous<node_pointer>(current_);
				return *this;
			}

			iterator operator--(int)
			{
				iterator tmp = *this;
				current_ = rbt_previous<node_pointer>(current_);
				return tmp;
			}

			reference operator*() const
			{ return current_->value;}

			pointer operator->() const
			{ return &(operator*());}

			/***********************************************
				ITERATOR COMPARISON REQUIREMENTS
			***********************************************/

			bool operator==(const iterator& other) const { return current_ == other.base();}

			bool operator==(const const_iterator& other) const {return current_ == other.base();}

			bool operator!=(const iterator& other) const { return current_ != other.base();}

			bool operator!=(const const_iterator& other) const { return current_ != other.base();}
	};
	

	template <typename T, typename DIFFTYPE>
	class const_rbt_iterator
	{
		public:
			typedef	T													value_type;
			typedef const T*											pointer;
			typedef const T&											reference;
			typedef DIFFTYPE											difference_type;
			typedef bidirectional_iterator_tag							iterator_category;
			typedef const_rbt_iterator<value_type, DIFFTYPE>			const_iterator;
			typedef ft::rbt_iterator<value_type, DIFFTYPE>				iterator;

		private:
			typedef typename Node<value_type>::pointer					node_pointer;
			typedef typename Node<value_type>::const_pointer			const_node_pointer;

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
			const_rbt_iterator(const iterator& other)
			:current_(other.base()){}

			/*Copy Constructor*/
			const_rbt_iterator(const const_iterator& other)
			:current_(other.current_){}

			/***********************************************
				DESTRUCTORS
			***********************************************/
			
			/*default destructor*/
			~const_rbt_iterator(){}

			/***********************************************
				FORWARD ITERATOR REQUIREMENTS
			***********************************************/

			const_iterator& operator++()
			{
				current_ = rbt_next<const_node_pointer>(current_);
				return *this;
			}

			const_iterator operator++(int)
			{
				const_iterator tmp = *this;
				current_ = rbt_next<const_node_pointer>(current_);
				return tmp;
			}

			const_node_pointer base() const
			{ return current_;}

			/***********************************************
				BIDIRECTIONAL ITERATOR REQUIREMENTS
			***********************************************/

			const_iterator& operator--()
			{
				current_ = rbt_previous<const_node_pointer>(current_);
				return *this;
			}

			const_iterator operator--(int)
			{
				const_iterator tmp = *this;
				current_ = rbt_previous<const_node_pointer>(current_);
				return tmp;
			}

			reference operator*() const
			{ return current_->value;}

			pointer operator->() const
			{ return &(operator*());}

			/***********************************************
				ITERATOR COMPARISON REQUIREMENTS
			***********************************************/

			bool operator==(const const_iterator& other) const { return current_ == other.base();}

			bool operator!=(const const_iterator& other) const { return current_ != other.base();}

			bool operator==(const iterator &other) const { return current_ == other.base();}

			bool operator!=(const iterator &other) const { return current_ != other.base();}
	};
}
