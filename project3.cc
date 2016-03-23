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

/*
* Destructor for the program called when the user enters q
* Ensures all nodes are deleted
* If done correctly we are a good steward of nodes
*/
ThreadedBinarySearchTree::~ThreadedBinarySearchTree()
{
  //Adam and Dr Tuck
  Iterator it;
  Node *tempnode;

  for (it = this->inorder_begin(); it != this->end(); it++)
  {
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
{
  // if (empty())
  // {
  //         return end();
  // }
  // else
  // {
  //         Node *tempnode;
  //         Node *parent = this->parent()._ptr;
  //         Iterator it;
  //         for (iter = this->inorder_begin(); iter != this->end(); it++)
  //         {
  //                 if (key == iter._ptr->_key)
  //                 {
  //                         tempnode = iter._ptr;
  //
  //                         if(!isThread(tempnode->_rchild) && isThread(tempnode->_lchild))
  //                                 delete iter._ptr;
  //                         else if (isThread(tempnode->_rchild) && !isThread(tempnode->_lchild))
  //                                 delete iter._ptr;
  //                         else if(isThread(tempnode->_rchild) && isThread(tempnode->_lchild))
  //                                 delete iter._ptr;
  //                         else
  //                                 delete iter._ptr;
  //
  //                 }
  //         }
  //         return end();
  // }
  //return end();
}


/*
 * Test to see if the function is empty()
 *
 * RETURN-true: if the header is the only node
 * RETURN-false: if there is atleast one node and the header
 */
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


/*
 * Lookup function called when the user enter l
 * PARAM-key: the string used to determine tree position
 * RETURN-iterator: at the desired node based on key
 */
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


//indorder traversal
Iterator& Iterator::insucc()
{
  //check if the rchild is a thread
  if (isThread(_ptr->_rchild))
  {
    // if so make a pointer to rchild
    _ptr = makePointer(_ptr->_rchild);
  }
  else
  {             //if its a pinter, follow rchild
    _ptr = _ptr->_rchild;
    //while lchild isnt a thread, follow down to bottom
    while (!isThread(_ptr->_lchild))
    {
      _ptr = _ptr->_lchild;
    }
  }
  //return current pointer
  return *this;
}


//indorder reversed traversal
Iterator& Iterator::inpred()
{
  //check if the lchild is a thread
  if (isThread(_ptr->_lchild))
  {
    // if so make a pointer to lchild
    _ptr = makePointer(_ptr->_lchild);
  }
  else
  {
    //if its a pinter, follow lchild
    _ptr = _ptr->_lchild;
    //while rchild isnt a thread, follow down to bottom
    while (!isThread(_ptr->_rchild))
    {
      _ptr = _ptr->_rchild;
    }
  }
  return *this;
}


//preorder traversal
Iterator& Iterator::presucc()
{
  //if lchild is a pointer follow lchild
  if (!isThread(_ptr->_lchild))
  {
    _ptr = _ptr->_lchild;
  }
  //if rchild is a pointer follow rchild
  else if (!isThread(_ptr->_rchild))
  {
    _ptr = _ptr->_rchild;
  }
  else
  {
    //while rchild is a thread, make a pointer of rchild then follow it to its rchild
    while (isThread(_ptr->_rchild))
    {
      _ptr = makePointer(_ptr->_rchild);
    }
    //go to the rchild of the current pointer
    _ptr = _ptr->_rchild;
  }
  return *this;
}


//preorder reverse traversal
Iterator& Iterator::prepred()
{
  //create a node for the parent
  Node *parent = this->parent()._ptr;

  //if pointer is the parent of the left child
  if (_ptr == parent->_lchild)
  {
    //move to the parent node
    _ptr = parent;
  }
  //if the pointer is the rchild, and there is not lchild
  else if ((_ptr == parent->_rchild) && isThread(parent->_lchild))
  {
    // make pointer to the parent
    _ptr = makePointer(parent);
  }
  else
  {
    // if the pointer is the rchild
    if (parent->_rchild == _ptr)
    {
      //go to the lchild of the parent
      _ptr = parent->_lchild;
    }
    //while there is a lchild is or lchild
    while (!isThread(_ptr->_lchild) || !isThread(_ptr->_rchild))
    {
      // if ther is a rchild, go the the rchild
      if (!isThread(_ptr->_rchild))
      {
        _ptr = _ptr->_rchild;
      }
      //if there is a lchild go to the lchild
      else
      {
        _ptr = _ptr->_lchild;
      }
    }
  }
  return *this;
}


//post order
Iterator& Iterator::postsucc()
{
  //create a node that points to the parent
  Node *parent = this->parent()._ptr;
  //create a boool checking for number of siblings
  bool onechild;

  //if pointer is a lchild of the header
  if (_ptr == _header->_lchild)
  {
    //create a node for the header then return
    _ptr = (Node *)_header;
    return *this;
  }
  //if pointer is the header  go the the lchild
  if (_ptr == _header)
  {
    _ptr = _ptr->_lchild;
  }

  //if there is no lchild but there is a rchild
  if (isThread(parent->_lchild) && !isThread(parent->_rchild))
  {
    //set onechild to true
    onechild = true;
  }
  //if there is no rchild but there is a lchild
  else if (isThread(parent->_rchild) && !isThread(parent->_lchild))
  {
    //set onchild to true
    onechild = true;
  }
  else
  {
    // if it has two children set onechild to false
    onechild = false;
  }

  //if the pointer is the rchild or the only child, and if it is not the header
  if (((_ptr == parent->_rchild) || onechild) && (parent != _header))
  {
    // make the parent the pointer
    _ptr = parent;
  }
  else
  {
    // if it has two children and the parent is not the header
    if (!onechild && (parent != _header))
    {
      // go to the rchild
      _ptr = parent->_rchild;
    }
    // while there is a lchild or a rchild
    while (!isThread(_ptr->_lchild) || !isThread(_ptr->_rchild))
    {
      //if there is a lchild go to the child
      if (!isThread(_ptr->_lchild))
      {
        _ptr = _ptr->_lchild;
      }
      //else if there is a r child, go to the r child
      else if (!isThread(_ptr->_rchild))
      {
        _ptr = _ptr->_rchild;
      }
    }
  }
  return *this;
}


//reverse post traversal
Iterator& Iterator::postpred()
{
  //if pointer is the header, go to the lchild
  if (_ptr == _header)
  {
    _ptr = _ptr->_lchild;
  }
  //else if there is a rchild, go to the r child
  else if (!isThread(_ptr->_rchild))
  {
    _ptr = _ptr->_rchild;
  }
  //else if there is a lchild go to the lchild
  else if (!isThread(_ptr->_lchild))
  {
    _ptr = _ptr->_lchild;
  }
  //if there is no children
  else
  {             //follwo the lchild thread to lchild is a pointer
    while (isThread(_ptr->_lchild))
    {
      _ptr = makePointer(_ptr->_lchild);
    }
    //if the pointer is the header, return
    if (_ptr == _header)
    {
      return *this;
    }
    //else go to the lchild
    else
    {
      _ptr = _ptr->_lchild;
    }
  }
  return *this;
}


//find the parent of the pointer
Iterator Iterator::parent() const
{
  bool found = false;
  //create a new node pointed to the header
  Node *tempnode = (Node *)_header;

  while (!found)
  {
    //if lchild is a pointer  and the key is greater then the childs key
    if (!isThread(tempnode->_lchild) && (key() == tempnode->_lchild->_key))
    {
      //return the pointer
      return Iterator(_header, tempnode, Iterator::UNDEFINED);
    }
    //if there is a rchild and the key is equal to the rchild's key
    else if (!isThread(tempnode->_rchild) && (key() == tempnode->_rchild->_key))
    {
      //return the pointer
      return Iterator(_header, tempnode, Iterator::UNDEFINED);
    }
    else
    {
      //if the node is the header
      if (tempnode == _header)
      {
        //go to the lchild
        tempnode = tempnode->_lchild;
      }
      //if the key is greater the current pointers node
      else if (key() > tempnode->_key)
      {
        //go to the rchild
        tempnode = tempnode->_rchild;
      }

      //if the key is less then the current nodes key
      else if (key() < tempnode->_key)
      {
        //go to the lchild
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
