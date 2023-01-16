#pragma once

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
    typedef random_access_iterator_tag iterator_category;
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

    typedef typename ft::iterator_traits<Iterator>::iterator_category   iterator_category;
    typedef typename ft::iterator_traits<Iterator>::value_type          value_type;
    typedef typename ft::iterator_traits<Iterator>::pointer             pointer;
    typedef typename ft::iterator_traits<Iterator>::reference           reference;
    typedef typename ft::iterator_traits<Iterator>::difference_type     difference_type;


	public:
		//CONSTRUCTORS

    /*constructor initialising with @Iterator type*/
		normal_iterator(): current_(Interator()){};

    /*constructor takes object of the Iterator type and initializes with the passed Iterator object.*/
    normal_iterator(const Iterator& other)
    :current_(other){};

    /*constructor that allows iterator to const_iterator conversion*/
    template <typename Iter>
    normal_iterator(const normal_iterator<Iter,typename ft::enable_if<(ft::are_same<Iter, typename Container::pointer>::value),Container>::type>& i)
    : current_(i.base()) {};

    // Forward iterator requirements

    reference operator*() const
    {return *current_;}

    pointer operator->() const
    {return current_;}

    normal_iterator& operator++()
    {
      
    }


};