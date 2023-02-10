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
			node_pointer				root_;
			size_type					node_count_;
			node_pointer				left_most_;
		
		private:
		public:

			node_pointer&				end_node_() {return root_;}
			const_node_pointer			end_node_() const {return root_;}
			node_pointer&				root_node_() {return root_->left;}
			const_node_pointer			root_node_() const {return root_->left;}
			
			node_pointer create_new_node_(const value_type& value, COLOUR colour)
			{
				node_pointer new_node = alloc_node_.allocate(1);
				alloc_value_.construct(&new_node->value, value);
				new_node->colour = colour;
				new_node->parent = mynullptr;
				new_node->left = mynullptr;
				new_node->right = mynullptr;
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
			{
				root_ = create_new_node_(value_type(), BLACK);
				root_->parent = left_most_ = root_;
			}

			/***********************************************
				Iterators
			***********************************************/
			
			iterator begin() { return iterator(left_most_);}

			const_iterator begin() const { return const_iterator(left_most_);}

			iterator end() { return iterator(end_node_());}
	
			const_iterator end() const { return const_iterator(end_node_());}

			/***********************************************
				Capacity
			***********************************************/

			size_type size() const { return node_count_; }

			size_type max_size() const { return alloc_node_.max_size(); }

			bool empty() const { return node_count_ == 0 ;}


			// template <typename Key>
			// node_pointer find_key_or_pos_(node_pointer& parent, const Key& key)
			// {
			// 	node_pointer iter = root_node_()
			// 	if (iter == mynullptr)
			// 		parent = end_node_();
			// 	else
			// 	{
			// 		if (compare_(key, iter->val))
			// 		{
			// 			if (iter->left == mynullptr)
			// 			{
			// 				parent = iter;
			// 				return parent->left;
			// 			}
			// 			else
			// 				iter = iter->left;
			// 		}
			// 		else if (compare_(iter->val, key))
			// 		{
			// 			if (iter->right == mynullptr)
			// 			{
			// 				parent = iter;
			// 				return parent->right;
			// 			}
			// 			else
			// 				iter = iter->right;
			// 		}
			// 		else
			// 		{
			// 			parent = iter;
			// 			return parent;
			// 		}
			// 	}
			// }

			void rotate_right_(node_pointer x)
			{
				node_pointer y = x->left;
				x->left = y->right;
				if (x->left != nullptr)
					x->left->parent = x;
				y->parent = x->parent;
				if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->right = x;
				x->parent = y;
			}

			void rotate_left_(node_pointer x)
			{
				node_pointer y = x->right;
				x->right = y->left;
				if (x->right != nullptr)
					x->right->parent = x;
				y->parent = x->parent;
				if (x == x->parent->left)
					x->parent->left = y;
				else
					x->parent->right = y;
				y->left = x;
				x->parent = y;
			}

			
			void balance_insert(node_pointer node)
			{
				if (node == root_node_())
					node->colour  = BLACK;
				else
					node->colour = RED;
				while(node != root_node_() && node->parent->colour == RED)
				{
					if(node->parent->parent->left == node->parent)
					{
						node_pointer uncle = node->parent->parent->right;
						if (uncle != mynullptr && uncle->colour == RED)
						{
							uncle->colour = BLACK;
							node = node->parent;
							node->colour = BLACK;
							node = node->parent; // könnte parent->parent sein
							if (node == root_node_())
								node->colour  = BLACK;
							else
								node->colour = RED;
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
							break;
						}
					}
					else
					{
						node_pointer uncle = node->parent->parent->left;
						if (uncle != mynullptr && uncle->colour == RED)
						{
							uncle->colour = BLACK;
							node = node->parent;
							node->colour = BLACK;
							node = node->parent;
							if (node == root_node_())
								node->colour  = BLACK;
							else
								node->colour = RED;
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
								break;
						}
					}
				}
			}
				
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				node_pointer *iter = &root_node_();
				node_pointer parent;

				if (*iter == mynullptr)
				{
					parent = root_;
					iter = &(root_->left);
					std::cout << "first time"  << std::endl;
				}
				else
				{
					std::cout << "second time"  << std::endl;
					while (*iter != mynullptr)
					{
						parent = *iter;
						if (compare_(value, (*iter)->value))
							*iter = (*iter)->left;
						else if (compare_((*iter)->value, value))
							*iter = (*iter)->right;
						else
							return ft::make_pair(iterator(*iter), false);
					}
				}
				node_pointer new_node = create_new_node_(value, RED);
				*iter = new_node;
				(*iter)->parent = parent;
				if (left_most_->left != mynullptr)
					left_most_ = left_most_->left;
				// balance_insert(new_node);
				std::cout << (*iter)->value.first << " | " << (*iter)->parent->value.first << std::endl;
				++node_count_;
				return ft::make_pair(iterator(*iter), true);
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
				if (node != nullptr) 
				{
					std::cout << "print" << std::endl;
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