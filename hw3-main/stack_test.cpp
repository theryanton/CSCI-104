#include "stack.h"
#include <iostream>
using namespace std;

int main()
{
  Stack<int> stacking;
  cout<< "Pushing: "<<endl;
  stacking.push(2);
  cout << "2" << endl;
  stacking.push(4);
  cout << "4" << endl;
  stacking.push(6);
  cout << "6" << endl;
  cout << "Size: " <<stacking.size() << endl;
  cout<<"Pop: "<<endl;
  while(!stacking.empty())
  {
    cout<<stacking.top()<<endl;
    stacking.pop();
  }
  cout << "Size: " <<stacking.size() << endl;
  /*
  cout << "Pop: " << endl;
  stacking.pop(); // pop empty stack
  */
  return 0;
}