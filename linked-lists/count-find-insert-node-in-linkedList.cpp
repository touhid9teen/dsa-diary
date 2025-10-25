#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int value)
    {
        data = value;
        next = nullptr;
    }
};

// Function 1: Display the linked list
void displayList(Node *head)
{
    if (head == nullptr)
    {
        cout << "List is empty!" << endl;
        return;
    }

    Node *temp = head;
    cout << "Linked List: ";
    while (temp != nullptr)
    {
        cout << temp->data;
        if (temp->next != nullptr)
            cout << " -> ";
        temp = temp->next;
    }
    cout << " -> NULL" << endl;
}

// Function 2: Count total nodes
int countNodes(Node *head)
{
    // YOUR CODE HERE
    // Hint: Use a counter and traverse the entire list
    int totalNode = 0;
    Node *temp = head;
    while (temp != nullptr)
    {
        totalNode++;
        temp = temp->next;
    }
    return totalNode;
}

// Function 3: Search for an element
bool search(Node *head, int value)
{
    // YOUR CODE HERE
    // Hint: Traverse and compare each node's data with value
    Node *temp = head;
    while (temp != nullptr)
    {
        if (temp->data == value)
            return true;
        temp = temp->next;
    }
    return false;
}

// Function 4: Insert at beginning
Node *insertAtBeginning(Node *head, int value)
{
    // YOUR CODE HERE
    // Hint: Create new node, link it to current head, return new node
    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
    return head;
}

// Function 5: Delete entire list (cleanup)
void deleteList(Node *head)
{
    Node *temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

// Function 6: Create list from user input
Node *createList()
{
    int n, val;
    cout << "\nEnter number of elements: ";
    cin >> n;

    Node *head = nullptr, *tail = nullptr;

    if (n > 0)
    {
        cout << "Enter " << n << " elements: ";
        for (int i = 0; i < n; i++)
        {
            cin >> val;
            Node *newNode = new Node(val);

            if (head == nullptr)
            {
                head = newNode;
                tail = newNode;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    return head;
}

int main()
{
    Node *head = nullptr;
    int choice, value;

    cout << "==================================" << endl;
    cout << "  LINKED LIST OPERATIONS MENU" << endl;
    cout << "==================================" << endl;

    while (true)
    {
        cout << "\n--- Menu ---" << endl;
        cout << "1. Create/Reset List" << endl;
        cout << "2. Display List" << endl;
        cout << "3. Count Nodes" << endl;
        cout << "4. Search Element" << endl;
        cout << "5. Insert at Beginning" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Create new list
            if (head != nullptr)
            {
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
            if (search(head, value))
            {
                cout << "Element " << value << " FOUND in the list!" << endl;
            }
            else
            {
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