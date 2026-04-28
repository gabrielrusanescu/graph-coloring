Graph Coloring Greedy Algorithm
This project implements a Greedy Algorithm for graph coloring, written in C. The program assigns the minimum possible color to each vertex such that no two adjacent vertices share the same color, prioritizing nodes with higher degrees.

Features
Dynamic Memory Allocation: Efficiently handles graph structures based on input size.

Welsh-Powell Logic: Sorts nodes by their degree in descending order before coloring to optimize the number of colors used.

Validation: Uses assert statements to verify correctness against known test cases.

Input File Format
The program reads from text files (e.g., input1.txt). The structure should be:

An integer representing the total number of nodes (n).

For each node: the node ID, its degree, and the IDs of its neighbors.

Example:

Plaintext
3
1 2 2 3
2 1 1
3 1 1
Technical Details
Data Structures
The graph is represented using a custom Node structure:

id: Unique identifier for the node.

degree: Number of edges connected to the node.

color: The assigned color index (initializes at -1).

neighbors: An array of integers storing neighbor IDs.

Algorithm Steps
Allocation: Load the graph from the file and allocate memory.

Sorting: Sort the nodes by their degree descending.

Coloring: For each node, check the colors of its neighbors and assign the smallest available positive color.

Cleanup: Free all dynamically allocated memory to prevent leaks.
