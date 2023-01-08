// Vector implementation -*- C++ -*-
/** @file stl_vector.h
 *  This is an internal header file, included by other library headers.
 *  You should not attempt to use it directly.
 */

#ifndef STL_VECTOR_H_
#define STL_VECTOR_H_

#include <memory>
#include <algorithm>
#include <stdexcept>
#include <iterator>

#include "stl_uninitialized.h"
#include "stl_iterator.h"
#include "stl_algobase.h"

namespace ft {


/**
 * @if maint
 * Vector base class. This class provides the unified face for %vector's
 * allocation. This class's constructor and destructor allocate and
 * deallocate (but do not initialize) storage. This makes %exception
 * safety easier.
 * 
 * Nothing in this class ever constructs or destroys an actual Tp element.
 * (Vector handles that itself.) Only/All memory management is performed
 * here.
 * @endif
 */

template<typename Tp, typename Alloc>
struct Vector_base
{
  typedef typename Alloc::template rebind<Tp>::other Tp_alloc_type;

  struct Vector_impl
    : public Tp_alloc_type
    {
      Tp* M_start;
      Tp* M_finish;
      Tp* M_end_of_storage;
      Vector_impl(Tp_alloc_type const& a)
      : Tp_alloc_type(a), M_start(0), M_finish(0), M_end_of_storage(0)
      { }
    };

   public:
    typedef Alloc allocator_type;
    Vector_impl   M_impl;

    Tp_alloc_type&
    M_get_Tp_allocator()
    { return *static_cast<Tp_alloc_type*>(&this->M_impl); } 

    const Tp_alloc_type&
    M_get_Tp_allocator() const
    { return *static_cast<const Tp_alloc_type*>(&this->M_impl); } 

    allocator_type
    get_allocator() const
    { return allocator_type(M_get_Tp_allocator()); }

    Vector_base(const allocator_type& a)
    : M_impl(a)
    { }

    Vector_base(size_t n, const allocator_type& a)
    : M_impl(a)
    {
      this->M_impl.M_start = this->M_allocate(n);
      this->M_impl.M_finish = this->M_impl.M_start;
      this->M_impl.M_end_of_storage = this->M_impl.M_start + n;
    }

    ~Vector_base()
    {
      M_deallocate(this->M_impl.M_start, this->M_impl.M_end_of_storage
        - this->M_impl.M_start);
    }
  
    Tp*
    M_allocate(size_t n)
    { return M_impl.allocate(n); }

    void
    M_deallocate(Tp* p, size_t n)
    {
      if (p)
        M_impl.deallocate(p, n);
    }
};

/**
 * @brief A standard container which offers fixed time access to
 * individual elements in any order.
 * 
 * @ingroup Containers
 * @ingroup Sequences
 * 
 * In some terminology a %vector can be described as a dynamic
 * C-style array, it offers fast and efficient access to individual
 * elements in any order and saves the user from worrying about
 * memory and size allocation. Subscripting ( @c [] ) access is
 * also provided as with C-style arrays.
*/
template<typename Tp, typename Alloc = std::allocator<Tp> >
class vector : protected Vector_base<Tp, Alloc>
{
  private:
    typedef typename Alloc::value_type                        Alloc_value_type;
    typedef Vector_base<Tp, Alloc>                            Base;
    typedef vector<Tp, Alloc>                                 vector_type;
    typedef typename Base::Tp_alloc_type                      Tp_alloc_type;

  public:
    typedef Tp                                                value_type;
    typedef typename Tp_alloc_type::pointer                   pointer;
    typedef typename Tp_alloc_type::const_pointer             const_pointer;
    typedef typename Tp_alloc_type::reference                 reference;
    typedef typename Tp_alloc_type::const_reference           const_reference;
    typedef ft::normal_iterator<pointer, vector_type>         iterator;
    typedef ft::normal_iterator<const_pointer, vector_type>   const_iterator;
    typedef ft::reverse_iterator<iterator>                    reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>              const_reverse_iterator;
    typedef std::size_t                                       size_type;
    typedef std::ptrdiff_t                                    difference_type;
    typedef Alloc                                             allocator_type;

  protected:
    using Base::M_allocate;
    using Base::M_deallocate;
    using Base::M_impl;
    using Base::M_get_Tp_allocator;


  public:

    // construct/copy/destroy
    // (assign() and get_allocator() are also listed in this section)
    /**
     * @brief Default constructor creates no elements.
     */
    explicit
    vector(const allocator_type& a = allocator_type())
    : Base(a)
    { }

    /**
     * @brief Create a %vector with copies of an exemplar element.
     * @param n The number of elements to initially create.
     * @param value An element to copy.
     * 
     * This constructor fills the %vector with @a n copies of @a value.
     */
    explicit
    vector(size_type n, const value_type& value = value_type(),
      const allocator_type& a = allocator_type())
    : Base(n, a)
    {
      ft::uninitialized_fill_n_a(this->M_impl.M_start, n, value,
        M_get_Tp_allocator());
      this->M_impl.M_finish = this->M_impl.M_start + n;
    }

    /**
     * @brief %Vector copy constructor.
     * @param x A %vector of identical element and allocator types.
     * 
     * The newly-created %vector uses a copy of the allocation
     * object used by @a x. All the elements of @a x are copied,
     * but an extra memory in
     * @a x (for fast expansion) will not be copied.
     */
    vector(const vector& x)
    : Base(x.size(), x.M_get_Tp_allocator())
    {
      this->M_impl.M_finish = ft::uninitialized_copy_a(x.begin(), x.end(),
        this->M_impl.M_start, M_get_Tp_allocator());
    }

    /**
     * @brief Builds a %vector from a range.
     * @param first An input iterator.
     * @param last An input iterator.
     * 
     * Create a %vector consisting of copies of the elements from
     * [first,last).
     * 
     * If the iterators are forward, bidirectional, or
     * random-access, then this will call the elements' copy
     * constructor N times (where N is distance(first,last)) and do
     * no memory reallocation. But if only input iterators are
     * used, then this will do at most 2N calls to the copy
     * constructor, and lonN memory reallocations.
     */
    template <typename InputIterator>
    vector(InputIterator first, InputIterator last,
      const allocator_type& a = allocator_type())
    : Base(a)
    {
      // Check whether it's an integral type. If so, it's not an iterator.
      typedef typename ft::is_integer<InputIterator>::type Integral;
      M_initialize_dispatch(first, last, Integral());
    }

    /**
     * The dtor only erases the elements, and note that if the
     * elements themselves are pointers, the pointed-to memory is
     * not touched in any way. Managing the pointer is the user's
     * responsibilty.
     */
    ~vector()
    {
      ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish,
        M_get_Tp_allocator());
    }

    /**
     * @brief %Vector assignment operator.
     * @param x A $vector of identical element and allocator types.
     * 
     * All the elements of @a x are copied, but any extra memory in
     * @a x (for fast expansion) will not be copied. Unlinke the
     * copy constructor, the allocator object is not copied.
     */
    vector&
    operator=(const vector& x)
    {
      if (&x != this)
      {
        const size_type xlen = x.size();
        if (xlen > capacity())
        {
          pointer tmp = M_allocate_and_copy(xlen, x.begin(),
            x.end());
          ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish,
            M_get_Tp_allocator());
          M_deallocate(this->M_impl.M_start,
            this->M_impl.M_end_of_storage
            - this->M_impl.M_start);
          this->M_impl.M_start = tmp;
          this->M_impl.M_end_of_storage = this->M_impl.M_start + xlen;
        }
        else if (size() >= xlen)
        {
          ft::Destroy(std::copy(x.begin(), x.end(), begin()),
            end(), M_get_Tp_allocator());
        }
        else
        {
          std::copy(x.M_impl.M_start, x.M_impl.M_start + size(),
            this->M_impl.M_start);
          ft::uninitialized_copy_a(x.M_impl.M_start + size(),
            x.M_impl.M_finish,
            this->M_impl.M_finish,
            M_get_Tp_allocator());
        }
        this->M_impl.M_finish = this->M_impl.M_start + xlen;
      }
      return *this;
    }

    /**
     * @brief Assigns a given value to a %vector.
     * @param n Number of elements to be assigned.
     * @param val Value to be assigned.
     * 
     * This function fills a %vector with @a n copies of the given
     * value. Note that the assignment completely changes the
     * %vector and that the resulting %vector's size is the same as
     * the number of elements assigned. Old data may be lost.
     */
    void
    assign(size_type n, const value_type& val)
    { M_fill_assign(n, val); }
    
    /**
     * @brief Assigns a range to a %vector.
     * @param first An input iterator.
     * @param last An input iterator.
     * 
     * Thie function fills a %vector with copies of the elements in the
     * range [first,last).
     * 
     * Note that the assignment completely changes the %vector and
     * that the resulting %vector's size is the same as the number
     * of elements assigend. Old data may be lost.
     */
    template <typename InputIterator>
    void
    assign(InputIterator first, InputIterator last)
    {
      // Check whether it's an integral type. If so, it's not an iterator.
      typedef typename ft::is_integer<InputIterator>::type Integral;
      M_assign_dispatch(first, last, Integral());
    }

    // iterators
    /**
     * Returns a read/write iterator that points to the first
     * element in the %vector. Iteration is done in ordinary
     * element order.
     */
    iterator
    begin()
    { return iterator(this->M_impl.M_start); }

    /**
     * Returns a read-only (constant) iterator that points to the
     * first element in the %vector. Iteration is done in ordinary
     * element order.
     */
    const_iterator
    begin() const
    { return const_iterator(this->M_impl.M_start); }

    /**
     * Returns a read/write iterator that points one past the last
     * element in the %vector. Iteration is done in ordinary
     * element order.
     */
    iterator
    end()
    { return iterator(this->M_impl.M_finish); }

    /**
     * Returns a read-only (constant) iterator that points one past
     * the last element in the %vector. Iteration is done in
     * ordinary element order.
     */
    const_iterator
    end() const
    { return const_iterator(this->M_impl.M_finish); }

    /**
     * Returns a read/write reverse iterator that points to the
     * last element in the %vector. Iteration is done in reverse
     * element order.
     */
    reverse_iterator
    rbegin()
    { return reverse_iterator(end()); }

    /**
     * Returns a read-only (constant) reverse iterator that points
     * to the last element in the %vector. Iteration is done in
     * reverse element order.
     */
    const_reverse_iterator
    rbegin() const
    { return const_reverse_iterator(end()); }

    /**
     * Returns a read/write reverse iterator that points to one
     * beforee the first element in the %vector. Iteration is done
     * in rever element order.
     */
    reverse_iterator
    rend()
    { return reverse_iterator(begin()); }

    /**
     * Returns a read-only (constant) reverse iterator that points
     * to one before the first element in the %vector. Iteration
     * is done in reverse element order.
     */
    const_reverse_iterator
    rend() const
    { return const_reverse_iterator(begin()); }

    // capacity
    /** Returns the number of elements in the %vector. */
    size_type
    size() const
    { return size_type(this->M_impl.M_finish - this->M_impl.M_start); }

    /** Returns the size() of the largest possible %vector. */
    size_type
    max_size() const
    { return M_get_Tp_allocator().max_size(); }

    /**
     * @brief Resizes the %vector to the specified number of elements.
     * @param new_size Number of elements the %vector should contain.
     * @param x Data with which new elements should be populated.
     * 
     * This function will %resize the %vector to the specified
     * number of elements. If the number is smaller than the
     * %vector's current size the %vector is truncated, otherwise
     * the %vector is extended and new elements are populated with
     * given data.
     */
    void
    resize(size_type new_size, value_type x = value_type())
    {
      if (new_size < size())
        M_erase_at_end(this->M_impl.M_start + new_size);
      else
        insert(end(), new_size - size(), x);
    }

    /**
     * Returns the total number of elements that the %vector can
     * hold before needing to allocate more memory.
     */
    size_type
    capacity() const
    { return size_type(this->M_impl.M_end_of_storage
      - this->M_impl.M_start); }

    /**
     * Returns true is the %vector is empty. (Thus begin() would
     * equal end().)
     */
    bool
    empty() const
    { return begin() == end(); }

    /**
     * @brief Attempt to preallocate enough memory for specified number of 
     *        elements.
     * @param n Number of elements required.
     * @throw std::length_error If @a n exceeds @c max_size().
     * 
     * This function attempts to reserve enough memory for the
     * %vector to hold the specified number of elements. If the
     * number requested is more than max_size(), length_error is
     * thrown.
     * 
     * The advantage of this function is that if optimal code is a
     * necessity and the user can determine the number of elements
     * that will be required, the user can reserve the memory in
     * %advance, and thus prevent a possible reallocation of memory
     * and copying of %vector data.
     */
    void
    reserve(size_type n)
    {
      if (n > this->max_size())
        throw std::length_error("vector::reserve");
      if (this->capacity() < n)
      {
        const size_type old_size = size();
        pointer tmp = M_allocate_and_copy(n, this->M_impl.M_start,
          this->M_impl.M_finish);
        ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish,
          M_get_Tp_allocator());
        M_deallocate(this->M_impl.M_start,
          this->M_impl.M_end_of_storage
          - this->M_impl.M_start);
        this->M_impl.M_start = tmp;
        this->M_impl.M_finish = tmp + old_size;
        this->M_impl.M_end_of_storage = this->M_impl.M_start + n;
      }
    }

    // element access
    /**
     * @brief Subscript access to the data contained in the %vector.
     * @param n The index of the element for which data should be
     * accessed.
     * @return Read/write reference to data.
     * 
     * This operator allows for easy, array-style, data access.
     * Note that data access with this operator is unchecked and
     * out_of_range lookups are not defined. (For checked lookups
     * see at().)
     */
    reference
    operator[](size_type n)
    { return *(this->M_impl.M_start + n); }

    /**
     * @brief Subscript access to the data contained in the %vector.
     * @param n The index of the element for which data should be
     * accessed.
     * @return Read-only (constant) reference to data.
     * 
     * This operator allows for easy, array-style, data access.
     * Note that data access with this operator is unchecked and
     * out_of_range lookups are not defined. (For checked lookups
     * see at().)
     */
    const_reference
    operator[](size_type n) const
    { return *(this->M_impl.M_start + n); }

  protected:
    /// @if maint Safety check used only from at(). @endif
    void
    M_range_check(size_type n) const
    {
      if (n >= this->size())
        throw std::out_of_range("vector::M_range_check");
    }

  public:
    /**
     * @brief Provides access to the data contained in the %vector.
     * @param n The index of the element for which data should be
     * accessed.
     * @return Read/write reference to data.
     * @throw std::out_of_range If @a n is an invalid index.
     * 
     * This function provides for safer data access. The parameter
     * is first checked that it is in the range of the vector. The
     * function throws out_of_range if the check fails.
     */
    reference
    at(size_type n)
    {
      M_range_check(n);
      return (*this)[n];
    }

    /**
     * @brief Provides access to the data contained in the %vector.
     * @param n The index of the element for which data should be
     * accessed.
     * @return Read-only (constant) reference to data.
     * @throw std::out_of_range If @a n is an invalid index.
     * 
     * This function provides for safer data access. The parameter
     * is first checked that it is in the range of the vector. The
     * function throws out_of_range if the check fails.
     */

    const_reference
    at(size_type n) const
    {
      M_range_check(n);
      return (*this)[n];
    }

    /**
     * Returns a read/write reference to the data at the first
     * element of the %vector.
     */
    reference
    front()
    { return *begin(); }

    /**
     * Returns a read-only (constant)reference to the data at the first
     * element of the %vector.
     */
    const_reference
    front() const
    { return *begin(); }

    /**
     * Returns a read/write reference to the data at the last
     * element of the %vector.
     */
    reference
    back()
    { return *(end() - 1); }

    /**
     * Returns a read-only (constant)reference to the data at the
     * last element of the %vector.
     */
    const_reference
    back() const
    { return *(end() - 1); }

    // DR 464. Suggestion for new member functions in standard containers.
    // data access
    /**
     * Returns a pointer such that [data(), data() + size()) is a valid
     * range. For a non-empty %vector, data() == &front().
     */
    pointer
    data()
    { return pointer(this->M_impl.M_start); }

    const_pointer
    data() const
    { return pointer(this->M_impl.M_start); }

    // modifiers
    /**
     * @brief Add data to the end of the %vector.
     * @param x Data to be added.
     * 
     * This is a typical stack operation. The function creates an
     * element at the end of the %vector and assigns the given data
     * to it. Due to the nature of a %vector this operation can be
     * done in constant time if the %vector has preallocated space
     * available.
     */
    void
    push_back(const value_type& x)
    {
      if (this->M_impl.M_finish != this->M_impl.M_end_of_storage)
      {
        this->M_impl.construct(this->M_impl.M_finish, x);
        ++this->M_impl.M_finish;
      }
      else
        M_insert_aux(end(), x);
    }

    /**
     * @brief Removes last element.
     * 
     * This is a typical stack operation. It shrinks the %vector by one.
     * 
     * Note that no data is returned, and if the last element's
     * data is needed, it should be retrieved before pop_back() is
     * called.
     */
    void
    pop_back()
    {
      --this->M_impl.M_finish;
      this->M_impl.destroy(this->M_impl.M_finish);
    }

    /**
     * @brief Inserts given value into %vector before specified iterator.
     * @param position An iterator into the %vector.
     * @param x Data to be inserted.
     * @return An iterator that points to the inserted data.
     * 
     * This function will insert a copy of the given value before
     * the specified location. Note that this kind of operation
     * could be expensive for a %vector and if it is frequently
     * used the user should consider using std::list.
     */
    iterator
    insert(iterator position, const value_type& x)
    {
      const size_type n = position - begin();
      if (this->M_impl.M_finish != this->M_impl.M_end_of_storage
        && position == end())
      {
        this->M_impl.construct(this->M_impl.M_finish, x);
        ++this->M_impl.M_finish;
      }
      else
        M_insert_aux(position, x);
      return iterator(this->M_impl.M_start + n);
    }

    /**
     * @brief Inserts given value into %vector before specified iterator.
     * @param position An iterator into the %vector.
     * @param x Data to be inserted.
     * @return An iterator that points to the inserted data.
     * 
     * This function will insert a specified number of copies of
     * the given data before the location specified by @a position.
     * 
     * Note that this kind of operation could be expensive for a
     * %vector and if it is frequently used the user should
     * consider using std::list.
     */
    void
    insert(iterator position, size_type n, const value_type& x)
    { M_fill_insert(position, n, x); }

    /**
     * @brief Inserts a range into the %vector.
     * @param position An iterator into the %vector.
     * @param first An input iterator.
     * @param last An input iterator.
     * 
     * This function will insert copies of the data in the range
     * [first,last) into the %vector before the location specified
     * by @a pos.
     * 
     * Note that this kind of operation could be expensive for a
     * %vector and if it is frequently used the user should
     * consider using std::list.
     */
    template <typename InputIterator>
    void
    insert(iterator position, InputIterator first,
      InputIterator last)
    {
      // Check whether it's an integral type. If so, it's not an iterator.
      typedef typename ft::is_integer<InputIterator>::type Integral;
      M_insert_dispatch(position, first, last, Integral());
    }

    /**
     * @brief Remove element at given position.
     * @param position Iterator pointing to element to be erased.
     * @return An iterator pointing to the next element (or end()).
     * 
     * This function will erase the element at the given position and thus
     * shorten the %vector by one.
     * 
     * Note This operation could be expensive and if it is
     * frequently used the user should consider using std::list.
     * The user is also cautioned that this function only erases
     * the element, and that if the element is itself a pointer,
     * the pointed-to memory is not touched in any way. Managing
     * The pointer is the user's responsibilty.
     */
    iterator
    erase(iterator position)
    {
      if (position + 1 != end())
        std::copy(position + 1, end(), position);
      --this->M_impl.M_finish;
      this->M_impl.destroy(this->M_impl.M_finish);
      return position;
    }

    /**
     * @brief Remove a range of elements.
     * @param first Iterator pointing to the first element to be erased.
     * @param last Iterator pointing to one past the last element to be
     *              erased.
     * @return An iterator pointing to the element pointed to by @a last
     *         prior to erasing (or end()).
     * 
     * This function will erase the elements in the range [first,last) and
     * shorten the %vector accordingly.
     * 
     * Note This operation could be expensive and if it is
     * frequently used the user should consider using std::list.
     * The user is also cautioned that this function only erases
     * the elements, and that if the elements themselves are
     * pointers, the pointed-to memory is not touched in any way.
     * Managing the pointer is the user's responsibilty
     */
    iterator
    erase(iterator first, iterator last)
    {
      if (last != end())
        std::copy(last, end(), first);
      M_erase_at_end(first.base() + (end() - last));
      return first;
    }

    /**
     * @brief Swaps data with another %vector.
     * @param x A %vector of the same element and allocator types.
     * 
     * This exchages the elements between two vectors in constant time.
     * (Three pointers, so it should be quite fast.)
     * Note that the global std::swap() function is specialized such that
     * std::swap(v1,v2) will feed to this function.
     */
    void
    swap(vector& x)
    {
      std::swap(this->M_impl.M_start, x.M_impl.M_start);
      std::swap(this->M_impl.M_finish, x.M_impl.M_finish);
      std::swap(this->M_impl.M_end_of_storage, x.M_impl.M_end_of_storage);
    }

    /**
     * Erases all the elements. Note that this function only erases the
     * elements, and that if the elements themselves are pointers, the
     * pointed-to memory is not touched in any way. Managing the pointer is
     * the user's responsibilty.
     */
    void
    clear()
    { M_erase_at_end(this->M_impl.M_start); }

    allocator_type
    get_allocator() const
    { return Base::get_allocator(); }
  protected:
    /**
     * @if maint
     * Memory expansion handler. Uses the member allocation function to
     * obtain @a n bytes of memory, and then copies [first,last) into it.
     * @endif
     */
    template <typename ForwardIterator>
    pointer
    M_allocate_and_copy(size_type n,
      ForwardIterator first, ForwardIterator last)
    {
      pointer result = this->M_allocate(n);
      try
      {
        ft::uninitialized_copy_a(first, last, result,
          M_get_Tp_allocator());
        return result;
      }
      catch(...)
      {
        M_deallocate(result, n);
        throw;
      }
    }
  
    // Internal constructor functions follow.

    // Called by the range constructor to implement
    template <typename Integer>
    void
    M_initialize_dispatch(Integer n, Integer value, __true_type)
    {
      this->M_impl.M_start = M_allocate(n);
      this->M_impl.M_end_of_storage = this->M_impl.M_start + n;
      ft::uninitialized_fill_n_a(this->M_impl.M_start, n, value,
        M_get_Tp_allocator());
      this->M_impl.M_finish = this->M_impl.M_end_of_storage;
    }

    // Called by the range constructor to implement
    template <typename InputIterator>
    void
    M_initialize_dispatch(InputIterator first, InputIterator last,
    __false_type)
    {
      typedef typename ft::iterator_traits<InputIterator>::
        iterator_category IterCategory;
      M_range_initialize(first, last, IterCategory());
    }

    // Called by the second initialize_dispatch above
    template <typename InputIterator>
    void
    M_range_initialize(InputIterator first,
      InputIterator last, std::input_iterator_tag)
    {
      for (; first != last; ++first)
        push_back(*first);
    }

    // Called by the second initialize_dispatch above
    template <typename ForwardIterator>
    void
    M_range_initialize(ForwardIterator first,
      ForwardIterator last, std::forward_iterator_tag)
    {
      // Todo remove
      const size_type n = std::distance(first, last);
      // const size_type n = ft::distance(first, last);
      this->M_impl.M_start = this->M_allocate(n);
      this->M_impl.M_end_of_storage = this->M_impl.M_start + n;
      this->M_impl.M_finish =
        ft::uninitialized_copy_a(first, last,
          this->M_impl.M_start,
          M_get_Tp_allocator());
    }

    // Internal assign functions follow. The *_aux functions do the actual
    // assignment work for the range versions.

    // Called by the range assign to implement [23.1.1]/9
    template <typename Integer>
    void
    M_assign_dispatch(Integer n, Integer val, __true_type)
    {
      M_fill_assign(static_cast<size_type>(n),
        static_cast<value_type>(val));
    }

    // Called by the range assign to implement [23.1.1]/9
    template <typename InputIterator>
    void
    M_assign_dispatch(InputIterator first, InputIterator last,
      __false_type)
    {
      typedef typename ft::iterator_traits<InputIterator>::
        iterator_category IterCategory;
      M_assign_aux(first, last, IterCategory());
    }

    // Called by second assign_dispatch above
    template <typename InputIterator>
    void
    M_assign_aux(InputIterator first, InputIterator last,
      std::input_iterator_tag)
    {
      pointer cur(this->M_impl.M_start);
      for (; first != last && cur != this->M_impl.M_finish;
        ++cur, ++first)
        *cur = *first;
      if (first == last)
        M_erase_at_end(cur);
      else
        insert(end(), first, last);
    }

    // Called by second assign_dispatch above
    template <typename ForwardIterator>
    void
    M_assign_aux(ForwardIterator first, ForwardIterator last,
      std::forward_iterator_tag)
    {
      // Todo remove
      const size_type len = std::distance(first, last);
      // const size_type n = ft::distance(first, last);

      if (len > capacity())
      {
        pointer tmp(M_allocate_and_copy(len, first, last));
        ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish,
          M_get_Tp_allocator());
        M_deallocate(this->M_impl.M_start,
          this->M_impl.M_end_of_storage
          - this->M_impl.M_start);
        this->M_impl.M_start = tmp;
        this->M_impl.M_finish = this->M_impl.M_start + len;
        this->M_impl.M_end_of_storage = this->M_impl.M_finish;
      }
      else if (size() >= len)
        M_erase_at_end(std::copy(first, last, this->M_impl.M_start));
      else
      {
        ForwardIterator mid = first;
        std::advance(mid, size());
        std::copy(first, mid, this->M_impl.M_start);
        this->M_impl.M_finish =
          ft::uninitialized_copy_a(mid, last,
            this->M_impl.M_finish,
            M_get_Tp_allocator());
      }
    }

    // Called by assign(n,t), and the range assign when it turns out
    // to be the same thing.
    void
    M_fill_assign(size_type n, const value_type& val)
    {
      if (n > capacity())
      {
        vector tmp(n, val, M_get_Tp_allocator());
        tmp.swap(*this);
      }
      else if (n > size())
      {
        // Todo remove
        // ft::fill(begin(), end(), val);
        std::fill(begin(), end(), val);
        ft::uninitialized_fill_n_a(this->M_impl.M_finish,
          n - size(), val,
          M_get_Tp_allocator());
        this->M_impl.M_finish += n - size();
      }
      else
      {
        M_erase_at_end(std::fill_n(this->M_impl.M_start, n, val));
      }
    }
    

    // Called by insert(p,x)
    void
    M_insert_aux(iterator position, const value_type& x)
    {
      if (this->M_impl.M_finish != this->M_impl.M_end_of_storage)
      {
        this->M_impl.construct(this->M_impl.M_finish,
          *(this->M_impl.M_finish - 1));
        ++this->M_impl.M_finish;
        Tp x_copy = x;
        std::copy_backward(position.base(),
          this->M_impl.M_finish - 2,
          this->M_impl.M_finish - 1);
        *position = x_copy;
      }
      else
      {
        const size_type old_size = size();
        if (old_size == this->max_size())
          throw std::length_error("vector::M_range_insert");
        
        // When sizeof(value_type) == 1 and old_size > size_type(-1)/2
        // len overflows: if we don't notice and M_allocate doesn't
        // throw we crash badly later.
        size_type len = old_size != 0 ? 2 * old_size : 1;
        if (len < old_size)
          len = this->max_size();
        
        pointer new_start(this->M_allocate(len));
        pointer new_finish(new_start);
        try
        {
          new_finish =
            ft::uninitialized_copy_a(this->M_impl.M_start,
              position.base(), new_start,
              M_get_Tp_allocator());
          this->M_impl.construct(new_finish, x);
          ++new_finish;
          new_finish =
            ft::uninitialized_copy_a(position.base(),
              this->M_impl.M_finish, new_finish,
              M_get_Tp_allocator());
        }
        catch(...)
        {
          ft::Destroy(new_start, new_finish, M_get_Tp_allocator());
          M_deallocate(new_start, len);
          throw;
        }
        ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish,
          M_get_Tp_allocator());
        M_deallocate(this->M_impl.M_start,
          this->M_impl.M_end_of_storage
          - this->M_impl.M_start);
        this->M_impl.M_start = new_start;
        this->M_impl.M_finish = new_finish;
        this->M_impl.M_end_of_storage = new_start + len;
      }
    }
    
    void
    M_fill_insert(iterator position, size_type n, const value_type& x)
    {
      if (n != 0)
      {
        if (size_type(this->M_impl.M_end_of_storage
          - this->M_impl.M_finish) >= n)
        {
          value_type x_copy = x;
          const size_type elems_after = end() - position;
          pointer old_finish(this->M_impl.M_finish);
          if (elems_after > n)
          {
            ft::uninitialized_copy_a(this->M_impl.M_finish - n,
              this->M_impl.M_finish,
              this->M_impl.M_finish,
              M_get_Tp_allocator());
            this->M_impl.M_finish += n;
            std::copy_backward(position.base(), old_finish - n,
              old_finish);
            std::fill(position.base(), position.base() + n,
              x_copy);
          }
          else
          {
            ft::uninitialized_fill_n_a(this->M_impl.M_finish,
              n - elems_after,
              x_copy,
              M_get_Tp_allocator());
            this->M_impl.M_finish += n - elems_after;
            ft::uninitialized_copy_a(position.base(), old_finish,
              this->M_impl.M_finish,
              M_get_Tp_allocator());
            this->M_impl.M_finish += elems_after;
            std::fill(position.base(), old_finish, x_copy);
          }
        }
        else
        {
          const size_type old_size = capacity();
          if (this->max_size() - old_size < n)
            throw std::length_error("vector::M_fill_insert");
          
          // See M_insert_aux above.
          // size_type len = old_size + std::max(old_size, n);
          size_type len = std::max(size() + n, capacity() * 2);
          if (len < old_size)
            len = this->max_size();
          pointer new_start(this->M_allocate(len));
          pointer new_finish(new_start);
          try
          {
            new_finish = 
              ft::uninitialized_copy_a(this->M_impl.M_start,
              position.base(),
              new_start,
              M_get_Tp_allocator());
            ft::uninitialized_fill_n_a(new_finish, n, x,
              M_get_Tp_allocator());
            new_finish += n;
            new_finish =
              ft::uninitialized_copy_a(position.base(),
                this->M_impl.M_finish,
                new_finish,
                M_get_Tp_allocator());
          }
          catch(...)
          {
            ft::Destroy(new_start, new_finish,
              M_get_Tp_allocator());
            M_deallocate(new_start, len);
            throw;
          }
          ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish,
            M_get_Tp_allocator());
          M_deallocate(this->M_impl.M_start,
            this->M_impl.M_end_of_storage
            - this->M_impl.M_start);
          this->M_impl.M_start = new_start;
          this->M_impl.M_finish = new_finish;
          this->M_impl.M_end_of_storage = new_start + len;
        }
      }
    }
    // Internal erase functions follow.

    // Internal insert functions follow.

    // Called by the range insert to implement [23.1.1]/9
    template <typename Integer>
    void
    M_insert_dispatch(iterator pos, Integer n, Integer val,
      __true_type)
    {
      M_fill_insert(pos, static_cast<size_type>(n),
        static_cast<value_type>(val));
    }

    // Called by the range insert to implement [23.1.1]/9
    template <typename InputIterator>
    void
    M_insert_dispatch(iterator pos, InputIterator first,
      InputIterator last, __false_type)
    {
      typedef typename ft::iterator_traits<InputIterator>::
        iterator_category IterCategory;
      M_range_insert(pos, first, last, IterCategory());
    }

    // Called by the second insert_dispatch above
    template <typename InputIterator>
    void
    M_range_insert(iterator pos, InputIterator first,
      InputIterator last, std::input_iterator_tag)
    {
      for (; first != last; ++first)
      {
        pos = insert(pos, *first);
        ++pos;
      }
    }
    // Called by the second insert_dispatch above
    template <typename ForwardIterator>
    void
    M_range_insert(iterator pos, ForwardIterator first,
      ForwardIterator last, std::forward_iterator_tag)
    {
      if (first != last)
      {
        const size_type n = std::distance(first, last);
        if (size_type(this->M_impl.M_end_of_storage
          - this->M_impl.M_finish) >= n)
        {
          const size_type elems_after = end() - pos;
          pointer old_finish(this->M_impl.M_finish);
          if (elems_after > n)
          {
            ft::uninitialized_copy_a(this->M_impl.M_finish - n,
              this->M_impl.M_finish,
              this->M_impl.M_finish,
              M_get_Tp_allocator());
            this->M_impl.M_finish += n;
            std::copy_backward(pos.base(), old_finish - n,
              old_finish);
            std::copy(first, last, pos);
          }
          else
          {
            ForwardIterator mid = first;
            std::advance(mid, elems_after);
            ft::uninitialized_copy_a(mid, last,
              this->M_impl.M_finish,
              M_get_Tp_allocator());
            this->M_impl.M_finish += n - elems_after;
            ft::uninitialized_copy_a(pos.base(),
              old_finish,
              this->M_impl.M_finish,
              M_get_Tp_allocator());
            this->M_impl.M_finish += elems_after;
            std::copy(first, mid, pos);
          }
        }
        else
        {
          const size_type old_size = size();
          if (this->max_size() - old_size < n)
            throw std::length_error("vector::M_range_insert");
          // See M_insert_aux above.
          size_type len = old_size + std::max(old_size, n);
          if (len < old_size)
            len = this->max_size();
          
          pointer new_start(this->M_allocate(len));
          pointer new_finish(new_start);

          try
          {
            new_finish =
              ft::uninitialized_copy_a(this->M_impl.M_start,
                pos.base(),
                new_start,
                M_get_Tp_allocator());
            new_finish =
              ft::uninitialized_copy_a(first, last, new_finish,
                M_get_Tp_allocator());
            new_finish =
              ft::uninitialized_copy_a(pos.base(),
                this->M_impl.M_finish,
                new_finish,
                M_get_Tp_allocator());
          }
          catch(...)
          {
            ft::Destroy(new_start, new_finish,
              M_get_Tp_allocator());
              M_deallocate(new_start, len);
              throw;
          }
          ft::Destroy(this->M_impl.M_start, this->M_impl.M_finish,
            M_get_Tp_allocator());
          M_deallocate(this->M_impl.M_start,
            this->M_impl.M_end_of_storage
            - this->M_impl.M_start);
          this->M_impl.M_start = new_start;
          this->M_impl.M_finish = new_finish;
          this->M_impl.M_end_of_storage = new_start + len;
        }
      }
    }

    // Called by erase(q1, q2), clear(), resize(), M_fill_assign,
    // M_assign_aux.
    void
    M_erase_at_end(pointer pos)
    {
      ft::Destroy(pos, this->M_impl.M_finish, M_get_Tp_allocator());
      this->M_impl.M_finish = pos;
    }
};

/**
 * @brief Vector equality comparison.
 * @param x A %vector
 * @param y A %vector of the same type as @a x.
 * @return True if the size and elements of the vectors are equal.
 * 
 * This is an equivalence relation. It is linear in the size of the
 * vectors. Vectors are considered equivalent if their sizes are equal,
 * and if corresponding elements compare equal.
 */
template <typename Tp, typename Alloc>
bool
operator==(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
{ return (x.size() == y.size()
    && ft::equal(x.begin(), x.end(), y.begin())); }

/**
 * @brief Vector ordering relation.
 * @param x A %vector.
 * @param y A %vector of the same type as @a x.
 * @return True if @a x is lexicographically less than @a y.
 * 
 * This is a total ordering ralation. It is linear in the size of the
 * vectors. The elements must be comparable with @c <.
 * 
 * See ft::lexicographical_compare() for how the determination is made.
 */
template <typename Tp, typename Alloc>
bool
operator<(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
{ return ft::lexicographical_compare(x.begin(), x.end(),
    y.begin(), y.end()); }

/// Based on operator==
template <typename Tp, typename Alloc>
bool
operator!=(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
{ return !(x == y); }

/// Based on operator<
template <typename Tp, typename Alloc>
bool
operator>(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
{ return y < x; }

/// Based on operator<
template <typename Tp, typename Alloc>
bool
operator<=(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
{ return !(y < x); }

/// Based on operator<
template <typename Tp, typename Alloc>
bool
operator>=(const vector<Tp, Alloc>& x, const vector<Tp, Alloc>& y)
{ return !(x < y); }

/// See std::vector::swap().
template <typename Tp, typename Alloc>
void
swap(vector<Tp, Alloc>& x, vector<Tp, Alloc>& y)
{ x.swap(y); }

} // ft
#endif // STL_VECTOR_H_