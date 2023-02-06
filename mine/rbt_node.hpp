#pragma once

#include "mynullptr.hpp"

namespace ft
{
	enum COLOUR { RED, BLACK};

	template <typename T>
	class Node
	{
		public:
			typedef T							value_type;
			typedef Node* 						pointer;
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
}