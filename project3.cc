//TODO add stuff here

#include "project3.h"
#include <iomanip>
using namespace std;

/*
 * Methods of class ThreadedBinarySearchTree
 *
 */

typedef ThreadedBinarySearchTree::Iterator   Iterator;

ThreadedBinarySearchTree::ThreadedBinarySearchTree()
  : _header(new  Node())
{
  _header->_lchild = makeThread(_header);
  _header->_rchild = _header;
}


ThreadedBinarySearchTree::~ThreadedBinarySearchTree()
{
  //Adam and Dr Tuck
  Iterator it;
  Node *tempnode;

  for (it = this->inorder_begin(); it != this->end(); it++)
  {
    //temp node = to pointer

    tempnode = it._ptr;

    delete it._ptr;
  }
  // delete pointer;

  delete _header;
}


/*
 * Insert function called when the user calls i in the program
 * PARAM-key: the string used to determine tree position
 * PARAM-value: value that for the node
 */
void ThreadedBinarySearchTree::insert(string key, int value)
{
  //Deal with the case that are first item is the header
  if (empty())
  {
    Node *newnode = new Node();
    _header->_lchild = newnode;

    newnode->_lchild = makeThread(_header);
    newnode->_rchild = makeThread(_header);
    newnode->_value = value;
    newnode->_key = key;
  }
  else
  {
    ThreadedBinarySearchTree::insertr(key, value, _header->_lchild);
  }
}


/*
 * Recursive insertion called by insert()
 * PARAM-key: the string used to determine tree position
 * PARAM-value: value that for the node
 * PARAM-root: the starting node for each recursion
 */
void ThreadedBinarySearchTree::insertr(string key, int value, Node *& root)
{
  if (isThread(root->_lchild) && (key < root->_key))
  {
    Node *newnode = new Node();

    newnode->_lchild = root->_lchild;
    newnode->_rchild = makeThread(root);

    root->_lchild = newnode;

    newnode->_value = value;
    newnode->_key = key;
  }
  else if (isThread(root->_rchild) && (key > root->_key))
  {
    Node *newnode = new Node();

    newnode->_lchild = makeThread(root);
    newnode->_rchild = root->_rchild;

    root->_rchild = newnode;

    newnode->_value = value;
    newnode->_key = key;
  }
  else
  {
    if (key > root->_key)
    {
      insertr(key, value, root->_rchild);
    }

    else if (key < root->_key)
    {
      insertr(key, value, root->_lchild);
    }
  }
}


void ThreadedBinarySearchTree::erase(Iterator iter)
{ /* STUB - REPLACE WITH REAL CODE */
}


//NOTE | TESTED and works as intended
bool ThreadedBinarySearchTree::empty() const
{
  if (makePointer(_header->_lchild) == _header)
  {
    return true;
  }
  else
  {
    return false;
  }
}


Iterator ThreadedBinarySearchTree::lookup(string key) const
{
  if (empty())
  {
    return end();
  }
  else
  {
    Iterator it;
    for (it = this->inorder_begin(); it != this->end(); it++)
    {
      if (key == it._ptr->_key)
      {
        return it;
      }
    }
    return end();
  }

//        ThreadedBinarySearchTree::lookupr(key, _header);
}


Iterator ThreadedBinarySearchTree::inorder_begin() const
{
  return Iterator(_header, _header, Iterator::INORDER).insucc();
}


Iterator ThreadedBinarySearchTree::inorder_rbegin() const
{
  return Iterator(_header, _header, Iterator::INORDER).inpred();
}


Iterator ThreadedBinarySearchTree::preorder_begin() const
{
  return Iterator(_header, _header, Iterator::PREORDER).presucc();
}


Iterator ThreadedBinarySearchTree::preorder_rbegin() const
{
  return Iterator(_header, _header, Iterator::PREORDER).prepred();
}


Iterator ThreadedBinarySearchTree::postorder_begin() const
{
  return Iterator(_header, _header, Iterator::POSTORDER).postsucc();
}


Iterator ThreadedBinarySearchTree::postorder_rbegin() const
{
  return Iterator(_header, _header, Iterator::POSTORDER).postpred();
}


Iterator ThreadedBinarySearchTree::end() const
{
  return Iterator(_header, _header, Iterator::UNDEFINED);
}


/*
 * Thread manipulation methods
 *
 */

#define THREAD_FLAG_MASK    0x8000000000000000

bool ThreadedBinarySearchTree::isThread(Node *ptr)
{
  return (((long)ptr) & THREAD_FLAG_MASK) != 0;
}


ThreadedBinarySearchTree::Node *ThreadedBinarySearchTree::makeThread(Node *ptr)
{
  return (Node *)(((long)ptr) | THREAD_FLAG_MASK);
}


ThreadedBinarySearchTree::Node *ThreadedBinarySearchTree::makePointer(Node *thread)
{
  return (Node *)(((long)thread) & ~THREAD_FLAG_MASK);
}


/*
 * Methods of class ThreadedBinarySearchTree::Iterator
 *
 */

Iterator::Iterator()
  : _header(NULL), _ptr(NULL), _order(UNDEFINED)
{
}


Iterator& Iterator::operator ++()
{
  switch (_order)
  {
  case INORDER:
    return insucc();

  case PREORDER:
    return presucc();

  case POSTORDER:
    return postsucc();

  default:
    return *this;
  }
}


Iterator& Iterator::operator --()
{
  switch (_order)
  {
  case INORDER:
    return inpred();

  case PREORDER:
    return prepred();

  case POSTORDER:
    return postpred();

  default:
    return *this;
  }
}


Iterator Iterator::operator ++(int)
{
  Iterator result = *this;

  operator ++();
  return result;
}


Iterator Iterator::operator --(int)
{
  Iterator result = *this;

  operator --();
  return result;
}


//NOTE | Untested
Iterator& Iterator::insucc()
{
  if (isThread(_ptr->_rchild))
  {
    _ptr = makePointer(_ptr->_rchild);
  }
  else
  {
    _ptr = _ptr->_rchild;
    while (!isThread(_ptr->_lchild))
    {
      _ptr = _ptr->_lchild;
    }
  }
  return *this;
}


Iterator& Iterator::inpred()
{
  if (isThread(_ptr->_lchild))
  {
    _ptr = makePointer(_ptr->_lchild);
  }
  else
  {
    _ptr = _ptr->_lchild;
    while (!isThread(_ptr->_rchild))
    {
      _ptr = _ptr->_rchild;
    }
  }
  return *this;
}


//close but getting a core dump error in the else statment
Iterator& Iterator::presucc()
{
  if (!isThread(_ptr->_lchild))
  {
    _ptr = _ptr->_lchild;
  }

  else if (!isThread(_ptr->_rchild))
  {
    _ptr = _ptr->_rchild;
  }
  else
  {
    while (isThread(_ptr->_rchild))
    {
      _ptr = makePointer(_ptr->_rchild);
    }
    _ptr = _ptr->_rchild;
  }
  return *this;
}


Iterator& Iterator::prepred()
{
  Node *parent = this->parent()._ptr;

  if (_ptr == parent->_lchild)
  {
    _ptr = parent;
  }

  else if ((_ptr == parent->_rchild) && isThread(parent->_lchild))
  {
    _ptr = makePointer(parent);
  }
  else
  {
    if (parent->_rchild == _ptr)
    {
      _ptr = parent->_lchild;
    }

    while (!isThread(_ptr->_lchild) || !isThread(_ptr->_rchild))
    {
      if (!isThread(_ptr->_rchild))
      {
        _ptr = _ptr->_rchild;
      }
      else
      {
        _ptr = _ptr->_lchild;
      }
    }
  }
  return *this;
}


Iterator& Iterator::postsucc()
{
  Node *parent = this->parent()._ptr;

  bool onechild;

  if (_ptr == _header->_lchild)
  {
    _ptr = (Node *)_header;
    return *this;
  }
  if (_ptr == _header)
  {
    _ptr = _ptr->_lchild;
  }


  if (isThread(parent->_lchild) && !isThread(parent->_rchild))
  {
    onechild = true;
  }
  else if (isThread(parent->_rchild) && !isThread(parent->_lchild))
  {
    onechild = true;
  }
  else
  {
    onechild = false;
  }


  if (((_ptr == parent->_rchild) || onechild) && (parent != _header))
  {
    _ptr = parent;
  }
  else
  {
    if (!onechild && (parent != _header))
    {
      _ptr = parent->_rchild;
    }
    while (!isThread(_ptr->_lchild) || !isThread(_ptr->_rchild))
    {
      if (!isThread(_ptr->_lchild))
      {
        _ptr = _ptr->_lchild;
      }
      else if (!isThread(_ptr->_rchild))
      {
        _ptr = _ptr->_rchild;
      }
    }
  }
  return *this;
}


Iterator& Iterator::postpred()
{
  if (_ptr == _header)
  {
    _ptr = _ptr->_lchild;
  }

  else if (!isThread(_ptr->_rchild))
  {
    _ptr = _ptr->_rchild;
  }

  else if (!isThread(_ptr->_lchild))
  {
    _ptr = _ptr->_lchild;
  }

  else
  {
    while (isThread(_ptr->_lchild))
    {
      _ptr = makePointer(_ptr->_lchild);
    }
    if (_ptr == _header)
    {
      return *this;
    }
    else
    {
      _ptr = _ptr->_lchild;
    }
  }
  return *this;
}


Iterator Iterator::parent() const
{
  bool found = false;
  Node *tempnode = (Node *)_header;

  while (!found)
  {
    if (!isThread(tempnode->_lchild) && (key() == tempnode->_lchild->_key))
    {
      return Iterator(_header, tempnode, Iterator::UNDEFINED);
    }
    else if (!isThread(tempnode->_rchild) && (key() == tempnode->_rchild->_key))
    {
      return Iterator(_header, tempnode, Iterator::UNDEFINED);
    }
    else
    {
      if (tempnode == _header)
      {
        tempnode = tempnode->_lchild;
      }
      else if (key() > tempnode->_key)
      {
        tempnode = tempnode->_rchild;
      }

      else if (key() < tempnode->_key)
      {
        tempnode = tempnode->_lchild;
      }
    }
  }
}


string Iterator::key() const
{
  return _ptr->_key;
}


int Iterator::value() const
{
  return _ptr->_value;
}


bool Iterator::operator ==(const Iterator& other) const
{
  return _ptr == other._ptr && _ptr != NULL;
}


bool Iterator::operator !=(const Iterator& other) const
{
  return _ptr != other._ptr || _ptr == NULL;
}


Iterator::Iterator(const Node *header,
                   Node       *ptr,
                   Order      order)
  : _header(header), _ptr(ptr), _order(order)
{
}


// ostream operator << is in a separate file
