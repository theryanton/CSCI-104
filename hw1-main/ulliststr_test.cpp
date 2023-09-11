/* Write your test code for the ULListStr in this file */

#include <iostream>
using namespace std;
#include "ulliststr.h"

int main(int argc, char* argv[])
{

  ULListStr dat;
  dat.pop_front(); // returns for empty list
  dat.pop_back();
  cout << "Empty list check completed, adding values now" << endl;

  cout << "Pushing back" << endl; // pushing 11 values, meaning there's multiple nodes
  dat.push_back("0");
  dat.push_back("1");
  dat.push_back("2");
  dat.push_back("3");
  dat.push_back("4");
  dat.push_back("5");
  dat.push_back("6");
  dat.push_back("7");
  dat.push_back("8");
  dat.push_back("9");
  dat.push_back("10");
  for (unsigned int i=0; i<dat.size(); i++)
  {
    cout << dat.get(i) << " ";
  }
  cout << endl;
  cout << "Front: " << dat.front() << endl; // test front
  cout << "Back: " << dat.back() << endl; // test back
  cout << "Count prior to pop: " << dat.size() << endl; 
  dat.pop_back(); // pop 5 values
  dat.pop_back();
  dat.pop_back();
  dat.pop_back();
  dat.pop_back();
  for (unsigned int i=0; i<dat.size(); i++)
  {
    cout << dat.get(i) << " ";
  }
  cout << endl;
  cout << "Front: " << dat.front() << endl;
  cout << "Back: " << dat.back() << endl;
  cout << "Count post-pop back: " << dat.size() << endl; // pop 5 elements
  cout << "Pushing front" << endl;
  dat.push_front("1");
  dat.push_front("2");
  dat.push_front("3");
  dat.push_front("4");
  dat.push_front("5");
  dat.push_front("6");
  dat.push_front("7");
  for (unsigned int i=0; i<dat.size(); i++)
  {
    cout << dat.get(i) << " ";
  }
  cout << endl;
  cout << "Front: " << dat.front() << endl;
  cout << "Back: " << dat.back() << endl;
  cout << "Count prior to pop: " << dat.size() << endl;
  dat.pop_front();
  dat.pop_front();
  dat.pop_front();
  dat.pop_front();
  for (unsigned int i=0; i<dat.size(); i++)
  {
    cout << dat.get(i) << " ";
  }
  cout << endl;
  cout << "Front: " << dat.front() << endl;
  cout << "Back: " << dat.back() << endl;
  cout << "Count post-pop front: " << dat.size() << endl;
  return 0;
}