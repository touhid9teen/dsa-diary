#include <bits/stdc++.h>
#define int long long
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node(int val) : data(val), next(nullptr) {}
};

Node *createList()
{
    cout << "Enter the value n";
    int n;
    cin >> n;
    cout << "Enter n nodes";
    Node *head = nullptr, *tail = nullptr;
    while (n--)
    {
        int val;
        cin >> val;
        Node *newNode = new Node(val);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
            continue;
        }
        tail->next = newNode;
        tail = newNode;
    }
    return head;
}

Node *deleteList(Node *head)
{
    Node *temp;
    while (head != nullptr)
    {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void Do_Solve()
{
    cout << "==========================================" << endl;
    cout << "  ADVANCED LINKED LIST OPERATIONS" << endl;
    cout << "==========================================" << endl;

    while (true)
    {
        Node *head = nullptr;
        int choice;
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

        switch (choice)
        {
        case 1:
            if (head != nullptr)
                deleteList(head);
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
            if (head == nullptr)
            {
                cout << "List is empty!" << endl;
            }
            else
            {
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

    int32_t main()
    {
        ios::sync_with_stdio(false);
        cin.tie(0);

        Do_Solve();

        return 0;
    }