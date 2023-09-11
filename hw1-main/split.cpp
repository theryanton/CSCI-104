/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>
#include <iostream>
using namespace std;

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  if (in == NULL) // empty list
  {
    return;
  }
  else
  {
    Node *temp = in; // temp pointer to head of list
    if (in->value %2 == 0)
    {
      if (in->next == NULL) // edge case: if reached end of linked list, set pointer of evens list' next element to null
      {
        evens->next = NULL;
      }
      evens = temp; // add element to evens
      split(temp->next,odds,evens->next); // move onto next node in original linked list, iterate evens
    }
    else // odds
    {
      if (in->next == NULL)
      {
        odds->next = NULL;
      }
      odds = temp;
      split(temp->next,odds->next,evens);
    }
  }
}

/* If you needed a helper function, write it here */
// WRITE YOUR CODE HERE