#include <iostream>
#include <iomanip>

using namespace std;
class GraphElement {
public:
    virtual ~GraphElement() {}
    virtual void Print() const = 0;
};

class GraphNode : public GraphElement {
public:
    GraphNode(int id) : id(id) {}
    void Print() const {
        cout << "Node " << id << endl;
    }
    int GetId() const {
        return id;
    }
private:
    int id;
};

class GraphArc : public GraphElement {
public:
    GraphArc(int from, int to) : from(from), to(to) {}
    void Print() const {
        cout << "Arc from " << from << " to " << to << endl;
    }
    int GetFrom() const {
        return from;
    }
    int GetTo() const {
        return to;
    }
private:
    int from;
    int to;
};

class GraphContainer {
public:
    GraphContainer() : size(0), capacity(10), elements(new GraphElement* [10]) {}
    ~GraphContainer() {
        for (int i = 0; i < size; i++) {
            delete elements[i];
        }
        delete[] elements;
    }
    void AddElement(GraphElement* element) {
        if (size == capacity) {
            GraphElement** newElements = new GraphElement * [capacity * 2];
            for (int i = 0; i < size; i++) {
                newElements[i] = elements[i];
            }
            delete[] elements;
            elements = newElements;
            capacity *= 2;
        }
        elements[size] = element;
        size++;
    }
    void Print(const GraphNode& node) const {
        node.Print();
    }
    void Print(const GraphArc& arc) const {
        arc.Print();
    }
    void PrintAdjacencyMatrix() const {
        int maxNodeId = -1;
        for (int i = 0; i < size; i++) {
            GraphNode* node = dynamic_cast<GraphNode*>(elements[i]);
            if (node && node->GetId() > maxNodeId) {
                maxNodeId = node->GetId();
            }
        }
        int** matrix = new int* [maxNodeId + 1];
        for (int i = 0; i <= maxNodeId; i++) {
            matrix[i] = new int[maxNodeId + 1];
            for (int j = 0; j <= maxNodeId; j++) {
                matrix[i][j] = 0;
            }
        }
        for (int i = 0; i < size; i++) {
            GraphArc* arc = dynamic_cast<GraphArc*>(elements[i]);
            if (arc) {
                int from = arc->GetFrom();
                int to = arc->GetTo();
                matrix[from][to] = 1;
            }
        }
        std::cout << "Adjacency Matrix:" << std::endl;
        std::cout << "  ";
        for (int i = 0; i <= maxNodeId; i++) {
            std::cout << "a" << i << " ";
        }
        std::cout << std::endl;
        std::cout << "  ";
        for (int i = 0; i <= maxNodeId; i++) {
            std::cout << "___";
        }
        std::cout << std::endl;
        for (int i = 0; i <= maxNodeId; i++) {
            std::cout << i << "|";
            for (int j = 0; j <= maxNodeId; j++) {
                std::cout << std::setw(2) << matrix[i][j] << "|";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        for (int i = 0; i <= maxNodeId; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void PrintIncidenceMatrix() const {
        int numNodes = 0, numArcs = 0;
        // count number of nodes and arcs
        for (int i = 0; i < size; i++) {
            if (dynamic_cast<GraphNode*>(elements[i])) {
                numNodes++;
            }
            else if (dynamic_cast<GraphArc*>(elements[i])) {
                numArcs++;
            }
        }
        // allocate incidence matrix
        int** matrix = new int* [numNodes];
        for (int i = 0; i < numNodes; i++) {
            matrix[i] = new int[numArcs];
            for (int j = 0; j < numArcs; j++) {
                matrix[i][j] = 0;
            }
        }
        // fill in incidence matrix
        int arcIndex = 0;
        for (int i = 0; i < size; i++) {
            GraphArc* arc = dynamic_cast<GraphArc*>(elements[i]);
            if (arc) {
                int from = -1, to = -1;
                for (int j = 0; j < size; j++) {
                    GraphNode* node = dynamic_cast<GraphNode*>(elements[j]);
                    if (node && node->GetId() == arc->GetFrom()) {
                        from = j;
                    }
                    else if (node && node->GetId() == arc->GetTo()) {
                        to = j;
                    }
                    if (from != -1 && to != -1) {
                        break;
                    }
                }
                matrix[from][arcIndex] = 1;
                matrix[to][arcIndex] = -1;
                arcIndex++;
            }
        }
        // Print the incidence matrix as a table
        std::cout << "Incidence Matrix:" << std::endl;
        std::cout << "  ";
        for (int i = 0; i < arcIndex; i++) {
            std::cout << "e" << i << " ";
        }
        std::cout << std::endl;
        std::cout << "  ";
        for (int i = 0; i < arcIndex; i++) {
            std::cout << "___";
        }
        std::cout << std::endl;
        for (int i = 0; i < numNodes; i++) {
            std::cout << i << "|";
            for (int j = 0; j < numArcs; j++) {
                std::cout << std::setw(2) << matrix[i][j] << "|";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        // deallocate incidence matrix
        for (int i = 0; i < numNodes; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    void DFS(int startNode) const {
        bool* visited = new bool[size];
        for (int i = 0; i < size; i++) {
            visited[i] = false;
        }
        DFSHelper(startNode, visited);
        delete[] visited;
    }

    void DFSHelper(int nodeIndex, bool* visited) const {
        visited[nodeIndex] = true;
        GraphNode* node = dynamic_cast<GraphNode*>(elements[nodeIndex]);
        if (node) {
            Print(*node);
        }
        for (int i = 0; i < size; i++) {
            GraphArc* arc = dynamic_cast<GraphArc*>(elements[i]);
            if (arc && arc->GetFrom() == nodeIndex && !visited[arc->GetTo()]) {
                DFSHelper(arc->GetTo(), visited);
            }
        }
    }
private:
    int size;
    int capacity;
    GraphElement** elements;
};


int main() {
    GraphContainer graph;
    
    graph.AddElement(new GraphNode(0));
    graph.AddElement(new GraphNode(1));
    graph.AddElement(new GraphNode(2));
    graph.AddElement(new GraphArc(0, 1));
    graph.AddElement(new GraphArc(1, 2));
    graph.AddElement(new GraphArc(2, 0));
    graph.Print(GraphArc(2, 0));
    graph.Print(GraphArc(1, 2));
    graph.Print(GraphNode(2));
    graph.PrintAdjacencyMatrix();
    graph.PrintIncidenceMatrix();
    graph.DFS(0);
    return 0;
}
