// g++ -std=c++17 -o fullgraph fullgraph.cpp && ./fullgraph
// Code by U. on 21/05/2026
//
// Extended graph curriculum — same manual GraphNode/Edge style as graph.cpp,
// plus connectivity, shortest path, cycle/bipartite checks, and grid BFS/DFS.
#include <iostream>
#include <queue>

struct Edge {
    struct GraphNode* to;
    Edge* next;
};

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

// 1. LOOKUP & BUILD (same as graph.cpp)
GraphNode* findNode(GraphNode* head, int val) {
    while (head != nullptr) {
        if (head->data == val) return head;
        head = head->next;
    }
    return nullptr;
}

void insertNode(GraphNode*& head, int val) {
    if (findNode(head, val) != nullptr) return;
    GraphNode* node = new GraphNode(val);
    node->next = head;
    head = node;
}

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

// 2. TRAVERSALS
// dfsVisit marks nodes without printing (used by component/reachability helpers).
void dfsVisit(GraphNode* node, bool visited[]) {
    if (node == nullptr) return;

    visited[node->data] = true;

    Edge* edge = node->edges;
    while (edge != nullptr) {
        if (!visited[edge->to->data]) {
            dfsVisit(edge->to, visited);
        }
        edge = edge->next;
    }
}

// dfsPrint marks and prints in DFS order.
void dfsPrint(GraphNode* node, bool visited[]) {
    if (node == nullptr) return;

    visited[node->data] = true;
    std::cout << node->data << " ";

    Edge* edge = node->edges;
    while (edge != nullptr) {
        if (!visited[edge->to->data]) {
            dfsPrint(edge->to, visited);
        }
        edge = edge->next;
    }
}

void dfsFrom(GraphNode* head, int start) {
    GraphNode* node = findNode(head, start);
    if (node == nullptr) return;

    bool visited[100] = {false};
    dfsPrint(node, visited);
    std::cout << std::endl;
}

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

// 3. GRAPH ALGORITHMS
// Run DFS from every unvisited vertex — each run is one connected component.
int countConnectedComponents(GraphNode* head) {
    bool visited[100] = {false};
    int components = 0;

    GraphNode* curr = head;
    while (curr != nullptr) {
        if (!visited[curr->data]) {
            components++;
            dfsVisit(curr, visited);
        }
        curr = curr->next;
    }

    return components;
}

// DFS from src; target is reachable if its visited flag is set afterward.
bool isReachable(GraphNode* head, int src, int target) {
    GraphNode* start = findNode(head, src);
    if (start == nullptr) return false;

    bool visited[100] = {false};
    dfsVisit(start, visited);
    return visited[target];
}

// BFS assigns dist[] = edge count from src; returns -1 if dest unreachable.
int shortestPathUnweighted(GraphNode* head, int src, int dest) {
    GraphNode* start = findNode(head, src);
    if (start == nullptr) return -1;

    int dist[100];
    for (int i = 0; i < 100; i++) dist[i] = -1;

    bool visited[100] = {false};
    std::queue<GraphNode*> q;

    visited[start->data] = true;
    dist[start->data] = 0;
    q.push(start);

    while (!q.empty()) {
        GraphNode* curr = q.front();
        q.pop();

        if (curr->data == dest) return dist[dest];

        Edge* edge = curr->edges;
        while (edge != nullptr) {
            if (!visited[edge->to->data]) {
                visited[edge->to->data] = true;
                dist[edge->to->data] = dist[curr->data] + 1;
                q.push(edge->to);
            }
            edge = edge->next;
        }
    }

    return -1;
}

// Undirected cycle: back-edge to a visited neighbor that is not the parent.
bool hasCycleUndirected(GraphNode* node, bool visited[], int parentData) {
    if (node == nullptr) return false;

    visited[node->data] = true;

    Edge* edge = node->edges;
    while (edge != nullptr) {
        if (!visited[edge->to->data]) {
            if (hasCycleUndirected(edge->to, visited, node->data)) return true;
        } else if (edge->to->data != parentData) {
            return true;
        }
        edge = edge->next;
    }

    return false;
}

bool graphHasCycle(GraphNode* head) {
    bool visited[100] = {false};

    GraphNode* curr = head;
    while (curr != nullptr) {
        if (!visited[curr->data]) {
            if (hasCycleUndirected(curr, visited, -1)) return true;
        }
        curr = curr->next;
    }

    return false;
}

// Two-color BFS — odd cycle means not bipartite.
bool isBipartite(GraphNode* head) {
    int color[100];
    for (int i = 0; i < 100; i++) color[i] = -1;

    GraphNode* curr = head;
    while (curr != nullptr) {
        if (color[curr->data] == -1) {
            std::queue<GraphNode*> q;
            color[curr->data] = 0;
            q.push(curr);

            while (!q.empty()) {
                GraphNode* u = q.front();
                q.pop();

                Edge* edge = u->edges;
                while (edge != nullptr) {
                    GraphNode* v = edge->to;
                    if (color[v->data] == -1) {
                        color[v->data] = 1 - color[u->data];
                        q.push(v);
                    } else if (color[v->data] == color[u->data]) {
                        return false;
                    }
                    edge = edge->next;
                }
            }
        }
        curr = curr->next;
    }

    return true;
}

// 4. MEMORY MANAGEMENT
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

// 5. GRID GRAPHS — treat each cell as a node, 4-direction edges
const int DR4[] = {-1, 1, 0, 0};
const int DC4[] = {0, 0, -1, 1};

bool inBounds(int r, int c, int rows, int cols) {
    return r >= 0 && r < rows && c >= 0 && c < cols;
}

// DFS flood-fill for one connected '1' region.
void markIsland(char grid[][10], bool visited[][10], int rows, int cols, int r, int c) {
    visited[r][c] = true;
    for (int d = 0; d < 4; d++) {
        int nr = r + DR4[d];
        int nc = c + DC4[d];
        if (inBounds(nr, nc, rows, cols) && !visited[nr][nc] && grid[nr][nc] == '1') {
            markIsland(grid, visited, rows, cols, nr, nc);
        }
    }
}

// Count separate groups of adjacent '1' cells.
int countIslands(char grid[][10], int rows, int cols) {
    bool visited[10][10] = {false};
    int islands = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == '1' && !visited[r][c]) {
                islands++;
                markIsland(grid, visited, rows, cols, r, c);
            }
        }
    }

    return islands;
}

// BFS on a grid maze: '.' walkable, '#' wall; returns step count or -1.
int mazeShortestPath(char maze[][10], int rows, int cols, int sr, int sc, int er, int ec) {
    int dist[10][10];
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) dist[r][c] = -1;
    }

    struct Cell { int r; int c; };
    std::queue<Cell> q;

    dist[sr][sc] = 0;
    q.push({sr, sc});

    while (!q.empty()) {
        Cell curr = q.front();
        q.pop();

        if (curr.r == er && curr.c == ec) return dist[er][ec];

        for (int d = 0; d < 4; d++) {
            int nr = curr.r + DR4[d];
            int nc = curr.c + DC4[d];
            if (inBounds(nr, nc, rows, cols) && maze[nr][nc] == '.' && dist[nr][nc] == -1) {
                dist[nr][nc] = dist[curr.r][curr.c] + 1;
                q.push({nr, nc});
            }
        }
    }

    return -1;
}

int main() {
    GraphNode* head = nullptr;

    // Main component {0,1,2,3,4} plus isolated {5,6}
    std::cout << "=== Graph (manual adjacency list) ===\n";
    addEdge(head, 0, 1);
    addEdge(head, 0, 2);
    addEdge(head, 1, 3);
    addEdge(head, 2, 4);
    addEdge(head, 5, 6);

    printGraph(head);

    std::cout << "DFS from 0: ";
    dfsFrom(head, 0);

    std::cout << "BFS from 0: ";
    bfs(head, 0);

    std::cout << "Connected components: " << countConnectedComponents(head) << "\n";
    std::cout << "Reachable 0 -> 3: " << (isReachable(head, 0, 3) ? "yes" : "no") << "\n";
    std::cout << "Shortest path 0 -> 3: " << shortestPathUnweighted(head, 0, 3) << "\n";
    std::cout << "Has cycle: " << (graphHasCycle(head) ? "yes" : "no") << "\n";

    // Square 0—1—2—3—0 is bipartite; tested on a separate graph.
    GraphNode* bipartiteHead = nullptr;
    addEdge(bipartiteHead, 0, 1);
    addEdge(bipartiteHead, 0, 3);
    addEdge(bipartiteHead, 1, 2);
    addEdge(bipartiteHead, 2, 3);
    std::cout << "Is bipartite: " << (isBipartite(bipartiteHead) ? "yes" : "no") << "\n";
    deleteGraph(bipartiteHead);

    std::cout << "\n=== Grid graphs ===\n";
    char grid[3][10] = {
        {'1', '1', '0'},
        {'1', '0', '0'},
        {'0', '0', '1'}
    };
    std::cout << "Islands: " << countIslands(grid, 3, 3) << "\n";

    char maze[3][10] = {
        {'.', '.', '#', '.'},
        {'.', '#', '.', '.'},
        {'.', '.', '.', '.'}
    };
    std::cout << "Maze shortest path (0,0) -> (2,3): "
              << mazeShortestPath(maze, 3, 4, 0, 0, 2, 3) << "\n";

    deleteGraph(head);
    return 0;
}
