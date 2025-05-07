#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

const int NODES = 9;
vector<vector<int>> graph(NODES + 1);
vector<bool> recursionStack(NODES + 1, false);
vector<int> path;
set<vector<int>> cycles;

char toChar(int node) {
    return 'A' + node - 1;
}

void findCycles(int start, int v) {
    recursionStack[v] = true;
    path.push_back(v);

    for (int neighbor : graph[v]) {
        if (neighbor == start) {
            // A cycle is found
            vector<int> cycle = path;
            // Normalize the cycle to start from the smallest node
            auto it = min_element(cycle.begin(), cycle.end());
            rotate(cycle.begin(), it, cycle.end());
            cycles.insert(cycle);
        } else if (!recursionStack[neighbor]) {
            findCycles(start, neighbor);
        }
    }

    recursionStack[v] = false;
    path.pop_back();
}

int main() {

    graph[1] = {2};
    graph[2] = {5};
    graph[3] = {2};
    graph[4] = {1, 7};
    graph[5] = {4, 6, 8};
    graph[6] = {3, 9};
    graph[7] = {5};
    graph[8] = {6, 7};
    graph[9] = {8};

    // Find cycles starting from each unvisited node
    for (int i = 1; i <= NODES; i++) {
        findCycles(i, i);
    }

    // Print all unique cycles (using alphabets)
    cout << "All unique cycles found:" << endl;
    for (const auto& cycle : cycles) {
        for (int node : cycle) {
            cout << toChar(node) << " ";
        }
        cout << toChar(cycle[0]); // Complete the cycle
        cout << endl;
    }

    return 0;
}
