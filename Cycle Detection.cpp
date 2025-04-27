#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

const int NODES = 6;
vector<vector<int>> graph(NODES + 1);
vector<bool> visited(NODES + 1, false);
vector<bool> recursionStack(NODES + 1, false);
vector<int> path;
vector<vector<int>> cycles;

void findCycles(int v) {
    if (visited[v]) return;

    visited[v] = true;
    recursionStack[v] = true;
    path.push_back(v);

    for (int neighbor : graph[v]) {
        if (!visited[neighbor]) {
            findCycles(neighbor);
        } else if (recursionStack[neighbor]) {
            // Cycle detected
            vector<int> cycle;
            auto it = find(path.begin(), path.end(), neighbor);
            if (it != path.end()) {
                cycle.assign(it, path.end());
                cycles.push_back(cycle);
            }
        }
    }

    recursionStack[v] = false;
    path.pop_back();
}

int main() {
    // Graph definition
    graph[1] = {2};
    graph[2] = {4};
    graph[3] = {1};
    graph[4] = {5,3,1};
    graph[5] = {3};

    // Find cycles starting from each unvisited node
    for (int i = 1; i <= NODES; ++i) {
        if (!visited[i]) {
            findCycles(i);
        }
    }

    // Remove duplicate cycles
    sort(cycles.begin(), cycles.end());
    cycles.erase(unique(cycles.begin(), cycles.end()), cycles.end());

    // Print all unique cycles
    cout << "All unique cycles found:" << endl;
    for (auto& cycle : cycles) {
        for (int node : cycle) {
            cout << node << " ";
        }
        cout << cycle[0]; // Complete the cycle
        cout << endl;
    }

    return 0;
}
