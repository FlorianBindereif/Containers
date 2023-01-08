#ifndef STL_ITERATOR_BASE_TYPES_H_
#define STL_ITERATOR_BASE_TYPES_H_

/** @file stl_iterator_base_types.h
 * This is an internal header file, included by other library headers.
 * Do not attempt to use it directly.
 * 
 * This file contains all of the general iterator-related utility types,
 * such as iterator_traits and struct iterator.
 */

#include <cstddef>

namespace ft {

/** @defgroup iterators Iterators
 *  Abstractions for uniform iterating through various underlying types.
 */
///@{

  /**
   * @defgroup iterator_tags Iterator Tags
   * These are empty types, used to distinguish different iterators. The
   * distinction is not made by what they contain, but simply by what they
   * are. Different underlying algorithms can then be used based on the
   * different operations supported by different iterator types.
   */
///@{
// /// Marking input iterators.
// struct input_iterator_tag { };

// /// Marking output iterators.
// struct output_iterator_tag { };

// /// Forward iterators support a superset of input iterator operations.
// struct forward_iterator_tag : public input_iterator_tag { };

// /// Bidirectional iterators support a superset of forward iterator
// /// operations.
// struct bidirectional_iterator_tag : public forward_iterator_tag { };

// /// Random-access iterators support a superset of bidirectional
// /// iterator operations.
// struct random_access_iterator_tag : public bidirectional_iterator_tag { };
// ///@}

/**
 * @brief Common %iterator class.
 * 
 * This class does nothing but define nested typedefs. %Iterator classes
 * can inherit from this class to save some work. The typedefs are then
 * used in specializations and overloading.
 * 
 * In paricular, there are no default implementations of requirements
 * such as @c operator++ and the like.
 */

template<typename Category, typename Tp, typename Distance = std::ptrdiff_t,
          typename Pointer = Tp*, typename Reference = Tp&>
struct iterator
{
  /// One of the @link iterator_tags tag types@endlink.
  typedef Category  iterator_category;
  /// The type "pointed to" by the iterator.
  typedef Tp        value_type;
  /// Distance between iterators is represented as this type.
  typedef Distance  difference_type;
  /// This type represents a pointer-to-value_type.
  typedef Pointer   pointer;
  /// This type represents a reference-to-value_type.
  typedef Reference reference;
};

template <typename Iterator>
struct iterator_traits
{
  typedef typename Iterator::iterator_category  iterator_category;
  typedef typename Iterator::value_type         value_type;
  typedef typename Iterator::difference_type    difference_type;
  typedef typename Iterator::pointer            pointer;
  typedef typename Iterator::reference          reference;
};

/// Partial specialization for pointer types.
template <typename Tp>
struct iterator_traits<Tp*>
{
  typedef std::random_access_iterator_tag  iterator_category;
  typedef Tp                               value_type;
  typedef ptrdiff_t                        difference_type;
  typedef Tp*                              pointer;
  typedef Tp&                              reference;
};

/// Partial specialization for const pointer types.
template <typename Tp>
struct iterator_traits<const Tp*>
{
  typedef std::random_access_iterator_tag   iterator_category;
  typedef Tp                                value_type;
  typedef ptrdiff_t                         difference_type;
  typedef const Tp*                         pointer;
  typedef const Tp&                         reference;
};

/**
 * This function is not a part of the C++ standard but is syntactic
 * sugar for internal library use only.
 */
template <typename Iter>
typename std::iterator_traits<Iter>::iterator_category
iterator_category(const Iter&)
{ return typename ft::iterator_traits<Iter>::iterator_category(); }

} // ft
#endif // STL_ITERATOR_BASE_TYPES_H_