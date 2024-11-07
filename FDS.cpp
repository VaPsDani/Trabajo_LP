#include "FDS.h"
#include "raylib.h"
#include <vector>
#include <queue>
#include <cmath>
#include <iostream>
#include <algorithm>

struct Node {
    int x, y;
    int totalCost, heuristic;
    Node* backPointer;
    std::string status;

    Node(int x, int y) : x(x), y(y), totalCost(INT_MAX), heuristic(INT_MAX), backPointer(nullptr), status("NEW") {}
    
    bool operator>(const Node& other) const {
        return heuristic > other.heuristic;
    }
};

struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return *a > *b;
    }
};

int heuristic(Node* node, Node* goal) {
    return std::abs(node->x - goal->x) + std::abs(node->y - goal->y);
}

std::vector<Node*> getNeighbors(Node* node, std::vector<std::vector<Node*>>& grid, int R, int C) {
    std::vector<Node*> neighbors;
    int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
    
    for (auto& dir : directions) {
        int nx = node->x + dir[0];
        int ny = node->y + dir[1];
        
        if (nx >= 0 && nx < R && ny >= 0 && ny < C && grid[nx][ny] != nullptr) {
            neighbors.push_back(grid[nx][ny]);
        }
    }
    
    return neighbors;
}

std::vector<std::pair<int, int>> constructPath(Node* goal) {
    std::vector<std::pair<int, int>> path;
    Node* current = goal;
    
    while (current != nullptr) {
        path.emplace_back(current->x, current->y);
        current = current->backPointer;
    }
    
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::pair<int, int>> FDS(int ix, int iy, int fx, int fy, int R, int C, int cellStates[20][20]) {
    // Check starting and goal positions
    if (ix < 0 || ix >= R || iy < 0 || iy >= C || fx < 0 || fx >= R || fy < 0 || fy >= C) {
        std::cerr << "Start or goal position out of bounds." << std::endl;
        return {};
    }

    // Create grid of nodes, avoiding obstacles
    std::vector<std::vector<Node*>> grid(R, std::vector<Node*>(C, nullptr));
    for (int x = 0; x < R; ++x) {
        for (int y = 0; y < C; ++y) {
            if (cellStates[x][y]!=1) { // Assuming 0 means walkable
                grid[x][y] = new Node(x, y);
            }
        }
    }

    Node* start = grid[ix][iy];
    Node* goal = grid[fx][fy];

    // Ensure start and goal nodes are not obstacles
    if (!start || !goal) {
        std::cerr << "Start or goal node is an obstacle." << std::endl;
        // Cleanup allocated nodes before returning
        for (auto& row : grid) {
            for (auto& node : row) {
                delete node; // Freeing allocated memory
            }
        }
        return {};
    }

    start->totalCost = 0;
    start->heuristic = heuristic(start, goal);
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> openList;
    openList.push(start);

    while (!openList.empty()) {
        Node* current = openList.top();
        openList.pop();
        
        if (current == goal) {
            auto path = constructPath(goal);
            // Cleanup allocated nodes
            for (auto& row : grid) {
                for (auto& node : row) {
                    delete node; // Freeing allocated memory
                }
            }
            return path;
        }

        current->status = "CLOSED";
        for (Node* neighbor : getNeighbors(current, grid, R, C)) {
            if (neighbor->status == "CLOSED") continue;
            
            int newCost = current->totalCost + 1;
            if (neighbor->status == "NEW" || newCost < neighbor->totalCost) {
                neighbor->totalCost = newCost;
                neighbor->heuristic = newCost + heuristic(neighbor, goal);
                neighbor->backPointer = current;

                if (neighbor->status == "NEW") {
                    neighbor->status = "OPEN";
                    openList.push(neighbor);
                } else {
                    // Re-insert the neighbor to update its priority
                    openList.push(neighbor);
                }
            }
        }
    }

    // Cleanup allocated nodes before returning
    for (auto& row : grid) {
        for (auto& node : row) {
            delete node; // Freeing allocated memory
        }
    }

    std::cerr << "No path found." << std::endl;
    return {};
}
