# PA-Tema2

## Cleaning
A Lee algorithm will be used to calculate all the minimum distances between the robots and dirty spaces and between the dirty spaces and dirty spaces. The vector of robots/dirty spots will be iterated and for every element, the shortest paths to each dirty spot will be calculated. A queue of pairs (row, column) will be used and all the positions in the directions up, left, down, right will be visited and have their distances updated if they are within bounds, are nt marked with an 'X' (unavailable) and have not been previously visited. At the end, all the distances to the dirty spots will be added into a matrix on the current element's respective row: [0 - (nrRobots - 1)] for robots, and [nrRobots - (nrRobots + nrDirtySpots - 1)]. Then, a backtracking algorithm will be used to generate all possible matrices, where one matrix contains on each line the path of one robot. The summed up lengths of each row will always be equal to the number of dirty spots. Then, for every row of this new matrix, all permutations will be generated in order to search for the lowest permutation sum. Then, out of all robots, the maximum such sum will be selected as the answer for this matrix. Finally, using a global variable, the minimum such answer out of all generated matrices will be selected.  
  
Time Complexity: O(nrRobots^2 * nrDirtySpots *(2^nrDirtySpots))

## Fortifications
A Dijkstra Algorithm will be used in order to calculate all the shortest distances to the nodes adjacent to the barbaric nodes (that appear before them in the graph, not after). A priority queue of pairs (node, distance) will be used and it will store pairs in ascending order based on the distances. If the queue is not empty, the top pair is extracted and the node's neighbours will have their distances updated. These nodes will be inserted in the queue only if they do not belong to barbarics. Then, for every node that corresponds to the barbarics and its edges, I calculate the sum of the distance to the edge's adjacent node and the cost between that node and the barbaric one and add it to a vector. Thus, a vector containing all possible distances to the barbaric nodes will be created. At first, I tried using a multiset instead of a vector, and by adding the difference between the second and first elemnt to the set's first element (if it was in the limit bounds), I could make sure the set would always keep the minimum element at the top at all times, which would be the result in the end. But I noticed that many tests were failing. In order to fix this, I used a binary search, imposing a limit on the minimum time and maximizing the distances to the barbarics. The distance vector will be iterated, and if an element has a lower value than the proposed limit, then the difference between the limit and the distance will be added to a sum. If this sum exceeds the number of forts k, then it means there aren't enough forts in order to have the proposed limit as the new shortest path to a barbaric. So, the binary search continues to the left because the limit must have a lower value. Otherwise, the search continues to the right, because alll the distances to the barbarics should be maximized.  

Time Complexity: O(n * log m), n = nr nodes that are not barbarics, m = edges not containing barbarics

## Beamdrone
For this task, I used a BFS/Lee algorithm. At every step, a pair of (node, previous direction) is inserted in the queue. The previous direction is important in order to determine the cost of the next movement. If the previous direction doesn't change, the cost for it is 0. For every perpendicular move, the cost is 1, but if the next move is opposite of the previous one, the cost is 0. In order to update the distance to the next position, a check is conducted first in order to verify if it falls within the matrix limits. For a lower calculated distance, the next position'signify distance will be updated and a new pair contining the next direction will be added to the queue.  

Time Complexity: O(m * n)

## Races
While reading the input, a previous line vector is being kept and the elements from the current line are compared by column. A variable is used to signify if the two elements on the previous column are equal, and if so, the two nodes (if different values) on the current column will form an edge and will be added to an adjacency list. Then, I will use a topological sorting algorithm based on DFS. The nodes will be added one by one in a vector starting from the last position and if a node is not visited, a DFS will be applied to its neighbours. If all neighbours are already visited, the node will be added in the sorted vector.  

Time Complexity: O(n + m)