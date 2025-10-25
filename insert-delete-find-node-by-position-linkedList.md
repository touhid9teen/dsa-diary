# 🚀 Phase 3: Advanced Linked List Operations

## 📋 Complete Challenge - All 7 Advanced Operations

Build upon your previous program and implement these **7 advanced operations** in one complete menu-driven application!

---

## 🎯 Overview of Operations

| Operation           | Difficulty | Key Concept                |
| ------------------- | ---------- | -------------------------- |
| Insert at End       | ⭐⭐       | Traverse to last node      |
| Insert at Position  | ⭐⭐⭐     | Navigate to specific index |
| Delete at Beginning | ⭐⭐       | Update head pointer        |
| Delete at End       | ⭐⭐⭐     | Track previous node        |
| Delete by Value     | ⭐⭐⭐     | Search and remove          |
| Reverse List        | ⭐⭐⭐⭐   | Pointer manipulation       |
| Find Middle         | ⭐⭐⭐⭐   | Two-pointer technique      |

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

// Helper: Display the linked list
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

// Helper: Count nodes
int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

// ============================================
// CHALLENGE 1: Insert at End
// ============================================
Node* insertAtEnd(Node* head, int value) {
    // YOUR CODE HERE
    // Steps:
    // 1. Create new node
    // 2. If list is empty, return new node as head
    // 3. Otherwise, traverse to last node
    // 4. Link last node to new node
    // 5. Return head (unchanged)
}

// ============================================
// CHALLENGE 2: Insert at Position
// ============================================
Node* insertAtPosition(Node* head, int value, int position) {
    // YOUR CODE HERE
    // Steps:
    // 1. If position is 0, insert at beginning
    // 2. Create new node
    // 3. Traverse to (position-1)th node
    // 4. Link: newNode->next = current->next
    // 5. Link: current->next = newNode
    // 6. Return head
    //
    // Edge case: If position > list length, insert at end
}

// ============================================
// CHALLENGE 3: Delete at Beginning
// ============================================
Node* deleteAtBeginning(Node* head) {
    // YOUR CODE HERE
    // Steps:
    // 1. Check if list is empty
    // 2. Store head in temp
    // 3. Move head to next node
    // 4. Delete temp
    // 5. Return new head
}

// ============================================
// CHALLENGE 4: Delete at End
// ============================================
Node* deleteAtEnd(Node* head) {
    // YOUR CODE HERE
    // Steps:
    // 1. Check if list is empty or has only one node
    // 2. Traverse to second-last node
    // 3. Delete last node
    // 4. Set second-last node's next to nullptr
    // 5. Return head
}

// ============================================
// CHALLENGE 5: Delete by Value
// ============================================
Node* deleteByValue(Node* head, int value) {
    // YOUR CODE HERE
    // Steps:
    // 1. Check if head contains the value (special case)
    // 2. Traverse to find the node before target
    // 3. Link: prev->next = prev->next->next
    // 4. Delete the target node
    // 5. Return head
    //
    // Edge case: Value not found - return head unchanged
}

// ============================================
// CHALLENGE 6: Reverse the List
// ============================================
Node* reverseList(Node* head) {
    // YOUR CODE HERE
    // Steps (Three Pointer Approach):
    // 1. Initialize: prev = nullptr, current = head, next = nullptr
    // 2. Loop while current != nullptr:
    //    - Store next: next = current->next
    //    - Reverse link: current->next = prev
    //    - Move pointers: prev = current, current = next
    // 3. Return prev (new head)
}

// ============================================
// CHALLENGE 7: Find Middle Element
// ============================================
int findMiddle(Node* head) {
    // YOUR CODE HERE
    // Two Pointer Technique (Slow-Fast):
    // 1. Initialize: slow = head, fast = head
    // 2. Loop while fast and fast->next are not null:
    //    - Move slow by 1: slow = slow->next
    //    - Move fast by 2: fast = fast->next->next
    // 3. When fast reaches end, slow is at middle
    // 4. Return slow->data
    //
    // Edge case: Empty list - return -1 or handle appropriately
}

// Helper: Delete entire list
void deleteList(Node* head) {
    Node* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

// Helper: Create list from input
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
    int choice, value, position;

    cout << "==========================================" << endl;
    cout << "  ADVANCED LINKED LIST OPERATIONS" << endl;
    cout << "==========================================" << endl;

    while (true) {
        cout << "\n--- Menu ---" << endl;
        cout << "1.  Create/Reset List" << endl;
        cout << "2.  Display List" << endl;
        cout << "3.  Insert at End" << endl;
        cout << "4.  Insert at Position" << endl;
        cout << "5.  Delete at Beginning" << endl;
        cout << "6.  Delete at End" << endl;
        cout << "7.  Delete by Value" << endl;
        cout << "8.  Reverse List" << endl;
        cout << "9.  Find Middle Element" << endl;
        cout << "10. Count Nodes" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (head != nullptr) deleteList(head);
                head = createList();
                cout << "List created successfully!" << endl;
                displayList(head);
                break;

            case 2:
                displayList(head);
                break;

            case 3:
                cout << "Enter value to insert at end: ";
                cin >> value;
                head = insertAtEnd(head, value);
                cout << "Element inserted at end!" << endl;
                displayList(head);
                break;

            case 4:
                cout << "Enter value: ";
                cin >> value;
                cout << "Enter position (0-indexed): ";
                cin >> position;
                head = insertAtPosition(head, value, position);
                cout << "Element inserted at position " << position << "!" << endl;
                displayList(head);
                break;

            case 5:
                head = deleteAtBeginning(head);
                cout << "First element deleted!" << endl;
                displayList(head);
                break;

            case 6:
                head = deleteAtEnd(head);
                cout << "Last element deleted!" << endl;
                displayList(head);
                break;

            case 7:
                cout << "Enter value to delete: ";
                cin >> value;
                head = deleteByValue(head, value);
                cout << "Element deleted (if found)!" << endl;
                displayList(head);
                break;

            case 8:
                head = reverseList(head);
                cout << "List reversed!" << endl;
                displayList(head);
                break;

            case 9:
                if (head == nullptr) {
                    cout << "List is empty!" << endl;
                } else {
                    cout << "Middle element: " << findMiddle(head) << endl;
                }
                break;

            case 10:
                cout << "Total nodes: " << countNodes(head) << endl;
                break;

            case 11:
                cout << "Cleaning up and exiting..." << endl;
                deleteList(head);
                cout << "Goodbye!" << endl;
                return 0;

            default:
                cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
```

---

## 🎓 Detailed Explanations

### Challenge 1: Insert at End ⭐⭐

**Concept:** Add a new node after the last node.

**Visual:**

```
Before: 10 -> 20 -> 30 -> NULL
Insert 40 at end
After:  10 -> 20 -> 30 -> 40 -> NULL
```

**Algorithm:**

1. Create new node
2. If list is empty, return new node as head
3. Traverse to the last node (where next == nullptr)
4. Set last node's next to new node
5. Return head (unchanged)

**Key Challenge:** Finding the last node requires full traversal.

---

### Challenge 2: Insert at Position ⭐⭐⭐

**Concept:** Add a node at a specific index (0-based).

**Visual:**

```
Before: 10 -> 20 -> 40 -> NULL
Insert 30 at position 2
After:  10 -> 20 -> 30 -> 40 -> NULL
```

**Algorithm:**

1. If position is 0, insert at beginning
2. Create new node
3. Traverse to node at (position - 1)
4. Link new node: `newNode->next = current->next`
5. Link current: `current->next = newNode`

**Edge Cases:**

- Position 0: Insert at beginning
- Position > length: Insert at end
- Negative position: Handle error

---

### Challenge 3: Delete at Beginning ⭐⭐

**Concept:** Remove the first node and update head.

**Visual:**

```
Before: 10 -> 20 -> 30 -> NULL
Delete first
After:  20 -> 30 -> NULL
```

**Algorithm:**

1. Check if list is empty
2. Store current head in temp
3. Move head to head->next
4. Delete temp
5. Return new head

**Critical:** Must update and return the new head!

---

### Challenge 4: Delete at End ⭐⭐⭐

**Concept:** Remove the last node.

**Visual:**

```
Before: 10 -> 20 -> 30 -> NULL
Delete last
After:  10 -> 20 -> NULL
```

**Algorithm:**

1. Handle empty list or single node
2. Traverse to second-last node
3. Delete last node
4. Set second-last node's next to nullptr
5. Return head

**Key Challenge:** Need to track the node BEFORE the last node.

---

### Challenge 5: Delete by Value ⭐⭐⭐

**Concept:** Find and remove the first node with a specific value.

**Visual:**

```
Before: 10 -> 20 -> 30 -> 40 -> NULL
Delete value 30
After:  10 -> 20 -> 40 -> NULL
```

**Algorithm:**

1. Special case: If head contains value, delete at beginning
2. Traverse to find node before target
3. Link: `prev->next = prev->next->next`
4. Delete the target node
5. Return head

**Edge Cases:**

- Value is at head
- Value doesn't exist
- Multiple occurrences (delete first only)

---

### Challenge 6: Reverse List ⭐⭐⭐⭐

**Concept:** Reverse all the next pointers.

**Visual:**

```
Before: 10 -> 20 -> 30 -> NULL
Reverse
After:  30 -> 20 -> 10 -> NULL
```

**Algorithm (Three Pointers):**

```
prev = nullptr
current = head
next = nullptr

While current != nullptr:
    next = current->next     // Store next
    current->next = prev     // Reverse link
    prev = current           // Move prev forward
    current = next           // Move current forward

Return prev  // New head
```

**Step-by-step visualization:**

```
Initial: nullptr <- 10 -> 20 -> 30 -> NULL
         [prev]  [curr] [next]

Step 1:  nullptr <- 10   20 -> 30 -> NULL
                  [prev][curr][next]

Step 2:  nullptr <- 10 <- 20   30 -> NULL
                        [prev][curr][next]

Step 3:  nullptr <- 10 <- 20 <- 30   NULL
                              [prev][curr]
```

---

### Challenge 7: Find Middle Element ⭐⭐⭐⭐

**Concept:** Find the middle node using two-pointer technique (NO counting allowed!).

**Visual:**

```
List: 10 -> 20 -> 30 -> 40 -> 50 -> NULL
Middle: 30

List: 10 -> 20 -> 30 -> 40 -> NULL
Middle: 30 (or 20, depending on even-length handling)
```

**Algorithm (Slow-Fast Pointers):**

```
slow = head
fast = head

While fast != nullptr AND fast->next != nullptr:
    slow = slow->next          // Move 1 step
    fast = fast->next->next    // Move 2 steps

Return slow->data  // Slow is at middle
```

**Why it works:**

- Fast pointer moves twice as fast
- When fast reaches end, slow is at middle
- This is O(n/2) = O(n) but single pass!

**Visualization:**

```
Step 0: S,F -> 20 -> 30 -> 40 -> 50 -> NULL
        10

Step 1: 10 -> S -> 30 -> F -> 50 -> NULL
             20         40

Step 2: 10 -> 20 -> S -> 40 -> 50 -> F
                   30                NULL

Middle found: 30
```

---

## 🧪 Complete Test Sequence

Test all operations systematically:

```
1. Create list: 10 20 30 40 50
   Display: 10 -> 20 -> 30 -> 40 -> 50 -> NULL

2. Insert 60 at end
   Display: 10 -> 20 -> 30 -> 40 -> 50 -> 60 -> NULL

3. Insert 25 at position 2
   Display: 10 -> 20 -> 25 -> 30 -> 40 -> 50 -> 60 -> NULL

4. Delete at beginning
   Display: 20 -> 25 -> 30 -> 40 -> 50 -> 60 -> NULL

5. Delete at end
   Display: 20 -> 25 -> 30 -> 40 -> 50 -> NULL

6. Delete value 30
   Display: 20 -> 25 -> 40 -> 50 -> NULL

7. Find middle
   Output: 40 (or 25, depending on implementation)

8. Reverse list
   Display: 50 -> 40 -> 25 -> 20 -> NULL

9. Count nodes
   Output: 4
```

---

## 💡 Tips for Each Challenge

### Insert at End

```cpp
// Pseudo-code hint
if (head == nullptr) return newNode;
Node* temp = head;
while (temp->next != nullptr) {
    temp = temp->next;
}
temp->next = newNode;
```

### Insert at Position

```cpp
// Pseudo-code hint
if (position == 0) return insertAtBeginning(...);
Node* temp = head;
for (int i = 0; i < position - 1 && temp != nullptr; i++) {
    temp = temp->next;
}
// Insert here
```

### Delete at Beginning

```cpp
// Pseudo-code hint
if (head == nullptr) return nullptr;
Node* temp = head;
head = head->next;
delete temp;
return head;
```

### Delete at End

```cpp
// Pseudo-code hint
if (head->next == nullptr) { /* single node */ }
Node* temp = head;
while (temp->next->next != nullptr) {
    temp = temp->next;
}
delete temp->next;
temp->next = nullptr;
```

---

## ✅ Success Criteria

Your implementation is complete when:

- ✅ All 7 operations work correctly
- ✅ Edge cases handled (empty list, single node)
- ✅ No memory leaks
- ✅ Proper pointer updates
- ✅ List displays correctly after each operation
- ✅ All test sequences pass

---

## 🏆 Challenge Difficulty Rating

Start with the easier ones and work your way up:

**Beginner Level:**

1. Insert at End
2. Delete at Beginning

**Intermediate Level:** 3. Delete at End 4. Insert at Position 5. Delete by Value

**Advanced Level:** 6. Reverse List (Most important interview question!) 7. Find Middle (Two-pointer technique)

---

## 🚀 Ready to Code?

1. Copy the template
2. Implement functions one by one
3. Test each function thoroughly
4. Move to next only when current works perfectly
5. Share your solution when done!

**Pro Tip:** Start with Insert at End and Delete at Beginning. They're the easiest and will build your confidence!

Good luck! You've got this! 💪🔥
