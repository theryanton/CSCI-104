#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "ulliststr.h"
using namespace std;

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::push_front(const std::string& val) // start from last, pushing elements up to first
{
  if (head_ == NULL)
  {
    Item *temp = new Item();
    head_ = tail_ = temp;
    temp->first = ARRSIZE - 1; // 9
    temp->last = ARRSIZE; // 10
    temp->val[temp->first] = val; // fill first index
    size_++;
  }
  else if (head_->first >= 0) // index can be 0-9
  {
    head_->first--;
    head_->val[head_->first] = val;
    size_++;
  }
  else // if node is filled up
  {
    Item *temp = new Item(); // create new node and set to head
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
    head_->first = ARRSIZE - 1;
    head_->last = ARRSIZE;
    head_->val[head_->first] = val; // fill first index in list
    head_->first--; // decrement first pointer
    size_++;
  }
}

void ULListStr::push_back(const std::string& val) // start from first, push elements back to last
{
  if (head_ == NULL)
  {
    Item *temp = new Item();
    head_ = tail_ = temp;
    temp->val[temp->first] = val;
    temp->last++;
    size_++;
  }
  else if (tail_->last != ARRSIZE) // if we haven't hit max array size (10 vals)
  {
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
  }
  else // if node is filled up
  {
    Item *temp = new Item(); // creating new item as new tail
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
    tail_->val[tail_->last] = val;
    tail_->last++;
    size_++;
  }
}

void ULListStr::pop_front()
{
  if (head_!=NULL)
  {
    if (head_->last - head_->first == 0) // empty list
    {
      if (head_ == tail_) // empty head node, only node in list so equal to tail
      {
        tail_ = NULL;
        delete head_;
        head_ = NULL;
      }
      else // empty head node
      {
        Item *temp = head_;
        head_ = head_->next;
        delete temp;
        head_->prev = NULL;
      }
    }
    else if (head_->last - head_->first == 1) // 1 element in list
    {
      Item *temp = head_;
      head_ = head_->next; // change head to next node
      head_->prev = NULL;
      delete temp; // delete previous head
    }
    else if (head_->last - head_->first > 1) // multiple elements in list
    {
      head_->first++;
    }
    size_--;
  }
  return; // return if list is empty
}

void ULListStr::pop_back()
{
  if (tail_ != NULL) // make sure tail exists
  {
    if (tail_->last - tail_->first == 0) // empty tail
    {
      if (head_ == tail_) // head/tail pointers point to same container, only node in list
      {
        head_ = NULL;
        delete tail_;
        tail_ = NULL;
      }
      else // empty tail node 
      {
        Item *temp = tail_;
        tail_ = tail_->prev;
        delete temp;
        tail_->next = NULL;
      }
    }
    else if (tail_->last - tail_->first == 1) // 1 element in list
    {
      Item *temp = tail_;
      tail_ = tail_->prev; // change tail to point to previous node
      tail_->next = NULL;
      delete temp; // delete previous empty tail
    }
    else if (tail_->last - tail_->first > 1) // multiple elements in list
    {
      tail_->last--;
    }
    size_--;
  }
  return; // return if list is empty
}

std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1]; // decrement by 1 as last points 1 index beyond
}

std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
  if (loc < 0) // edge case: negative index
  {
    return NULL;
  }
  if (loc >= size_) // if user inputs location that's out of list's slope
  {
    return NULL;
  }
  Item *temp = head_;
  size_t index = loc; // copy of loc value so we don't change val
  size_t diff = temp->last - temp->first; // amount of vals in list
  while (diff <= index)
  {
    index = index - diff; // index will continuously decrement until correct one is found
    temp = temp->next;
  }
  return &temp->val[index + temp->first]; // return val at index
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
