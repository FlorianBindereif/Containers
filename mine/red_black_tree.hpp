#pragma once

#include "mynullptr.hpp"

namespace ft
{
	template <typename NodePointer>
	NodePointer rbt_leftmost(NodePointer node)
	{
		while (node->left != mynullptr)
			node =  node->left;
		return node;
	}

	template <typename NodePointer>
	NodePointer rbt_rightmost(NodePointer node)
	{
		while (node->right != mynullptr)
			node =  node->right;
		return node;
	}

	template <typename NodePointer>
	NodePointer rbt_next(NodePointer node)
	{
		if (node->right != mynullptr)
			return rbt_leftmost(node->right);
		while (node == node->parent->right)
			node = node->parent;
		return node->parent;
	}

	template <typename NodePointer>
	NodePointer rbt_previous(NodePointer node)
	{
		if (node->left != mynullptr)
			return rbt_rightmost(node->left);
		while (node == node->parent->left)
			node = node->parent;
		return node->parent;
	}

	enum COLOUR { RED, BLACK};

	template <typename T>
	class Node
	{
		public:
			typedef T							value_type;
			typedef Node<value_type>* 			pointer;
			typedef const Node<value_type>* 	const_pointer;

		public:
			value_type	value;
			COLOUR 		colour;
			Node*		parent;  //potentially just "pointer"
			Node*		left;
			Node*		right;

		public:
			/***********************************************
				Constructors
			***********************************************/

			/*Default Constructor instanciating empty node*/
			Node()
			:value(mynullptr), colour(RED), parent(mynullptr), left(mynullptr), right(mynullptr) {}

			/*Constructor initializing value with @value and colour with @colour*/
			Node(value_type value, COLOUR colour)
			:value(value), colour(colour), parent(mynullptr), left(mynullptr), right(mynullptr) {}
			
			/*Copy Constructor. Constructs the container with the copy of the contents of @other**/
			Node(const Node& other)
			:value(other.value), colour(other.colour), parent(other.parent), left(other.left), right(other.right) {}
	};

	template <typename T, typename COMPARE, typename Allocator>
	class RBT
	{
		public:
			typedef T															value_type;
			typedef COMPARE														value_compare;
			typedef Allocator													allocator_type;
			typedef typename allocator_type::template rebind<node_type>::other 	node_allocator_type;
			typedef Node<value_type> 											node_type;

			typedef typename node_type::pointer									node_pointer;
			typedef typename allocator_type::size_type							size_type;

		protected:
			node_allocator_type			alloc_node_;
			allocator_type				alloc_value_;
			node_pointer				smallest_;
			node_pointer				biggest_;
			node_pointer				root_;
			size_type					node_count_;
		
		private:

			node_pointer create_new_node_(const value_type& value, COLOUR colour)
			{
				node_pointer new_node = alloc_node_.allocate(1);
				alloc_value_.construct(new_node, value);
				new_node.colour = colour;
				new_node.parent = mynullptr;
				new_node.left = mynullptr;
				new_node.right = mynullptr;
			}
	};
}