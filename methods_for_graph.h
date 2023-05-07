#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#include "graph.h"


using namespace std;
void Graph::DepthFirstSearch(int start_node) const {
    vector<bool> visited(adjacency_matrix.size(), false);
    stack<int> nodes_to_visit;
    nodes_to_visit.push(start_node);
    while (!nodes_to_visit.empty()) {
        int current_node = nodes_to_visit.top();
        nodes_to_visit.pop();
        if (!visited[current_node]) {
            cout << current_node << " ";
            visited[current_node] = true;
            for (int neighbor = 0; neighbor < adjacency_matrix[current_node].size(); neighbor++) {
                if (adjacency_matrix[current_node][neighbor] == 1 && !visited[neighbor]) {
                    nodes_to_visit.push(neighbor);
                }
            }
        }

    }
    cout << endl;
}
void Graph::AddNode() {
    adjacency_matrix.push_back(vector<int>(adjacency_matrix.size()));
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        adjacency_matrix[i].push_back(0);
    }
    incidence_matrix.push_back(vector<int>(incidence_matrix[0].size(), 0));
}

void Graph::AddArc(int v1, int v2) {
    adjacency_matrix[v1][v2] = 1;
    adjacency_matrix[v2][v1] = 1;
    size_t new_node_index = incidence_matrix[0].size();
    for (int i = 0; i < incidence_matrix.size(); i++) {
        if (i == v1) {
            incidence_matrix[i].push_back(1);
        }
        else if (i == v2) {
            incidence_matrix[i].push_back(-1);
        }
        else {
            incidence_matrix[i].push_back(0);
        }
    }
}

void Graph::PrintAdjacencyMatrix() const {
    cout << "Adjacency Matrix:" << endl;
    cout <<"   ";
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        cout << i<< "  ";
    }
    cout << endl;
    cout << "  ";
    for (int i = 0; i < adjacency_matrix[0].size(); i++) {
        cout << "___";
    }
    cout << endl;
    for (int i = 0; i < adjacency_matrix.size(); i++) {
        cout << i << "|";
        for (int j = 0; j < adjacency_matrix[i].size(); j++) {
            cout << setw(2) << adjacency_matrix[i][j] << "|";
        }
        cout << endl;
    }
    cout << endl;
}

void Graph::PrintIncidenceMatrix() const {
    cout << "Incidence Matrix:" << endl;
    cout << "  ";
    for (int i = 0; i < incidence_matrix[0].size(); i++) {
        cout << "e" << i << " ";
    }
    cout << endl;
    cout << "  ";
    for (int i = 0; i<incidence_matrix[0].size(); i++) {
        cout << "___";
    }
    cout << endl;
    for (int i = 0; i < incidence_matrix.size(); i++) {
        cout << i << "|";
        for (int j = 0; j < incidence_matrix[i].size(); j++) {
            cout << setw(2) << incidence_matrix[i][j] << "|";
        }
        cout << endl;
    }
    cout << endl;
}
