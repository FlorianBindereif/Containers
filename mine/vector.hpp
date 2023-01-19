#pragma once

#include "mynullptr.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include <memory>
#include <exception>

namespace ft
{
	template<typename T, typename Alloc = std::allocator<T> >
	class vector
	{
		private:
			// TYPEDEFS
			typedef vector<T, Alloc>                           vector_type;

		public:
			// TYPEDEFS
			typedef T											value_type;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::pointer			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::size_type			size_type;
		    typedef std::ptrdiff_t                          	difference_type;

		public:
			//CONSTRUCTORS

			/*Default constructor creates no elements*/
			explicit vector(const allocator_type& alloc = allocator_type())
			:alloc_(alloc), start_(mynullptr), finish_(mynullptr), finish_of_storage_(mynullptr)
			{ };

			/*Constructors that fills the vector with @n copies of @value*/
			explicit vector(size_type n, const value_type& value = value_type(), const allocator_type& alloc = allocator_type())
			:alloc_(alloc), start_(mynullptr), finish_(mynullptr), finish_of_storage_(mynullptr)
			{
				if (n > 0)
				{
					allocate_(n);
					construct_(n);
				}
			}

			/*constructor builds vector consisting of copies of the elements from [@first, last) */
			template <typename InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
			{

			}

			//PUBLIC MEMBER FUNCTIONS

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
					vector tmp(n, value)
					(*this).swap(tmp);
				}
			}

			template <typename InputIterator>
			void assign (InputIterator first, InputIterator last)
			{
				
			}


			//ELEMENT ACCESS

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
			{return *finish_ - 1;}

			/*Returns a read-only reference to the data at the last element of the vector*/
			const_reference back() const
			{return *finish_ - 1;}

			/*Returns pointer to the underlying array serving as element storage.*/
			pointer data()
			{return start_;}

			/*Returns a read-only pointer to the underlying array serving as element storage.*/
			const_pointer data() const
			{return start_;}

			// ITERATORS

			// CAPACITY
			
			/*Checks if the container has no elements*/
			bool empty() const
			{return start_ == finish_;}

			/*Returns the number of elements in the container*/
			size_type size() const
			{return size_type(finish_ - start_);}

			/*Returns the maximum number of elements the container is able to hold due to system or library limitations*/
			size_type max_size() const
			{return ft::min<size_type>(alloc_.max_size(), std::numeric_limits<difference_type>::max());}

			/*Returns the number of elements that the container has currently allocated space for. */
			size_type capacity() const
			{return size_type(finish_of_storage_ - start_);}

			/*Increase the capacity of the vector. 
			If @new_cap is greater than the current capacity, new storage is allocated, otherwise the function does nothing*/
			void reserve(size_type new_cap)
			{
				if (new_cap > max_size())
					throw std::length_error("vector");
				if (new_cap > capacity())
				{
				}
			}

			// MODIFIERS

			/*Exchanges the contents and capacity of the container with those of other. */
			void swap(vector& other)
			{
				ft:swap(start_, other.start_);
				ft:swap(finish_, other.finish_);
				ft:swap(finish_of_storage_, other.finish_of_storage_);
				ft:swap(alloc_, other.alloc_);
			}

			private:

			//PRIVATE MEMBER FUNCTIONS

			/*Allocates (but does not initialize) storage for @n instances of objec-type @value_type*/
			inline void allocate_(size_type n)
			{
				if (n > max_size())
					throw std::length_error("vector");
				start_ = finish_ = alloc_.allocate(n);
				finish_of_storage_ = start_ + n;
			}

			/*Initializes @n objects of objec-type @val*/
			inline void construct_(size_type n, val = value_type())
			{
				for (size_type i = 0; i < n; ++i, ++finish_)
					alloc_.construct(finish_, val);
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

		private:
			allocator_type	alloc_;
			pointer			start_;
			pointer			finish_;
			pointer			finish_of_storage_;
	};
};
