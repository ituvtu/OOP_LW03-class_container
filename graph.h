#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include <iomanip>
#ifndef GRAPH_H
#define GRAPH_H

using namespace std;
class GraphElement {
public:
    virtual void print() const = 0;
    virtual ~GraphElement() {}
};

class GraphArc : public GraphElement {
public:
    GraphArc(int from, int to) : from_(from), to_(to) {}
    void print() const override {
        std::cout << "Arc from " << from_ << " to " << to_ << std::endl;
    }
    int from() const { return from_; }
    int to() const { return to_; }
private:
    int from_, to_;
};

class GraphNode : public GraphElement {
public:
    GraphNode(int id) : id_(id) {}
    void print() const override {
        std::cout << "Node " << id_ << std::endl;
    }
    int id() const { return id_; }
private:
    int id_;
};

class Graph {
public:
    Graph(int num_nodes = 0) : adjacency_matrix(num_nodes, vector<int>(num_nodes)), incidence_matrix(num_nodes, vector<int>()) {}

    void AddNode();
    void AddArc(int v1, int v2);
    void PrintAdjacencyMatrix() const;
    void PrintIncidenceMatrix() const;
    void DepthFirstSearch(int start_node) const;


private:
    vector<vector<int>> adjacency_matrix;
    vector<vector<int>> incidence_matrix;
};
#endif