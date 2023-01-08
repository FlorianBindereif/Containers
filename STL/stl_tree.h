// RB tree implementation -*- C++ -*-

/** @file stl_tree.h
 *  This is an internal header file, included by other library headers.
 *  You should not attempt to use it directly.
 */

#ifndef STL_TREE_H_
#define STL_TREE_H_

#include <memory>
#include "cpp_type_traits.h"
#include "stl_iterator.h"
#include "stl_pair.h"
#include "stl_algobase.h"

namespace ft {
// Red-black tree class, designed for use in implementing STL
// associative containers (set, multiset, map, and multimap). The
// insertion and deletion algorithms are based on those in Cormen,
// Leiserson, and Rivest, Introduction to Algorithms (MIT Press,
// 1990), except that
//
// (1) the header cell is maintained with links not only to the root
// but also to the leftmost node of the tree, to enable constant
// time begin(), and to the rightmost node of the tree, to enable
// linear time performance when used with the generic set algorithms
// (set_union, etc.)
// 
// (2) when a node being deleted has two children its successor node
// is relinked into its place, rather than copied, so that the only
// iterators invalidated are those referring to the deleted node.

enum Rb_tree_color { S_red = false, S_black = true };

struct Rb_tree_node_base
{
  typedef Rb_tree_node_base*        Base_ptr;
  typedef const Rb_tree_node_base*  Const_Base_ptr;

  Rb_tree_color   M_color;
  Base_ptr        M_parent;
  Base_ptr        M_left;
  Base_ptr        M_right;

  static Base_ptr
  S_minimum(Base_ptr x)
  {
    while (x->M_left != 0) x = x->M_left;
    return x;
  }
  
  static Const_Base_ptr
  S_minimum(Const_Base_ptr x)
  {
    while (x->M_left != 0) x = x->M_left;
    return x;
  }
  
  static Base_ptr
  S_maximum(Base_ptr x)
  {
    while (x->M_right != 0) x = x->M_right;
    return x;
  }
  
  static Const_Base_ptr
  S_maximum(Const_Base_ptr x)
  {
    while (x->M_right != 0) x = x->M_right;
    return x;
  }
};

template <typename Val>
struct Rb_tree_node : public Rb_tree_node_base
{
  typedef Rb_tree_node<Val>*  Link_type;
  Val                         M_value_field;
};

Rb_tree_node_base*
Rb_tree_increment(Rb_tree_node_base* x)
{
  if (x->M_right != 0)
  {
    x = x->M_right;
    while (x->M_left != 0)
      x = x->M_left;
  }
  else
  {
    Rb_tree_node_base* y = x->M_parent;
    while (x == y->M_right)
    {
      x = y;
      y = y->M_parent;
    }
    //
    // Can't understand
    //
    if (x->M_right != y)
      x = y;
  }
  return x;
}

const Rb_tree_node_base*
Rb_tree_increment(const Rb_tree_node_base* x)
{
  return Rb_tree_increment(const_cast<Rb_tree_node_base*>(x));
}

Rb_tree_node_base*
Rb_tree_decrement(Rb_tree_node_base* x)
{
  //
  // Can't understand
  //
  if (x->M_color == S_red
      && x->M_parent->M_parent == x)
      x = x->M_right;
  else if (x->M_left != 0)
  {
    Rb_tree_node_base* y = x->M_left;
    while (y->M_right != 0)
      y = y->M_right;
    x = y;
  }
  else
  {
    Rb_tree_node_base* y = x->M_parent;
    while (x == y->M_left)
    {
      x = y;
      y = y->M_parent;
    }
    x = y;
  }
  return x;
}

const Rb_tree_node_base*
Rb_tree_decrement(const Rb_tree_node_base* x)
{
  return Rb_tree_decrement(const_cast<Rb_tree_node_base*>(x));
}

template <typename Tp>
struct Rb_tree_iterator
{
  typedef Tp                                value_type;
  typedef Tp&                               reference;
  typedef Tp*                               pointer;

  typedef std::bidirectional_iterator_tag   iterator_category;
  typedef ptrdiff_t                         difference_type;

  typedef Rb_tree_iterator<Tp>              Self;
  typedef Rb_tree_node_base::Base_ptr       Base_ptr;
  typedef Rb_tree_node<Tp>*                 Link_type;


  Rb_tree_iterator()
  : M_node() { }

  explicit
  Rb_tree_iterator(Link_type x)
  : M_node(x) { }

  reference
  operator*() const
  { return static_cast<Link_type>(M_node)->M_value_field; }

  pointer
  operator->() const
  { return &static_cast<Link_type>(M_node)->M_value_field; }

  Self&
  operator++()
  {
    M_node = Rb_tree_increment(M_node);
    return *this;
  }

  Self
  operator++(int)
  {
    Self tmp = *this;
    M_node = Rb_tree_increment(M_node);
    return tmp;
  }

  Self&
  operator--()
  {
    M_node = Rb_tree_decrement(M_node);
    return *this;
  }

  Self
  operator--(int)
  {
    Self tmp = *this;
    M_node = Rb_tree_decrement(M_node);
    return tmp;
  }

  bool
  operator==(const Self& x) const
  { return M_node == x.M_node; }

  bool
  operator!=(const Self& x) const
  { return M_node != x.M_node; }

  Base_ptr M_node;
};

template <typename Tp>
struct Rb_tree_const_iterator
{
  typedef Tp                                value_type;
  typedef const Tp&                         reference;
  typedef const Tp*                         pointer;

  typedef Rb_tree_iterator<Tp>              iterator;

  typedef std::bidirectional_iterator_tag   iterator_category;
  typedef ptrdiff_t                         difference_type;

  typedef Rb_tree_const_iterator<Tp>        Self;
  typedef Rb_tree_node_base::Const_Base_ptr Base_ptr;
  typedef const Rb_tree_node<Tp>*           Link_type;

  Rb_tree_const_iterator()
  : M_node() { }

  explicit
  Rb_tree_const_iterator(Link_type x)
  : M_node(x) { }

  Rb_tree_const_iterator(const iterator& it)
  : M_node(it.M_node) { }

  reference
  operator*() const
  { return static_cast<Link_type>(M_node)->M_value_field; }

  pointer
  operator->() const
  { return &static_cast<Link_type>(M_node)->M_value_field; }

  Self&
  operator++()
  {
    M_node = Rb_tree_increment(M_node);
    return *this;
  }

  Self
  operator++(int)
  {
    Self tmp = *this;
    M_node = Rb_tree_increment(M_node);
    return tmp;
  }

  Self&
  operator--()
  {
    M_node = Rb_tree_decrement(M_node);
    return *this;
  }

  Self
  operator--(int)
  {
    Self tmp = *this;
    M_node = Rb_tree_decrement(M_node);
    return tmp;
  }

  bool
  operator==(const Self& x) const
  { return M_node == x.M_node; }

  bool
  operator!=(const Self& x) const
  { return M_node != x.M_node; }

  Base_ptr M_node;
};

template <typename Val>
bool
operator==(const Rb_tree_iterator<Val>& x,
          const Rb_tree_const_iterator<Val>& y)
{ return x.M_node == y.M_node; }

template <typename Val>
bool
operator!=(const Rb_tree_iterator<Val>& x,
          const Rb_tree_const_iterator<Val>& y)
{ return x.M_node != y.M_node; }

void
Rb_tree_rotate_left(Rb_tree_node_base* const x,
                    Rb_tree_node_base*& root)
{
  Rb_tree_node_base* const y = x->M_right;

  x->M_right = y->M_left;
  if (y->M_left != 0)
    y->M_left->M_parent = x;
  y->M_parent = x->M_parent;

  if (x == root)
    root = y;
  else if (x == x->M_parent->M_left)
    x->M_parent->M_left = y;
  else
    x->M_parent->M_right = y;
  y->M_left = x;
  x->M_parent = y;
}

void
Rb_tree_rotate_right(Rb_tree_node_base* const x,
                    Rb_tree_node_base*& root)
{
  Rb_tree_node_base* const y = x->M_left;

  x->M_left = y->M_right;
  if (y->M_right != 0)
    y->M_right->M_parent = x;
  y->M_parent = x->M_parent;

  if (x == root)
    root = y;
  else if (x == x->M_parent->M_right)
    x->M_parent->M_right = y;
  else
    x->M_parent->M_left = y;
  y->M_right = x;
  x->M_parent = y;
}

void
Rb_tree_insert_and_rebalance(const bool insert_left,
                            Rb_tree_node_base* x,
                            Rb_tree_node_base* p,
                            Rb_tree_node_base& header)
{
  Rb_tree_node_base*& root = header.M_parent;

  // Initialize fields in new node to insert.
  x->M_parent = p;
  x->M_left = 0;
  x->M_right = 0;
  x->M_color = S_red;

  // Insert.
  // Make new node child of parent and maintain root, leftmost and
  // rightmost nodes.
  // N.B. First node is always inserted left.
  if (insert_left)
  {
    p->M_left = x; // also makes leftmost = x when p == &header

    if (p == &header)
    {
      header.M_parent = x;
      header.M_right = x;
    }
    else if (p == header.M_left)
      header.M_left = x; // maintain leftmost pointing to min node
  }
  else
  {
    p->M_right = x;

    if (p == header.M_right)
      header.M_right = x; // maintain rightmost pointing to max node
  }
  // Rebalance.
  while (x != root
    && x->M_parent->M_color == S_red)
  {
    Rb_tree_node_base* const xpp = x->M_parent->M_parent;

    if (x->M_parent == xpp->M_left)
    {
      Rb_tree_node_base* const y = xpp->M_right;

      if (y && y->M_color == S_red) // Case 1
      {
        x->M_parent->M_color = S_black;
        y->M_color = S_black;
        xpp->M_color = S_red;
        x = xpp;
      }
      else  // Case 2
      {
        if (x == x->M_parent->M_right)
        {
          x = x->M_parent;
          Rb_tree_rotate_left(x, root);
        }
        x->M_parent->M_color = S_black;
        xpp->M_color = S_red;
        Rb_tree_rotate_right(xpp, root);
      }
    }
    else
    {
      Rb_tree_node_base* const y = xpp->M_left;

      if (y && y->M_color == S_red) // Case 1
      {
        x->M_parent->M_color = S_black;
        y->M_color = S_black;
        xpp->M_color = S_red;
        x = xpp;
      }
      else  // Case 2
      {
        if (x == x->M_parent->M_left)
        {
          x = x->M_parent;
          Rb_tree_rotate_right(x, root);
        }
        x->M_parent->M_color = S_black;
        xpp->M_color = S_red;
        Rb_tree_rotate_left(xpp, root);
      }
    }
  }
  root->M_color = S_black;
}

Rb_tree_node_base*
Rb_tree_rebalance_for_erase(Rb_tree_node_base* const z,
                            Rb_tree_node_base& header)
{
  Rb_tree_node_base*& root = header.M_parent;
  Rb_tree_node_base*& leftmost = header.M_left;
  Rb_tree_node_base*& rightmost = header.M_right;
  Rb_tree_node_base* y = z;
  Rb_tree_node_base* x = 0;
  Rb_tree_node_base* x_parent = 0;

  if (y->M_left == 0)     // z has at most one non-null child. y == z.
    x = y->M_right;       // x might be null.
  else
  {
    if (y->M_right == 0)  // z has exactly one non-null child. y == z.
      x = y->M_left;      // __x is not null.
    else
    {
	    // z has two non-null children.
      y = y->M_right;   // Set y to z's successor.  x might be null.
      while (y->M_left != 0)
        y = y->M_left;
      x = y->M_right;
    }
  }

  if (y != z)
  {
  	// relink y in place of z.  y is z's successor
    z->M_left->M_parent = y;
    y->M_left = z->M_left;
    if (y != z->M_right)
    {
      x_parent = y->M_parent;
      if (x) x->M_parent = y->M_parent;
      y->M_parent->M_left = x;   // y must be a child of M_left
      y->M_right = z->M_right;
      z->M_right->M_parent = y;
    }
    else
      x_parent = y;

    if (root == z)
      root = y;
    else if (z->M_parent->M_left == z)
      z->M_parent->M_left = y;
    else
      z->M_parent->M_right = y;
    y->M_parent = z->M_parent;
    std::swap(y->M_color, z->M_color);
    y = z;
	  // y now points to node to be actually deleted
  }
  else
  {
    // y == z
    x_parent = y->M_parent;
    if (x)
      x->M_parent = y->M_parent;

    if (root == z)
      root = x;
    else
    {
      if (z->M_parent->M_left == z)
        z->M_parent->M_left = x;
      else
        z->M_parent->M_right = x;
    }

    if (leftmost == z)
    {
      if (z->M_right == 0)        // __z->_M_left must be null also
        leftmost = z->M_parent;
	    else                        // makes __leftmost == _M_header if __z == __root
        leftmost = Rb_tree_node_base::S_minimum(x);
    }

    if (rightmost == z)
    {
      if (z->M_left == 0)         // __z->_M_right must be null also
        rightmost = z->M_parent;
      else                        	// makes __rightmost == _M_header if __z == __root
        rightmost = Rb_tree_node_base::S_maximum(x);  // __x == __z->_M_left
    }
  }

  if (y->M_color != S_red)
  {
    while (x != root && (x == 0 || x->M_color == S_black))
    {
      if (x == x_parent->M_left)
      {
        Rb_tree_node_base* w = x_parent->M_right;
        if (w->M_color == S_red)  // Case 1
        {
          w->M_color = S_black;
          x_parent->M_color = S_red;
          Rb_tree_rotate_left(x_parent, root);
          w = x_parent->M_right;
        }

        if ((w->M_left == 0 ||
            w->M_left->M_color == S_black) &&
            (w->M_right == 0 ||
            w->M_right->M_color == S_black))  // Case 2
        {
          w->M_color = S_red;
          x = x_parent;
          x_parent = x_parent->M_parent;
        }
        else
        {
          if (w->M_right == 0
            || w->M_right->M_color == S_black) // Case 3
          {
            w->M_left->M_color = S_black;
            w->M_color = S_red;
            Rb_tree_rotate_right(w, root);
            w = x_parent->M_right;
          }
          w->M_color = x_parent->M_color; // Case 4
          x_parent->M_color = S_black;
          if (w->M_right)
            w->M_right->M_color = S_black;
          Rb_tree_rotate_left(x_parent, root);
          break;
        }
      }
      else
      {
 	      // same as above, with _M_right <-> _M_left.
        Rb_tree_node_base* w = x_parent->M_left;
        if (w->M_color == S_red)  // Case 1
        {
          w->M_color = S_black;
          x_parent->M_color = S_red;
          Rb_tree_rotate_right(x_parent, root);
          w = x_parent->M_left;
        }

        if ((w->M_right == 0 ||
            w->M_right->M_color == S_black) &&
            (w->M_left == 0 ||
            w->M_left->M_color == S_black))  // Case 2
        {
          w->M_color = S_red;
          x = x_parent;
          x_parent = x_parent->M_parent;
        }
        else
        {
          if (w->M_left == 0
            || w->M_left->M_color == S_black)  // Case 3
          {
            w->M_right->M_color = S_black;
            w->M_color = S_red;
            Rb_tree_rotate_left(w, root);
            w = x_parent->M_left;
          }
          w->M_color = x_parent->M_color; // Case 4
          x_parent->M_color = S_black;
          if (w->M_left)
            w->M_left->M_color = S_black;
          Rb_tree_rotate_right(x_parent, root);
          break;
        }
      }
    }
    if (x) x->M_color = S_black;
  }
  return y;
}


template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc = std::allocator<Val> >
class Rb_tree
{
  typedef typename Alloc::template rebind<Rb_tree_node<Val> >::other
          Node_allocator;

  protected:
    typedef Rb_tree_node_base*                    Base_ptr;
    typedef const Rb_tree_node_base*              Const_Base_ptr;
    typedef Rb_tree_node<Val>                     Rb_tree_node;

  public:
    typedef Key                                   key_type;
    typedef Val                                   value_type;
    typedef value_type*                           pointer;
    typedef const value_type*                     const_pointer;
    typedef value_type&                           reference;
    typedef const value_type&                     const_reference;
    typedef Rb_tree_node*                         Link_type;
    typedef const Rb_tree_node*                   Const_Link_type;
    typedef std::size_t                           size_type;
    typedef std::ptrdiff_t                        difference_type;
    typedef Alloc                                 allocator_type;

    Node_allocator&
    M_get_Node_allocator()
    { return *static_cast<Node_allocator*>(&this->M_impl); }

    const Node_allocator&
    M_get_Node_allocator() const
    { return *static_cast<const Node_allocator*>(&this->M_impl); }

    allocator_type
    get_allocator() const
    { return allocator_type(M_get_Node_allocator()); };

  protected:
    Rb_tree_node*
    M_get_node()
    { return M_impl.Node_allocator::allocate(1); }
  
    void
    M_put_node(Rb_tree_node* p)
    { M_impl.Node_allocator::deallocate(p, 1); }

    Link_type
    M_create_node(const value_type& x)
    {
      Link_type tmp = M_get_node();
      try
      {
        get_allocator().construct(&tmp->M_value_field, x);
      }
      catch(...)
      {
        M_put_node(tmp);
        throw;
      }
      return tmp;
    }

    Link_type
    M_clone_node(Const_Link_type x)
    {
      Link_type tmp = M_create_node(x->M_value_field);
      tmp->M_color = x->M_color;
      tmp->M_left = 0;
      tmp->M_right = 0;
      return tmp;
    }

    void
    M_destroy_node(Link_type p)
    {
      get_allocator().destroy(&p->M_value_field);
      M_put_node(p);
    }
    
  protected:
    template <typename Key_compare,
              bool Is_pod_comparator = ft::is_pod<Key_compare>::value>
    struct Rb_tree_impl : public Node_allocator
    {
      Key_compare       M_key_compare;
      Rb_tree_node_base M_header;
      size_type         M_node_count; // Keeps track of size of tree.

      Rb_tree_impl(const Node_allocator& a = Node_allocator(),
        const Key_compare& comp = Key_compare())
      : Node_allocator(a), M_key_compare(comp), M_header(),
        M_node_count(0)
      {
        this->M_header.M_color = S_red;
        this->M_header.M_parent = 0;
        this->M_header.M_left = &this->M_header;
        this->M_header.M_right = &this->M_header;
      }
    };

    // Specialization for Comparison types that are not capable of
    // being base classes / super classes.
    template <typename Key_compare>
    struct Rb_tree_impl<Key_compare, true> : public Node_allocator
    {
      Key_compare       M_key_compare;
      Rb_tree_node_base M_header;
      size_type         M_node_count; // Keeps track of size of tree.

      Rb_tree_impl(const Node_allocator& a = Node_allocator(),
        const Key_compare& comp = Key_compare())
      : Node_allocator(a), M_key_compare(comp), M_header(),
        M_node_count(0)
      {
        this->M_header.M_color = S_red;
        this->M_header.M_parent = 0;
        this->M_header.M_left = &this->M_header;
        this->M_header.M_right = &this->M_header;
      }
    };

    Rb_tree_impl<Compare> M_impl;


  protected:
    Base_ptr&
    M_root()
    { return this->M_impl.M_header.M_parent; }

    Const_Base_ptr
    M_root() const
    { return this->M_impl.M_header.M_parent; }

    Base_ptr&
    M_leftmost()
    { return this->M_impl.M_header.M_left; }

    Const_Base_ptr
    M_leftmost() const
    { return this->M_impl.M_header.M_left; }

    Base_ptr&
    M_rightmost()
    { return this->M_impl.M_header.M_right; }

    Const_Base_ptr
    M_rightmost() const
    { return this->M_impl.M_header.M_right; }

    Link_type
    M_begin()
    { return static_cast<Link_type>(this->M_impl.M_header.M_parent); }

    Const_Link_type
    M_begin() const
    { return static_cast<Const_Link_type>(this->M_impl.M_header.M_parent); }

    Link_type
    M_end()
    { return static_cast<Link_type>(&this->M_impl.M_header); }

    Const_Link_type
    M_end() const
    { return static_cast<Const_Link_type>(&this->M_impl.M_header); }

    static const_reference
    S_value(Const_Link_type x)
    { return x->M_value_field; }

    static const Key&
    S_key(Const_Link_type x)
    { return KeyOfValue()(S_value(x)); }

    static Link_type
    S_left(Base_ptr x)
    { return static_cast<Link_type>(x->M_left); }

    static Const_Link_type
    S_left(Const_Base_ptr x)
    { return static_cast<Const_Link_type>(x->M_left); }

    static Link_type
    S_right(Base_ptr x)
    { return static_cast<Link_type>(x->M_right); }

    static Const_Link_type
    S_right(Const_Base_ptr x)
    { return static_cast<Const_Link_type>(x->M_right); }

    static const_reference
    S_value(Const_Base_ptr x)
    { return static_cast<Const_Link_type>(x)->M_value_field; }

    static const Key&
    S_key(Const_Base_ptr x)
    { return KeyOfValue()(S_value(x)); }

    static Base_ptr
    S_minimum(Base_ptr x)
    { return Rb_tree_node_base::S_minimum(x); }
     
    static Const_Base_ptr
    S_minimum(Const_Base_ptr x)
    { return Rb_tree_node_base::S_minimum(x); }

    static Base_ptr
    S_maximum(Base_ptr x)
    { return Rb_tree_node_base::S_maximum(x); }
     
    static Const_Base_ptr
    S_maximum(Const_Base_ptr x)
    { return Rb_tree_node_base::S_maximum(x); }

  public:
    typedef Rb_tree_iterator<value_type>          iterator;
    typedef Rb_tree_const_iterator<value_type>    const_iterator;

    typedef ft::reverse_iterator<iterator>        reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>  const_reverse_iterator;
  
  private:
    iterator
    M_insert(Base_ptr x, Base_ptr p, const value_type& v)
    {
      bool insert_left = (x != 0 || p == M_end()
                          || M_impl.M_key_compare(KeyOfValue()(v), S_key(p)));
      
      Link_type z = M_create_node(v);

      Rb_tree_insert_and_rebalance(insert_left, z, p,
          this->M_impl.M_header);
      ++M_impl.M_node_count;
      return iterator(z);
    }

    // 233. Insertion hints in associative containers.
    iterator
    M_insert_lower(Base_ptr x, Base_ptr p, const value_type& v)
    {
      bool insert_left = (x != 0 || p == M_end()
          || !M_impl.M_key_compare(S_key(p),
          KeyOfValue()(v)));
      
      Link_type z = M_create_node(v);

      Rb_tree_insert_and_rebalance(insert_left, z, p,
            this->M_impl.M_header);
      ++M_impl.M_node_count;
      return iterator(z);
    }

    const_iterator
    M_insert(Const_Base_ptr x, Const_Base_ptr p, const value_type& v)
    {
      bool insert_left = (x != 0 || p == M_end()
          || M_impl.M_key_compare(KeyOfValue()(v),
          S_key(p)));
      
      Link_type z = M_create_node(v);

      Rb_tree_insert_and_rebalance(insert_left, z,
            const_cast<Base_ptr>(p),
            this->M_impl.M_header);
      ++M_impl.M_node_count;
      return const_iterator(z);
    }

    Link_type
    M_copy(Const_Link_type x, Link_type p)
    {
      // Structural copy.  __x and __p must be non-null.
      Link_type top = M_clone_node(x);
      top->M_parent = p;

      try
      {
        if (x->M_right)
          top->M_right = M_copy(S_right(x), top);
        p = top;
        x = S_left(x);

        while (x != 0)
        {
          Link_type y = M_clone_node(x);
          p->M_left = y;
          y->M_parent = p;
          if (x->M_right)
            y->M_right = M_copy(S_right(x) , y);
          p = y;
          x = S_left(x);
        }
      }
      catch(...)
      {
        M_erase(top);
        throw;
      }
      return top;
    }

    void
    M_erase(Link_type x)
    {
      // Erase without realancing.
      while (x != 0)
      {
        M_erase(S_right(x));
        Link_type y = S_left(x);
        M_destroy_node(x);
        x = y;
      }
    }

  public:
    // allocation/deallocation
    Rb_tree()
    { }

    Rb_tree(const Compare& comp)
    : M_impl(allocator_type(), comp)
    { }

    Rb_tree(const Compare& comp, const allocator_type& a)
    : M_impl(a, comp)
    { }

    Rb_tree(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x)
    : M_impl(x.M_get_Node_allocator(), x.M_impl.M_key_compare)
    {
      if (x.M_root() != 0)
      {
        M_root() = M_copy(x.M_begin(), M_end());
        M_leftmost() = S_minimum(M_root());
        M_rightmost() = S_minimum(M_root());
        M_impl.M_node_count = x.M_impl.M_node_count;
      }
    }

    ~Rb_tree()
    { M_erase(M_begin()); }

    Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>&
    operator=(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x)
    {
      if (this != &x)
      {
        // Note that Key may e a constant type.
        clear();
        M_impl.M_key_compare = x.M_impl.M_key_compare;
        if (x.M_root() != 0)
        {
          M_root() = M_copy(x.M_begin(), M_end());
          M_leftmost() = S_minimum(M_root());
          M_rightmost() = S_maximum(M_root());
          M_impl.M_node_count = x.M_impl.M_node_count;
        }
      }
      return *this;
    }

    // Accessors.
    Compare
    key_comp() const
    { return M_impl.M_key_compare; }

    iterator
    begin()
    { return iterator(static_cast<Link_type>(this->M_impl.M_header.M_left)); }
  
    const_iterator
    begin() const
    { return const_iterator(static_cast<Const_Link_type>(this->M_impl.M_header.M_left)); }

    iterator
    end()
    { return iterator(static_cast<Link_type>(&this->M_impl.M_header)); }

    const_iterator
    end() const
    { return const_iterator(static_cast<Const_Link_type>(&this->M_impl.M_header)); }

    reverse_iterator
    rbegin()
    { return reverse_iterator(end()); }

    const_reverse_iterator
    rbegin() const
    { return const_reverse_iterator(end()); }

    reverse_iterator
    rend()
    { return reverse_iterator(begin()); }

    const_reverse_iterator
    rend() const
    { return const_reverse_iterator(begin()); }

    bool
    empty() const
    { return M_impl.M_node_count == 0; }

    size_type
    size() const
    { return M_impl.M_node_count; }

    size_type
    max_size() const
    { return get_allocator().max_size(); }

    void
    swap(Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& t)
    {
      if (M_root() == 0)
      {
        if (t.M_root() != 0)
        {
          M_root() = t.M_root();
          M_leftmost() = t.M_leftmost();
          M_rightmost() = t.M_rightmost();
          M_root()->M_parent = M_end();

          t.M_root() = 0;
          t.M_leftmost() = t.M_end();
          t.M_rightmost() = t.M_end();
        }
      }
      else if (t.M_root() == 0)
      {
        t.M_root() = M_root();
        t.M_leftmost() = M_leftmost();
        t.M_rightmost() = M_rightmost();
        t.M_root()->M_parent = t.M_end();

        M_root() = 0;
        M_leftmost() = M_end();
        M_rightmost() = M_end();
      }
      else
      {
        std::swap(M_root(), t.M_root());
        std::swap(M_leftmost(), t.M_leftmost());
        std::swap(M_rightmost(), t.M_rightmost());

        M_root()->M_parent = M_end();
        t.M_root()->M_parent = t.M_end();
      }

      // No need to swap header's color as it does not change.
      std::swap(this->M_impl.M_node_count, t.M_impl.M_node_count);
      std::swap(this->M_impl.M_key_compare, t.M_impl.M_key_compare);
    }

    // Insert/erase.
    pair<iterator, bool>
    M_insert_unique(const value_type& v)
    {
      Link_type x = M_begin();
      Link_type y = M_end();
      bool comp = true;
      while (x != 0)
      {
        y = x;
        comp = M_impl.M_key_compare(KeyOfValue()(v), S_key(x));
        x = comp ? S_left(x) : S_right(x);
      }
      iterator j = iterator(y);
      if (comp) {
        if (j == begin()) {
          return pair<iterator, bool>(M_insert(x, y, v), true);
        }
        else
          --j;
      }
      if (M_impl.M_key_compare(S_key(j.M_node), KeyOfValue()(v)))
        return pair<iterator, bool>(M_insert(x, y, v), true);
      return pair<iterator, bool>(j, false);
    }

    iterator
    M_insert_equal(const value_type& v)
    {
      Link_type x = M_begin();
      Link_type y = M_end();
      while (x != 0)
      {
        y = x;
        x = M_impl.M_key_compare(KeyOfValue()(v), S_key(x)) ?
            S_left(x) : S_right(x);
      }
      return M_insert(x, y, v);
    }

    // 233. Insertion hints in associative containers.
    iterator
    M_insert_equal_lower(const value_type& v)
    {
      Link_type x = M_begin();
      Link_type y = M_end();
      while (x != 0)
      {
        y = x;
        x = !M_impl.M_key_compare(S_key(x), KeyOfValue()(v)) ?
            S_left(x) : S_right(x);
      }
      return M_insert_lower(x, y, v);
    }

    iterator
    M_insert_unique(iterator position, const value_type& v)
    {
      // end()
      if (position.M_node == M_end())
      {
        if (size() > 0
          && M_impl.M_key_compare(S_key(M_rightmost()), KeyOfValue()(v)))
          return M_insert(0, M_rightmost(), v);
        else
          return M_insert_unique(v).first;
      }
      else if (M_impl.M_key_compare(KeyOfValue()(v), S_key(position.M_node)))
      {
        // First, try before...
        iterator before = position;
        if (position.M_node == M_leftmost()) // begin()
          return M_insert(M_leftmost(), M_leftmost(), v);
        else if ( M_impl.M_key_compare(S_key((--before).M_node), KeyOfValue()(v)))
        {
          if (S_right(before.M_node) == 0)
            return M_insert(0, before.M_node, v);
          else
            return M_insert(position.M_node, position.M_node, v);
        }
        else
          return M_insert_unique(v).first;
      }
      else if (M_impl.M_key_compare(S_key(position.M_node), KeyOfValue()(v)))
      {
        // ... then try after
        iterator after = position;
        if (position.M_node == M_rightmost())
          return M_insert(0, M_rightmost(), v);
        else if (M_impl.M_key_compare(KeyOfValue()(v), S_key((++after).M_node)))
        {
          if (S_right(position.M_node) == 0)
            return M_insert(0, position.M_node, v);
          else
            return M_insert(after.M_node, after.M_node, v);
        }
        else
          return M_insert_unique(v).first;
      }
      else
        return position; // Equivalent keys.
    }

    const_iterator
    M_insert_unique(const_iterator position, const value_type& v)
    {
      // end()
      if (position.M_node == M_end())
      {
        if (size() > 0
          && M_impl.M_key_compare(S_key(M_rightmost()), KeyOfValue()(v)))
          return M_insert(0, M_rightmost(), v);
        else
          return const_iterator(M_insert_unique(v).first);
      }
      else if (M_impl.M_key_compare(KeyOfValue()(v), S_key(position.M_node)))
      {
        // First, try before...
        const_iterator before = position;
        if (position.M_node == M_leftmost()) // begin()
          return M_insert(M_leftmost(), M_leftmost(), v);
        else if (M_impl.M_key_compare(S_key((--before).M_node), KeyOfValue()(v)))
        {
          if (S_right(before.M_node) == 0)
            return M_insert(0, before.M_node, v);
          else
            return M_insert(position.M_node, position.M_node, v);
        }
        else
          return const_iterator(M_insert_unique(v).first);
      }
      else if (M_impl.M_key_compare(S_key(position.M_node), KeyOfValue()(v)))
      {
        // ... then try after
        const_iterator after = position;
        if (position.M_node == M_rightmost())
          return M_insert(0, M_rightmost(), v);
        else if (M_impl.M_key_compare(KeyOfValue()(v), S_key((++after).M_node)))
        {
          if (S_right(position.M_node) == 0)
            return M_insert(0, position.M_node, v);
          else
            return M_insert(after.M_node, after.M_node, v);
        }
        else
          return const_iterator(M_insert_unique(v).first);
      }
      else
        return position; // Equivalent keys.
    }

    iterator
    M_insert_equal(iterator position, const value_type& v)
    {
      // end()
      if (position.M_node == M_end())
      {
        if (size() > 0
          && !M_impl.M_key_compare(KeyOfValue()(v)), S_key(M_rightmost()))
          return M_insert(0, M_rightmost(), v);
        else
          return M_insert_unique(v);
      }
      else if (!M_impl.M_key_compare(S_key(position.M_node), KeyOfValue()(v)))
      {
        // First, try before...
        iterator before = position;
        if (position.M_node == M_leftmost()) // begin()
          return M_insert(M_leftmost(), M_leftmost(), v);
        else if (!M_impl.M_key_compare(KeyOfValue()(v), S_key((--before).M_node)))
        {
          if (S_right(before.M_node) == 0)
            return M_insert(0, before.M_node, v);
          else
            return M_insert(position.M_node, position.M_node, v);
        }
        else
          return M_insert_unique(v);
      }
      else
      {
        // ... then try after
        iterator after = position;
        if (position.M_node == M_rightmost())
          return M_insert(0, M_rightmost(), v);
        else if (!M_impl.M_key_compare(S_key((++after).M_node)), KeyOfValue()(v))
        {
          if (S_right(position.M_node) == 0)
            return M_insert(0, position.M_node, v);
          else
            return M_insert(after.M_node, after.M_node, v);
        }
        else
          return M_insert_equal_lower(v);
      }
    }

    const_iterator
    M_insert_equal(const_iterator position, const value_type& v)
    {
      // end()
      if (position.M_node == M_end())
      {
        if (size() > 0
          && !M_impl.M_key_compare(KeyOfValue()(v)), S_key(M_rightmost()))
          return M_insert(0, M_rightmost(), v);
        else
          return const_iterator(M_insert_unique(v));
      }
      else if (!M_impl.M_key_compare(S_key(position.M_node), KeyOfValue()(v)))
      {
        // First, try before...
        const_iterator before = position;
        if (position.M_node == M_leftmost()) // begin()
          return M_insert(M_leftmost(), M_leftmost(), v);
        else if (!M_impl.M_key_compare(KeyOfValue()(v), S_key((--before).M_node)))
        {
          if (S_right(before.M_node) == 0)
            return M_insert(0, before.M_node, v);
          else
            return M_insert(position.M_node, position.M_node, v);
        }
        else
          return const_iterator(M_insert_unique(v));
      }
      else
      {
        // ... then try after
        const_iterator after = position;
        if (position.M_node == M_rightmost())
          return M_insert(0, M_rightmost(), v);
        else if (!M_impl.M_key_compare(S_key((++after).M_node)), KeyOfValue()(v))
        {
          if (S_right(position.M_node) == 0)
            return M_insert(0, position.M_node, v);
          else
            return M_insert(after.M_node, after.M_node, v);
        }
        else
          return const_iterator(M_insert_equal_lower(v));
      }
    }

    template<typename InputIterator>
    void
    M_insert_unique(InputIterator first, InputIterator last)
    {
      for (; first != last; ++first)
        M_insert_unique(end(), *first);
    }

    template<typename InputIterator>
    void
    M_insert_equal(InputIterator first, InputIterator last)
    {
      for (; first != last; ++first)
        M_insert_equal(end(), *first);      
    }

    void
    erase(iterator position)
    {
      Link_type y = static_cast<Link_type>(Rb_tree_rebalance_for_erase(
            position.M_node,
            this->M_impl.M_header));
      M_destroy_node(y);
      --M_impl.M_node_count;
    }

    void
    erase(const_iterator position)
    {
      Link_type y = static_cast<Link_type>(Rb_tree_rebalance_for_erase(
            const_cast<Base_ptr>(position.M_node),
            this->M_impl.M_header));
      M_destroy_node(y);
      --M_impl.M_node_count;
    }

    size_type
    erase(const key_type& x)
    {
      pair<iterator, iterator> p = equal_range(x);
      const size_type old_size = size();
      erase(p.first, p.second);
      return old_size - size();
    }

    void
    erase(iterator first, iterator last)
    {
      if (first == begin() && last == end())
        clear();
      else
      {
        while (first != last)
          erase(first++);
      }
    }

    void
    erase(const_iterator first, const_iterator last)
    {
      if (first == begin() && last == end())
        clear();
      else
      {
        while (first != last)
          erase(first++);
      }
    }

    void
    erase(const key_type* first, const key_type* last)
    {
      while (first != last)
        erase(*first++);
    }

    void
    clear()
    {
      M_erase(M_begin());
      M_leftmost() = M_end();
      M_root() = 0;
      M_rightmost() = M_end();
      M_impl.M_node_count = 0;
    }

    // Set operations.
    iterator
    find(const key_type& k)
    {
      Link_type x = M_begin(); // Current node.
      Link_type y = M_end(); // Last node which is not less than k.

      while (x != 0)
      {
        if (!M_impl.M_key_compare(S_key(x), k))
        {
          y = x;
          x = S_left(x);
        }
        else
          x = S_right(x);
      }
      iterator j = iterator(y);
      return j == end()
        || M_impl.M_key_compare(k, S_key(j.M_node)) ? end() : j;
    }
    
    const_iterator
    find(const key_type& k) const
    {
      Const_Link_type x = M_begin(); // Current node.
      Const_Link_type y = M_end(); // Last node which is not less than k.

      while (x != 0)
      {
        if (!M_impl.M_key_compare(S_key(x), k))
        {
          y = x;
          x = S_left(x);
        }
        else
          x = S_right(x);
      }
      const_iterator j = const_iterator(y);
      return j == end()
        || M_impl.M_key_compare(k, S_key(j.M_node)) ? end() : j;
    }

    size_type
    count(const key_type& k) const
    {
      pair<const_iterator, const_iterator> p = equal_range(k);
      const size_type n = std::distance(p.first, p.second);
      return n;
    }

    iterator
    lower_bound(const key_type& k)
    {
      Link_type x = M_begin(); // Current node.
      Link_type y = M_end(); // Last node which is not less than k.

      while (x != 0)
      {
        if (!M_impl.M_key_compare(S_key(x), k))
        {
          y = x;
          x = S_left(x);
        }
        else
          x = S_right(x);
      }
      return iterator(y);
    }

    const_iterator
    lower_bound(const key_type& k) const
    {
      Const_Link_type x = M_begin(); // Current node.
      Const_Link_type y = M_end(); // Last node which is not less than k.

      while (x != 0)
      {
        if (!M_impl.M_key_compare(S_key(x), k))
        {
          y = x;
          x = S_left(x);
        }
        else
          x = S_right(x);
      }
      return const_iterator(y);
    }

    iterator
    upper_bound(const key_type& k)
    {
      Link_type x = M_begin(); // Current node.
      Link_type y = M_end(); // Last node which is greater than k.

      while (x != 0)
      {
        if (M_impl.M_key_compare(k, S_key(x)))
        {
          y = x,
          x = S_left(x);
        }
        else
          x = S_right(x);
      }
      return iterator(y);
    }

    const_iterator
    upper_bound(const key_type& k) const
    {
      Const_Link_type x = M_begin(); // Current node.
      Const_Link_type y = M_end(); // Last node which is greater than k.

      while (x != 0)
      {
        if (M_impl.M_key_compare(k, S_key(x)))
        {
          y = x,
          x = S_left(x);
        }
        else
          x = S_right(x);
      }
      return const_iterator(y);
    }

    pair<iterator, iterator>
    equal_range(const key_type& k)
    { return pair<iterator, iterator>(lower_bound(k), upper_bound(k)); }

    pair<const_iterator, const_iterator>
    equal_range(const key_type& k) const
    { return pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k)); }
};

template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc>
bool
operator==(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
          const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{
  return x.size() == y.size()
      && ft::equal(x.begin(), x.end(), y.begin());
}

template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc>
bool
operator<(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
          const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{
  return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
}

template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc>
bool
operator!=(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
          const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{
  return !(x == y);
}

template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc>
bool
operator>(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
          const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{
  return y < x;
}

template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc>
bool
operator<=(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
          const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{
  return !(y < x);
}

template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc>
bool
operator>=(const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
          const Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{
  return !(x < y);
}

template <typename Key, typename Val, typename KeyOfValue,
          typename Compare, typename Alloc>
void
swap(Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& x,
    Rb_tree<Key, Val, KeyOfValue, Compare, Alloc>& y)
{ x.swap(y); }


} // ft
#endif // STL_TREE_H_