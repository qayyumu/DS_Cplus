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
void insert(TreeNode* root, int val) {
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
// In-order: left, root, right — prints BST values in sorted order.
void printInOrder(TreeNode* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    std::cout << root->data << " ";
    printInOrder(root->right);
}

// Pre-order DFS: visit root before children.
void dfs(TreeNode* root) {
    if (root == nullptr) return;
    std::cout << root->data << " ";
    dfs(root->left);
    dfs(root->right);
}

// Level-order BFS: process nodes layer by layer using a queue.
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
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    TreeNode* root = nullptr;

    // Build BST: 10, 5, 15, 3, 7, 12, 20
    insert(root, 10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 3);
    insert(root, 7);
    insert(root, 12);
    insert(root, 20);

    std::cout << "In-order: ";
    printInOrder(root);
    std::cout << std::endl;

    std::cout << "DFS (pre-order): ";
    dfs(root);
    std::cout << std::endl;

    std::cout << "BFS (level-order): ";
    bfs(root);
    std::cout << std::endl;

    search(root, 7);
    search(root, 9);

    deleteTree(root);

    return 0;
}
