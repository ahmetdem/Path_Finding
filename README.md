# A* Pathfinding Algorithm in Python and C++.

This repository contains a Python implementation of the A* algorithm for pathfinding. The A* algorithm is a popular search algorithm used to find the shortest path between two points in a graph or grid.

## Features

- A* algorithm implementation in Python and C++.
- Support for grid-based pathfinding problems.
- Customizable heuristic function for estimating the cost.
- Returns the shortest path from a start node to a goal node.


## Algorithm 

Typical implementations of A* use a priority queue to perform the repeated selection of minimum (estimated) cost nodes to expand. This priority queue is known as the open set, fringe or frontier. At each step of the algorithm, the node with the lowest f(x) value is removed from the queue, the f and g values of its neighbors are updated accordingly, and these neighbors are added to the queue. The algorithm continues until a removed node (thus the node with the lowest f value out of all fringe nodes) is a goal node.b The f value of that goal is then also the cost of the shortest path, since h at the goal is zero in an admissible heuristic.
