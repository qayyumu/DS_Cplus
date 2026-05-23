# Data Structure in Cplusplus

A C++ refresher repo for core data structures with vector/queue/linkedlist/graph/tree algorithms. Most files are standalone programs with a demo.

## Overall Structure of Repo

| File | Topic | Style |
|------|-------|-------|
| `PointerExample.cpp` | Pointer examples | Pointer to pointer, pointer assignment
| `StructExample.cpp` | Struct defination | Plain struct, free function |
| `PointerStructExample.cpp` |structure pointer example | pointer assignment  
| `ClassExample.cpp` | Class | Constructor, public/private, methods |
| `VectorExample.cpp` | `std::vector<int>` | Push, index, pop_back, clear |
| `VectorExample2.cpp` | `std::vector<Employee>` | Custom struct in a vector |
| `QueueExample.cpp` | `std::queue<Employee>` | FIFO enqueue/dequeue |
| `linkedlist.cpp` | Singly linked list | Raw pointers, manual memory, interactive menu |
| `linkedlistVector.cpp` | List in one node | `vector<int>` inside a single `Node`, interactive menu |
| `tree.cpp` | Binary search tree | Raw pointers + `std::queue` for BFS |
| `graph.cpp` | Undirected graph | Manual node/edge lists + `std::queue` for BFS |
| `fullgraph.cpp` | Graph + grid problems | Extends `graph.cpp` with BFS/DFS algorithms and grid BFS/DFS |


---

## StructExample.cpp

Introduces a plain `struct` with aggregate initialization and pointer access.

### Structure

```cpp
struct Employee {
    string name;
    int age;
    double salary;
};
```

### Highlights

| Topic | What it shows |
|-------|----------------|
| `printEmployee` | Pass struct by value |
| Aggregate init | `Employee employee = {"Ali Khan", 30, 50000.0};` |
| Pointer access | `Employee* employeePtr = &employee;` then `->` to modify fields |

### Build & run

```bash
g++ -std=c++17 StructExample.cpp && ./a.out
```

---

## ClassExample.cpp

Same `Employee` idea as a `class` with access control, constructor, and member methods.

### Structure

```cpp
class Employee {
public:
    string name;
    int age;
    double salary;
private:
    string secretcode;
public:
    Employee(string name, int age, double salary, string secretcode);
    void addAge(int age);
    void addSalary(double salary);
    void printEmployee();
};
```

### Highlights

| Topic | What it shows |
|-------|----------------|
| Constructor | Initializes all fields including private `secretcode` |
| Encapsulation | `secretcode` is private (direct access commented out in `main`) |
| Methods | `addAge`, `addSalary`, and public field updates in the demo |

### Build & run

```bash
g++ -std=c++17 ClassExample.cpp && ./a.out
```

---

## VectorExample.cpp

Basic `std::vector<int>` usage: insert, index access, size, and drain with `pop_back`.

### Operations demonstrated

| API | Description |
|-----|-------------|
| `push_back` | Add elements `1`, `2`, `3` |
| `operator[]` | Read by index |
| `size` | Print current length |
| `front` / `pop_back` | Drain the vector in a loop |
| `clear` | Empty the vector at the end |

### Build & run

```bash
g++ -std=c++17 VectorExample.cpp && ./a.out
```

---

## VectorExample2.cpp

Stores custom `Employee` records in a `std::vector<Employee>`.

### Structure

```cpp
struct Employee {
    std::string name;
    int age;
    double salary;
};
```

### Highlights

- Three employees pushed with brace initialization
- Loop prints each employee from the front, then removes with `pop_back` until empty

### Build & run

```bash
g++ -std=c++17 VectorExample2.cpp && ./a.out
```

---

## QueueExample.cpp

FIFO processing with `std::queue<Employee>` — same `Employee` struct as `VectorExample2.cpp`.

### Highlights

| API | Description |
|-----|-------------|
| `push` | Enqueue three employees |
| `front` | Peek at the next item |
| `pop` | Dequeue after printing (FIFO order) |

### Build & run

```bash
g++ -std=c++17 QueueExample.cpp && ./a.out
```

---

## linkedlist.cpp

Singly linked list built from raw `Node` pointers and manual memory management. Includes an interactive menu for insert, search, delete, and exit.

### Structure

```cpp
struct Node {
    int data;
    Node* next;

    Node(int val);
};
```

### Operations

| Function | Description | Time |
|----------|-------------|------|
| `insertAtHead` | Insert at the front | O(1) |
| `insertAtTail` | Insert at the end | O(n) |
| `printPointerList` | Print the list | O(n) |
| `searchNode` | Find a value | O(n) |
| `deleteNode` | Remove first occurrence (head or middle/tail) | O(n) |
| `freeList` | Delete all nodes | O(n) |

### Interactive menu

1. Insert at tail  
2. Insert at head  
3. Search  
4. Delete  
5. Exit (labelled in menu; use option **6** to free memory and quit)  

Invalid input shuts the program down safely.

### Build & run

```bash
g++ -std=c++17 linkedlist.cpp && ./a.out
```

---

## linkedlistVector.cpp

Learning variant: one `Node` holds the entire list in a `std::vector<int>` instead of chaining separate nodes. Same interactive menu API as `linkedlist.cpp`.

### Structure

```cpp
struct Node {
    int data;
    std::vector<int> dataVector;

    Node(int val);
};
```

### Operations

| Function | Description |
|----------|-------------|
| `insertAtTail` | `push_back` onto `dataVector` |
| `insertAtHead` | `insert` at front of `dataVector` |
| `printPointerList` | Walk `dataVector` |
| `searchNode` | Linear scan of `dataVector` |
| `deleteNode` | `erase` first match; delete node if vector empty |
| `freeList` | `delete` the single node |

### Interactive menu

Same options as `linkedlist.cpp`; option **5** prints the list, option **6** exits and frees memory.

### Build & run

```bash
g++ -std=c++17 linkedlistVector.cpp && ./a.out
```

---

## tree.cpp

Binary search tree (BST) with traversal and search. Uses raw `TreeNode` pointers; `std::queue` is used for BFS only.

### Structure

```cpp
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val);
};
```

### Operations

| Function | Description |
|----------|-------------|
| `insert` | Insert by BST rule (left if smaller, right otherwise) |
| `printInOrder` | In-order traversal (sorted output for a BST) |
| `search` | Recursive lookup with console message |
| `dfs` | Pre-order depth-first traversal |
| `bfs` | Level-order breadth-first traversal (`std::queue`) |
| `deleteTree` | Post-order cleanup of all nodes |

### Build & run

```bash
g++ -std=c++17 tree.cpp && ./a.out
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

Undirected graph using manual adjacency lists: a linked list of vertices, each with a linked list of edges. Uses `std::queue` for BFS.

### Structures

```cpp
struct Edge {
    GraphNode* to;
    Edge* next;
};

struct GraphNode {
    int data;
    GraphNode* next;   // next vertex in the graph
    Edge* edges;       // adjacency list for this vertex
};
```

### Operations

| Function | Description |
|----------|-------------|
| `findNode` | Linear search for a vertex by id |
| `insertNode` | Add a vertex (skips duplicates) |
| `addEdge` | Add an undirected edge between two vertices |
| `deleteNode` | Remove a vertex and all edges pointing to it |
| `printGraph` | Print each vertex and its neighbors |
| `dfs` / `dfsFrom` | Depth-first traversal from a start vertex |
| `bfs` | Breadth-first traversal from a start vertex |
| `search` | Check whether a vertex exists |
| `deleteGraph` | Free all nodes and edges |

### Build & run

```bash
g++ -std=c++17 graph.cpp && ./a.out
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

Extended graph curriculum on the same manual `GraphNode` / `Edge` style as `graph.cpp`. Adds connectivity, shortest path, cycle/bipartite checks, and grid BFS/DFS — no vector adjacency lists.

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

Internal helpers: `dfsVisit` (mark only), `dfsPrint` (mark and print), `hasCycleUndirected`.

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

The demo builds the main component `{0,1,2,3,4}` plus isolated `{5,6}`, then runs traversals, connectivity, reachability, shortest path, and cycle checks. A separate square graph tests bipartite coloring. Grid demos count islands and solve a small maze.

Example graph (two components):

```
0 — 1 — 3        5 — 6
|
2 — 4
```

---

