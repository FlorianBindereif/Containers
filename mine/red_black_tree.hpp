#pragma once

#include "mynullptr.hpp"
#include "iterator.hpp"
#include "rbt_iterator.hpp"
#include "pair.hpp"
#include <memory>
#include <iostream>

namespace ft
{
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
		
		public:	

			node_pointer root_node() { return root_; }

			red_black_tree(const red_black_tree& other)
			:compare_(other.compare_),
			alloc_node_(other.alloc_node_),
			alloc_value_(other.alloc_value_),
			node_count_(other.node_count_)
			{
				left_most_ = root_ = nil_ = create_nil_();
				*this = other;
			}

			red_black_tree(const value_compare& compare, const allocator_type& alloc)
			:compare_(compare), alloc_node_(alloc), alloc_value_(alloc), node_count_(0)
			{ 
				left_most_ = root_ = nil_ = create_nil_();
			}

			red_black_tree& operator=(const red_black_tree& other)
			{
				if (this != &other)
				{
					alloc_node_ = other.alloc_node_;
					alloc_value_ = other.alloc_value_;
					clear();
					root_ = tree_copy_(other.root_, nil_, other.nil_);
					node_count_ = other.node_count_;
					left_most_ = rbt_leftmost(root_);
				}
				return *this;
			}
			
			~red_black_tree()
			{
				clear();
				alloc_node_.destroy(nil_);
				alloc_node_.deallocate(nil_, 1);
			}

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

			/***********************************************
				GETTERS
			***********************************************/
			
			allocator_type get_allocator() const
			{ return alloc_value_;}
		private:

			node_pointer create_nil_()
			{
				nil_ = alloc_node_.allocate(1);
				alloc_value_.construct(&nil_->value, value_type());
				nil_->colour = BLACK;	
				nil_->parent = nil_;
				nil_->left = nil_;
				nil_->right = nil_;
				nil_->nil = nil_;
				return nil_;
			}

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

			node_pointer tree_copy_(node_pointer node, node_pointer parent, node_pointer nil)
			{
				if (node == nil)
					return nil_;
				node_pointer new_node = create_new_node_(node->value, node->colour, parent);
				new_node->right = tree_copy_(node->right, new_node, nil);
				new_node->left = tree_copy_(node->left, new_node, nil);
				return new_node;
			}

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

			void transplant_(node_pointer x, node_pointer y)
			{
				if (x->parent == nil_)
					root_ = y;
				else if (x == x->parent->left) //x is left child
					x->parent->left = y;
				else
					x->parent->right = y; //x is right child
				y->parent = x->parent;
			}

			void balance_erase_(node_pointer node)
			{
				node_pointer sibling;
				while(node != root_ && node->colour == BLACK)
				{
					if (node == node->parent->left)
					{
						sibling = node->parent->right;
						if (sibling->colour == RED)
						{
							sibling->colour = BLACK;
							node->parent->colour = RED;
							rotate_left_(node->parent);
							sibling = node->parent->right;
						}
						if (sibling->left->colour == BLACK && sibling->right->colour == BLACK)
						{
							sibling->colour = RED;
							node = node->parent;
						}
						else
						{
							if (sibling->right->colour == BLACK)
							{
								sibling->left->colour = BLACK;
								sibling->colour = RED;
								rotate_right_(sibling);
								sibling = node->parent->right;
							}
							sibling->colour = node->parent->colour;
							node->parent->colour = BLACK;
							sibling->right->colour = BLACK;
							rotate_left_(node->parent);
							node = root_;
						}
					}
					else
					{
						sibling = node->parent->left;
						if (sibling->colour == RED)
						{
							sibling->colour = BLACK;
							node->parent->colour = RED;
							rotate_right_(node->parent);
							sibling = node->parent->left;
						}
						if (sibling->right->colour == BLACK && sibling->right->colour == BLACK)
						{
							sibling->colour = RED;
							node = node->parent;
						}
						else
						{
							if (sibling->left->colour == BLACK)
							{
								sibling->right->colour = BLACK;
								sibling->colour = RED;
								rotate_left_(sibling);
								sibling = node->parent->left;
							}
							sibling->colour = node->parent->colour;
							node->parent->colour = BLACK;
							sibling->left->colour = BLACK;
							rotate_right_(node->parent);
							node = root_;
						}
					}
				}
				node->colour = BLACK;
			}

			void balance_insert_(node_pointer node)
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

			void clear_tree_(node_pointer node)
			{
				if (node == nil_ || node == mynullptr || node == node->left || node == node->right)
					return ;
				clear_tree_(node->right);
				clear_tree_(node->left);
				destroy_node_(node);
			}
		
			void destroy_node_(node_pointer node)
			{
				alloc_value_.destroy(&node->value);
				alloc_node_.deallocate(node, 1);
				node = nil_;
			}

		public:

			void clear()
			{
				clear_tree_(root_);
				node_count_ = 0;
				root_ = nil_;
				left_most_ = root_;
			}

			iterator	erase(iterator pos)
			{
				if (pos == end())
					return end();
				node_pointer next = rbt_next(pos.base());
				node_pointer z = pos.base();
				node_pointer y = z;
				node_pointer x;
				COLOUR original_colour = y->colour;

				if (z->left == nil_)
				{
					x = z->right;
					transplant_(z, x);
				}
				else if (z->right == nil_)
				{
					x = z->left;
					transplant_(z, x);
				}
				else
				{
					y = rbt_leftmost(z->right);
					original_colour = y->colour;
					x = y->right;
					if (y->parent == z)
						x->parent = y;
					else
					{
						transplant_(y, y->right);
						y->right = z->right;
						y->right->parent = y;
					}
					transplant_(z, y);
					y->left = z->left;
					y->left->parent = y;
					y->colour = z->colour;
				}
				if (z == left_most_)
					left_most_ = next;
				destroy_node_(z);
				if (original_colour == BLACK)
					balance_erase_(x);
				nil_->parent = rbt_rightmost(root_); // muss es eine bessere Lösung geben
				--node_count_;
				return iterator(next);
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
				if (left_most_->left != nil_)
					left_most_ = left_most_->left;
				balance_insert_(new_node);
				++node_count_;
				if (new_node == rbt_rightmost(root_)) //geht besser
					nil_->parent = new_node;
				return ft::make_pair(iterator(new_node), true);
			}

			template <typename Key>
			iterator find (const Key& key)
			{
				node_pointer iter = root_;
				while(iter != nil_)
				{
					if (compare_(iter->value, key))
						iter = iter->right;
					else if (compare_(key, iter->value))
						iter = iter->left;
					else
						return iter;
				}
				return (end());
			}

			template <typename Key>
			const_iterator find (const Key& key) const
			{
				node_pointer iter = root_;
				while(iter != nil_)
				{
					if (compare_(iter->value, key))
						iter = iter->right;
					else if (compare_(key, iter->value))
						iter = iter->left;
					else
						return iter;
				}
				return (end());
			}

			void swap(red_black_tree& other)
			{
				ft::swap(compare_, other.compare_);
				ft::swap(alloc_value_, other.alloc_value_);
				ft::swap(alloc_node_, other.alloc_node_);
				ft::swap(root_, other.root_);
				ft::swap(left_most_, other.left_most_);
				ft::swap(nil_, other.nil_);
				ft::swap(node_count_, other.node_count_);
			}

			template <typename Key>
			iterator lower_bound(const Key& key)
			{
				iterator it = begin();

				while (compare_(*it, key) && it != end())
					++it;
				return iterator(it);	
			}

			template <typename Key>
			const_iterator lower_bound(const Key& key) const
			{
				const_iterator it = begin();

				while (compare_(*it, key) && it != end())
					++it;
				return const_iterator(it);
			}

			template <typename Key>
			iterator upper_bound(const Key& key)
			{
				iterator it = lower_bound(key);
				if (!compare_(*it, key) && !compare_(key, *it))
					++it;
				return it;
			}

			template <typename Key>
			const_iterator upper_bound(const Key& key) const
			{
				const_iterator it = lower_bound(key);
				if(!compare_(*it, key) && !compare_(key, *it))
					++it;
				return it;
			}

			template <typename Key>
			ft::pair<iterator,iterator> equal_range(const Key& key)
			{return ft::make_pair(lower_bound(key), upper_bound(key)); }

			template <typename Key>
			ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
			{return ft::make_pair(lower_bound(key), upper_bound(key)); }

			void print_from_node_(node_pointer node, const std::string& prefix = "", bool is_left = false,
			bool is_first = true)
			{
				if (node != nil_) 
				{
					print_from_node_(node->right, prefix + (is_first ? " " : "    "), false, false);
					std::cerr << prefix;
					if (!is_first)
						std::cerr << (is_left ? "└──" : "┌──");
					if (node->colour == BLACK)
						std::cerr << node->value.first << std::endl;
					else
						std::cerr << "\033[0;31m" << node->value.first << "\033[0m" << std::endl;
					print_from_node_(node->left, prefix + (is_first ? " " : "    "), true, false);
				}
			}
	};
}