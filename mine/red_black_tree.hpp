#pragma once
#include "mynullptr.hpp"
#include "iterator.hpp"
#include "rbt_iterator.hpp"
#include "pair.hpp"
#include <memory>

namespace ft
{
	//compare removen
	template <typename T, typename COMPARE, typename Allocator >
	class red_black_tree
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
			typedef typename allocator_type::difference_type					difference_type;
			typedef typename allocator_type::pointer							pointer;
			typedef typename allocator_type::const_pointer						const_pointer;

			typedef ft::rbt_iterator<value_type, difference_type>				iterator;
			typedef ft::const_rbt_iterator<value_type, difference_type>			const_iterator;
			typedef ft::reverse_iterator<iterator>								reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;

		
		protected:
			value_compare				compare_;
			node_allocator_type			alloc_node_;
			allocator_type				alloc_value_;
			size_type					node_count_;
			node_pointer				left_most_;
			node_pointer				root_;
			node_pointer				nil_;

		
		private:
		public:

			// node_pointer&			end_node_() {return root_;}
			// const_node_pointer		end_node_() const {return root_;}
			node_pointer&				root_node_() {return root_;}
			const_node_pointer			root_node_() const {return root_;}
			
			node_pointer create_new_node_(const value_type& value, COLOUR colour, node_pointer parent)
			{
				node_pointer new_node = alloc_node_.allocate(1);
				alloc_value_.construct(&new_node->value, value);
				new_node->colour = colour;
				new_node->parent = parent;
				new_node->left = nil_;
				new_node->right = nil_;
				new_node->nil = nil_;
				return new_node;
			}
		
		public:	

			red_black_tree(const red_black_tree& other)
			:compare_(other.compare_),
			alloc_node_(other.alloc_node_),
			alloc_value_(other.alloc_value_),
			node_count_(other.node_count_)
			{
				//
			}

			red_black_tree(const value_compare& compare, const allocator_type& alloc)
			:compare_(compare), alloc_node_(alloc), alloc_value_(alloc), node_count_(0)
			{ left_most_ = root_ = nil_ = create_new_node_(value_type(), BLACK, nil_);}

			/***********************************************
				Iterators
			***********************************************/
			
			iterator begin() { return iterator(left_most_);}

			const_iterator begin() const { return const_iterator(left_most_);}

			iterator end() { return iterator(nil_);}
	
			const_iterator end() const { return const_iterator(nil_);}

			/***********************************************
				Capacity
			***********************************************/

			size_type size() const { return node_count_; }

			size_type max_size() const { return alloc_node_.max_size(); }

			bool empty() const { return node_count_ == 0 ;}

			void rotate_right_(node_pointer x)
			{
				node_pointer y = x->left;
				x->left = y->right;					// turn y's subtree in x's subtree
				if (y->right != nil_)
					y->right->parent = x;
				y->parent = x->parent;
				if (x->parent == nil_)				// if x is root
					root_ = y;
				else if (x == x->parent->right)		// or x is left child
					x->parent->right = y;
				else								// or x is right child
					x->parent->left = y;
				y->right = x;						//put x on y's left
				x->parent = y;
			}

			void rotate_left_(node_pointer x)
			{
				node_pointer y = x->right;
				x->right = y->left;					// turn y's subtree in x's subtree
				if (y->left != nil_)
					y->left->parent = x;
				y->parent = x->parent;
				if (x->parent == nil_)				// if x is root
					root_ = y;
				else if (x == x->parent->left)		// or x is left child
					x->parent->left = y;
				else								// or x is right child
					x->parent->right = y;
				y->left = x;						//put x on y's left
				x->parent = y;
			}
	
			void balance_insert(node_pointer node)
			{
				while(node != root_ && node->parent->colour == RED)
				{
					if(node->parent->parent->left == node->parent)
					{
						node_pointer uncle = node->parent->parent->right;
						if (uncle != nil_ && uncle->colour == RED)
						{
							uncle->colour = BLACK;
							node->parent->colour = BLACK;
							node->parent->parent->colour = RED;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->right)
							{
								node = node->parent;
								rotate_left_(node);
							}
							node->parent->colour = BLACK;
							node->parent->parent->colour = RED;
							rotate_right_(node->parent->parent);
						}
					}
					else
					{
						node_pointer uncle = node->parent->parent->left;
						if (uncle != mynullptr && uncle->colour == RED)
						{
							uncle->colour = BLACK;
							node->parent->colour = BLACK;
							node->parent->parent->colour = RED;
							node = node->parent->parent;
						}
						else
						{
							if (node == node->parent->left)
							{
								node = node->parent;
								rotate_right_(node);
							}
							node->parent->colour = BLACK;
							node->parent->parent->colour = RED;
							rotate_left_(node->parent->parent);
						}
					}
					root_->colour = BLACK;
				}
			}
			
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				node_pointer parent = root_, new_node;

				for(node_pointer iter = root_; iter != nil_;)
				{
					parent = iter;
					if (compare_(value, iter->value))
						iter = iter->left;
					else if (compare_(iter->value, value))
						iter = iter->right;
					else
						return ft::make_pair(iterator(iter), false);
				}
				if (root_ == nil_)
					root_ = left_most_ = new_node = create_new_node_(value, BLACK, parent);
				else
				{
					new_node = create_new_node_(value, RED, parent);
					if (compare_(value, parent->value))
						parent->left = new_node;
					else
						parent->right = new_node;
				}
				// new_node->nil = new_node->left;
				if (left_most_->left != nil_)
					left_most_ = left_most_->left;
				balance_insert(new_node);
				++node_count_;
				if (new_node == rbt_rightmost(root_)) //vielleicht nciht notwendig
					nil_->parent = new_node;
				return ft::make_pair(iterator(new_node), true);
			}

			// template <typename Key>
			// iterator find (const Key& key)
			// {
			// 	node_pointer search = root_node_();
			// 	while(search != mynullptr)
			// 	{
			// 		if (compare_(search->value, key))
			// 			search = search_->right_;
			// 		else if (compare_(key, search->value))
			// 			search = search->left_;
			// 		else
			// 			return iterator(search);
			// 	}
			// 	return (end());
			// }

			// template <typename Key>
			// const_iterator find (const Key& key) const
			// {
			// 	node_pointer search = root_node_();
			// 	while(search != mynullptr)
			// 	{
			// 		if (compare_(search->value, key))
			// 			search = search_->right_;
			// 		else if (compare_(key, search->value))
			// 			search = search->left_;
			// 		else
			// 			return const_iterator(search);
			// 	}
			// 	return (end());
			// }

			void print_from_node_(node_pointer node, const std::string& prefix = "", bool is_left = false,
			bool is_first = true)
			{
				if (node != nil_) 
				{
					print_from_node_(node->right, prefix + (is_first ? " " : "    "), false, false);
					std::cout << prefix;
					if (!is_first)
						std::cout << (is_left ? "└──" : "┌──");
					if (node->colour == BLACK)
						std::cout << node->value.first << std::endl;
					else
						std::cout << "\033[0;31m" << node->value.first << "\033[0m" << std::endl;
					print_from_node_(node->left, prefix + (is_first ? " " : "    "), true, false);
				}
			}
		};
};