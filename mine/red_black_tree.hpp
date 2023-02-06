#pragma once
#include "mynullptr.hpp"
#include "rbt_iterator.hpp"
#include <memory>

namespace ft
{
	template <typename T, typename COMPARE, typename Allocator= std::allocator<T> >
	class Rbt
	{
		public:
			typedef T															value_type;
			typedef COMPARE														value_compare;
			typedef Allocator													allocator_type;

			typedef Node<value_type>											node_type;
			typedef typename allocator_type::template rebind<node_type>::other 	node_allocator_type;
			typedef typename node_type::pointer									node_pointer;
			typedef typename node_type::const_pointer							const_node_pointer;

			typedef typename allocator_type::size_type							size_type;
			typedef typename allocator_type::difference							difference_type;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;

			typedef rbt_iterator<value_type, difference_type>					iterator;
			typedef const_rbt_iterator<value_type, difference_type>				const_iterator;

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
			
			Rbt()
			:alloc_node_()
		

	};
}