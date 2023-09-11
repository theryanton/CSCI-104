Ryan Ton
CSCI 104 HW 3
rton@usc.edu

Included are the final implementations of a linked list pivot recursive algorithm, a templated stack,
a heap implementation supporting building both min/max heaps, and a circuit logic simulator.

To run linked list recursion, type "make", then "./llrec-test [input file]"

To test the stack implementation, my test file is included, compile "g++ -o stack_test stack.h stack_test.cpp",
and run the executable.

To test the logic simulator, navigate to the correct directory, type "make", then "./logicsim [txt file you want to test] > [new uml file]"
and use the provided java command "java -jar plantuml.jar [new uml file]" to create a new png image.