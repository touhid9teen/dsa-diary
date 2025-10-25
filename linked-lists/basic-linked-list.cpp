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

// Display the linked list
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
        {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << " -> NULL" << endl;
}

// Delete the entire linked list (free memory)
void deleteList(Node *head)
{
    Node *temp;
    while (head != nullptr)
    {
        temp = head;       // Store current node
        head = head->next; // Move to next
        delete temp;       // Delete current
    }
}

void Do_Solve()
{
    int n, val;
    cout << "Enter number of elements: ";
    cin >> n;

    // Initialize both pointers to nullptr
    Node *head = nullptr, *tail = nullptr;

    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        cin >> val;
        Node *newNode = new Node(val);

        if (head == nullptr)
        {
            // First node - initialize head
            head = newNode;
            tail = newNode;
        }
        else
        {
            // Link the new node to the end
            tail->next = newNode;
            tail = newNode; // Update tail
        }
    }

    // Display the list
    displayList(head);

    // Clean up memory
    deleteList(head);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    Do_Solve();

    return 0;
}