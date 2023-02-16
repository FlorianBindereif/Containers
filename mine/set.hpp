#pragma once
#include "red_black_tree.hpp"
#include "pair.hpp"
#include <exception>

namespace ft
{
	template <typename Key, typename Compare = std::less<Key>, typename Allocator = std::allocator< Key > >
	class set
	{
		public:
			typedef Key																key_type;
			typedef Key																value_type;									
			typedef Compare															key_compare;
			typedef Compare															value_compare;
			typedef Allocator														allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef typename allocator_type::size_type								size_type;
			typedef typename allocator_type::difference_type						difference_type;

		private:
			typedef ft::red_black_tree<value_type, value_compare, allocator_type>	tree_type;
			typedef typename tree_type::iterator									non_const_iterator;

		public:
			typedef typename tree_type::iterator								iterator;
			typedef typename tree_type::const_iterator								const_iterator;
			typedef typename tree_type::const_reverse_iterator						reverse_iterator;
			typedef typename tree_type::const_reverse_iterator						const_reverse_iterator;
			
		public:

			set(
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				:tree_(comp, alloc){}

		    template <class InputIterator>
			set(InputIterator first, 
				InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				:tree_(comp, alloc)
			{ insert(first, last); }
			
			set(const set& other): tree_(other.tree_) {}

			~set() {}

			set& operator=(const set& other)
			{
				tree_ = other.tree_;
				return *this;
			}
		
		private:
			tree_type tree_;

		public:

			/***********************************************
				ITERATORS
			***********************************************/
			
			/*Returns an iterator to the first element of the set.*/
			iterator begin()
			{ return tree_.begin();}

			/*Returns an read-only iterator to the first element of the set. */
			const_iterator begin() const
			{ return tree_.begin();}

			/*Returns an iterator to the element following the last element of the set.*/
			iterator end() 
			{ return tree_.end();}

			/*Returns an read-only iterator to the element following the last element of the set. */
			const_iterator end() const
			{ return tree_.end();}

			/*Returns a reverse iterator to the first element of the reversed set.*/
			reverse_iterator rbegin()
			{ return reverse_iterator(end());}

			/*Returns a read-only reverse iterator to the first element of the reversed set.*/
			const_reverse_iterator rbegin() const
			{ return const_reverse_iterator(end());}

			/*Returns a reverse iterator to the element following the last element of the reversed set.*/
			reverse_iterator rend()
			{ return reverse_iterator(begin());}

			/*Returns a read-only reverse iterator to the element following the last element of the reversed set. */
			const_reverse_iterator rend() const
			{ return const_reverse_iterator(begin());}

			/***********************************************
				CAPACITY
			***********************************************/

			/*Checks if the container has no elements*/
			bool empty() const
			{return tree_.empty(); }

			/*Returns the number of elements in the container*/
			size_type size() const
			{ return tree_.size(); }

			/*Returns the maximum number of elements the container is able to hold*/
			size_type max_size() const
			{ return tree_.max_size(); }

			/***********************************************
				MODIFIERS
			***********************************************/

			/*Erases all elements from the container*/
			void clear()
			{ tree_.clear(); }

			/*Inserts element @val into the container, there is no element with equivalent key.*/
		    ft::pair<iterator, bool> insert(const value_type& val) 
			{ return tree_.insert(val); }

			/*Inserts elements from range [first, last) */
		    template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{ 
				while (first != last)
				{
					tree_.insert(*first);
					++first;
				}
			}

			/* Inserts value in the position as close as possible to the position just prior to pos*/
			iterator insert(iterator pos, const value_type& value)
			{
				(void) pos;
				return tree_.insert(value).first;
			}

			/*Removes the element at pos*/
			iterator erase(iterator pos)
			{
				try
				{
					return tree_.erase(pos);
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << "ft::set::compare";
				}
				return pos;
			}	

			/*Removes the elements in the range [first, last)*/
			iterator erase( iterator first, iterator last)
			{
				try
				{
					while(first != last)
						first = erase(first);
				}
				catch (const std::exception& e)
				{
					std::cerr << e.what() << "ft::set::compare";
				}
				return first;
			}

			/*Removes the element with the key equivalent to key*/
			size_type erase( const key_type& key )
			{
				non_const_iterator node = tree_.find(key);

				if (node == end())
					return 0;
				tree_.erase(node);
				return 1;
			}

			/*Exchanges the contents of the container with those of other*/
			void swap(set& other)
			{ tree_.swap(other.tree_);	}

			/***********************************************
				Lookup
			***********************************************/
			
			/*Returns the number of elements with key that compares equivalent to the specified argument.*/
			size_type count(const key_type& key) const
			{
				if (tree_.find(key) == end())
					return 0;
				return 1;
			}

			/*Finds an element with key equivalent to key.*/
			iterator find (const key_type& key)
			{ return tree_.find(key); }

			/*Finds an element with key equivalent to key.*/
			const_iterator find(const key_type& key) const
			{ return tree_.find(key); }

			/*Returns a range containing all elements with the given key in the container.*/
			ft::pair<iterator,iterator> equal_range(const key_type& key )
			{ return tree_.equal_range(key); }

			/*Returns a range containing all elements with the given key in the container.*/
			ft::pair<const_iterator, const_iterator> equal_range(const key_type& key ) const
			{ return tree_.equal_range(key); }

		    iterator lower_bound(const key_type& key) 
			{ return tree_.lower_bound(key); }

		    const_iterator lower_bound(const key_type& key) const
			{ return tree_.lower_bound(key); }

    		iterator upper_bound(const key_type& key) 
			{ return tree_.upper_bound(key); }

    		const_iterator upper_bound(const key_type& key) const 
			{ return tree_.upper_bound(key); }

			/***********************************************
				OBSERVERS
			***********************************************/

			/*Returns the function that compares keys*/
			key_compare key_comp() const
			{ return key_compare(); }

			value_compare value_comp() const
			{ return value_compare(key_comp()); }

			allocator_type get_allocator() const
			{ return tree_.get_allocator(); }

			void print_tree()
			{ tree_.print_from_node_(tree_.root_node());};

	};

	template <typename Key, typename Compare, typename Allocator>
	inline bool operator==(const set<Key, Compare, Allocator>& lhs,
							const set<Key, Compare, Allocator>& rhs)
	{
		return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename Key, typename Compare, typename Allocator>
	inline bool operator!=(const set<Key, Compare, Allocator>& lhs,
						const set<Key, Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Key, typename Compare, typename Allocator>
	inline bool operator<(const set<Key, Compare, Allocator>& lhs,
						const set<Key, Compare, Allocator>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename Key, typename Compare, typename Allocator>
	inline bool operator<=(const set<Key,  Compare, Allocator>& lhs,
						const set<Key, Compare, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename Key, typename Compare, typename Allocator>
	inline bool operator>(const set<Key, Compare, Allocator>& lhs,
						const set<Key, Compare, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template <typename Key, typename Compare, typename Allocator>
	inline bool operator>=(const set<Key, Compare, Allocator>& lhs,
						const set<Key, Compare, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	inline void swap(set<Key, Compare, Allocator>& x, set<Key, Compare, Allocator>& y)
	{
		x.swap(y);
	}
}