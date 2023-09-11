#include "split.h"
#include <cstddef>
#include <iostream>
using namespace std;

int main (){
  Node *head;
  head = new Node(0, NULL);
  Node* temp = head;
  for (int i=1; i<=10; i++)
  {
    Node* tail = new Node(i, NULL);
    temp->next = tail;
    temp = tail;
  }
  Node *odd, *even;
  odd = NULL;
  even = NULL;
  split(head,odd,even);
  Node *tempodd, *tempeven;
  tempodd = odd; // used to keep track of head of separated arrays
  tempeven = even;
  while (tempodd != NULL)
  {
    cout << tempodd->value << endl;
    tempodd = tempodd->next;
  }
  while (tempeven != NULL)
  {
    cout << tempeven->value << endl;
    tempeven = tempeven->next;
  }
  while (odd !=NULL) //delete memory associated before moving to next node
  {
    Node *temp;
    temp = odd;
    odd = odd->next;
    delete temp;
    //odd = odd->next;
  }
  while (even !=NULL) //delete memory associated before moving to next node
  {
    Node *temp;
    temp = even;
    even = even->next;
    delete temp;
    //even = even->next;
  }
  return 0;
}
