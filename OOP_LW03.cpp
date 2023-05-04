#include "methods_for_graph.h"

int main() {
    Graph g(3); //тобто маємо вершини 0, 1, 2
    g.AddNode(); //додаємо ще одну вершину та її індекс вже буде 3
    g.AddArc(0, 1);
    g.AddArc(0, 2);
    g.AddArc(1, 3);
    g.AddArc(2, 3);
    g.PrintIncidenceMatrix();
    g.PrintAdjacencyMatrix();
    g.DepthFirstSearch(0);
}
