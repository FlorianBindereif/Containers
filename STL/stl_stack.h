// Stack implementation -*- C++ -*-

/** @file stl_stack.h
 * This is an internal header file, included by other library headers.
 * You should not attempt to use it directly.
 */


#ifndef STL_STACK_H_
#define STL_STACK_H_

#include "stl_vector.h"

namespace ft {

/**
 * @brief A standard container giving FILO behavior.
 * 
 * @ingroup Containers
 * @ingroup Sequences
 * 
 * Meets many of the requirements of a
 * container,
 * but does not define anything to do with iterators. Very few of the
 * other standard container interfaces are defined.
 * 
 * This is not a true container, but an @e adaptor. It holds
 * another container, and provides a wrapper interface to that
 * container. The wrapper is what enforces strict
 * first-in-last-out %stack behavior.
 * 
 * The second template parameter defines the type of the underlying
 * sequence/container. It defaults to std::deque, but it can be
 * any type that supports @c back, @c push_back, and @c pop_front,
 * such as std::list, std::vector, or an appropriate user-defined
 * type.
 * 
 * Members not found in "normal" containers are @c container_type,
 * which is a typedef for the second Sequence parameter, and @c
 * push, @c pop, and @c top, which are standard %stack/FILO
 * operations.
 */
template <typename Tp, typename Sequence = ft::vector<Tp> >
class stack
{
  typedef typename Sequence::value_type Sequence_value_type;

  template <typename Tp1, typename Seq1>
  friend bool
  operator==(const stack<Tp1, Seq1>&, const stack<Tp1, Seq1>&);

  template <typename Tp1, typename Seq1>
  friend bool
  operator<(const stack<Tp1, Seq1>&, const stack<Tp1, Seq1>&);

public:
  typedef typename Sequence::value_type       value_type;
  typedef typename Sequence::size_type        size_type;
  typedef          Sequence                   container_type;

protected:
  /**
   * 'c' is the underlying container. Maintainers wondering why
   * this isn't uglified as per style guidelines should note that
   * this name is specified in the standard, [23.2.3.1]. (Why?
   * Presumably for the same reason that it's protected instead
   * of private: to allow derivation. But none of the other
   * containers allow for derivation. Odd.)
   */
  Sequence c;
  typedef typename Sequence::reference        reference;
  typedef typename Sequence::const_reference  const_reference;

public:
  // XXX removed old def ctor, added def arg to this one to match 14882
  /**
   * @brief Default constructor creates no elements.
   */
  explicit
  stack(const Sequence& c = Sequence())
  : c(c) {}

  /**
   * Returns true if the  the %stack is empty.
   */
  bool
  empty() const
  { return c.empty(); }

  /** Returns the number of elements in the %stack. */
  size_type
  size() const
  { return c.size(); }

  /**
   * Returns a read/write reference to the data at the first
   * element of the %stack.
   */
  reference
  top()
  {
    return c.back();
  }
  /**
   * Returns a read-only (constant) reference to the data at the first
   * element of the %stack.
   */
  reference
  top() const
  {
    return c.back();
  }

  /**
   * @brief Add data to the top of the %stack.
   * @param x Data to be added.
   * 
   * This is a typical %stack operation. The function creates an
   * element at the top of the %stack and assigns the given data
   * to it. The time complexity of the operation depends on the
   * underlying sequence.
   */
  void
  push(const value_type& x)
  { c.push_back(x); }

  /**
   * @brief Removes first element.
   * 
   * This is a typical %stack operation. It shrinks the %stack
   * by one. The time complexity of the operation depends on the
   * underlying sequence.
   * 
   * Note that no data is returned, and if the first element's
   * data is neede, it should be retrieved before pop() is
   * called.
   */
  void
  pop()
  {
    c.pop_back();
  }
};

/**
 * @brief Stack equality comparison.
 * @param x A %stack
 * @param y A %stack of the same type as @a x.
 * @return True if the size and elements of the stacks are equal.
 * 
 * This is an equivalence relation. Complexity and semantics
 * depend on the underlying sequence type, but the expected rules
 * are: thie relation is linear in the size of the sequences, and
 * stacks are considered equivalent if their sequences compare
 * equal.
 */
template <typename Tp, typename Seq>
bool
operator==(const stack<Tp, Seq>& x, const stack<Tp, Seq>& y)
{ return x.c == y.c; }

/**
 *  @brief  Stack ordering relation.
 *  @param  x  A %stack.
 *  @param  y  A %stack of the same type as @a x.
 *  @return  True iff @a x is lexicographically less than @a y.
 *
 *  This is an total ordering relation.  Complexity and semantics
 *  depend on the underlying sequence type, but the expected rules
 *  are: this relation is linear in the size of the sequences, the
 *  elements must be comparable with @c <, and
 *  std::lexicographical_compare() is usually used to make the
 *  determination.
*/
template <typename Tp, typename Seq>
bool
operator<(const stack<Tp, Seq>& x, const stack<Tp, Seq>& y)
{ return x.c < y.c; }

/// Based on operator==
template <typename Tp, typename Seq>
bool
operator!=(const stack<Tp, Seq>& x, const stack<Tp, Seq>& y)
{ return !(x == y); }

/// Based on operator<
template <typename Tp, typename Seq>
bool
operator>(const stack<Tp, Seq>& x, const stack<Tp, Seq>& y)
{ return y < x; }

/// Based on operator<
template <typename Tp, typename Seq>
bool
operator<=(const stack<Tp, Seq>& x, const stack<Tp, Seq>& y)
{ return !(y < x); }

/// Based on operator<
template <typename Tp, typename Seq>
bool
operator>=(const stack<Tp, Seq>& x, const stack<Tp, Seq>& y)
{ return !(x < y); }

} // ft
#endif // STL_STACK_H_