#include <iostream>
#include <string>
using namespace std;

struct Product {
    string name;
    double price;
    string date;
    Product* next;
    Product(string n, double p, string d) {
        name = n;
        price = p;
        date = d;
        next = NULL;
    }
};

class LinkedList {
public:
    Product* head;
    LinkedList() { head = NULL; }

    void insert(string name, double price, string date) {
        Product* newNode = new Product(name, price, date);
        newNode->next = head;
        head = newNode;
    }

    void display() {
        Product* temp = head;
        if (!temp) {
            cout << "No products in this list.\n";
            return;
        }
        while (temp) {
            cout << "Name: " << temp->name << ", Price: " << temp->price << ", Date: " << temp->date << endl;
            temp = temp->next;
        }
    }

    void update(string name) {
        Product* temp = head;
        while (temp) {
            if (temp->name == name) {
                cout << "Enter new name: ";
                cin >> temp->name;
                cout << "Enter new price: ";
                cin >> temp->price;
                cout << "Enter new date: ";
                cin >> temp->date;
                cout << "Product updated.\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Product not found.\n";
    }

    void deleteProduct(string name) {
        Product* temp = head;
        Product* prev = NULL;
        while (temp && temp->name != name) {
            prev = temp;
            temp = temp->next;
        }
        if (!temp) {
            cout << "Product not found.\n";
            return;
        }
        if (!prev)
            head = temp->next;
        else
            prev->next = temp->next;
        delete temp;
        cout << "Product deleted.\n";
    }

    Product* findMostExpensive() {
        if (!head) return NULL;
        Product* max = head;
        Product* temp = head->next;
        while (temp) {
            if (temp->price > max->price)
                max = temp;
            temp = temp->next;
        }
        return max;
    }
};

struct ListNode {
    LinkedList* list;
    ListNode* next;
    ListNode(LinkedList* l) {
        list = l;
        next = NULL;
    }
};

class MasterList {
public:
    ListNode* head;
    MasterList() { head = NULL; }

    void addUserList(LinkedList* list) {
        ListNode* newNode = new ListNode(list);
        newNode->next = head;
        head = newNode;
        cout << "List added to master.\n";
    }

    void displayAll() {
        ListNode* temp = head;
        int count = 1;
        if (!temp) {
            cout << "No user lists.\n";
            return;
        }
        while (temp) {
            cout << "\nUser List #" << count++ << ":\n";
            temp->list->display();
            temp = temp->next;
        }
    }

    void showMostExpensive() {
        ListNode* temp = head;
        Product* maxProduct = NULL;
        while (temp) {
            Product* localMax = temp->list->findMostExpensive();
            if (!maxProduct || (localMax && localMax->price > maxProduct->price))
                maxProduct = localMax;
            temp = temp->next;
        }
        if (maxProduct) {
            cout << "\nMost Expensive Product:\n";
            cout << "Name: " << maxProduct->name << ", Price: " << maxProduct->price << ", Date: " << maxProduct->date << endl;
        } else {
            cout << "No products available.\n";
        }
    }
};

int main() {
    MasterList master;
    LinkedList* currentList = NULL;
    int choice;
    string name, date;
    double price;

    do {
        cout << "\n1. New user list\n2. Add product\n3. Update product\n4. Delete product\n5. Display current list\n6. Add list to master\n7. Display all lists\n8. Show most expensive\n9. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                currentList = new LinkedList();
                cout << "New list created.\n";
                break;
            case 2:
                if (!currentList) { cout << "Create list first.\n"; break; }
                cout << "Enter name, price, date: ";
                cin >> name >> price >> date;
                currentList->insert(name, price, date);
                break;
            case 3:
                if (!currentList) { cout << "Create list first.\n"; break; }
                cout << "Enter product name to update: ";
                cin >> name;
                currentList->update(name);
                break;
            case 4:
                if (!currentList) { cout << "Create list first.\n"; break; }
                cout << "Enter product name to delete: ";
                cin >> name;
                currentList->deleteProduct(name);
                break;
            case 5:
                if (!currentList) { cout << "No current list.\n"; break; }
                currentList->display();
                break;
            case 6:
                if (!currentList) { cout << "No current list.\n"; break; }
                master.addUserList(currentList);
                currentList = NULL;
                break;
            case 7:
                master.displayAll();
                break;
            case 8:
                master.showMostExpensive();
                break;
            case 9:
                cout << "Bye babe!\n";
                break;
            default:
                cout << "Invalid.\n";
        }
    } while (choice != 9);

    return 0;
}
