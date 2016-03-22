//TODO add stuff here

#include "project3.h"
#include <iomanip>
using namespace std;

/*
 * Methods of class ThreadedBinarySearchTree
 *
 */

typedef ThreadedBinarySearchTree::Iterator Iterator;

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
        Node * tempnode;
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

        if (isThread(root->_lchild))
        {
                Node *newnode = new Node();

                newnode->_lchild = root->_lchild;
                newnode->_rchild = makeThread(root);
                makePointer(root->_lchild);
                root->_lchild = newnode;

                newnode->_value = value;
                newnode->_key = key;
        }
        else if (isThread(root->_rchild))
        {
                Node *newnode = new Node();

                newnode->_lchild = makeThread(root);
                newnode->_rchild = root->_rchild;
                makePointer(root->_lchild);
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

/*
Iterator ThreadedBinarySearchTree::lookup(string key) const
{


        Node *newnode = new Node();
        newnode = ThreadedBinarySearchTree::lookupr(key,  _header->_lchild );
        return end();
}


void ThreadedBinarySearchTree::lookupr(String key, Node *& root )
{

        if (empty())
                return NULL;
        else if (key == root->_key)
                return root;
        else if (key > root->_key)
                lookupr(key,_root->_lchild);
        else
                lookupr(key,_root->_rchild);
}

*/

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
                   Order order)
        : _header(header), _ptr(ptr), _order(order)
{
}


// ostream operator << is in a separate file
