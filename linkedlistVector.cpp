// g++ -std=c++17 linkedlistVector.cpp && ./a.out
// Code by U. on 20/05/2026
//
// Singly linked list stored in a vector inside one Node (learning variant).
#include <iostream>
#include <vector>

// Node: holds the list values in dataVector (simulates list order).
struct Node {
    int data;
    std::vector<int> dataVector;

    Node(int val) {
        data = val;
        dataVector.push_back(val);
    }
};

// 1. CREATE / INSERT

void insertAtTail(Node*& head, int val) {
    if (head == nullptr) {
        head = new Node(val);
        return;
    }
    head->dataVector.push_back(val);
    head->data = val;
}

void insertAtHead(Node*& head, int val) {
    if (head == nullptr) {
        head = new Node(val);
        return;
    }
    head->dataVector.insert(head->dataVector.begin(), val);
    head->data = head->dataVector.front();
}

// 2. READ / PRINT & SEARCH

void printPointerList(Node* head) {
    if (head == nullptr || head->dataVector.empty()) {
        std::cout << "NULL\n";
        return;
    }
    for (int i = 0; i < head->dataVector.size(); i++) {
        std::cout << head->dataVector[i] << " -> ";
    }
    std::cout << "NULL\n";
}

bool searchNode(Node* head, int target) {
    if (head == nullptr) return false;
    for (int i = 0; i < head->dataVector.size(); i++) {
        if (head->dataVector[i] == target) return true;
    }
    return false;
}

// 3. DELETE

void deleteNode(Node*& head, int val) {
    if (head == nullptr || head->dataVector.empty()) {
        std::cout << "Nothing to delete, the list is empty.\n";
        return;
    }

    for (int i = 0; i < head->dataVector.size(); i++) {
        if (head->dataVector[i] == val) {
            head->dataVector.erase(head->dataVector.begin() + i);
            if (head->dataVector.empty()) {
                delete head;
                head = nullptr;
            } else {
                head->data = head->dataVector.front();
            }
            std::cout << "Deleted " << val << " from the list.\n";
            return;
        }
    }

    std::cout << "Value " << val << " not found in the list.\n";
}

void freeList(Node*& head) {
    delete head;
    head = nullptr;
}

int main() {
    Node* head = nullptr;
    int choice = 0;
    int value = 0;

    while (true) {
        std::cout << "\n====================================\n";
        std::cout << "   LINKED LIST INTERACTIVE SYSTEM   \n";
        printPointerList(head);
        std::cout << "====================================\n";
        std::cout << "1. Insert Node at Tail\n";
        std::cout << "2. Insert Node at Head\n";
        std::cout << "3. Search for a Node\n";
        std::cout << "4. Delete a Node\n";
        std::cout << "5. Exit Program\n";
        std::cout << "------------------------------------\n";
        std::cout << "Enter your choice (1-6): ";

        if (!(std::cin >> choice)) {
            std::cout << "Invalid input detected. Shutting down...\n";
            freeList(head);
            break;
        }

        std::cout << "\n";

        switch (choice) {
            case 1:
                std::cout << "Enter the integer to insert at the tail: ";
                std::cin >> value;
                insertAtTail(head, value);
                std::cout << ">> Inserted " << value << ".\n";
                break;

            case 2:
                std::cout << "Enter the integer to insert at the head: ";
                std::cin >> value;
                insertAtHead(head, value);
                std::cout << ">> Inserted " << value << ".\n";
                break;

            case 3:
                std::cout << "Enter the integer to search for: ";
                std::cin >> value;
                if (searchNode(head, value)) {
                    std::cout << ">> Found! The value " << value << " is in the list.\n";
                } else {
                    std::cout << ">> Not found. The value " << value << " is not in the list.\n";
                }
                break;

            case 4:
                std::cout << "Enter the integer to delete: ";
                std::cin >> value;
                deleteNode(head, value);
                break;

            case 5:
                printPointerList(head);
                break;

            case 6:
                std::cout << ">> Freeing memory and exiting program. Goodbye!\n";
                freeList(head);
                return 0;

            default:
                std::cout << ">> Invalid choice. Please select a number between 1 and 6.\n";
        }
    }

    return 0;
}
