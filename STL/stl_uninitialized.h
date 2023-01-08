#ifndef STL_UNINITIALIZED_H_
#define STL_UNINITIALIZED_H_

#include "stl_construct.h"

namespace ft {

// Extensions: versions of uninitialized_copy and uninitialized_fill_n
//  that take an allocator parameter.
//  We dispatch back to the standard versions when we're given the
//  default allocator. For nondefault allocators we do not use
//  any of the POD optimizations.

template <typename InputIterator, typename ForwardIterator,
  typename Allocator>
ForwardIterator
uninitialized_copy_a(InputIterator first, InputIterator last,
  ForwardIterator result,
  Allocator alloc)
{
  ForwardIterator cur = result;
  try
  {
    for (; first != last; ++first, ++cur)
      alloc.construct(&*cur, *first);
    return cur;
  }
  catch(...)
  {
    ft::Destroy(result, cur, alloc);
    throw;
  }
}

template <typename ForwardIterator, typename Size, typename Tp,
  typename Allocator>
void
uninitialized_fill_n_a(ForwardIterator first, Size n,
  const Tp& x, Allocator alloc)
{
  ForwardIterator cur = first;
  try
  {
    for (; n > 0; --n, ++cur)
      alloc.construct(&*cur, x);
  }
  catch(...)
  {
    ft::Destroy(first, cur, alloc);
    throw;
  }
}

} // ft
#endif // STL_UNINITIALIZED_H_