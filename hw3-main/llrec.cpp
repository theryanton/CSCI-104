#include "llrec.h"

//*********************************************
// Provide your implementation of llpivot below
//*********************************************


void llpivot(Node *&head, Node *&smaller, Node *&larger, int pivot) // pivot = 7
{
  if (head == NULL)
  {
    smaller = NULL;
    larger = NULL;
    return;
  }
  llpivot(head->next, smaller, larger, pivot); //iterate to next node, 
  if (head->val <= pivot)
  {
    head->next = smaller;
    smaller = head; // set temp small to node
    head = NULL; // set head to null
  }
  else if (head->val > pivot)
  {
    head->next = larger;
    larger = head; // set temp larger to node
    head = NULL; // set head to null
  }
}