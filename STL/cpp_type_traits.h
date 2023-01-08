#ifndef CPP_TYPE_TRATIS_H_
#define CPP_TYPE_TRATIS_H_

//
//  This file provides some compile-time information about various types.
//  These representations were designed, on purpose, to be constant-expressions
//  and not types as found in <type_traits.h>. In particular, they
//  can be used in control structures and the optimizer hopefully will do
//  the obvious thing.

#include "../ext/type_traits.h"

namespace ft {

struct __true_type { };
struct __false_type { };

template <bool>
struct truth_type
{ typedef __false_type type; };

template <>
struct truth_type<true>
{ typedef __true_type type; };

// Compare for equality of types.
template <typename, typename>
struct are_same
{
  enum { value = 0 };
  typedef __false_type type;
};

template<typename Tp>
struct are_same<Tp, Tp>
{
  enum { value = 1 };
  typedef __true_type type;
};

//
// Integer types
//
template <typename Tp>
struct is_integer
{
  enum { value = 0 };
  typedef __false_type type;
};

// Thirteen specializations (yes there are eleven standard integer
// types; <em>long long</em> and <em>unsigned long long</em> are
// supported as extensions). Up to four target-specific __int<N>
// types are supported as well.
template<>
struct is_integer<bool>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<char>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<signed char>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned char>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<short>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned short>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<int>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned int>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<long>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned long>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<long long>
{
  enum { value = 1 };
  typedef __true_type type;
};

template<>
struct is_integer<unsigned long long>
{
  enum { value = 1 };
  typedef __true_type type;
};



// For the immediate use, the following is a good approximation.
template <typename Tp>
struct is_pod
: public ft::integral_constant<bool, __is_pod(Tp)>
{ };


} // ft
#endif // CPP_TYPE_TRATIS_H_