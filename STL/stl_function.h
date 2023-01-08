#ifndef STL_FUNCTION_H_
#define STL_FUNCTION_H_

#include <functional>

namespace ft {

template <typename Pair>
struct Select1st
: public std::unary_function<Pair, typename Pair::first_type>
{
  typename Pair::first_type&
  operator()(Pair& x) const
  { return x.first; }

  const typename Pair::first_type&
  operator()(const Pair& x) const
  { return x.first; }
};

template <typename Tp>
struct Identity
: public std::unary_function<Tp, Tp>
{
  Tp&
  operator()(Tp& x) const 
  { return x; }

  const Tp&
  operator()(const Tp& x) const
  { return x; }
};

// Partial specialization, avoids confusing errors in e.g. std::set<const T>.
template <typename Tp>
struct Identity <const Tp>
: Identity<Tp> { };


} // ft
#endif // STL_FUNCTION_H_