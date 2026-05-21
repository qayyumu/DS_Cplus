// g++ -std=c++17 -o linkedlist linkedlist.cpp && ./linkedlist
// Code by U. on 20/05/2026
//
// Singly linked list — raw Node pointers, manual memory management.
#include <iostream>

// Node: one integer value and a pointer to the next node (nullptr at tail).
struct Node {
    int data;
    Node* next;

    Node(int val) 
    {
        data = val;
        next = nullptr;
    } 
};

// 1. CREATE / INSERT
// Inserts a new node at the front of the list (O(1) time).
// Note: head is passed by value — use Node*& to update the caller's head.
void insertAtHead(Node* head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    head = newNode;
}

// Inserts a new node at the end of the list (O(N) time without a tail pointer)
void insertAtTail(Node* head, int val) {
    Node* newNode = new Node(val);
    if (head == nullptr) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 2. READ / PRINT & SEARCH
// Prints the entire list
void printPointerList(Node* head) {
    while (head != nullptr) {
        std::cout << head->data << " -> ";
        head = head->next;
    }
    std::cout << "NULL\n";
}

// Searches for a value in the list (O(N) time)
bool searchNode(Node* head, int target) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->data == target) return true;
        temp = temp->next;
    }
    return false;
}

// 3. DELETE
// Deletes the first occurrence of a value (O(N) time)
void deleteNode(Node* head, int val) {
    if (head == nullptr) return;

    // Case 1: The node to delete is the head node
    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    // Case 2: The node is somewhere in the middle or end
    Node* current = head;
    while (current->next != nullptr && current->next->data != val) {
        current = current->next;
    }

    // If the value was found
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

// 4. MEMORY MANAGEMENT
// Safely deletes all nodes to prevent memory leaks
void freeList(Node* head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    } 
}

int main() {
    Node* head = nullptr;

    // Demo: insert, search, delete, then free all nodes.
    std::cout << "--- Inserting Elements ---\n";
    insertAtTail(head, 10);
    insertAtTail(head, 20);
    insertAtTail(head, 30);
    insertAtTail(head, 5);
    // insertAtHead(head,  5); // List should be: 5 -> 10 -> 20 -> 30 -> NULL
    
    
    printPointerList(head);

    std::cout << "\n--- Searching Elements ---\n";
    std::cout << "Searching for 20: " << (searchNode(head, 20) ? "Found" : "Not Found") << "\n";
    std::cout << "Searching for 99: " << (searchNode(head, 99) ? "Found" : "Not Found") << "\n";

    std::cout << "\n--- Deleting Elements ---\n";
    std::cout << "Deleting 20 (middle node):\n";
    deleteNode(head, 20);
    printPointerList(head);

    std::cout << "Deleting 10 (head node):\n";
    deleteNode(head, 10);
    printPointerList(head);

    // Clean up memory before exiting
    freeList(head);
    
    return 0;
}