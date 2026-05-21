# DS_Cplus

A C++ study repo for core data structures and graph/tree algorithms. Each file is a standalone program with pointer-based nodes, free functions, and a demo `main()`.

**Compiler:** `g++ -std=c++17`

---

## linkedlist.cpp

Singly linked list built from raw `Node` pointers.

### Structure

```cpp
struct Node {
    int data;
    Node* next;
};
```

### Operations

| Function | Description | Time |
|----------|-------------|------|
| `insertAtHead` | Insert at the front | O(1) |
| `insertAtTail` | Insert at the end | O(n) |
| `printPointerList` | Print the list | O(n) |
| `searchNode` | Find a value | O(n) |
| `deleteNode` | Remove first occurrence | O(n) |
| `freeList` | Delete all nodes | O(n) |

### Build & run

```bash
g++ -std=c++17 -o linkedlist linkedlist.cpp && ./linkedlist
```

The demo inserts values, searches, deletes, and frees the list before exit.

---

## tree.cpp

Binary search tree (BST) with traversal and search.

### Structure

```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;
};
```

### Operations

| Function | Description |
|----------|-------------|
| `insert` | Insert by BST rule (left if smaller, right otherwise) |
| `printInOrder` | In-order traversal (sorted output for a BST) |
| `search` | Recursive lookup |
| `dfs` | Pre-order depth-first traversal |
| `bfs` | Level-order breadth-first traversal (`std::queue`) |
| `deleteTree` | Post-order cleanup of all nodes |

### Build & run

```bash
g++ -std=c++17 -o tree tree.cpp && ./tree
```

Sample tree after inserts `{10, 5, 15, 3, 7, 12, 20}`:

```
        10
       /  \
      5    15
     / \   / \
    3   7 12  20
```

Expected demo output:

- **In-order:** `3 5 7 10 12 15 20`
- **DFS (pre-order):** `10 5 3 7 15 12 20`
- **BFS (level-order):** `10 5 15 3 7 12 20`

---

## graph.cpp

Undirected graph using manual adjacency lists: a linked list of nodes, each with a linked list of edges.

### Structures

```cpp
struct Edge {
    GraphNode* to;
    Edge* next;
};

struct GraphNode {
    int data;
    GraphNode* next;   // next node in the graph
    Edge* edges;       // adjacency list for this node
};
```

### Operations

| Function | Description |
|----------|-------------|
| `insertNode` | Add a vertex (skips duplicates) |
| `addEdge` | Add an undirected edge between two vertices |
| `deleteNode` | Remove a vertex and all edges pointing to it |
| `printGraph` | Print each vertex and its neighbors |
| `dfsFrom` | Depth-first traversal from a start vertex |
| `bfs` | Breadth-first traversal from a start vertex |
| `search` | Check whether a vertex exists |
| `deleteGraph` | Free all nodes and edges |

### Build & run

```bash
g++ -std=c++17 -o graph graph.cpp && ./graph
```

Demo graph:

```
0 — 1 — 3
|
2 — 4
```

After building edges `(0,1)`, `(0,2)`, `(1,3)`, `(2,4)`, the program prints the adjacency list, runs DFS/BFS from `0`, searches for nodes, deletes vertex `2`, and prints the updated graph.

---

## fullgraph.cpp

Extended graph curriculum built on the same manual `GraphNode` / `Edge` style as `graph.cpp`. Adds common graph and grid problems without `vector` adjacency lists or advanced STL.

Uses the same structures as `graph.cpp` (`GraphNode`, `Edge`).

### Graph algorithms

| Function | Description |
|----------|-------------|
| `dfsFrom` | Depth-first traversal from a start vertex |
| `bfs` | Breadth-first traversal from a start vertex |
| `countConnectedComponents` | Count disconnected parts of the graph |
| `isReachable` | Check if one vertex can reach another |
| `shortestPathUnweighted` | BFS distance in an unweighted graph (`-1` if unreachable) |
| `graphHasCycle` | Detect a cycle in an undirected graph |
| `isBipartite` | Two-coloring check via BFS |

### Grid algorithms

| Function | Description |
|----------|-------------|
| `countIslands` | Count connected `'1'` regions (4-direction DFS) |
| `mazeShortestPath` | Shortest path in a maze (`'.'` walkable, `'#'` wall) |

Grids use fixed-size `char` arrays and 4-direction movement (`DR4` / `DC4`).

### Build & run

```bash
g++ -std=c++17 -o fullgraph fullgraph.cpp && ./fullgraph
```

The demo builds the `graph.cpp` sample plus an isolated `{5, 6}` component, then runs traversals, connectivity, reachability, shortest path, cycle and bipartite checks, island counting, and maze BFS.

Example graph (two components):

```
0 — 1 — 3        5 — 6
|
2 — 4
```

---

## VS Code debug

`.vscode/launch.json` includes a **Run/Debug linkedlist** configuration (preLaunchTask: `build linkedlist`, debugger: lldb on macOS). Build and debug configs for `tree` and `graph` can be added the same way.

---

## File overview

| File | Data structure | Style |
|------|----------------|-------|
| `linkedlist.cpp` | Singly linked list | Raw pointers, manual memory |
| `tree.cpp` | Binary search tree | Raw pointers + `std::queue` for BFS |
| `graph.cpp` | Undirected graph | Manual node/edge lists + `std::queue` for BFS |
| `fullgraph.cpp` | Graph + grid problems | Extends `graph.cpp` with BFS/DFS algorithms and grid BFS/DFS |
