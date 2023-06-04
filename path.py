
def h(n, goal):
    """
    Calculates the heuristic value for the A* algorithm
    """
    return abs(n[0] - goal[0]) + abs(n[1] - goal[1])

def reconstruct_path(came_from, current):
    """
    Reconstructs the path from the start to the goal node
    """

    total_path = [current]

    while current in came_from:
        current = came_from[current]
        total_path.append(current)

    return total_path


def get_neighbors(node, grid, ROWS=25, COLS=25):
    """
    Returns a list of neighbors of the node
    """

    neighbors = []

    if node[0] > 0 and grid[node[0] - 1][node[1]] != 1:
        neighbors.append((node[0] - 1, node[1]))
    if node[0] < ROWS - 1 and grid[node[0] + 1][node[1]] != 1:
        neighbors.append((node[0] + 1, node[1]))
    if node[1] > 0 and grid[node[0]][node[1] - 1] != 1:
        neighbors.append((node[0], node[1] - 1))
    if node[1] < COLS - 1 and grid[node[0]][node[1] + 1] != 1:
        neighbors.append((node[0], node[1] + 1))

    return neighbors


def A_star(start, goal, grid, heuristic=h):
    """
    A* algorithm
    """

    open_set = {start} # set of nodes to be evaluated
    came_from = {}

    g_score = {start: 0}
    f_score = {start: heuristic(start, goal)}


    while open_set: # while open set is not empty
        current = min(open_set, key=lambda x: f_score[x]) # get the node with the lowest f score

        if current == goal:
            return reconstruct_path(came_from, current)
    
        open_set.remove(current)

        for neighbor in get_neighbors(current, grid):
            tentative_g_score = g_score[current] + 1

            if tentative_g_score < g_score.get(neighbor, float('inf')):
                came_from[neighbor] = current
                g_score[neighbor] = tentative_g_score

                f_score[neighbor] = g_score[neighbor] + heuristic(neighbor, goal)

                if neighbor not in open_set:
                    open_set.add(neighbor)
        
