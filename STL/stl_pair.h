// Pair implementation -*- C++ -*-

/** @file stl_pair.h
 *  This is an internal header file, included by other library headers.
 *  You should not attempt to use it directly.
 */

#ifndef STL_PAIR_H_
#define STL_PAIR_H_

namespace ft {

/// pair holds two objects of arbitrary type.
template <class T1, class T2>
struct pair
{
  typedef T1 first_type;  ///<  @c first_type is the first bound type
  typedef T2 second_type; ///<  @c second_type is the second bound type

  T1  first;              ///< @c first is a copy of the first object
  T2  second;             ///< @c second is a copy of the second object

  // 265.  std::pair::pair() effects overly restrictive
  /** The default constructor creates @c first and @c second using their
   *  respective default constructors.  */
  pair()
  : first(), second() { }

  /** Two objects may be passed to a @c pair constructor to be copied.  */
  pair(const T1& a, const T2& b)
  : first(a), second(b) { }

  /** There is also a templated copy ctor for the @c pair class itself.  */
  template <class U1, class U2>
  pair(const pair<U1, U2>& p)
  : first(p.first), second(p.second) { }
};

/// Two pairs of the same type are equal if their members are equal.
template <class T1, class T2>
bool
operator==(const pair<T1, T2>& x, const pair<T1, T2>& y)
{ return x.first == y.first && x.second == y.second; }

/// <http://gcc.gnu.org/onlinedocs/libstdc++/20_util/howto.html#pairlt>
template <class T1, class T2>
bool
operator<(const pair<T1, T2>& x, const pair<T1, T2>& y)
{ return x.first < y.first
    || (!(y.first < x.first) && x.second < y.second); }

/// Uses @c operator== to find the result.
template <class T1, class T2>
bool
operator!=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{ return !(x == y); }

/// Uses @c operator< to find the result.
template <class T1, class T2>
bool
operator>(const pair<T1, T2>& x, const pair<T1, T2>& y)
{ return y < x; }


/// Uses @c operator< to find the result.
template <class T1, class T2>
bool
operator<=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{ return !(y < x); }

/// Uses @c operator< to find the result.
template <class T1, class T2>
bool
operator>=(const pair<T1, T2>& x, const pair<T1, T2>& y)
{ return !(x < y); }

/**
 *  @brief A convenience wrapper for creating a pair from two objects.
 *  @param  x  The first object.
 *  @param  y  The second object.
 *  @return   A newly-constructed pair<> object of the appropriate type.
 *
 *  The standard requires that the objects be passed by reference-to-const,
 *  but LWG issue #181 says they should be passed by const value.  We follow
 *  the LWG by default.
 */
template <class T1, class T2>
pair<T1, T2>
make_pair(T1 x, T2 y)
{ return pair<T1, T2>(x, y); }

} // ft
#endif // STL_PAIR_H_