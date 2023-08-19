Algorithms to Solve 8-Puzlze.

1.Astar.cpp it uses the A * search algorithm to solve the puzzle. this algorithm is able to solve the most complex puzzles and at a considerably fast rate than the traditional algorithms i.e Breadth-first-search and Depth-first-search.

2.BFS.cpp it uses the Breadth-First-Search algorithm to solve the puzzle. this algorithm is able to solve some puzzles intermediate and easy puzzles but it fails or rather takes alot of time and memory to solve the complex puzzles compared to A star search algorithm. 

3.DFS.cpp it uses the Depth-First-Search algorithm to solve the puzzle. this algorithm is able to solve easy puzzles but when it comes to intermediate and complex puzzles it takes alot of time and memory compared to the Breadth-First-search algorithm.

4.DIA.cpp it uses the Deepening iterative A star search to solve the puzzle. this algorithm is an extension of the A star search algorithm. Its disadvatange is that it is memeory-intensive and often can become inefficient for more complex and larger puzzle but it uses the threshold limiter which limits it from exploring too deep but compared to the traditional A star search it very slow.

5.We the Conclude that even though BFS and DFS are commmonly used to solve puzzle problems it is much better and time saving to use the A * search algorithm since it uses some sophisticated heuristics instead of BFS and DFS which simply rely on exploring the nodes till it arrives to some form of conculsion. This has been an amazing project has helped me understand algorithms better and efficiency that is why i even chose to use C++ so that i could learn to use  better memory management techniques.

This is the end of this project :) .

# Time Complexities

# A Star search Algorithm
   The time complexity of this algorithm is primarily determined by the A* search algorithm, which is used to find the solution to the 8-puzzle problem. Let's break down the main components that contribute to the time complexity:

1. Generating Valid Moves:
   - The `generateMoves` function generates all possible moves (up, down, left, and right) from the current board state. It iterates over the board's dimensions, which is a 3x3 grid in this case. Therefore, this part has a time complexity of O(N^2), where N is the size of the board (in this case, N = 3).

2. A* Search:
   - The A* search algorithm involves a priority queue (min-heap) where nodes are inserted and removed based on their estimated cost (f value). The worst-case time complexity of the A* search depends on the branching factor (average number of successors for each node) and the depth of the solution.
   - In the worst case, A* may explore all possible states before finding a solution. However, with a good heuristic (like the Manhattan distance), the actual time complexity is often much better than the worst case.
   - The heuristic function (Manhattan distance) is applied to each node, which involves iterating through the board's dimensions (N^2 operations) to calculate the distance.
   - The time complexity of A* can be approximated as O(b^d), where b is the branching factor and d is the depth of the solution.

3. Other Operations:
   - Other operations, such as inserting nodes into the tree and printing the solution path, are generally not the dominant factors in the time complexity.

In summary, the time complexity of this algorithm is influenced by the A* search algorithm, and it can be roughly estimated as O(b^d), where 'b' depends on the puzzle and 'd' is the depth of the solution. The actual performance may vary depending on the specific puzzle instances and the quality of the heuristic function. For a 3x3 puzzle like the 8-puzzle, it tends to perform reasonably well in practice.

 # Breadth first search Algorithm

 The time complexity of this algorithm mainly depends on the breadth-first search (BFS) algorithm used to solve the puzzle. Let's analyze the key components that contribute to the time complexity:

1. Generating Valid Moves:
   - The `generateMoves` function generates all possible moves (up, down, left, and right) from the current board state. It iterates over the board's dimensions, which is a 3x3 grid in this case. Therefore, this part has a time complexity of O(N^2), where N is the size of the board (in this case, N = 3).

2. BFS:
   - In the worst case, BFS may explore all possible states before finding a solution. The time complexity of BFS is O(b^d), where 'b' is the branching factor (average number of successors for each node) and 'd' is the depth of the solution.
   - In this particular implementation, BFS uses a queue to explore nodes in a breadth-first manner, ensuring that it explores all nodes at the current depth before moving to the next depth level.

3. Other Operations:
   - Other operations, such as inserting nodes into the tree, printing the solution path, and checking the goal state, do not significantly affect the overall time complexity compared to the BFS.

In summary, the time complexity of this algorithm can be approximated as O(b^d), where 'b' depends on the puzzle, and 'd' represents the depth of the solution. BFS is guaranteed to find the shortest path to the solution, but the actual performance may vary depending on the specific puzzle instances and the order in which states are explored. For a 3x3 puzzle like the 8-puzzle, BFS typically performs reasonably well in practice.

# Depth first search Algorithm

The time complexity of this algorithm is exponential and can be expressed as O(b^d), where 'b' represents the branching factor (the number of possible moves at each state), and 'd' represents the depth of the solution.

Here's why:

1. **Depth-First Search (DFS):** This algorithm uses depth-first search to explore the state space. In the worst case, DFS could explore all possible states before finding a solution. This worst-case scenario occurs when the goal state is located deep in the search tree.

2. **Branching Factor (b):** The branching factor 'b' represents the average number of successors for each state. In your case, 'b' is determined by the number of valid moves (UP, DOWN, LEFT, RIGHT) from each state. For an 8-puzzle, 'b' can be as high as 4, as there are typically four possible moves from each state.

3. **Depth (d):** The depth 'd' represents how deep the goal state is in the search tree. In the worst case, 'd' can be as large as the number of states in the state space, which can be quite large for puzzles like the 8-puzzle.

Since DFS explores the search tree depth-first and may explore all possible states before finding a solution, the time complexity is exponential and can grow rapidly as 'd' and 'b' increase. In practice, the performance may vary depending on the specific puzzle instances and the order in which states are explored. In the worst case, DFS can be very slow for puzzles with a high branching factor or deep solution paths.

# Deepening A star search Algorothm

The time complexity of the Iterative Deepening A* (IDA*) search algorithm in this code can be described as follows:

- The code uses a variation of the A* search algorithm, which is guided by the Manhattan distance heuristic.
- In the IDA* loop, the threshold for each iteration is increased until a solution is found. This threshold starts from an initial value and increases with each iteration.

Let's break down the time complexity:

1. **Generating Initial State:** Converting the input puzzle state into a 2D vector and creating the initial `startNode` and `goalNode` takes O(N^2) time, where N is the size of the puzzle (3 in this case).

2. **IDA* Search Loop:** The code uses an iterative deepening loop to gradually increase the threshold until a solution is found. In each iteration of this loop, an A* search is performed with the given threshold.

   - The worst-case time complexity of A* search with a Manhattan distance heuristic is O(b^d), where 'b' is the effective branching factor (the average number of successors per node) and 'd' is the depth of the solution. In this case, 'b' depends on the number of valid moves from each state, which can be up to 4.
   - The depth 'd' represents the depth of the solution path.
   - The threshold starts from an initial value (the Manhattan distance between the start and goal states) and increases by 1 in each iteration.

3. **Heuristic Calculations:** Calculating the Manhattan distances between nodes and the goal state (for both the start and current states) has a time complexity of O(N^2), where N is the size of the puzzle.

4. **Generating Neighbor Nodes:** Generating the neighbor nodes for the current node also depends on the number of valid moves (up to 4) and requires copying the puzzle board, which has a time complexity of O(N^2).

Given these considerations, the overall time complexity of the IDA* search algorithm in this code is approximately O(b^d * N^2), where 'b' is the branching factor, 'd' is the depth of the solution, and 'N' is the size of the puzzle (3 in this case).

Please note that the actual performance of the algorithm can vary depending on factors such as the specific puzzle instance and the order in which states are explored. In practice, IDA* is often efficient for solving 8-puzzle and similar problems.
