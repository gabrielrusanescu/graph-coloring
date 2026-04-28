Graph Coloring Greedy Algorithm
This project implements a Greedy Algorithm for graph coloring, written in C. The program assigns the minimum possible color to each vertex such that no two adjacent vertices share the same color, prioritizing nodes with higher degrees.

Features
Dynamic Memory Allocation: Efficiently handles graph structures based on input size.

Welsh-Powell Logic: Sorts nodes by their degree in descending order before coloring to optimize the number of colors used.

Validation: Uses assert statements to verify correctness against known test cases.

Algorithm Steps
Allocation: Load the graph from the file and allocate memory.

Sorting: Sort the nodes by their degree descending.

Coloring: For each node, check the colors of its neighbors and assign the smallest available positive color.

Cleanup: Free all dynamically allocated memory to prevent leaks.
