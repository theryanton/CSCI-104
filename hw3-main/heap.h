#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  void trickleUp (int);
  void trickleDown (int);
  std::vector<T> items;
  size_t size_ = 0; // size_t variable keeps track of # of elements in heap
  int num_ary; // number of possible child nodes per parent
  PComparator comp; // comparator returning true if first element is less than second
};


// Add implementation of member functions here
template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : num_ary(m), comp(c)
{}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap() {}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const 
{
  if (items.empty())
  {
    return true;
  }
  return false;
}


template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) 
{
  items.push_back(item);
  size_++;
  trickleUp(items.size()-1);
}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty!");
  }
  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return items.front();

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  if(empty()){
    // ================================
    // throw the appropriate exception
    // ================================
    throw std::underflow_error("Heap is empty!");
  }
  std::swap(items.front(), items.back());
  size_--;
  items.pop_back();
  trickleDown(0);
}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const
{
  return size_;
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleDown(int index) // max heap
{
  if (index * num_ary + 1 >= (int)size_)
  {
    return;
  }
  int leftChild = index * num_ary + 1; // start w/ left if right child exists
  int nextChild = leftChild;
  /*
  int rightChild = index * num_ary + num_ary; // so called big child that we must compare to every other object in heap
  for (int i = leftChild; i < (int)size_ && i < rightChild; i++)
  {
    int nextChild = i+1;
    if (comp(items[i], items[nextChild]))
    {
      nextChild = i;
    }
  }
  */
  for (int i=1; i<num_ary; i++)
  {
    if (nextChild + i < (int)size_) // iterate through # of possible children, swapping if right nodes are lesser than left
    {
      if (comp(items[nextChild + i], items[leftChild]))
      {
        leftChild = nextChild + i;
      }
    }
  }
  if (comp(items[leftChild], items[index])) // swap if parent node is lesser than child
  {
    std::swap(items[index], items[leftChild]);
    trickleDown(leftChild);
  }
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::trickleUp(int index) // min heap
{
  int parent = (index - 1)/num_ary; // minus one just in case for indexing
  while(parent >= 0 && comp(items[index], items[parent]))
  { 
    std::swap(items[parent], items[index]);
    index = parent;
    if (parent == 0) // base case, if we are at the top
    {
      return;
    }
    parent = (index - 1)/num_ary; // index - 1
  }
}

#endif

