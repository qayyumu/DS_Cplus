// g++ -std=c++17 graph.cpp && ./a.out
// Code by U. on 21/05/2026
//
// Undirected graph — manual adjacency lists (GraphNode list + Edge list per node).
#include <iostream>
#include <queue>

// Edge: one neighbor pointer and link to the next edge in the adjacency list.
struct Edge {
    struct GraphNode* to;
    Edge* next;
};

// GraphNode: vertex id, link to next vertex in the graph, head of adjacency list.
struct GraphNode {
    int data;
    GraphNode* next;
    Edge* edges;

    GraphNode(int val) {
        data = val;
        next = nullptr;
        edges = nullptr;
    }
};

// 1. LOOKUP
// Linear search through the vertex list by node id.
GraphNode* findNode(GraphNode* head, int val) {
    while (head != nullptr) {
        if (head->data == val) return head;
        head = head->next;
    }
    return nullptr;
}

// 2. VERTEX OPERATIONS
// Add a vertex at the front of the vertex list (skip if already exists).
void insertNode(GraphNode*& head, int val) {
    if (findNode(head, val) != nullptr) return;
    GraphNode* node = new GraphNode(val);
    node->next = head;
    head = node;
}

// Remove a vertex, all edges pointing to it, and its own adjacency list.
void deleteNode(GraphNode*& head, int val) {
    GraphNode* target = findNode(head, val);
    if (target == nullptr) return;

    // Strip incoming edges from every remaining vertex.
    GraphNode* curr = head;
    while (curr != nullptr) {
        Edge* edge = curr->edges;
        Edge* prev = nullptr;

        while (edge != nullptr) {
            if (edge->to == target) {
                if (prev == nullptr) curr->edges = edge->next;
                else prev->next = edge->next;
                delete edge;
                break;
            }
            prev = edge;
            edge = edge->next;
        }

        curr = curr->next;
    }

    // Unlink the vertex from the vertex list.
    if (head == target) head = head->next;
    else {
        GraphNode* prev = head;
        while (prev->next != target) prev = prev->next;
        prev->next = target->next;
    }

    while (target->edges != nullptr) {
        Edge* next = target->edges->next;
        delete target->edges;
        target->edges = next;
    }

    delete target;
}

// 3. EDGE OPERATIONS
// Undirected edge: prepend one Edge to each endpoint's adjacency list.
void addEdge(GraphNode*& head, int u, int v) {
    insertNode(head, u);
    insertNode(head, v);

    GraphNode* a = findNode(head, u);
    GraphNode* b = findNode(head, v);

    Edge* e1 = new Edge();
    e1->to = b;
    e1->next = a->edges;
    a->edges = e1;

    Edge* e2 = new Edge();
    e2->to = a;
    e2->next = b->edges;
    b->edges = e2;
}

// Print each vertex and its neighbor ids.
void printGraph(GraphNode* head) {
    while (head != nullptr) {
        std::cout << head->data << " -> ";
        Edge* edge = head->edges;
        while (edge != nullptr) {
            std::cout << edge->to->data << " ";
            edge = edge->next;
        }
        std::cout << std::endl;
        head = head->next;
    }
}

// 4. TRAVERSALS
// DFS helper — mark visited by node id, then recurse into unvisited neighbors.
void dfs(GraphNode* node, bool visited[]) {
    if (node == nullptr) return;

    visited[node->data] = true;
    std::cout << node->data << " ";

    Edge* edge = node->edges;
    while (edge != nullptr) {
        if (!visited[edge->to->data]) {
            dfs(edge->to, visited);
        }
        edge = edge->next;
    }
}

void dfsFrom(GraphNode* head, int start) {
    GraphNode* node = findNode(head, start);
    if (node == nullptr) return;

    bool visited[100] = {false};
    dfs(node, visited);
    std::cout << std::endl;
}

// BFS — enqueue start, then visit neighbors level by level.
void bfs(GraphNode* head, int start) {
    GraphNode* node = findNode(head, start);
    if (node == nullptr) return;

    bool visited[100] = {false};
    std::queue<GraphNode*> q;

    visited[node->data] = true;
    q.push(node);

    while (!q.empty()) {
        GraphNode* curr = q.front();
        q.pop();
        std::cout << curr->data << " ";

        Edge* edge = curr->edges;
        while (edge != nullptr) {
            if (!visited[edge->to->data]) {
                visited[edge->to->data] = true;
                q.push(edge->to);
            }
            edge = edge->next;
        }
    }

    std::cout << std::endl;
}

// 5. SEARCH
void search(GraphNode* head, int val) {
    if (findNode(head, val) != nullptr) {
        std::cout << "Found " << val << " in the graph." << std::endl;
    } else {
        std::cout << "Node " << val << " not found." << std::endl;
    }
}

// 6. MEMORY MANAGEMENT
void deleteGraph(GraphNode* head) {
    while (head != nullptr) {
        GraphNode* nextNode = head->next;

        while (head->edges != nullptr) {
            Edge* nextEdge = head->edges->next;
            delete head->edges;
            head->edges = nextEdge;
        }

        delete head;
        head = nextNode;
    }
}

int main() {
    GraphNode* head = nullptr;

    // Demo graph: 0—1—3 and 0—2—4 (undirected)
    addEdge(head, 0, 1);
    addEdge(head, 0, 2);
    addEdge(head, 1, 3);
    addEdge(head, 2, 4);

    printGraph(head);

    std::cout << "DFS: ";
    dfsFrom(head, 0);

    std::cout << "BFS: ";
    bfs(head, 0);

    search(head, 3);
    search(head, 9);

    deleteNode(head, 2);
    std::cout << "\nAfter delete 2:\n";
    printGraph(head);

    deleteGraph(head);
    return 0;
}
