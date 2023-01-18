#pragma once

#include "type_traits.hpp"

namespace ft{

/*Primary template struct for interator_traits is used to obtain information about the properties of an iterator*/
template <typename Iter>
struct iterator_traits {
    typedef typename Iter::value_type        value_type;
    typedef typename Iter::difference_type   difference_type;
    typedef typename Iter::pointer           pointer;
    typedef typename Iter::reference         reference;
    typedef typename Iter::iterator_category iterator_category;
};


/*Specialization of iterator_traits for pointer types*/
template <typename T>
struct iterator_traits<T*> {
    typedef T                          value_type;
    typedef std::ptrdiff_t             difference_type;
    typedef T*                         pointer;
    typedef T&                         reference;
    // typedef random_access_iterator_tag iterator_category;
};

/*Specialization of iterator_traits for pointer to const types*/
template <typename T>
struct iterator_traits<const T*> {
    typedef T                          value_type;
    typedef std::ptrdiff_t             difference_type;
    typedef const T*                   pointer;
    typedef const T&                   reference;
    // typedef random_access_iterator_tag iterator_category;
};

/* Converts iterator that is not a class, e.g. a pointer, into an iterator that is a class.
 @Container exists so that different containers using this template can instantiate different types, 
 even if the Iterator parameter is the same.*/
template <typename Iterator, typename Container>
class normal_iterator
{
	protected:
		Iterator current_;

  public:
    // TYPEDEFS
    typedef Iterator                                                    iterator_type;
    typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
    typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
    typedef typename ft::iterator_traits<Iterator>::reference           reference;
    typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;
    typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;

	public:
		//CONSTRUCTORS & DESTRUCTOR

    /*constructor initialising with @Iterator type*/
		normal_iterator()
    : current_(Iterator()){};

    /*constructor takes object of the Iterator type and initializes with the passed Iterator object.*/
    explicit normal_iterator(const Iterator& iter)
    :current_(iter){};

    /*constructor that allows iterator to const_iterator conversion*/
    template <typename Iter>
    normal_iterator(const normal_iterator<
      Iter, typename ft::enable_if<
        (ft::are_same<Iter, typename Container::pointer>::equality), Container>::type>& it)
    :current_(it.base()) {};

    /*default destructor*/
    ~normal_iterator(){};
  
    // FORWARD ITERATOR REQUIREMRNTS

    reference operator*() const
    {return *current_;}

    pointer operator->() const
    {return current_;}

    normal_iterator& operator++()
    {
      ++current_;
      return *this;
    }

    normal_iterator operator++(int)
    {
      normal_iterator tmp(*this);
      ++current_;
      return tmp;
    }

    // BIDIRECTIONAL ITERATOR REQUIREMRNTS

    normal_iterator& operator--()
    {
      --current_;
      return *this;
    }

    normal_iterator operator--(int)
    {
      normal_iterator tmp(*this);
      --current_;
      return tmp;
    }

    // RANDOM ACCESS ITERATOR REQUIREMENTS

    reference operator[](const difference_type& n) const
    {return this[n];};

    normal_iterator operator+(const difference_type& n) const
    {
      return normal_iterator(current_ + n);
    }

    normal_iterator operator-(const difference_type& n) const
    {
      return normal_iterator(current_ - n);
    }

    normal_iterator& operator+=(const difference_type& n)
    {
      current_ += n;
      return *this;
    }

    normal_iterator& operator-=(const difference_type& n)
    {
      current_ -= n;
      return *this;
    }

    iterator_type base() const
    {return current_;}
};

// ITERATOR COMPARISON REQUIREMENTS

template <typename IteratorL, typename IteratorR, typename Container>
inline bool operator==
(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorL, Container>& rhs)
{ return lhs.base() == rhs.base();}

template <typename IteratorL, typename IteratorR, typename Container>
inline bool operator!=
(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorL, Container>& rhs)
{ return lhs.base() != rhs.base();}

template <typename IteratorL, typename IteratorR, typename Container>
inline bool operator<
(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorL, Container>& rhs)
{ return lhs.base() < rhs.base();}

template <typename IteratorL, typename IteratorR, typename Container>
inline bool operator>
(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorL, Container>& rhs)
{ return lhs.base() > rhs.base();}

template <typename IteratorL, typename IteratorR, typename Container>
inline bool operator>=
(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorL, Container>& rhs)
{ return lhs.base() >= rhs.base();}

template <typename IteratorL, typename IteratorR, typename Container>
inline bool operator<=
(const normal_iterator<IteratorL, Container>& lhs, const normal_iterator<IteratorL, Container>& rhs)
{ return lhs.base() <= rhs.base();}

// ITERATOR ARITHMETIC REQUIREMENTS

/*Allows for mixed iterator/const_iterator parameters*/
template <typename IteratorL, typename IteratorR, typename Container>
inline typename normal_iterator<IteratorL, Container>::difference_type operator-(
    const normal_iterator<IteratorL, Container>& lhs, 
    const normal_iterator<IteratorR, Container>& rhs)
{ return lhs.base() - rhs.base();}

template <typename Iterator, typename Container>
inline typename normal_iterator<Iterator, Container>::difference_type operator-(
    const normal_iterator<Iterator, Container>& lhs, 
    const normal_iterator<Iterator, Container>& rhs)
{ return lhs.base() - rhs.base();}

template <typename Iterator, typename Container>
inline normal_iterator<Iterator, Container> operator+(
    typename normal_iterator<Iterator, Container>::difference_type n,
    const normal_iterator<Iterator, Container>& it)
    {return normal_iterator<Iterator, Container>(it.base() + n);}
}