Ryan Ton
rton@usc.edu
CSCI 104

This code contains files designed to take an ordered linked list and split into 2
separate linked lists, each odd and even. In addition, there is also a program designed
to create an unrolled linked list, each node holding an array of string values and contains 
functions that can push/pop nodes from the front/back, print out values at front/back,
and output values at a specific location.

To compile split: 
g++ -g -Wall -std=c++11 -c split.cpp
g++ -g -Wall -std=c++11 split_test.cpp split.cpp -o split

To compile ulliststr:
g++ -g -Wall ulliststr.cpp ulliststr_test.cpp -o ulliststr_test
