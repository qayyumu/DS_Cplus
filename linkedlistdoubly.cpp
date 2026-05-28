// g++ -std=c++17 linkedlistdoubly.cpp && ./a.out
// Code by U. on 28/05/2026
//
// Doubly linked list — raw Node pointers, manual memory management.
#include <iostream>

// Node: value plus next and prev pointers (nullptr at ends).
struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int val)
    {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

// 1. CREATE / INSERT

// Inserts a new node at the end of the list (O(N) time without a tail pointer)
void insertAtTail(Node*& head, int val) {
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
    newNode->prev = temp;
}

// Inserts a new node at the front of the list (O(1) time).
void insertAtHead(Node*& head, int val) {
    Node* newNode = new Node(val);
    newNode->next = head;
    if (head != nullptr) {
        head->prev = newNode;
    }
    head = newNode;
}


// 2. READ / PRINT & SEARCH
// Prints the entire list forward
void printPointerList(Node* head) {
    if (head == nullptr) {
        std::cout << "NULL\n";
        return;
    }

    std::cout << "NULL <- ";
    Node* temp = head;
    while (temp != nullptr) {
        std::cout << temp->data;
        if (temp->next != nullptr) {
            std::cout << " <-> ";
        }
        temp = temp->next;
    }
    std::cout << " -> NULL\n";
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
void deleteNode(Node*& head, int val) {
    if (head == nullptr) {
        std::cout << "Nothing to delete, the list is empty.\n";
        return;
    }

    // Case 1: The node to delete is the head node
    if (head->data == val) {
        Node* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        delete temp;
        std::cout << "Deleted " << val << " from the head.\n";
        return;
    }

    Node* current = head;
    // Case 2: The node is somewhere in the middle or end
    while (current->next != nullptr && current->next->data != val) {
        current = current->next;
    }

    // If the value was found
    if (current->next != nullptr) {
        Node* temp = current->next;
        current->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = current;
        }
        delete temp;
        std::cout << "Deleted " << val << " from the list.\n";
    } else {
        std::cout << "Value " << val << " not found in the list.\n";
    }
}
// 4. MEMORY MANAGEMENT
// Safely deletes all nodes to prevent memory leaks
void freeList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

   // Demo: insert, search, delete, then free all nodes.
//     std::cout << "--- Inserting Elements ---\n";
//     insertAtTail(head, 10);
//     insertAtTail(head, 20);
//     insertAtTail(head, 30);
//     insertAtTail(head, 5);
//     printPointerList(head);

//     std::cout << "\n--- Searching Elements ---\n";
//     std::cout << "Searching for 20: " << (searchNode(head, 20) ? "Found" : "Not Found") << "\n";
//     std::cout << "Searching for 99: " << (searchNode(head, 99) ? "Found" : "Not Found") << "\n";

//     std::cout << "\n--- Deleting Elements ---\n";
//     std::cout << "Deleting 20 (middle node):\n";
//     deleteNode(head, 20);
//     printPointerList(head);

//     std::cout << "Deleting 10 (head node):\n";
//     deleteNode(head, 10);
//     printPointerList(head);

//     // Clean up memory before exiting
//     freeList(head);


int main() {
    Node* head = nullptr;
    int choice = 0;
    int value = 0;

    while (true) {
        std::cout << "\n====================================\n";
        std::cout << " DOUBLY LINKED LIST INTERACTIVE SYSTEM \n";
        printPointerList(head);
        std::cout << "====================================\n";
        std::cout << "1. Insert Node at Tail\n";
        std::cout << "2. Insert Node at Head\n";
        std::cout << "3. Search for a Node\n";
        std::cout << "4. Delete a Node\n";
        std::cout << "5. Exit Program\n";
        std::cout << "------------------------------------\n";
        std::cout << "Enter your choice (1-5): ";

        // Safety check for non-integer inputs
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input detected. Shutting down...\n";
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
                std::cout << ">> Freeing memory and exiting program. Goodbye!\n";
                freeList(head);
                return 0;

            default:
                std::cout << ">> Invalid choice. Please select a number between 1 and 5.\n";
        }
    }

    return 0;
}
