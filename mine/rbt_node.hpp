#pragma once

#include "mynullptr.hpp"

namespace ft
{
	enum COLOUR { RED, BLACK};
	enum SIDE { LEFT, RIGHT};

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
			pointer		parent;
			pointer		left;
			pointer		right;

		public:
			/***********************************************
				Constructors
			***********************************************/

			/*Default Constructor instanciating empty node*/
			Node()
			:value(), colour(BLACK), parent(mynullptr), left(mynullptr), right(mynullptr) {}

			// Möglicherweise nicht notwendig//

			/*Constructor initializing value with @value, colour with @colour*/
			Node(value_type value, COLOUR colour)
			:value(value), colour(colour), parent(mynullptr), left(mynullptr), right(mynullptr){}
			
			/*Copy Constructor. Constructs the container with the copy of the contents of @other**/
			Node(const Node& other)
			:value(other.value), colour(other.colour), parent(other.parent), left(other.left), right(other.right) {}
	};
}