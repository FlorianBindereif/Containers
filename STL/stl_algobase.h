#ifndef STL_ALGOBASE_H_
#define STL_ALGOBASE_H_

#include <cstring>

namespace ft {

/**
 * @brief Tests a range for element-wise equality.
 * @param first An input iterator.
 * @param last1 An input iterator.
 * @param first2 An input iterator.
 * @return A boolean true or false.
 * 
 * This compares the elements of two ranges using @c == and returns true or
 * false depending on whether all of the corresponding elements of the
 * ranges are eqaul.
 */
template <typename InputIterator1, typename InputIterator2>
bool
equal(InputIterator1 first1, InputIterator1 last1,
InputIterator2 first2)
{
  for (; first1 != last1; ++first1, ++first2 )
    if (!(*first1 == *first2))
      return false;
    return true;
}

/**
 * @brief Tests a range for element-wise equality.
 * @param first An input iterator.
 * @param last1 An input iterator.
 * @param first2 An input iterator.
 * @param binary_pred A binary predicate @link s20_3_1_base functor@endlink.
 * @return A boolean true or false.
 * 
 * This compares the elements of two ranges using the binary_pred
 * parameter, and returns true or
 * false depending on whether all of the corresponding elements of the
 * ranges are equal.
 */
template <typename InputIterator1, typename InputIterator2,
  typename BinaryPredicate>
bool
equal(InputIterator1 first1, InputIterator1 last1,
InputIterator2 first2,
BinaryPredicate binary_pred)
{
  for (; first1 != last1; ++first1, ++first2 )
    if (!binary_pred(*first1, *first2))
      return false;
    return true;
}

/**
 * @brief Performs "dictionary" comparison on ranges.
 * @param first1 An input iterator.
 * @param last1 An input iterator.
 * @param first2 An input iterator.
 * @param last2 An input iterator.
 * @return A boolean true or false.
 * 
 * "Returns true if the sequence of elements defined by the range
 * [first1,last1) is lexicographically less than the sequence of elements
 * defined by the range [first2, last). Return false otherwise."
 * (Quoted from [25.3.8]1.) It the iterators are all character pointers,
 * then this is an inline call to @c memcmp.
 */
template <typename InputIterator1, typename InputIterator2>
bool
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
  InputIterator2 first2, InputIterator2 last2)
{
  for (; first1 != last1 && first2 != last2; ++first1, ++first2)
  {
    if (*first1 < *first2)
      return true;
    if (*first2 < *first1)
      return false;
  }
  return first1 == last1 && first2 != last2;
}

/**
 * @brief Performs "dictionary" comparison on ranges.
 * @param first1 An input iterator.
 * @param last1 An input iterator.
 * @param first2 An input iterator.
 * @param last2 An input iterator.
 * @param comp A @link s20_3_3_comparisons comparison functor@endlink.
 * @return A boolean true or false.
 * 
 * The same as the four-parameter @c lexigraphical_compare, but uses the
 * comp parameter instead of @c <.
 */
template <typename InputIterator1, typename InputIterator2,
  typename Compare>
bool
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
  InputIterator2 first2, InputIterator2 last2,
  Compare comp)
{
  for (; first1 != last1 && first2 != last2; ++first1, ++first2)
  {
    if (comp(*first1, *first2))
      return true;
    if (comp(*first2, *first1))
      return false;
  }
  return first1 == last1 && first2 != last2;
}

} // ft

#endif // STL_ALGOBASE_H_