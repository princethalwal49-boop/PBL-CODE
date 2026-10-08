#ifndef GRAPH_H
#define GRAPH_H

const int MAX_GRAPH_STUDENTS = 100;

// One adjacency-list node represents one weighted connection.
struct GraphNode {
    int studentId;
    int weight;
    GraphNode* next;
};

class StudentGraph {
private:
    int studentIds[MAX_GRAPH_STUDENTS];
    GraphNode* adjacencyLists[MAX_GRAPH_STUDENTS];
    int vertexCount;

    int findIndex(int studentId) const;
    GraphNode* findEdge(int fromId, int toId) const;
    bool addOrUpdateOneWay(int fromId, int toId, int weight);
    void clearEdges(GraphNode* head);

public:
    StudentGraph();
    ~StudentGraph();

    bool addStudent(int studentId);
    bool addConnection(int firstStudentId, int secondStudentId, int weight);
    bool removeConnection(int firstStudentId, int secondStudentId);
    bool hasStudent(int studentId) const;
    void displayConnections(int studentId) const;
};

#endif
