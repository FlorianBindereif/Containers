#pragma once
#include "red_black_tree.hpp"
#include "pair.hpp"
#include <exception>

namespace ft
{
	template <typename Key, typename T, typename Compare>
	class map_value_type_compare : public std::binary_function<Key, Key, bool>
	{
		public:
			typedef Key  first_argument_type;
			typedef Key  second_argument_type;
			typedef bool result_type;

		public:
			map_value_type_compare() : comp_() {}

			map_value_type_compare(const Compare& c) : comp_(c) {}

		public:
			const Compare& key_comp() const { return comp_; }

			bool operator()(const T& x, const T& y) const { return comp_(x.first, y.first); }

			bool operator()(const Key& x, const T& y) const { return comp_(x, y.first); }

			bool operator()(const T& x, const Key& y) const { return comp_(x.first, y); }

			void swap(map_value_type_compare& other) { std::swap(comp_, other.comp_); }

		protected:
			Compare comp_;
	};

	template <typename Key, typename T, typename Compare = std::less<Key>, 
	typename Allocator = std::allocator< ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key                                      key_type;
			typedef T                                        mapped_type;
			typedef ft::pair<const key_type, mapped_type>    value_type;
			typedef Compare                                  key_compare;
			typedef Allocator                                allocator_type;
			typedef typename allocator_type::reference       reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef typename allocator_type::pointer         pointer;
			typedef typename allocator_type::const_pointer   const_pointer;
			typedef typename allocator_type::size_type       size_type;
			typedef typename allocator_type::difference_type difference_type;

		private:
			typedef map_value_type_compare<key_type, value_type, key_compare>  value_type_compare;
			typedef ft::red_black_tree<value_type, value_type_compare, allocator_type> tree_type;

		public:
			typedef typename tree_type::iterator               iterator;
			typedef typename tree_type::const_iterator         const_iterator;
			typedef typename tree_type::reverse_iterator       reverse_iterator;
			typedef typename tree_type::const_reverse_iterator const_reverse_iterator;
			
		public:
			/*Function object that compares objects of type value_type 
			by comparing of the first components of the pairs.*/
			class value_compare
			:public std::binary_function<value_type, value_type, bool>
			{
		        friend class map;

				public:
					typedef value_type 	first_argument_type;
					typedef value_type 	second_argument_type;
					typedef bool		result_type;
				
				protected:
					key_compare			comp_;
					value_compare( key_compare c): comp_(c) {};

				public:

					bool operator()( const value_type& lhs, const value_type& rhs ) const
					{ return comp_(lhs.first, rhs.first);}

					value_compare& operator=(const value_compare& other)
					{
						if (this !=  &other)
							comp_ = other.comp_;
						return *this;
					}
			};

			map(
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				:tree_(value_type_compare(comp), alloc){}

		    template <class InputIterator>
			map(InputIterator first, 
				InputIterator last,
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				:tree_(value_type_compare(comp), alloc)
			{ insert(first, last); }
			
			map(const map& other): tree_(other.tree_) {}

			~map() {}
		
		private:
			private:
				tree_type tree_;

		public:

			/***********************************************
				ELEMENT ACCESS
			***********************************************/

			/*Returns a reference to the mapped value of the element with key equivalent to key.*/
			mapped_type& at(const key_type& key)
			{
				iterator it = find(key);
				if (it == end())
					throw std::out_of_range("key not found");
				return it->second;
			}

			/*Returns a read-only reference to the mapped value of the element with key equivalent to key.*/
			const mapped_type& at(const key_type& key) const
			{
				const_iterator it = find(key);
				if (it == end())
					throw std::out_of_range("key not found");
				return it->second;
			}

			/*Returns a reference to the value that is mapped to a key equivalent to key, 
			inserting if such key does not already exist.*/
			mapped_type& operator[](const Key& key)
			{
				return tree_.insert(ft::make_pair(key, mapped_type())).first->second;
			}

			/***********************************************
				ITERATORS
			***********************************************/
			
			/*Returns an iterator to the first element of the map.*/
			iterator begin()
			{ return tree_.begin();}

			/*Returns an read-only iterator to the first element of the map. */
			const_iterator begin() const
			{ return tree_.begin();}

			/*Returns an iterator to the element following the last element of the map.*/
			iterator end() 
			{ return tree_.end();}

			/*Returns an read-only iterator to the element following the last element of the map. */
			const_iterator end() const
			{ return tree_.end();}

			/*Returns a reverse iterator to the first element of the reversed map.*/
			reverse_iterator rbegin()
			{ return reverse_iterator(end());}

			/*Returns a read-only reverse iterator to the first element of the reversed map.*/
			const_reverse_iterator rbegin() const
			{ return const_reverse_iterator(end());}

			/*Returns a reverse iterator to the element following the last element of the reversed map.*/
			reverse_iterator rend()
			{ return reverse_iterator(begin());}

			/*Returns a read-only reverse iterator to the element following the last element of the reversed map. */
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
				// std::cerr << pos.base()->value.first;
				try
				{
					return tree_.erase(pos);
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << "ft::map::compare";
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
					std::cerr << e.what() << "ft::map::compare";
				}
				return first;
			}

			/*Removes the element with the key equivalent to key*/
			size_type erase( const Key& key )
			{
				iterator node = find(key);

				if (node == end())
					return 0;
				tree_.erase(node);
				return 1;
			}

			/*Exchanges the contents of the container with those of other*/
			void swap(map& other)
			{ ft::swap(tree_.swap(other.tree_));	}

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

			/*Returns a reference to the mapped value of the element with key equivalent to key.*/

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
			{ return value_compare(); }

			allocator_type get_allocator() const
			{ return tree_.get_allocator(); }

			void print_tree()
			{ tree_.print_from_node_(tree_.root_node());};

	};

	template <typename Key, typename T, typename Compare, typename Allocator>
	inline bool operator==(const map<Key, T, Compare, Allocator>& lhs,
						const map<Key, T, Compare, Allocator>& rhs)
	{
		return (lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	inline bool operator!=(const map<Key, T, Compare, Allocator>& lhs,
						const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	inline bool operator<(const map<Key, T, Compare, Allocator>& lhs,
						const map<Key, T, Compare, Allocator>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	inline bool operator<=(const map<Key, T, Compare, Allocator>& lhs,
						const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	inline bool operator>(const map<Key, T, Compare, Allocator>& lhs,
						const map<Key, T, Compare, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	inline bool operator>=(const map<Key, T, Compare, Allocator>& lhs,
						const map<Key, T, Compare, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

	template <typename Key, typename T, typename Compare, typename Allocator>
	inline void swap(map<Key, T, Compare, Allocator>& x, map<Key, T, Compare, Allocator>& y)
	{
		x.swap(y);
	}
}