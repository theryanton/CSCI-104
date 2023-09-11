#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void insertFix (AVLNode<Key, Value>* p, AVLNode<Key, Value>* n);
    virtual void rotateLeft (AVLNode<Key, Value>* n);
    virtual void rotateRight (AVLNode<Key, Value>* n);
    virtual void removeFix (AVLNode<Key, Value>* n, int diff);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO
    if (this->root_ == NULL) // if empty tree, set new node n as root, b(n) = 0
    {
        AVLNode<Key, Value>* n = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        n->setBalance(0);
        this->root_ = n;
        return;
    }
    else
    {
        AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_); // using pointer to walk tree
        while (curr != NULL) // should always be true as root cannot equal null at this point
        {
          if (new_item.first > curr->getKey())
          {
            if (curr->getRight() != NULL)
            {
              curr = curr->getRight();
            }
            else
            {
              AVLNode<Key, Value>* n = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
              curr->setRight(n);
              n->setBalance(0);
              //If b(p) was -1, then b(p) = 0. Done!
              if (curr->getBalance() == -1)
              {
                curr->setBalance(0);
              }
              else if (curr->getBalance() == 1) // If b(p) was +1, then b(p) = 0. Done!
              {
                curr->setBalance(0);
              }
              else if (curr->getBalance() == 0) // If b(p) was 0, then update b(p) and call insert-fix(p, n)
              {
                curr->setBalance(1);
                insertFix(curr, n);
              }
              return;
            }
          }
          else if (new_item.first < curr->getKey())
          {
            if (curr->getLeft() != NULL) 
            {
              curr = curr->getLeft(); 
            }
            else 
            {
              AVLNode<Key, Value>* n = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
              curr->setLeft(n);
              n->setBalance(0);
              //If b(p) was -1, then b(p) = 0. Done!
              if (curr->getBalance() == -1)
              {
                curr->setBalance(0);
              }
              else if (curr->getBalance() == 1) // If b(p) was +1, then b(p) = 0. Done!
              {
                curr->setBalance(0);
              }
              else if (curr->getBalance() == 0) // If b(p) was 0, then update b(p) and call insert-fix(p, n)
              {
                curr->setBalance(-1);
                insertFix(curr, n);
              }
              return;
            }
          }
          else if (new_item.first == curr->getKey())
          {
            curr->setValue(new_item.second);
            return;
          }
        }
    }
}

/* Helper function that automatically balances AVL tree when inserting 
 * new nodes via rotate helper functions
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix (AVLNode<Key, Value>* p, AVLNode<Key, Value>* n)
{
  if (p == NULL || p->getParent() == NULL)
  {
    return;
  }
  AVLNode<Key, Value>* g = p->getParent(); // Let g = parent(p)
  if (g->getLeft() == p)
  {
    g->updateBalance(-1);
    if (g->getBalance() == 0) // case 1, return
    {
      return;
    }
    else if (g->getBalance() == -1) // case 2, recurse insertFix()
    {
      insertFix(g, p);
    }
    else if (g->getBalance() == -2) 
    {
      if (p->getLeft() == n) //if zig zig
      {
        rotateRight(g); //rotate right g
        p->setBalance(0);
        g->setBalance(0);
      }
      else if (p->getRight() == n) // if zig zag
      {
        rotateLeft(p);
        rotateRight(g);
        if (n->getBalance() == -1) // subcases via slides
        {
          p->setBalance(0);
          g->setBalance(1);
          n->setBalance(0);
        }
        else if (n->getBalance() == 0)
        {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        else if (n->getBalance() == 1)
        {
          p->setBalance(-1);
          g->setBalance(0);
          n->setBalance(0);
        }
      }
    }
  }
  else if (g->getRight() == p) // for right child, swap left/right, +/-
  {
    g->updateBalance(1);
    if (g->getBalance() == 0)
    {
      return;
    }
    else if (g->getBalance() == 1)
    {
      insertFix(g, p);
    }
    else if (g->getBalance() == 2)
    {
      if (p->getRight() == n)
      {
        rotateLeft(g);
        p->setBalance(0);
        g->setBalance(0);
      }
      else if (p->getLeft() == n)
      {
        rotateRight(p);
        rotateLeft(g);
        if (n->getBalance() == 1)
        {
          p->setBalance(0);
          g->setBalance(-1);
          n->setBalance(0);
        }
        else if (n->getBalance() == 0)
        {
          p->setBalance(0);
          g->setBalance(0);
          n->setBalance(0);
        }
        else if (n->getBalance() == -1)
        {
          p->setBalance(1);
          g->setBalance(0);
          n->setBalance(0);
        }
      }
    }
  }
}

// Takes right child, makes it the new parent, takes original parent, makes it new right child
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value> *n)
{
  if (n->getRight() == NULL) // no right child, so rotating left not possible
  {
    return;
  }

  AVLNode<Key, Value>* nParent = n->getParent();
  AVLNode<Key, Value>* nRight = n->getRight();
  n->setRight(nRight->getLeft());
  if (n->getParent() == NULL)
  {
    this->root_ = nRight;
  }
  else if (n->getParent()->getLeft() == n)
  {
    nParent->setLeft(nRight);
  }
  else
  {
    nParent->setRight(nRight);
  }
  n->setParent(nRight);
  nRight->setParent(nParent);
  nRight->setLeft(n);
  if (n->getRight() != NULL)
  {
    n->getRight()->setParent(n);
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key, Value> *n)
{
  if (n->getLeft() == NULL) // no right child, so rotating left not possible
  {
    return;
  }

  AVLNode<Key, Value>* nParent = n->getParent();
  AVLNode<Key, Value>* nLeft = n->getLeft();
  n->setLeft(nLeft->getRight()); // fix pointers?
  if (n->getParent() == NULL)
  {
    this->root_ = nLeft;
  }
  else if (n->getParent()->getLeft() == n)
  {
    nParent->setLeft(nLeft);
  }
  else
  {
    nParent->setRight(nLeft);
  }
  n->setParent(nLeft);
  nLeft->setParent(nParent);
  nLeft->setRight(n);
  if (n->getLeft() != NULL)
  {
    n->getLeft()->setParent(n);
  }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(key));
    if (curr == NULL)
    {
      return;
    }
    if (curr->getLeft() != NULL && curr->getRight() != NULL)
    {
      nodeSwap(static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(curr)), curr);
    }
    AVLNode<Key, Value>* currParent = curr->getParent();
    AVLNode<Key, Value>* currChild = NULL; // similar operation to bst remove, pointer keeps track of its children when swapping node
    int diff = 0;

    if (curr->getLeft() == NULL && curr->getRight() == NULL)
    {
      currChild = NULL; // no children
    }
    if (curr->getLeft() != NULL || curr->getRight() != NULL)
    {
      if (curr->getLeft() != NULL)
      {
        currChild = curr->getLeft();
      }
      else
      {
        currChild = curr->getRight();
      }
    }
    
    if (currParent == NULL)
    {
      this->root_ = currChild;
    }
    else if (currParent != NULL)
    {
      if (curr->getParent()->getLeft() == curr)
      {
        diff = 1;
        currParent->setLeft(currChild);
      }
      else if (curr->getParent()->getRight() == curr)
      {
        diff = -1;
        currParent->setRight(currChild);
      }
    }
    if (currChild != NULL)
    {
      currChild->setParent(currParent);
    }
    delete curr; // delete curr
    removeFix(currParent, diff); // call removeFix to patch tree
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix (AVLNode<Key, Value>* n, int diff)
{
  if (n == NULL)
  {
    return;
  }
  AVLNode<Key, Value>* p = n->getParent();
  int ndiff = 0;
  if (p != NULL)
  {
    if (p->getLeft() == n)
    {
      ndiff = 1;
    }
    else if (p->getRight() == n)
    {
      ndiff = -1;
    }
  }
  if (diff == -1)
  {
    if (n->getBalance() + diff == -2) // case 1
    {
      AVLNode<Key, Value>* c = n->getLeft();
      if (c->getBalance() == -1) // case 1a: zig zig
      {
        rotateRight(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      else if (c->getBalance() == 0) // 1b: zig zig
      {
        rotateRight(n);
        n->setBalance(-1);
        c->setBalance(1);
      }
      else if (c->getBalance() == 1) // 1c: zig zag
      {
        AVLNode<Key, Value>* g = c->getRight();
        rotateLeft(c);
        rotateRight(n);
        if (g->getBalance() == 1)
        {
          n->setBalance(0);
          c->setBalance(-1);
          g->setBalance(0);
        }
        else if (g->getBalance() == 0)
        {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if (g->getBalance() == -1)
        {
          n->setBalance(1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    else if (n->getBalance() + diff == -1)//case 2
    {
      n->setBalance(-1);
    }
    else if (n->getBalance() + diff == 0)
    {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
  else if (diff == 1) // mirror approach from diff = -1
  {
    if (n->getBalance() + diff == 2) // case 1
    {
      AVLNode<Key, Value>* c = n->getRight();
      if (c->getBalance() == 1) // case 1a: zig zig
      {
        rotateLeft(n);
        n->setBalance(0);
        c->setBalance(0);
        removeFix(p, ndiff);
      }
      else if (c->getBalance() == 0) // 1b: zig zig
      {
        rotateLeft(n);
        n->setBalance(1);
        c->setBalance(-1);
      }
      else if (c->getBalance() == -1) // 1c: zig zag
      {
        AVLNode<Key, Value>* g = c->getLeft();
        rotateRight(c);
        rotateLeft(n);
        if (g->getBalance() == -1)
        {
          n->setBalance(0);
          c->setBalance(1);
          g->setBalance(0);
        }
        else if (g->getBalance() == 0)
        {
          n->setBalance(0);
          c->setBalance(0);
          g->setBalance(0);
        }
        else if (g->getBalance() == 1)
        {
          n->setBalance(-1);
          c->setBalance(0);
          g->setBalance(0);
        }
        removeFix(p, ndiff);
      }
    }
    else if (n->getBalance() + diff == 1)//case 2
    {
      n->setBalance(1);
    }
    else if (n->getBalance() + diff == 0)
    {
      n->setBalance(0);
      removeFix(p, ndiff);
    }
  }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
