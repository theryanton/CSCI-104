#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap(Node<Key,Value>* n1, Node<Key,Value>* n2);

    // Add helper functions here
    bool BalanceHelper(Node<Key, Value> *root) const;
    int calculateHeight(Node<Key, Value> *root) const;
    void clearSubtree(Node<Key, Value>* root);


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    current_ = NULL;
}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (this->current_ == rhs.current_)
    {
      return true;
    }
    return false;
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (this->current_ == rhs.current_)
    {
      return false;
    }
    return true;
}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO    
    if (current_->getRight() == NULL) // iterate via left chain
    {
      Node<Key, Value> *parent = current_->getParent();
      while (parent != NULL && current_ == parent->getRight())
      {
        current_ = parent;
        parent = parent->getParent();
      }
      current_ = parent;
    }
    else if (current_->getRight() != NULL) // just go down right pathway until reaching last right
    {
      current_ = current_->getRight();
      while (current_->getLeft() != NULL) //check if left pathway exists
      {
        current_ = current_->getLeft();
      }
    }
    return *this;
}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
   clear();
}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO

    /* To insert an item walk the tree (go left if value is less than node, 
    right if greater than node) until you find an empty location, at which point 
    you insert the new value
    */
    if (root_ == NULL)
    {
      root_ = new Node<Key, Value> (keyValuePair.first, keyValuePair.second, NULL);
    }
    else // tree has nodes inside currently
    {
      Node<Key, Value>* curr = root_; // pointer we'll use to iterate thru tree
      Node<Key, Value>* prev = root_; // pointer used to track inserted node's parent
      // iterate down tree look for leaf node
      while (curr != NULL)
      {
        prev = curr; // used to determine correct placement
        if (curr->getKey() == keyValuePair.first)
        {
          curr->setValue(keyValuePair.second); // node already in tree, replace value with new one
          return;
        }
        else if (curr->getKey() < keyValuePair.first) //value of what we insert is greater than current node
        {
          curr = curr->getRight();
        }
        else if (curr->getKey() > keyValuePair.first) //value of what we insert is less than current node
        {
          curr = curr->getLeft();
        }
      }
      // check if inserted node fulfills bst nature
      if (prev->getKey() < keyValuePair.first) // inserted node's value is greater than parent's, should go on right
      {
        prev->setRight(new Node <Key, Value>(keyValuePair.first, keyValuePair.second, prev)); // new right child
      }
      else if (prev->getKey() > keyValuePair.first) // inserted node's value is less than parent's
      {
        prev->setLeft(new Node <Key, Value>(keyValuePair.first, keyValuePair.second, prev)); // new right child
      }
    }
    return;
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO
    // set parent's child to null to avoid bad access issues
    /*First find the value to remove by walking the tree
    0 children: If the value is in a leaf node, simply remove that leaf node 
    1 child: Promote the child into the node's location
    2 children: Swap the value with its in-order successor 
    or predecessor and then remove from its new location
    */

    Node<Key, Value>* curr = internalFind(key); // call internalFind to find val to remove
    if (curr == NULL)
    {
      return; // node not in tree
    }
    if (curr->getLeft() != NULL && curr->getRight() != NULL)
    {
      nodeSwap(predecessor(curr), curr);
      remove(curr->getKey());
    }
    Node<Key, Value>* currChild = NULL; // keeps track of children when swapping to set
    if (curr->getLeft() != NULL || curr->getRight() != NULL)
    {
      if (curr->getLeft() != NULL) // 1 left child, promote child to deleted node's location
      {
        currChild = curr->getLeft();
      }
      else
      {
        currChild = curr->getRight();
      }
    }
    if (curr->getParent() != NULL)
    {
      if (curr->getParent()->getLeft() == curr)
      {
        curr->getParent()->setLeft(currChild);
      }
      else
      {
        curr->getParent()->setRight(currChild);
      }
    }
    else
    {
      this->root_ = currChild;
    }
    if (currChild != NULL)
    {
      currChild->setParent(curr->getParent());
    }
    delete curr;
}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (current->getLeft() != NULL) // left child exists, predecessor is the right most node of the left subtree
    {
      current = current->getLeft(); // go all the way down to leftmost node
      while (current->getRight() != NULL) // go all the way to right most child
      {
        current = current->getRight();
      }
    }
    else
    {
      while (current->getParent() != NULL && current == current->getParent()->getLeft()) // walkup the ancestor chain until you traverse the first right child pointer
      {
        current = current->getParent();
      }
    }
    return current;
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
    clearSubtree(this->root_);
    root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearSubtree(Node<Key, Value>* root)
{
  if (root == NULL) // base case
  {
    return;
  }
  clearSubtree(root->getLeft()); // recursively calls function until hitting null
  clearSubtree(root->getRight());
  root->setParent(NULL);
  root->setLeft(NULL);
  root->setRight(NULL);
  delete root;
}

/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    if (root_ == NULL) // base case
    {
      return NULL;
    }
    Node<Key, Value> *curr = root_; // pointer used to iterate thru tree
    while (curr->getLeft() != NULL) // in bst, if a node is less than its parent, always on left
    {
      curr = curr->getLeft();
    }
    return curr;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    if (root_ == NULL) // empty tree
    {
      return NULL;
    }
    Node<Key, Value>* temp = root_;
    while (temp != NULL)
    {
      if (temp->getKey() == key)
      {
        return temp;
      }
      else if (temp->getKey() > key) 
      {
        temp = temp->getLeft();
      }
      else if (temp->getKey() < key)
      {
        temp = temp->getRight();
      }
    }
    return NULL;
}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    return BalanceHelper(root_);
}

template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::BalanceHelper(Node<Key, Value>* root) const
{
  if (root == NULL)
  {
    return true;
  }

  int lDepth = calculateHeight(root->getLeft());
  int rDepth = calculateHeight(root->getRight());

  if (std::abs(lDepth - rDepth) <= 1 && BalanceHelper(root->getLeft()) && BalanceHelper(root->getRight()))
  {
    return true;
  }
  return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::calculateHeight(Node<Key, Value> *root) const
{
  if (root == NULL) 
  {
    return 0;
  }
  return 1 + std::max(BalanceHelper(root->getLeft()), BalanceHelper(root->getRight()));
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
