# 🚀 Linked List Complete Challenge

## 📋 Problem Statement

Create a **complete linked list program** that implements all three operations in a single interactive application:

1. **Count Nodes** - Display total number of nodes
2. **Search Element** - Find if a value exists
3. **Insert at Beginning** - Add new node at the start

---

## 🎯 Your Mission

Build a menu-driven program that allows users to:

- Create a linked list from user input
- Count the total nodes
- Search for any element
- Insert new elements at the beginning
- Display the list at any time

---

## 📝 Complete Challenge Template

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

// Function 1: Display the linked list
void displayList(Node* head) {
    if (head == nullptr) {
        cout << "List is empty!" << endl;
        return;
    }

    Node* temp = head;
    cout << "Linked List: ";
    while (temp != nullptr) {
        cout << temp->data;
        if (temp->next != nullptr) cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL" << endl;
}

// Function 2: Count total nodes
int countNodes(Node* head) {
    // YOUR CODE HERE
    // Hint: Use a counter and traverse the entire list
}

// Function 3: Search for an element
bool search(Node* head, int value) {
    // YOUR CODE HERE
    // Hint: Traverse and compare each node's data with value
}

// Function 4: Insert at beginning
Node* insertAtBeginning(Node* head, int value) {
    // YOUR CODE HERE
    // Hint: Create new node, link it to current head, return new node
}

// Function 5: Delete entire list (cleanup)
void deleteList(Node* head) {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

// Function 6: Create list from user input
Node* createList() {
    int n, val;
    cout << "\nEnter number of elements: ";
    cin >> n;

    Node *head = nullptr, *tail = nullptr;

    if (n > 0) {
        cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; i++) {
            cin >> val;
            Node *newNode = new Node(val);

            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    return head;
}

int main() {
    Node* head = nullptr;
    int choice, value;

    cout << "==================================" << endl;
    cout << "  LINKED LIST OPERATIONS MENU" << endl;
    cout << "==================================" << endl;

    while (true) {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Create/Reset List" << endl;
        cout << "2. Display List" << endl;
        cout << "3. Count Nodes" << endl;
        cout << "4. Search Element" << endl;
        cout << "5. Insert at Beginning" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Create new list
                if (head != nullptr) {
                    deleteList(head);
                }
                head = createList();
                cout << "List created successfully!" << endl;
                displayList(head);
                break;

            case 2:
                // Display list
                displayList(head);
                break;

            case 3:
                // Count nodes
                cout << "Total nodes: " << countNodes(head) << endl;
                break;

            case 4:
                // Search element
                cout << "Enter value to search: ";
                cin >> value;
                if (search(head, value)) {
                    cout << "Element " << value << " FOUND in the list!" << endl;
                } else {
                    cout << "Element " << value << " NOT FOUND in the list!" << endl;
                }
                break;

            case 5:
                // Insert at beginning
                cout << "Enter value to insert at beginning: ";
                cin >> value;
                head = insertAtBeginning(head, value);
                cout << "Element inserted successfully!" << endl;
                displayList(head);
                break;

            case 6:
                // Exit
                cout << "Cleaning up memory and exiting..." << endl;
                deleteList(head);
                cout << "Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
```

---

## 🎮 Sample Run

```
==================================
  LINKED LIST OPERATIONS MENU
==================================

--- Menu ---
1. Create/Reset List
2. Display List
3. Count Nodes
4. Search Element
5. Insert at Beginning
6. Exit
Enter your choice: 1

Enter number of elements: 4
Enter 4 elements: 10 20 30 40
List created successfully!
Linked List: 10 -> 20 -> 30 -> 40 -> NULL

--- Menu ---
1. Create/Reset List
2. Display List
3. Count Nodes
4. Search Element
5. Insert at Beginning
6. Exit
Enter your choice: 3
Total nodes: 4

--- Menu ---
1. Create/Reset List
2. Display List
3. Count Nodes
4. Search Element
5. Insert at Beginning
6. Exit
Enter your choice: 4
Enter value to search: 30
Element 30 FOUND in the list!

--- Menu ---
1. Create/Reset List
2. Display List
3. Count Nodes
4. Search Element
5. Insert at Beginning
6. Exit
Enter your choice: 5
Enter value to insert at beginning: 5
Element inserted successfully!
Linked List: 5 -> 10 -> 20 -> 30 -> 40 -> NULL

--- Menu ---
1. Create/Reset List
2. Display List
3. Count Nodes
4. Search Element
5. Insert at Beginning
6. Exit
Enter your choice: 6
Cleaning up memory and exiting...
Goodbye!
```

---

## ✅ Your Tasks

Implement these **THREE functions**:

### Task 1: Count Nodes

```cpp
int countNodes(Node* head) {
    // Initialize counter
    // Traverse from head to NULL
    // Count each node
    // Return total count
}
```

**Expected behavior:**

- Empty list → return 0
- List with 5 nodes → return 5

---

### Task 2: Search Element

```cpp
bool search(Node* head, int value) {
    // Traverse the list
    // Compare each node's data with value
    // If found, return true
    // If reach end, return false
}
```

**Expected behavior:**

- Element exists → return true
- Element doesn't exist → return false
- Empty list → return false

---

### Task 3: Insert at Beginning

```cpp
Node* insertAtBeginning(Node* head, int value) {
    // Create new node with value
    // Point new node's next to current head
    // Return new node as new head
}
```

**Expected behavior:**

- Updates the head of the list
- Works even if list is empty
- New element becomes first element

---

## 🧪 Test Cases to Verify

After implementing all three functions, test these scenarios:

### Test 1: Basic Operations

1. Create list: `10 20 30`
2. Count nodes → Should show: `3`
3. Search for `20` → Should show: `FOUND`
4. Search for `50` → Should show: `NOT FOUND`

### Test 2: Insert at Beginning

1. Create list: `20 30 40`
2. Insert `10` at beginning
3. Display → Should show: `10 -> 20 -> 30 -> 40 -> NULL`
4. Count nodes → Should show: `4`

### Test 3: Empty List

1. Don't create any list (or create with 0 elements)
2. Count nodes → Should show: `0`
3. Search for any value → Should show: `NOT FOUND`
4. Insert element → Should create list with 1 node

### Test 4: Multiple Insertions

1. Create list: `30`
2. Insert `20` at beginning → List: `20 -> 30`
3. Insert `10` at beginning → List: `10 -> 20 -> 30`
4. Count nodes → Should show: `3`

---
---

## 🏆 Success Criteria

Your implementation is correct when:

- ✅ All menu options work without errors
- ✅ Count shows correct number of nodes
- ✅ Search finds existing elements and rejects non-existing ones
- ✅ Insert at beginning properly updates the list
- ✅ No memory leaks (program exits cleanly)
- ✅ Works with empty lists

---

## 🚀 Ready to Code?

1. Copy the template code
2. Implement the three functions (marked with YOUR CODE HERE)
3. Compile and run the program
4. Test all menu options thoroughly
5. Share your solution for review!

**Good luck!** 💪 You've got everything you need to succeed!
