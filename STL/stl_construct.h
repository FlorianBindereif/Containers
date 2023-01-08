#ifndef STL_CONSTRUCT_H_
#define STL_CONSTRUCT_H_

namespace ft {

/**
 * @if maint
 * Destroy a range of objects using the supplied allocator. For
 * nondefault allocators we do not optimize away invocation of
 * destroy() even if _Tp has a trivial destructor.
 * @endif
 */

template <typename ForwardIterator, typename Allocator>
void
Destroy(ForwardIterator first, ForwardIterator last,
  Allocator alloc)
{
  for (; first != last; ++first)
    alloc.destroy(&*first);
}


} // ft
#endif // STL_CONSTRUCT_H_