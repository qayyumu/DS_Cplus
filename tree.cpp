// g++ -std=c++17 tree.cpp && ./a.out
// Code by U. on 20/05/2026
//
// Binary search tree — raw TreeNode pointers, std::queue for BFS only.
#include <iostream>
#include <queue>   // for BFS

// TreeNode: value plus left/right child pointers (nullptr if absent).
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

// 1. INSERT
// Recursive BST insert — smaller goes left, greater-or-equal goes right.
void insert(TreeNode*& root, int val) {
    if (root == nullptr) {
        root = new TreeNode(val);
        return;
    }
    if (val < root->data) {
        insert(root->left, val);
    } else {
        insert(root->right, val);
    }
}

// 2. TRAVERSALS

// Preorder DFS: visit root before children. PREORDER (Root, Left, Right) ---
void preorder(TreeNode* root) {
    if (root == nullptr) return;
    std::cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

//postorder:  (Left, Right, Root) ---
void postorder(TreeNode* root) {
    if (root == nullptr) return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << " ";
}
// Inorder: left, root, right — prints BST values in sorted order.
void printInOrder(TreeNode* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    std::cout << root->data << " ";
    printInOrder(root->right);
}

// Level-order BFS: process nodes layer by layer using a queue.
// Step,      Queue ,             Action,Output
// Initial,   [1],                Push root,-
// Iter 1,   "[2, 3]",            "Pop 1, push its children 2 and 3",1
// Iter 2,   "[3, 4, 5]",         "Pop 2, push its children 4 and 5",1 2
// Iter 3,   "[4, 5]",            "Pop 3, it has no children",1 2 3
// Iter 4,    [5],                "Pop 4, it has no children",1 2 3 4
// Iter 5,    [],                 "Pop 5, queue is now empty",1 2 3 4 5

void bfs(TreeNode* root) {
    if (root == nullptr) return;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* current = q.front();
        q.pop();
        std::cout << current->data << " ";

        if (current->left != nullptr) q.push(current->left);
        if (current->right != nullptr) q.push(current->right);
    }
}

// 3. SEARCH
// Walk the BST like insert — O(height) per lookup.
void search(TreeNode* root, int val) {
    if (root == nullptr) return;
    if (root->data == val) {
        std::cout << "Found " << val << " in the tree." << std::endl;
        return;
    }
    if (val < root->data) {
        search(root->left, val);
    } else {
        search(root->right, val);
    }
}

// 4. MEMORY MANAGEMENT
// Post-order delete: free children before the current node.
void deleteTree(TreeNode*& root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// --- THE VISUALIZER FUNCTION ---
// prefix: Keeps track of the spacing and vertical lines from parent nodes
// isLeft: Tells us whether to draw a branching line (├──) or an ending line (└──)
// isRoot: A flag just to format the very first node nicely
void visualizeTree(TreeNode* node, std::string prefix = "", bool isLeft = false, bool isRoot = true) {
    // Base case: if the tree is empty, do nothing
    if (node == nullptr) {
        return;
    }

    // 1. Print the current node
    if (isRoot) {
        std::cout << node->data << "\n";
    } else {
        // If it's a left child, it gets a T-intersection. If it's a right child, it gets an L-corner.
        std::cout << prefix << (isLeft ? "├── " : "└── ") << node->data << "\n";
    }

    // 2. Calculate the prefix for the children
    // If the current node was a left child, we need to extend the vertical line downwards ("│   ")
    // If it was a right child, there are no more siblings below it, so we just use empty space ("    ")
    std::string nextPrefix = prefix + (isRoot ? "" : (isLeft ? "│   " : "    "));

    // 3. Recursive calls for children
    // We only make the calls if at least one child exists to prevent drawing empty lines
    if (node->left != nullptr || node->right != nullptr) {
        visualizeTree(node->left, nextPrefix, true, false);
        visualizeTree(node->right, nextPrefix, false, false);
    }
}

int main() {
    TreeNode* root = nullptr;

    // Build BST: 10, 5, 15, 3, 7, 12, 20
    std::cout << "Build BST: 10, 5, 15, 3, 7, 12, 20 " << std::endl;
    insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 3);
    insert(root, 7);
    insert(root, 12);
    insert(root, 20);
    visualizeTree(root);

    std::cout << "pre-order (DFS): ";
    preorder(root);
    std::cout << std::endl;

    std::cout << "Post-order: ";
    postorder(root);
    std::cout << std::endl;


    std::cout << "In-order: ";
    printInOrder(root);
    std::cout << std::endl;

    std::cout << "BFS (level-order): ";
    bfs(root);
    std::cout << std::endl;

    search(root, 7);
    search(root, 9);

    deleteTree(root);

    return 0;
}
