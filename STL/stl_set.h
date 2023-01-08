// Set implementation -*- C++ -*-

/** @file stl_set.h
 *  This is an internal header file, included by other library headers.
 *  You should not attempt to use it directly.
 */


#include <memory>
#include <functional>

#include "stl_tree.h"
#include "stl_function.h"

#ifndef STL_SET_H_
#define STL_SET_H_

namespace ft {
/**
 *  @brief A standard container made up of unique keys, which can be
 *  retrieved in logarithmic time.
 *
 *  @ingroup Containers
 *  @ingroup Assoc_containers
 *
 *  Meets the requirements of a <a href="tables.html#65">container</a>, a
 *  <a href="tables.html#66">reversible container</a>, and an
 *  <a href="tables.html#69">associative container</a> (using unique keys).
 *
 *  Sets support bidirectional iterators.
 *
 *  @param  Key  Type of key objects.
 *  @param  Compare  Comparison function object type, defaults to less<Key>.
 *  @param  Alloc  Allocator type, defaults to allocator<Key>.
 *
 *  @if maint
 *  The private tree data is declared exactly the same way for set and
 *  multiset; the distinction is made entirely in how the tree functions are
 *  called (*_unique versus *_equal, same as the standard).
 *  @endif
*/
template <class Key, class Compare = std::less<Key>, 
          class Alloc = std::allocator<Key> >
class set
{
  typedef typename Alloc::value_type            Alloc_value_type;

public:
  // typedefs:
  //@{
  /// Public typedefs.
  typedef Key     key_type;
  typedef Key     value_type;
  typedef Compare key_compare;
  typedef Compare value_compare;
  typedef Alloc   allocator_type;
  //@}

private:
  typedef typename Alloc::template rebind<Key>::other   Key_alloc_type;

  typedef Rb_tree<key_type, value_type, Identity<value_type>,
          key_compare, Key_alloc_type>                  Rep_type;
  Rep_type M_t; // red-black tree representing set

public:
  //@{
  ///  Iterator-related typedefs.
  typedef typename Key_alloc_type::pointer              pointer;
  typedef typename Key_alloc_type::const_pointer        const_pointer;
  typedef typename Key_alloc_type::reference            reference;
  typedef typename Key_alloc_type::const_reference      const_reference;
  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // DR 103. set::iterator is required to be modifiable,
  // but this allows modification of keys.
  typedef typename Rep_type::const_iterator             iterator;
  typedef typename Rep_type::const_iterator             const_iterator;
  typedef typename Rep_type::const_reverse_iterator     reverse_iterator;
  typedef typename Rep_type::const_reverse_iterator     const_reverse_iterator;
  typedef typename Rep_type::size_type                  size_type;
  typedef typename Rep_type::difference_type            difference_type;
  //@}

  // allocation/deallocation
  ///  Default constructor creates no elements.
  set()
  : M_t(Compare(), allocator_type()) {}

  /**
   *  @brief  Default constructor creates no elements.
   *
   *  @param  comp  Comparator to use.
   *  @param  a  Allocator to use.
   */
  explicit
  set(const Compare& comp, const allocator_type& a = allocator_type())
  : M_t(comp, a) {}

  /**
   *  @brief  Builds a %set from a range.
   *  @param  first  An input iterator.
   *  @param  last  An input iterator.
   *
   *  Create a %set consisting of copies of the elements from [first,last).
   *  This is linear in N if the range is already sorted, and NlogN
   *  otherwise (where N is distance(first,last)).
   */
  template <class InputIterator>
  set(InputIterator first, InputIterator last)
  : M_t(Compare(), allocator_type())
  { M_t.M_insert_unique(first, last); }

  /**
   *  @brief  Builds a %set from a range.
   *  @param  first  An input iterator.
   *  @param  last  An input iterator.
   *  @param  comp  A comparison functor.
   *  @param  a  An allocator object.
   *
   *  Create a %set consisting of copies of the elements from [first,last).
   *  This is linear in N if the range is already sorted, and NlogN
   *  otherwise (where N is distance(first,last)).
   */
  template <class InputIterator>
  set(InputIterator first, InputIterator last, const Compare& comp,
      const allocator_type& a = allocator_type())
  : M_t(comp, a)
  { M_t.M_insert_unique(first, last); }

  /**
   *  @brief  Set copy constructor.
   *  @param  x  A %set of identical element and allocator types.
   *
   *  The newly-created %set uses a copy of the allocation object used
   *  by @a x.
   */
  set(const set<Key, Compare, Alloc>& x)
  : M_t(x.M_t) { }

  /**
   *  @brief  Set assignment operator.
   *  @param  x  A %set of identical element and allocator types.
   *
   *  All the elements of @a x are copied, but unlike the copy constructor,
   *  the allocator object is not copied.
   */
  set<Key, Compare, Alloc>&
  operator=(const set<Key, Compare, Alloc>& x)
  {
    M_t = x.M_t;
    return *this;
  }

  // accessors:

  ///  Returns the comparison object with which the %set was constructed.
  key_compare
  key_comp() const
  { return M_t.key_comp(); }
  ///  Returns the comparison object with which the %set was constructed.
  value_compare
  value_comp() const
  { return M_t.key_comp(); }
  ///  Returns the allocator object with which the %set was constructed.
  allocator_type
  get_allocator() const
  { return M_t.get_allocator(); }

  /**
   *  Returns a read/write iterator that points to the first element in the
   *  %set.  Iteration is done in ascending order according to the keys.
   */
  iterator
  begin() const
  { return M_t.begin(); }

  /**
   *  Returns a read/write iterator that points one past the last element in
   *  the %set.  Iteration is done in ascending order according to the keys.
   */
  iterator
  end() const
  { return M_t.end(); }

  /**
   *  Returns a read/write reverse iterator that points to the last element
   *  in the %set.  Iteration is done in descending order according to the
   *  keys.
   */
  reverse_iterator
  rbegin() const
  { return M_t.rbegin(); }

  /**
   *  Returns a read-only (constant) reverse iterator that points to the
   *  last pair in the %map.  Iteration is done in descending order
   *  according to the keys.
   */
  reverse_iterator
  rend() const
  { return M_t.rend(); }

  ///  Returns true if the %set is empty.
  bool
  empty() const
  { return M_t.empty(); }

  ///  Returns the size of the %set.
  size_type
  size() const
  { return M_t.size(); }
  ///  Returns the maximum size of the %set.
  size_type
  max_size() const
  { return M_t.max_size(); }

  /**
   *  @brief  Swaps data with another %set.
   *  @param  x  A %set of the same element and allocator types.
   *
   *  This exchanges the elements between two sets in constant time.
   *  (It is only swapping a pointer, an integer, and an instance of
   *  the @c Compare type (which itself is often stateless and empty), so it
   *  should be quite fast.)
   *  Note that the global std::swap() function is specialized such that
   *  std::swap(s1,s2) will feed to this function.
   */
  void
  swap(set<Key, Compare, Alloc>& x)
  { M_t.swap(x.M_t); }

  // insert/erase
  /**
   *  @brief Attempts to insert an element into the %set.
   *  @param  x  Element to be inserted.
   *  @return  A pair, of which the first element is an iterator that points
   *           to the possibly inserted element, and the second is a bool
   *           that is true if the element was actually inserted.
   *
   *  This function attempts to insert an element into the %set.  A %set
   *  relies on unique keys and thus an element is only inserted if it is
   *  not already present in the %set.
   *
   *  Insertion requires logarithmic time.
   */
  ft::pair<iterator, bool>
  insert(const value_type& x)
  {
    ft::pair<typename Rep_type::iterator, bool> p = M_t.M_insert_unique(x);
    return ft::pair<iterator, bool>(p.first, p.second);
  }

  /**
   *  @brief Attempts to insert an element into the %set.
   *  @param  position  An iterator that serves as a hint as to where the
   *                    element should be inserted.
   *  @param  x  Element to be inserted.
   *  @return  An iterator that points to the element with key of @a x (may
   *           or may not be the element passed in).
   *
   *  This function is not concerned about whether the insertion took place,
   *  and thus does not return a boolean like the single-argument insert()
   *  does.  Note that the first parameter is only a hint and can
   *  potentially improve the performance of the insertion process.  A bad
   *  hint would cause no gains in efficiency.
   *
   *  See http://gcc.gnu.org/onlinedocs/libstdc++/23_containers/howto.html#4
   *  for more on "hinting".
   *
   *  Insertion requires logarithmic time (if the hint is not taken).
   */
  iterator
  insert(iterator position, const value_type& x)
  { return M_t.M_insert_unique(position, x); }

  /**
   *  @brief A template function that attemps to insert a range of elements.
   *  @param  first  Iterator pointing to the start of the range to be
   *                 inserted.
   *  @param  last  Iterator pointing to the end of the range.
   *
   *  Complexity similar to that of the range constructor.
   */
  template <class InputIterator>
  void
  insert(InputIterator first, InputIterator last)
  { M_t.M_insert_unique(first, last); }

  /**
   *  @brief Erases an element from a %set.
   *  @param  position  An iterator pointing to the element to be erased.
   *
   *  This function erases an element, pointed to by the given iterator,
   *  from a %set.  Note that this function only erases the element, and
   *  that if the element is itself a pointer, the pointed-to memory is not
   *  touched in any way.  Managing the pointer is the user's responsibilty.
   */
  void
  erase(iterator position)
  { M_t.erase(position); }

  /**
   *  @brief Erases elements according to the provided key.
   *  @param  x  Key of element to be erased.
   *  @return  The number of elements erased.
   *
   *  This function erases all the elements located by the given key from
   *  a %set.
   *  Note that this function only erases the element, and that if
   *  the element is itself a pointer, the pointed-to memory is not touched
   *  in any way.  Managing the pointer is the user's responsibilty.
   */
  size_type
  erase(const key_type& x)
  { return M_t.erase(x); }

  /**
   *  @brief Erases a [first,last) range of elements from a %set.
   *  @param  first  Iterator pointing to the start of the range to be
   *                 erased.
   *  @param  last  Iterator pointing to the end of the range to be erased.
   *
   *  This function erases a sequence of elements from a %set.
   *  Note that this function only erases the element, and that if
   *  the element is itself a pointer, the pointed-to memory is not touched
   *  in any way.  Managing the pointer is the user's responsibilty.
   */
  void
  erase(iterator first, iterator last)
  { M_t.erase(first, last); }

  /**
   *  Erases all elements in a %set.  Note that this function only erases
   *  the elements, and that if the elements themselves are pointers, the
   *  pointed-to memory is not touched in any way.  Managing the pointer is
   *  the user's responsibilty.
   */
  void
  clear()
  { M_t.clear(); }

  // set operations:

  /**
   *  @brief  Finds the number of elements.
   *  @param  x  Element to located.
   *  @return  Number of elements with specified key.
   *
   *  This function only makes sense for multisets; for set the result will
   *  either be 0 (not present) or 1 (present).
   */
  size_type
  count(const key_type& x) const
  { return M_t.find(x) == M_t.end() ? 0 : 1; }

  // _GLIBCXX_RESOLVE_LIB_DEFECTS
  // 214.  set::find() missing const overload
  //@{
  /**
   *  @brief Tries to locate an element in a %set.
   *  @param  x  Element to be located.
   *  @return  Iterator pointing to sought-after element, or end() if not
   *           found.
   *
   *  This function takes a key and tries to locate the element with which
   *  the key matches.  If successful the function returns an iterator
   *  pointing to the sought after element.  If unsuccessful it returns the
   *  past-the-end ( @c end() ) iterator.
   */
  iterator
  find(const key_type& x)
  { return M_t.find(x); }

  const_iterator
  find(const key_type& x) const
  { return M_t.find(x); }
  //@}

  //@{
  /**
   *  @brief Finds the beginning of a subsequence matching given key.
   *  @param  x  Key to be located.
   *  @return  Iterator pointing to first element equal to or greater
   *           than key, or end().
   *
   *  This function returns the first element of a subsequence of elements
   *  that matches the given key.  If unsuccessful it returns an iterator
   *  pointing to the first element that has a greater value than given key
   *  or end() if no such element exists.
   */
  iterator
  lower_bound(const key_type& x)
  { return M_t.lower_bound(x); }

  const_iterator
  lower_bound(const key_type& x) const
  { return M_t.lower_bound(x); }
  //@}

  //@{
  /**
   *  @brief Finds the end of a subsequence matching given key.
   *  @param  x  Key to be located.
   *  @return Iterator pointing to the first element
   *          greater than key, or end().
   */
  iterator
  upper_bound(const key_type& x)
  { return M_t.upper_bound(x); }

  const_iterator
  upper_bound(const key_type& x) const
  { return M_t.upper_bound(x); }
  //@}

  //@{
  /**
   *  @brief Finds a subsequence matching given key.
   *  @param  x  Key to be located.
   *  @return  Pair of iterators that possibly points to the subsequence
   *           matching given key.
   *
   *  This function is equivalent to
   *  @code
   *    std::make_pair(c.lower_bound(val),
   *                   c.upper_bound(val))
   *  @endcode
   *  (but is faster than making the calls separately).
   *
   *  This function probably only makes sense for multisets.
   */
  ft::pair<iterator, iterator>
  equal_range(const key_type& x)
  { return M_t.equal_range(x); }

  ft::pair<const_iterator, const_iterator>
  equal_range(const key_type& x) const
  { return M_t.equal_range(x); }
  //@}

  template <class K1, class C1, class A1>
  friend bool
  operator== (const set<K1, C1, A1>&, const set<K1, C1, A1>&);

  template <class K1, class C1, class A1>
  friend bool
  operator< (const set<K1, C1, A1>&, const set<K1, C1, A1>&);

};

/**
 *  @brief  Set equality comparison.
 *  @param  x  A %set.
 *  @param  y  A %set of the same type as @a x.
 *  @return  True iff the size and elements of the sets are equal.
 *
 *  This is an equivalence relation.  It is linear in the size of the sets.
 *  Sets are considered equivalent if their sizes are equal, and if
 *  corresponding elements compare equal.
*/
template <class Key, class Compare, class Alloc>
bool
operator==(const set<Key, Compare, Alloc>& x,
          const set<Key, Compare, Alloc>& y)
{ return x.M_t == y.M_t; }

/**
 *  @brief  Set ordering relation.
 *  @param  x  A %set.
 *  @param  y  A %set of the same type as @a x.
 *  @return  True iff @a x is lexicographically less than @a y.
 *
 *  This is a total ordering relation.  It is linear in the size of the
 *  maps.  The elements must be comparable with @c <.
 *
 *  See std::lexicographical_compare() for how the determination is made.
*/
template <class Key, class Compare, class Alloc>
bool
operator<(const set<Key, Compare, Alloc>& x,
          const set<Key, Compare, Alloc>& y)
{ return x.M_t < y.M_t; }

///  Returns !(x == y).
template <class Key, class Compare, class Alloc>
bool
operator!=(const set<Key, Compare, Alloc>& x,
          const set<Key, Compare, Alloc>& y)
{ return !(x == y); }

///  Returns y < x.
template <class Key, class Compare, class Alloc>
bool
operator>(const set<Key, Compare, Alloc>& x,
          const set<Key, Compare, Alloc>& y)
{ return y < x; }

///  Returns !(y < x)
template <class Key, class Compare, class Alloc>
bool
operator<=(const set<Key, Compare, Alloc>& x,
          const set<Key, Compare, Alloc>& y)
{ return !(y < x); }

///  Returns !(x < y)
template<class Key, class Compare, class Alloc>
bool
operator>=(const set<Key, Compare, Alloc>& x,
          const set<Key, Compare, Alloc>& y)
{ return !(x < y); }

/// See std::set::swap().
template <class Key, class Compare, class Alloc>
void
swap(set<Key, Compare, Alloc>& x, set<Key, Compare, Alloc>& y)
{ x.swap(y); }

} // ft

#endif // STL_SET_H_