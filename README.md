puzzle:
The homework is to judge whether two puzzles can be fully merged on a three by three grid. The two puzzles are one immovable puzzle and one movable puzzle. 
To merge these two puzzles, you can only rotate(90, 180, 270 degrees clockwise or counterclockwise) or translate (up, down, left, or right) the movable puzzle. 
Two puzzles may not be able to fully merged. 

stack:
1. Objective
Romeo and Juliet want to meet each other, but Count Paris sets up a maze to prevent them. Please implement a program to help Romeo and Juliet have a reunion. Let them live happily ever after.
2. Task Direction
First, Romeo and Juliet are at the initial position. Second, your program drives them and follows the rules to explore the given maze.
Finally, terminate your program according to the termination conditions and output the moving path of them.
3. Maze Specification
➢ Size: 2 × 101 × 101 (a 2-story 101 by 101 maze space including
walls)
➢ Direction: X-axis, Y-axis, and Z-axis.
➢ Initial position:
Romeo: (0,1,1) ( i.e., 1F position (1,1) )
Juliet: (1,99,99) ( i.e., 2F position (99,99) )
➢ Symbol representation
X: a wall
․: a road
O: a stair
4. Walk Rules
➢ Romeo: start from (0,1,1) and stop at (1,99,99) of the maze, and it
walks according to the rule that Upstairs > Right > Down > Up > Left. Additionally, Romeo will not go downstairs when he has already gone upstairs.
➢ Juliet: start from (1,99,99) and stop at (0,1,1) of the maze, and it walks according to the rule that Downstairs > Left > Up > Down
> Right. Additionally, Juliet will not go upstairs when she has already gone downstairs.
➢ Romeo goes one step further before Juliet goes one step.
➢ The road traveled will not be visited again unless there is no way to go, which avoids the infinite loop.
➢ The stair is a portal, that is, when somebody reaches the stair, goes straight up or down one floor.
Example:
The position of the stair is (0,2,3). When Romeo reaches the stair, his position directly becomes (1,2,3). In other words, going upstairs does not require an extra step.
5. Termination Condition:
➢ They meet each other.
➢ One of them arrives at its destination first.
For example:
Romeo : (0,1,1) → (0,2,1) → … → (1,99,99)
Juliet : (1,99,99) → (1,99,98) → … → (0,23,55)
The program is terminated since Romeo arrives at its destination first.

linked_list:
An article always has some repeated words. You are required to replace the repeated words with numbers. Thus, you need to create a linked list to store the words in the article. The word which does not appear in the linked list is stored in the head of the linked list. If the word has appeared in the linked list, you need to replace the word in the article by the current index of the word in the linked list.
Subsequently, the word is moved to the head of the linked list. You should notice the following three rules, and Figure 1 shows the example of the rules.
(1) Index value starts to increase from 1.
(2) You need to process the case-sensitive words which are different such as ‘Sun’ and ‘sun’.
(3) Special characters cannot be added to the linked list such as comma and period.

BST1:
Implement a Binary Search Tree with linked lists
A binary search tree (BST) is a sorted tree structure where each node has two children. The left node always needs to contain a value smaller than the parent and the right node always needs to contain a value equal or greater than the parent.
In this assignment, you need to implement a BST structure for storing integer numbers and provide the following functions:
- printInfixOrder() prints the whole tree in infix order (from left to right)
- printLevelOrder() prints the whole tree in level order (from up to down)
To help you getting started with this assignment, here is a piece of code you can use. It is the code for a node in a tree. The node can contain two child nodes, left and right.

BST2:
Treasure Hunter
The function of treasure hunter is very similar to Part one. In addition to implementing a BST, you need to implement a treasure hunter function to look for coins on the tree. The scenario is described as follows:
The treasure hunter who goes into the maze is represented by a binary search tree for finding the coins. The treasure hunter follows the BST to go into the maze and pass through the nodes which store the amount of coins. When passing the nodes, the treasure hunter collects the coins. The objective of the treasure hunter is to collect the maximum coins.
In this part of assignment, you are given a map file to construct the maze. The format of file is shown as follows. Each line contains a node number and the amount of coins.
Insert each number sequentially into the binary search tree with its corresponding amount of coins.

graph:
Given a set of points Q on a road network, an optimal meeting point (OMP) query returns the point on a road network G = (V, E) with the smallest sum of network
distances to all the points in Q.
Consider your team need to find a location for gathering. There are N members of the team (Team ID:1~N). You need to decide the meeting place with the smallest sum of distances to all the members. The total cost is defined as the total distance from everyone to the the meeting point. 

quick_sort:
Please write a program that can read data from a standard input (stdin). In this program, you are asked to read multiple input data from a given file. The quick sort algorithm uses a divide and conquer strategy. First, it selects the first number as the pivot. Second, it moves all the smaller elements to the left of the array and moves all the larger elements to the right of the array. Repeat the above procedure until the whole array is sorted.

selection_sort:
Please write a program that can read data from a standard input (stdin). In this program, you are asked to read multiple input data from a given file. The selection sort algorithm searches the whole array for the smallest element. First, the data is divided into two parts, sorted and unsorted. Suppose you want to put n data at the beginning is unsorted. At this time, the minimum value of n unsorted data is taken out and placed at the end of the sorted data, that is, it is exchanged with the first data, and the array result is printed. The procedure stops until there is no unsorted data.

minimum_gap
Please write a program that can read data from a standard input (stdin). In this program, you are asked to read multiple input data from a given file. Given an unsorted input data, find the minimum difference between the elements after you complete the sort.
Note: you have to use merge sort to sort the input elements from small to large, and you need to output the procedure and the minimum gap.
