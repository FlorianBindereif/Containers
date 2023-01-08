#ifndef STL_ITERATOR_H_
#define STL_ITERATOR_H_

#include "cpp_type_traits.h"
#include "stl_iterator_base_types.h"
#include "../ext/type_traits.h"

namespace ft {

// 24.4.1 Reverse iterators
/**
 * "Bidirectional and random access iterators have corresponding reverse
 * %iterator adaptors that iterate through the data structure in the
 * opposite direction. They have the same signatures as the corresponding
 * iteraotrs. The fundamental relation between a reverse %iterator and its
 * corresponding %iterator @c i is established by the identity:
 * @code
 *  &*(reverse_iterator(i)) == &*(i - 1)
 * @endcode
 * 
 * This mapping is dictated by the fact that while there is always a
 * pointer past the end of an array, there might not be a valid pointer
 * before the beginning of an array."
 * 
 * Reverse iterators can be tricky and surprising at first. Their
 * semantics make sense, however, and the trickiness is a side effect of
 * the requirement that the iterators must be safe.
 */
template <typename Iterator>
class reverse_iterator
: public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
                      typename ft::iterator_traits<Iterator>::value_type,
                      typename ft::iterator_traits<Iterator>::difference_type,
                      typename ft::iterator_traits<Iterator>::pointer,
                      typename ft::iterator_traits<Iterator>::reference>
{
protected:
  Iterator current;

public:
  typedef Iterator                                                iterator_type;
  typedef typename ft::iterator_traits<Iterator>::difference_type difference_type; 
  typedef typename ft::iterator_traits<Iterator>::reference       reference; 
  typedef typename ft::iterator_traits<Iterator>::pointer         pointer;

  /**
   * The default constructor default-initializes member @p current.
   * If it is a pointer, that means it is zero-initialized.
   */
  reverse_iterator() : current() { }

  /**
   * This %iterator will move in the opposite direction that @p x does.
   */
  explicit
  reverse_iterator(iterator_type x) : current(x) { }

  /**
   * The copy constructor is normal.
   */
  reverse_iterator(const reverse_iterator& x)
  : current(x.current) { }

  /**
   * A reverse_iterator across other types can be copied in the normal
   * fashion.
   */
  template <typename Iter>
  reverse_iterator(const reverse_iterator<Iter>& x)
  : current(x.base()) { }

  iterator_type
  base() const
  { return current; }

  reference
  operator*() const
  {
    Iterator tmp = current;
    return *--tmp;
  }

  pointer
  operator->() const
  { return &(operator*()); }

  reverse_iterator&
  operator++()
  {
    --current;
    return *this;
  }

  reverse_iterator
  operator++(int)
  {
    reverse_iterator tmp = *this;
    --current;
    return tmp;
  }

  reverse_iterator&
  operator--()
  {
    ++current;
    return *this;
  }

  reverse_iterator
  operator--(int)
  {
    reverse_iterator tmp = *this;
    ++current;
    return tmp;
  }

  reverse_iterator
  operator+(difference_type n) const
  { return reverse_iterator(current - n); }

  reverse_iterator&
  operator+=(difference_type n)
  {
    current -= n;
    return *this;
  }

  reverse_iterator
  operator-(difference_type n) const
  { return reverse_iterator(current + n); }

  reverse_iterator&
  operator-=(difference_type n)
  {
    current += n;
    return *this;
  }

  reference
  operator[](difference_type n) const
  { return *(*this + n); }
};
  //@{
  /**
   * @param x A %reverse_iterator.
   * @param y A %reverse_iterator.
   * @return A simple bool.
   * 
   * Reverse iterators forward many operations to their underlying base()
   * iterators. Others are implemented in terms of ont another.
   * 
   */
  template <typename Iterator>
  bool
  operator==(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
  { return x.base() == y.base(); }

  template <typename Iterator>
  bool
  operator<(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
  { return y.base() < x.base(); }

  template <typename Iterator>
  bool
  operator!=(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
  { return !(x == y); }

  template <typename Iterator>
  bool
  operator>(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
  { return y < x; }

  template <typename Iterator>
  bool
  operator<=(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
  { return !(y < x); }

  template <typename Iterator>
  bool
  operator>=(const reverse_iterator<Iterator>& x,
              const reverse_iterator<Iterator>& y)
  { return !(x < y); }

  template <typename Iterator>
  typename reverse_iterator<Iterator>::difference_type
  operator-(const reverse_iterator<Iterator>& x,
            const reverse_iterator<Iterator>& y)
  { return y.baes() - x.base(); }

  template <typename Iterator>
  reverse_iterator<Iterator>
  operator+(typename reverse_iterator<Iterator>::difference_type n,
            const reverse_iterator<Iterator>& x)
  { return reverse_iterator<Iterator>(x.base() - n); }

  // DR 280. Comparison of reverse_iterator to const reverse_iterator
  template <typename IteratorL, typename IteratorR>
  bool
  operator==(const reverse_iterator<IteratorL>& x,
            const reverse_iterator<IteratorR>& y)
  { return x.base() == y.base(); }

  template <typename IteratorL, typename IteratorR>
  bool
  operator<(const reverse_iterator<IteratorL>& x,
            const reverse_iterator<IteratorR>& y)
  { return y.base() < x.base(); }

  template <typename IteratorL, typename IteratorR>
  bool
  operator!=(const reverse_iterator<IteratorL>& x,
            const reverse_iterator<IteratorR>& y)
  { return !(x == y); }

  template <typename IteratorL, typename IteratorR>
  bool
  operator>(const reverse_iterator<IteratorL>& x,
            const reverse_iterator<IteratorR>& y)
  { return y < x; }

  template <typename IteratorL, typename IteratorR>
  bool
  operator<=(const reverse_iterator<IteratorL>& x,
            const reverse_iterator<IteratorR>& y)
  { return !(y < x); }

  template <typename IteratorL, typename IteratorR>
  bool
  operator>=(const reverse_iterator<IteratorL>& x,
            const reverse_iterator<IteratorR>& y)
  { return !(x < y); }

  template <typename IteratorL, typename IteratorR>
  typename reverse_iterator<IteratorL>::difference_type
  operator-(const reverse_iterator<IteratorL>& x,
            const reverse_iterator<IteratorR>& y)
  { return y.base() - x.base(); }



// This iterator adapter is 'normal' in the sense that it does not
// change the semantics of any of the operators of its iterator
// parameter. Its primary purpose is to convert an iterator that is
// not a class, e.g. a pointer, into an iterator that is a class.
// The Container parameter exists solely so that different containers
// using this template can instantiate different types, even if the
// Iterator parameter is the same.
template <typename Iterator, typename Container>
class normal_iterator
{
protected:
  Iterator M_current;

public:
  typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
  typedef typename iterator_traits<Iterator>::value_type        value_type;
  typedef typename iterator_traits<Iterator>::difference_type   difference_type;
  typedef typename iterator_traits<Iterator>::reference         reference;
  typedef typename iterator_traits<Iterator>::pointer           pointer;

  normal_iterator() : M_current(Iterator()) { }

  explicit
  normal_iterator(const Iterator& i) : M_current(i) { }

  // Allow iterator to const_iterator conversion
  template <typename Iter>
  normal_iterator(const normal_iterator<Iter,
  typename ft::enable_if<
    (ft::are_same<Iter, typename Container::pointer>::value),
    Container>::type>& i)
  : M_current(i.base()) { }

  // Forward iterator requirements
  reference
  operator*() const
  { return *M_current; }

  pointer
  operator->() const
  { return M_current; }

  normal_iterator&
  operator++()
  {
    ++M_current;
    return *this;
  }

  normal_iterator
  operator++(int)
  { return normal_iterator(M_current++); }

  // Bidirectional iterator requirements
  normal_iterator&
  operator--()
  {
    --M_current;
    return *this;
  }

  normal_iterator
  operator--(int)
  { return normal_iterator(M_current--); }

  // Random access iterator requirements
  reference
  operator[](const difference_type& n) const
  { return M_current[n]; }

  normal_iterator&
  operator+=(const difference_type& n)
  { M_current += n; return *this; }

  normal_iterator
  operator+(const difference_type& n) const
  { return normal_iterator(M_current + n); }

  normal_iterator&
  operator-=(const difference_type& n)
  { M_current -= n; return *this; }

  normal_iterator
  operator-(const difference_type& n) const
  { return normal_iterator(M_current - n); }

  const Iterator&
  base() const
  { return M_current; }
};

// Forward iterator requirements
template <typename IteratorL, typename IteratorR, typename Container>
bool
operator==(const normal_iterator<IteratorL, Container>& lhs,
          const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() == rhs.base(); }

template <typename Iterator, typename Container>
bool
operator==(const normal_iterator<Iterator, Container>& lhs,
          const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() == rhs.base(); }

template <typename IteratorL, typename IteratorR, typename Container>
bool
operator!=(const normal_iterator<IteratorL, Container>& lhs,
          const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() != rhs.base(); }

template <typename Iterator, typename Container>
bool
operator!=(const normal_iterator<Iterator, Container>& lhs,
          const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() != rhs.base(); }

// Random access iterator requirements
template <typename IteratorL, typename IteratorR, typename Container>
bool
operator<(const normal_iterator<IteratorL, Container>& lhs,
          const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() < rhs.base(); }

template <typename Iterator, typename Container>
bool
operator<(const normal_iterator<Iterator, Container>& lhs,
          const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() < rhs.base(); }

template <typename IteratorL, typename IteratorR, typename Container>
bool
operator>(const normal_iterator<IteratorL, Container>& lhs,
          const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() > rhs.base(); }

template <typename Iterator, typename Container>
bool
operator>(const normal_iterator<Iterator, Container>& lhs,
          const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() > rhs.base(); }

template <typename IteratorL, typename IteratorR, typename Container>
bool
operator<=(const normal_iterator<IteratorL, Container>& lhs,
          const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() <= rhs.base(); }

template <typename Iterator, typename Container>
bool
operator<=(const normal_iterator<Iterator, Container>& lhs,
          const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() <= rhs.base(); }

template <typename IteratorL, typename IteratorR, typename Container>
bool
operator>=(const normal_iterator<IteratorL, Container>& lhs,
          const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() >= rhs.base(); }

template <typename Iterator, typename Container>
bool
operator>=(const normal_iterator<Iterator, Container>& lhs,
          const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() >= rhs.base(); }

// According to the resolution of DR179 not only the various comparison
// operators but also operator- must accept mixed iterator/const_iterator
// parameters.
template<typename IteratorL, typename IteratorR, typename Container>
typename normal_iterator<IteratorL, Container>::difference_type
operator-(const normal_iterator<IteratorL, Container>& lhs,
          const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator, typename Container>
typename normal_iterator<Iterator, Container>::difference_type
operator-(const normal_iterator<Iterator, Container>& lhs,
          const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() - rhs.base(); }

template<typename Iterator, typename Container>
normal_iterator<Iterator, Container>
operator+(typename normal_iterator<Iterator, Container>::difference_type n,
          const normal_iterator<Iterator, Container>& i)
{ return normal_iterator<Iterator, Container>(i.base() + n); }

} // ft
#endif // STL_ITERATOR_H_