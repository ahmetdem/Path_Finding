#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <chrono>
#include "random.h"

class Timer
{
private:
    // Type aliases to make accessing nested type easier
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1> >;

    std::chrono::time_point<Clock> m_beg{ Clock::now() };

public:

    void reset()
    {
        m_beg = Clock::now();
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};


struct Node {
    int x, y;

    bool operator==(const Node& other) const {
        return x == other.x && y == other.y;
    }
};


namespace std {
    template <>
    struct hash<Node> {
        size_t operator()(const Node& node) const {
            return hash<int>()(node.x) ^ hash<int>()(node.y);
        }
    };
}


int h(Node n, Node goal) {
    return abs(n.x - goal.x) + abs(n.y - goal.y);
}

std::vector<Node> reconstruct_path(std::unordered_map<Node, Node>& came_from, Node current) {
    
    std::vector<Node> total_path;
    total_path.push_back(current);

    while (came_from.find(current) != came_from.end()) {
        current = came_from[current];
        total_path.push_back(current);
    }

    return total_path;
}


std::vector<Node> get_neighbors(Node node, std::vector<std::vector<int>>& grid, int ROWS = 200, int COLS = 200) {

    std::vector<Node> neighbors;


    if (node.x > 0 && grid[node.x - 1][node.y] != 1) {
        neighbors.push_back({node.x - 1, node.y});
    }
    if (node.x < ROWS - 1 && grid[node.x + 1][node.y] != 1) {
        neighbors.push_back({node.x + 1, node.y});
    }
    if (node.y > 0 && grid[node.x][node.y - 1] != 1) {
        neighbors.push_back({node.x, node.y - 1});
    }
    if (node.y < COLS - 1 && grid[node.x][node.y + 1] != 1) {
        neighbors.push_back({node.x, node.y + 1});
    }

    return neighbors;
}

std::vector<Node> A_star(Node start, Node goal, std::vector<std::vector<int>>& grid) {
    std::unordered_set<Node> open_set;
    open_set.insert(start);

    std::unordered_map<Node, Node> came_from;

    std::unordered_map<Node, int> g_score;
    g_score[start] = 0;

    std::unordered_map<Node, int> f_score;
    f_score[start] = h(start, goal);


    while (!open_set.empty()) {
        Node current = *std::min_element(open_set.begin(), open_set.end(), [&](const Node& a, const Node& b) {
            return f_score[a] < f_score[b];
        });

        if (current == goal) {
            return reconstruct_path(came_from, current);
        }

        open_set.erase(current);


        for (Node neighbor : get_neighbors(current, grid)) {
            int tentative_g_score = g_score[current] + 1;

            if (g_score.find(neighbor) == g_score.end() || tentative_g_score < g_score[neighbor]) {
                
                came_from[neighbor] = current;
                g_score[neighbor] = tentative_g_score;
                f_score[neighbor] = g_score[neighbor] + h(neighbor, goal);

                open_set.insert(neighbor);
            }
        }
    }
    return std::vector<Node>(); // No path found
}

std::vector<std::vector<int>> randomize_grid(int rows, int cols, int obstacle_percentage)
{
    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols, 0));

    // Set obstacles
    for (auto &&row : grid)
    {
        for (auto &&cell : row)
        {
            if (Random::get(1, 100) < obstacle_percentage) {
                cell = 1;
            }
        }
    }

    return grid;
}

int main() {

    Node start = {0, 0};  // Starting node at position (0, 0)
    Node goal = {199, 199};   // Goal node at position (9, 9)


    std::vector<std::vector<int>> grid { randomize_grid(200, 200, 20) };
    
    Timer T;
    std::vector<Node> path = A_star(start, goal, grid);
    std::cout << "Time elapsed in full program: " << T.elapsed() << " seconds" << std::endl;

    if (path.empty()) {
        std::cout << "No path found." << std::endl;
    }


    return 0;
}
