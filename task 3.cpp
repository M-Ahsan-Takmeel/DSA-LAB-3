#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};
class SinglyLinkedList {
private:
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}
    void insertAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        cout << "Successfully inserted " << val << " at the head.\n";
    }
    void insertAtThird(int val) {
        int count = countNodes();

        if (count < 2) {
            cout << "[Error] List has fewer than 2 nodes (Current count: " << count 
                 << "). Cannot insert specifically at 3rd position.\n";
            return;
        }
        Node* newNode = new Node(val);
        
        Node* temp = head;
        temp = temp->next;
        newNode->next = temp->next;
        temp->next = newNode;

        cout << "Successfully inserted " << val << " at the 3rd position.\n";
    }
    void displayList() const {
        if (head == nullptr) {
            cout << "List is empty: NULL\n";
            return;
        }

        Node* temp = head;
        cout << "List contents: ";
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
    void deleteLast() {
        if (head == nullptr) {
            cout << "[Error] List is empty. Nothing to delete.\n";
            return;
        }

        // Case: Only one node in the list
        if (head->next == nullptr) {
            cout << "Deleted node with value: " << head->data << "\n";
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        cout << "Deleted last node with value: " << temp->next->data << "\n";
        delete temp->next;
        temp->next = nullptr;
    }
    int countNodes() const {
        int count = 0;
        Node* temp = head;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }
    void reverseList() {
        if (head == nullptr || head->next == nullptr) {
            cout << "List reversed (or already empty/single node).\n";
            return;
        }

        Node* prev = nullptr;
        Node* current = head;
        Node* nextNode = nullptr;

        while (current != nullptr) {
            nextNode = current->next; 
            current->next = prev;     
            prev = current;        
            current = nextNode;     
        }

        head = prev;
        cout << "Linked list reversed successfully.\n";
    }
    void searchValue(int val) const {
        Node* temp = head;
        int position = 1;

        while (temp != nullptr) {
            if (temp->data == val) {
                cout << "Value " << val << " found at position (index) " << position << ".\n";
                return;
            }
            temp = temp->next;
            position++;
        }

        cout << "Value " << val << " not found in the list.\n";
    }
    ~SinglyLinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};
int main() {
    SinglyLinkedList list;
    int choice, value;
    do {
        cout << "\n=====================================\n";
        cout << "     SINGLY LINKED LIST MENU\n";
        cout << "=====================================\n";
        cout << "1. Insert at Head\n";
        cout << "2. Insert at 3rd Position\n";
        cout << "3. Display List\n";
        cout << "4. Delete Last Node\n";
        cout << "5. Count Total Nodes\n";
        cout << "6. Reverse List (Iterative)\n";
        cout << "7. Search Value\n";
        cout << "8. Exit\n";
        cout << "Enter your choice (1-8): ";
        cin >> choice;
        cout << "-------------------------------------\n";
        switch (choice) {
            case 1:
                cout << "Enter integer value to insert at head: ";
                cin >> value;
                list.insertAtHead(value);
                break;

            case 2:
                cout << "Enter integer value to insert at 3rd position: ";
                cin >> value;
                list.insertAtThird(value);
                break;

            case 3:
                list.displayList();
                break;

            case 4:
                list.deleteLast();
                list.displayList();
                break;

            case 5:
                cout << "Total nodes in the list: " << list.countNodes() << "\n";
                break;

            case 6:
                list.reverseList();
                list.displayList();
                break;

            case 7:
                cout << "Enter integer value to search: ";
                cin >> value;
                list.searchValue(value);
                break;

            case 8:
                cout << "Exiting program. Freeing memory...\n";
                break;

            default:
                cout << "Invalid choice! Please select an option between 1 and 8.\n";
        }

    } while (choice != 8);
    return 0;
}