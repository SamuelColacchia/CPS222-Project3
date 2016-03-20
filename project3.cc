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
}


void ThreadedBinarySearchTree::insert(string key, int value)
{
  if (_header == NULL)
  {
    // Special case - totally empty tree
    _header = new Node();
  }

  else
  {
    // Work down to a node without a child on the
    // appropriate side, then insert new node there
    bool inserted = false;
    Node *t = _header;

    while (!inserted)
    {
      if (key < t->_key)
      {
        if (t->_lchild == NULL)
        {
          t->_lchild = new Node();
          t->_key = key;
          t->_value = value;
          inserted = true;
        }
        else
        {
          t = t->_lchild;
        }
      }
      else
      if (t->_rchild == NULL)
      {
        t->_rchild = new Node();
        t->_key = key;
        t->_value = value;
        inserted = true;
      }
      else
      {
        t = t->_rchild;
      }
    }
  }
}


void ThreadedBinarySearchTree::erase(Iterator iter)
{ /* STUB - REPLACE WITH REAL CODE */
}


bool ThreadedBinarySearchTree::empty() const
{
  //Below shows how to access the child of node
  if (isThread(_header->_lchild) && (_header->_rchild == _header))
  {
    return true;
  }
  else
  {
    return false;
  }
}


Iterator ThreadedBinarySearchTree::lookup(string key) const
{ /* STUB - REPLACE WITH REAL CODE */
  return end();
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
{ /* STUB - REPLACE WITH REAL CODE */
  return *this;
}


Iterator& Iterator::presucc()
{ /* STUB - REPLACE WITH REAL CODE */
  return *this;
}


Iterator& Iterator::prepred()
{ /* STUB - REPLACE WITH REAL CODE */
  return *this;
}


Iterator& Iterator::postsucc()
{ /* STUB - REPLACE WITH REAL CODE */
  return *this;
}


Iterator& Iterator::postpred()
{ /* STUB - REPLACE WITH REAL CODE */
  return *this;
}


Iterator Iterator::parent() const
{ /* STUB - REPLACE WITH REAL CODE */
  return Iterator(_header, (Node *)_header, Iterator::UNDEFINED);
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
