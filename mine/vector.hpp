#pragma once

#include "mynullptr.hpp"
#include "vector_iterator.hpp"
#include "algorithm.hpp"
#include <memory>
#include <exception>

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		private:
			typedef vector<T, Alloc>							vector_type;

		public:
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::size_type			size_type;
			typedef typename allocator_type::difference_type	difference_type;
			typedef ft::normal_iterator<pointer, vector>		iterator;
			typedef ft::normal_iterator<const_pointer, vector>	const_iterator;
			typedef ft::reverse_iterator<iterator>				reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		public:
			/***********************************************
				Constructors
			***********************************************/

			/*Default constructor creates no elements*/
			explicit vector(const allocator_type& alloc = allocator_type())
			:alloc_(alloc), start_(mynullptr), finish_(mynullptr), finish_of_storage_(mynullptr)
			{ }

			/*Constructors that fills the vector with @n copies of @value*/
			explicit vector(
				size_type n, 
				const value_type& value = value_type(), 
				const allocator_type& alloc = allocator_type())
			:alloc_(alloc), start_(mynullptr), finish_(mynullptr), finish_of_storage_(mynullptr)
			{
				if (n > 0)
				{
					allocate_(n);
					construct_(n, value);
				}
			}

			/*constructor builds vector consisting of copies of the elements from [@first, last) */
			template <typename InputIterator>
			vector(
				InputIterator first, 
				typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type last, 
				const allocator_type& alloc = allocator_type())
			:alloc_(alloc), start_(mynullptr), finish_(mynullptr), finish_of_storage_(mynullptr)
			{ assign(first, last);}

			/*Copy constructor. Constructs the container with the copy of the contents of @other*/
			vector(const vector& other)
			:alloc_(other.get_allocator()), start_(mynullptr), finish_(mynullptr), finish_of_storage_(mynullptr)
			{
				allocate_(other.size());
				construct_(other.start_, other.finish_, ft::iterator_category(other.start_));
			}

			/***********************************************
				DESTRUCTORS
			***********************************************/

			/*Destructs the vector. The destructors of the elements are called and the used storage is deallocated.*/
				~vector(){deallocate_();}

			/***********************************************
				ASSIGNMENT
			***********************************************/

			/* Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.*/
			void assign (size_type n, const T& value)
			{
				if (n <= capacity())
				{
					ft::fill_n(start_, ft::min(size(), n), value);
					if (n > size())
						construct_(n - size(), value);
					else
						destroy_(start_ + n);
				}
				else
				{
					vector tmp(n, value);
					(*this).swap(tmp);
				}
			}

			/*Replaces the contents with copies of those in the range [first, last), and modifying its size accordingly.*/
			template <typename InputIterator>
			void assign (InputIterator first, typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type last)
			{ assign_in_range_(first, last, ft::iterator_category(first));}

			/*Returns the allocator associated with the container. */
			allocator_type get_allocator() const
			{ return alloc_;}

			/*Copy assignment operator. Replaces the contents with a copy of the contents of other.*/
			vector& operator=(const vector& other)
			{
				if (*this != other)
				{
					alloc_ = other.get_allocator();
					assign(other.begin(), other.end());
				}
				return *this;
			}

			/***********************************************
				ELEMENT ACCESS
			***********************************************/

			/*Provides access to the data contained in the vector. Throws exception if pos falls out of range of vector*/
			reference at(size_type pos)
			{
				if (pos >= size())
					throw std::out_of_range("vector");
				return (*this)[pos];
			}

			/*Provides access to the data contained in the vector. Throws exception if pos falls out of range of vector*/
			const_reference at( size_type pos ) const
			{
				if (pos >= size())
					throw std::out_of_range("vector");
				return (*this)[pos];
			}

			/*This operator allows for easy, array-style, data access. Out_of_range lookups are not defined.*/
			reference operator[](size_type pos)
			{return *(this->start_ + pos);}

			/*This operator allows for easy, array-style, data access. Out_of_range lookups are not defined.*/
			const_reference operator[](size_type pos) const
			{return *(this->start_ + pos);}

			/*Returns a read/write reference to the data at the first element of the vector*/
			reference front()
			{return *start_;}

			/*Returns a read-only reference to the data at the first element of the vector*/
			const_reference front() const
			{return *start_;}

			/*Returns a read/write reference to the data at the last element of the vector*/
			reference back()
			{return *(finish_ - 1);}

			/*Returns a read-only reference to the data at the last element of the vector*/
			const_reference back() const
			{return *(finish_ - 1);}

			/*Returns pointer to the underlying array serving as element storage.*/
			pointer data()
			{return start_;}

			/*Returns a read-only pointer to the underlying array serving as element storage.*/
			const_pointer data() const
			{return start_;}

			/***********************************************
				ITERATORS
			***********************************************/
			
			/*Returns an iterator to the first element of the vector. */
			iterator begin() {return iterator(start_);}

			/*Returns a read-only iterator to the first element of the vector. */
			const_iterator begin() const {return const_iterator(start_);}

			/*Returns a reverse iterator to the first element of the reversed vector.*/
			reverse_iterator rbegin() {return reverse_iterator(end());}

			/*Returns a read-only reverse iterator to the first element of the reversed vector.*/
			const_reverse_iterator rbegin() const {return const_reverse_iterator(end());}

			/*Returns an iterator to the element following the last element of the vector.*/
			iterator end() {return iterator(finish_);}

			/*Returns an read-only iterator to the element following the last element of the vector.*/
			const_iterator end() const {return const_iterator(finish_);}

			/*Returns a reverse iterator to the element following the last element of the reversed vector.*/
			reverse_iterator rend() {return reverse_iterator(begin());}

			/*Returns a read-only reverse iterator to the element following the last element of the reversed vector.*/
			const_reverse_iterator rend() const {return const_reverse_iterator(begin());}
	
			/***********************************************
				CAPACITY
			***********************************************/

			/*Checks if the container has no elements*/
			bool empty() const
			{return start_ == finish_;}

			/*Returns the number of elements in the container*/
			size_type size() const
			{return size_type(finish_ - start_);}

			/*Returns the maximum number of elements the container is able to hold due to system or library limitations*/
			size_type max_size() const
			{return ft::min<size_type>(alloc_.max_size(), std::numeric_limits<difference_type>::max());}

			/*Increase the capacity of the vector. 
			If @new_cap is greater than the current capacity, new storage is allocated, otherwise the function does nothing*/
			void reserve(size_type new_cap)
			{
				if (new_cap > max_size())
					throw std::length_error("vector");
				if (new_cap > capacity())
				{
					vector new_vect(alloc_);
					new_vect.allocate_(get_new_size_(new_cap));
					new_vect.construct_(start_, finish_, ft::iterator_category(finish_));
					swap(new_vect);
				}
			}

			/*Returns the number of elements that the container has currently allocated space for. */
			size_type capacity() const
			{return size_type(finish_of_storage_ - start_);}

			/***********************************************
				MODIFIERS
			***********************************************/

			/*Erases all elements from the container. After this call, size() returns zero.*/
			void clear()
			{ destroy_(start_);}

			/*Inserts elements at the specified location in the container. Inserts @value before @pos.*/
			iterator insert(iterator pos, const value_type& value)
			{
				difference_type offset = pos - begin();
				insert(pos, 1, value);
				return begin() + offset;
			// { return insert(pos, 1, value);}
			}

			/*Inserts elements at the specified location in the container. Inserts @count copies of the @value before @pos.*/
			void insert(iterator pos, size_type count, const value_type& value)
			{
				if (count > 0) 
				{
					const difference_type offset = pos - begin();
					const size_type       old_size = size();
					resize(old_size + count);
					ft::copy_backward(start_ + offset, start_ + old_size, start_ + old_size + count);
					ft::fill_n(start_ + offset, count, value);
        		}
			}
			
			/*Inserts elements at the specified location in the container. Inserts elements from range [@first, @last) before @pos.*/
		    template <class InputIterator>
			void insert(
				 iterator position, 
				 InputIterator first, 
				 typename ft::enable_if<!ft::is_integer<InputIterator>::value, InputIterator>::type last)
			{ insert_range_(position, first, last, ft::iterator_category(first));}

			/*Removes the element at pos*/
			iterator erase(iterator pos)
			{
				if ((pos + 1) != end())
					ft::copy(pos + 1, end(), pos);
				pop_back();
				return pos;
			}

			/*Removes the elements in the range [first, last)*/
			iterator erase(iterator first, iterator last)
			{
				if (first != last) 
				{
					pointer p = start_ + (first - begin());
					destroy_(ft::copy(p + (last - first), finish_, p));
				}
				return first;
			}
			
			/*Appends the given element value to the end of the container. The new element is initialized as a copy of value.*/
			void push_back(const value_type& value)
			{
				if (finish_ == finish_of_storage_)
					reserve(capacity() + 1);
				construct_(1, value);
			}

			/*Removes the last element of the container.*/
			void pop_back()
			{ destroy_(finish_ - 1);}

			/*Resizes the container to contain count elements.*/
			void resize(size_type count, value_type value = value_type())
			{
				const size_type old = size();
				if (old > count)
				{ destroy_(start_ + count);}
				if (old < count)
				{
					reserve(count);
					construct_(count - old, value);
				}
			}

			/*Exchanges the contents and capacity of the container with those of other.*/
			void swap(vector& other)
			{
				std::swap(start_, other.start_);
				std::swap(alloc_, other.alloc_);
				std::swap(finish_, other.finish_);
				std::swap(finish_of_storage_, other.finish_of_storage_);
			}


			private:
			/***********************************************
				PRIVATE MEMBER FUNCTIONS
			***********************************************/

			/*Allocates (but does not initialize) storage for @n instances of objec-type @value_type*/
			inline void allocate_(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector");
				start_ = finish_ = alloc_.allocate(n);
				finish_of_storage_ = start_ + n;
			}

			/*Initializes @n objects of objec-type @val*/
			inline void construct_(size_type n, const_reference val = value_type())
			{
				for (size_type i = 0; i < n; ++i, ++finish_)
					alloc_.construct(finish_, val);
			}

			template <typename ForwardIterator>
			inline void construct_(ForwardIterator first, ForwardIterator last, forward_iterator_tag)
			{
				for (; first != last; ++first, ++finish_)
					alloc_.construct(finish_, *first);
			}

			/*Calls the destructor of every object in storage up to @new_end starting from @_finish*/
			inline void destroy_(pointer new_end)
			{
				for (; finish_ != new_end;)
					alloc_.destroy(--finish_);
			}

			/*Deallocates the storage referenced by start_*/
			inline void deallocate_()
			{
				if (start_ != mynullptr)
				{
					destroy_(start_);
					alloc_.deallocate(start_, capacity());
					start_ = finish_ = finish_of_storage_ = mynullptr;
				}
			}

			/*Helper function used by @assign for ForwardIterators*/			
			template <typename ForwardIterator>
			inline void assign_in_range_(ForwardIterator first, ForwardIterator last, ft::forward_iterator_tag)
			{
				clear();
				const size_type range = static_cast<size_type>(ft::distance(first, last));
				if (range > 0)
				{
					if (range > capacity())
					{
						deallocate_();
						allocate_(range);
					}
					construct_(first, last, ft::iterator_category(first));
				}
			}

			/*Helper function used by @assign for InputIterators*/			
			template <typename InputIterator>
			inline void assign_in_range_(InputIterator first, InputIterator last, ft::input_iterator_tag)
			{
				clear();
				for (; first != last; ++first)
					push_back(*first);
			}

			/* Returns the new size to allocate when current capacity is exceeded*/ 
			size_type get_new_size_(size_type new_size) const
			{
				const size_type max(max_size());
				if (new_size > max)
					throw std::length_error("vector");
				const size_type cap(capacity());
				if (new_size <= cap)
					return new_size;
				return ft::min(ft::max(cap * 2, new_size), max);
			}

			template <class ForwardIterator>
			void insert_range_(
				iterator position, 
				ForwardIterator first, 
				ForwardIterator last,
				ft::forward_iterator_tag)
			{
				size_type n = static_cast<size_type>(ft::distance(first, last));
				if (n > 0) 
				{
					const difference_type offset = position - begin();
					const size_type       old_size = size();
					resize(old_size + n);
					ft::copy_backward(start_ + offset, start_ + old_size, start_ + old_size + n);
					ft::copy(first, last, start_ + offset);
				}
			}

			template <typename InputIterator>
			void insert_range_(
				iterator pos, 
				InputIterator first, 
				InputIterator last,
				ft::input_iterator_tag)
			{
				if (pos == end()) 
				{
					for (; first != last; ++first)
						push_back(*first);
				} 
				else if (first != last) 
				{
					vector tmp(first, last);
					insert(pos, tmp.begin(), tmp.end());
				}
			}

		private:
			allocator_type	alloc_;
			pointer			start_;
			pointer			finish_;
			pointer			finish_of_storage_;
	};

/***********************************************
	NON-MEMBER FUNCTIONS
***********************************************/

/*Checks if the contents of lhs and rhs are equal*/
template <typename T, class Allocator >
inline bool operator==(const vector <T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{ return lhs.size() == rhs.size() &&  ft::equal(lhs.begin(), lhs.end(), rhs.begin());}

/*Checks if the contents of lhs and rhs are not equal*/
template <typename T, class Allocator >
inline bool operator!=(const vector <T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{ return !(lhs == rhs);}

/*Compares the contents of lhs and rhs lexicographically.*/
template <typename T, class Allocator >
inline bool operator<(const vector <T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());}

/*Compares the contents of lhs and rhs lexicographically. Based on operator @< */
template <typename T, class Allocator >
inline bool operator> (const vector <T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{ return rhs < lhs;}

/*Compares the contents of lhs and rhs lexicographically. Based on operator @<*/
template <typename T, class Allocator >
inline bool operator<=(const vector <T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{ return !(rhs < lhs);}

/*Compares the contents of lhs and rhs lexicographically. Based on operator @<*/
template <typename T, class Allocator >
inline bool operator>=(const vector <T, Allocator>& lhs, const vector<T, Allocator>& rhs)
{ return !(lhs < rhs);}

/* Specializes the swap algorithm for vector. Swaps the contents of lhs and rhs*/
template <typename Tp, typename Allocator>
void swap(vector<Tp, Allocator>& lhs, vector<Tp, Allocator>& rhs)
{ lhs.swap(rhs);}

};