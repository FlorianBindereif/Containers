#pragma once
#include "red_black_tree.hpp"
#include "pair.hpp"

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

			explicit map(
				const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
				:tree_(value_type_compare(comp), alloc){}


		    ft::pair<iterator, bool> insert(const value_type& val) 
			{ return tree_.insert(val); }
		
			void print_tree()
			{
				tree_.print_from_node_(tree_.root_node_());
			}

		private:
			tree_type tree_;
	};
	
	
}