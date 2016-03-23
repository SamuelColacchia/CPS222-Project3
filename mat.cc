bool inserted = false;
if (_header == NULL)
{
  // Special case - totally empty tree
  _header = new Node();
}
else
{
  // Work down to a node without a child on the
  // appropriate side, then insert new node there

  Node *t = _header;
  cout << "enter while" << endl;
  int whilecounter = 0;
  while (inserted == false)
  {
    if (key < t->_key)
    {
      if (t->_lchild == NULL)
      {
        t->_lchild = new Node();
        t->_key = key;
        t->_value = value;
        inserted = true;
        cout << "option 1" << endl;
      }
      else
      {
        t = t->_lchild;
        cout << "option 2" << endl;
      }
    }
    else
    {
      if (t->_rchild == NULL)
      {
        t->_rchild = new Node();
        t->_key = key;
        t->_value = value;
        inserted = true;
        cout << "option 3" << endl;
      }
      else
      {
        t = t->_rchild;
        cout << "option 4" << endl;
      }
    }
    // cout << whilecounter++ << endl;
    // inserted = true;
  }
  cout << "left while" << endl;
}
