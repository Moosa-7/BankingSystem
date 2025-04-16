//Muhammad Moosa-2023469
//Muhammad Abdullah-2023342

#include <iostream>
#include <string>
using namespace std;

struct Transactions {
public:
    string type;
    int amount;

    Transactions(){
        type="";
        amount=0;
    }

    Transactions(string type, int amount) {
        this->type = type;
        this->amount = amount;
    }
};

struct TransactionNode {
public:
    Transactions data;
    TransactionNode* next;

    TransactionNode(Transactions transaction){
        data=transaction;
        next=nullptr; 
    }
};

class TransactionQueue {
public:
    TransactionNode* front;
    TransactionNode* rear;

    TransactionQueue(){
    
        front=nullptr;
        rear=nullptr; 
    
    }

    void enqueue(Transactions transaction) {

        TransactionNode* newNode = new TransactionNode(transaction);
        if (rear==nullptr) {
            front = rear = newNode;
        } 
        
        else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    Transactions dequeue() {
        if (front==nullptr) {
            throw runtime_error("Queue is empty");
        }

        TransactionNode* temp = front;
        Transactions transaction = temp->data;

        front = front->next;
        
        if (front=nullptr) {
            rear = nullptr;
        }
        
        delete temp;
        return transaction;
    }

    bool isEmpty() {
        return front == nullptr;
    }
};

struct Node {
public:
    long acc_num;
    string name;
    string address;
    long long ph_num;
    long amount;
    int pin;

    TransactionQueue transactionHistory;
    Node* left;
    Node* right;

    Node(long acc_num, string name, string address, long long ph_num, long amount, int pin) {

        this->acc_num = acc_num;
        this->name = name;
        this->address = address;
        this->ph_num = ph_num;
        this->amount = amount;
        this->pin = pin;
        this->left = nullptr;
        this->right = nullptr;
    }

    long getBalance() const {
        return this->amount;
    }
};


class BST {
public:
    Node* root;

    BST(){
         root=nullptr;
    }

    void insert(Node* newNode) {
        if (root==nullptr) {
            root = newNode;
        } else {
            insertRec(root, newNode);
        }
    }

    bool search(long acc_num) {
        return searchRec(root, acc_num);
    }

    Node* findNode(long acc_num) {
        return findNodeRec(root, acc_num);
    }

private:
    void insertRec(Node* current, Node* newNode) {
        if (newNode->acc_num < current->acc_num) {

            if (current->left==nullptr) {
                current->left = newNode;
            } else {
                insertRec(current->left, newNode);
            }
        } else {
            if (current->right==nullptr) {
                current->right = newNode;
            } else {
                insertRec(current->right, newNode);
            }
        }
    }

    bool searchRec(Node* current, long acc_num) {
        if (!current) {
            return false;
        }
        if (current->acc_num == acc_num) {
            return true;
        } else if (acc_num < current->acc_num) {
            return searchRec(current->left, acc_num);
        } else {
            return searchRec(current->right, acc_num);
        }
    }

    Node* findNodeRec(Node* current, long acc_num) {
        if (current==nullptr || current->acc_num == acc_num) {
            return current;
        } else if (acc_num < current->acc_num) {
            return findNodeRec(current->left, acc_num);
        } else {
            return findNodeRec(current->right, acc_num);
        }
    }
};

class BankingSystem {
private:
    Node* head;
    BST bst;
    long accountNumbers[100]; 
    int accountCount; 

public:
    BankingSystem(){
        head=nullptr; 
        accountCount=0; 
    }

    void addCustomer(long acc_num, string name, string address, long long ph_num, long amount, int pin) {
    
        if (amount < 0) {
            cout << "Initial amount cannot be negative!" << endl;
            return;
        }

        Node* newNode = new Node(acc_num, name, address, ph_num, amount, pin);

        if (head==nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->right) {
                temp = temp->right;
            }
            temp->right = newNode;
        }

        bst.insert(newNode);
        accountNumbers[accountCount++] = acc_num;

        cout << "\nWelcome Aboard!!!\nYour Account has been created! \n" << endl;
    }

    void displayCustomers() {

        for (int i = 0; i < accountCount; ++i) {
        
            Node* accountNode = bst.findNode(accountNumbers[i]);
        
            if (accountNode) {
                cout << "Client " << i + 1 << " Details" << endl;
                cout << "Account Number -> " << accountNode->acc_num << endl;
                cout << "Account Holder's Name -> " << accountNode->name << endl;
                cout << "Account Holder's Address -> " << accountNode->address << endl;
                cout << "Account Holder's Contact Information -> " << accountNode->ph_num << endl;
            }
        }
    }

    void performTransaction(long acc_num) {
        
        Node* accountNode = bst.findNode(acc_num);
        
        if (!accountNode) {
            cout << "Account not found!" << endl;
            return;
        }

        int enteredPin;
        cout << "Enter your PIN: ";
        cin >> enteredPin;

        if (enteredPin != accountNode->pin) {
            cout << "Incorrect PIN!" << endl;
            return;
        }

        int opt2;
        cout << "1. Cash Deposit " << endl;
        cout << "2. Cash Withdrawal " << endl;
        cout << "3. Exit" << endl;
        cout << "Enter option : ";
        cin >> opt2;

        Transactions temp;

        switch (opt2) {
        case 1: {
            cout << "Enter the amount you want to deposit: ";
            int deposit;
            cin >> deposit;

            if (deposit <= 0) {
                cout << "Deposit amount must be positive!" << endl;
                return;
            }

            accountNode->amount += deposit;
            cout << "Amount $" << deposit << " deposited successfully!\nYour current balance is: $" << accountNode->amount << endl;
            temp = Transactions("DEPOSIT", deposit);
            accountNode->transactionHistory.enqueue(temp);
            break;
        }

        case 2: {
            cout << "Enter the amount you want to withdraw: ";
            int withdraw;
            cin >> withdraw;

            if (withdraw <= 0) {
                cout << "Withdrawal amount must be positive!" << endl;
                return;
            }

            if (accountNode->amount >= withdraw) {
                accountNode->amount -= withdraw;
                cout << "Amount $" << withdraw << " withdrawn successfully!\nYour current balance is: $" << accountNode->amount << endl;
                temp = Transactions("WITHDRAW", withdraw);
                accountNode->transactionHistory.enqueue(temp);
            } else {
                cout << "Insufficient Balance for the withdrawal!" << endl;
            }
            break;
        }

        default:
            cout << "Invalid option" << endl;
            break;
        }
    }

    void displayTransactionHistory(long acc_num) {
        Node* accountNode = bst.findNode(acc_num);
        if (!accountNode) {
            cout << "Account not found!" << endl;
            return;
        }

        cout << "Transaction history for Account Number " << acc_num << " is:" << endl;
        while (!accountNode->transactionHistory.isEmpty()) {
            Transactions record = accountNode->transactionHistory.dequeue();
            cout << "Transaction Type: " << record.type << ", Amount: $" << record.amount << endl;
        }
    }
};

int main() {
    BankingSystem bankingSystem;

    long acc_num;
    string name, address;
    long long ph_num;
    long amount;
    int pin;

    int opt;

    do {
        cout <<endl<< "WELCOME TO SIMULATED BANKING SYSTEM" << endl;
        cout << "==== MENU ====" << endl;
        cout << "1. Open New Account" << endl;
        cout << "2. Show Account Holder Details" << endl;
        cout << "3. Perform Transaction" << endl;
        cout << "4. Display Transaction History" << endl;
        cout << "5. Exit" <<endl<<endl;
        cout << "Enter choice : ";
        cin >> opt;

        switch (opt) {
        case 1:
            cout<<endl << "Enter account number: ";
            cin >> acc_num;
            cout << "Enter your name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter your address: ";
            getline(cin, address);
            cout << "Enter your phone number: ";
            cin >> ph_num;
            cout << "Enter initial amount: ";
            cin >> amount;
            cout << "Enter Pin : ";
            cin >> pin;

            bankingSystem.addCustomer(acc_num, name, address, ph_num, amount, pin);
            break;

        case 2:
            bankingSystem.displayCustomers();
            break;

        case 3:
            cout << "Enter your account number: ";
            cin >> acc_num;
            bankingSystem.performTransaction(acc_num);
            break;

        case 4:
            cout << "Enter your account number: ";
            cin >> acc_num;
            bankingSystem.displayTransactionHistory(acc_num);
            break;

        case 5:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid option! Please try again." << endl;
            break;
        }

    } while (opt != 5);

    return 0;
}
