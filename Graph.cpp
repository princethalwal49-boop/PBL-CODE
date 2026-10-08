#include "Graph.h"
#include <iostream>

StudentGraph::StudentGraph() : vertexCount(0) {
    for (int i = 0; i < MAX_GRAPH_STUDENTS; ++i) {
        studentIds[i] = 0;
        adjacencyLists[i] = 0;
    }
}

StudentGraph::~StudentGraph() {
    for (int i = 0; i < vertexCount; ++i) clearEdges(adjacencyLists[i]);
}

int StudentGraph::findIndex(int studentId) const {
    for (int i = 0; i < vertexCount; ++i) {
        if (studentIds[i] == studentId) return i;
    }
    return -1;
}

GraphNode* StudentGraph::findEdge(int fromId, int toId) const {
    int index = findIndex(fromId);
    if (index == -1) return 0;
    GraphNode* current = adjacencyLists[index];
    while (current) {
        if (current->studentId == toId) return current;
        current = current->next;
    }
    return 0;
}

bool StudentGraph::addStudent(int studentId) {
    if (studentId <= 0 || hasStudent(studentId)) return false;
    if (vertexCount >= MAX_GRAPH_STUDENTS) return false;
    studentIds[vertexCount] = studentId;
    adjacencyLists[vertexCount] = 0;
    ++vertexCount;
    return true;
}

bool StudentGraph::addOrUpdateOneWay(int fromId, int toId, int weight) {
    int index = findIndex(fromId);
    if (index == -1) return false;

    GraphNode* existing = findEdge(fromId, toId);
    if (existing) {
        existing->weight = weight;
        return true;
    }

    GraphNode* newEdge = new GraphNode;
    newEdge->studentId = toId;
    newEdge->weight = weight;
    newEdge->next = adjacencyLists[index];
    adjacencyLists[index] = newEdge;
    return true;
}

bool StudentGraph::addConnection(int firstStudentId, int secondStudentId, int weight) {
    if (firstStudentId == secondStudentId || weight < 0 || weight > 100 ||
        !hasStudent(firstStudentId) || !hasStudent(secondStudentId)) return false;

    return addOrUpdateOneWay(firstStudentId, secondStudentId, weight) &&
           addOrUpdateOneWay(secondStudentId, firstStudentId, weight);
}

bool StudentGraph::removeConnection(int firstStudentId, int secondStudentId) {
    int indexA = findIndex(firstStudentId);
    int indexB = findIndex(secondStudentId);
    if (indexA == -1 || indexB == -1) return false;

    bool removed = false;
    int indices[2] = { indexA, indexB };
    int targets[2] = { secondStudentId, firstStudentId };
    for (int i = 0; i < 2; ++i) {
        GraphNode* current = adjacencyLists[indices[i]];
        GraphNode* previous = 0;
        while (current) {
            if (current->studentId == targets[i]) {
                if (previous) previous->next = current->next;
                else adjacencyLists[indices[i]] = current->next;
                delete current;
                removed = true;
                break;
            }
            previous = current;
            current = current->next;
        }
    }
    return removed;
}

bool StudentGraph::hasStudent(int studentId) const {
    return findIndex(studentId) != -1;
}

void StudentGraph::displayConnections(int studentId) const {
    int index = findIndex(studentId);
    if (index == -1) {
        std::cout << "No graph record exists for this student.\n";
        return;
    }

    GraphNode* current = adjacencyLists[index];
    if (!current) {
        std::cout << "No peer connections yet. Get recommendations to create connections.\n";
        return;
    }

    std::cout << "\n========== MY CONNECTIONS ==========\n";
    while (current) {
        std::cout << "Student ID: " << current->studentId
                  << " | Matching Score: " << current->weight << "%\n";
        current = current->next;
    }
}

void StudentGraph::clearEdges(GraphNode* head) {
    while (head) {
        GraphNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
    }
}
