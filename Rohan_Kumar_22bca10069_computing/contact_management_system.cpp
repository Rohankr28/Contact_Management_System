#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
using namespace std;

// Trie Node structure
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    vector<string> contactNumbers; // To store contact numbers
    bool isEndOfContact; // Marks the end of a contact name
    
    TrieNode() {
        isEndOfContact = false;
    }
};

// Trie class for Contact Book Management
class ContactBook {
private:
    TrieNode* root;
    
public:
    ContactBook() {
        root = new TrieNode();
    }
    
    // Function to add a contact name and number
    void addContact(const string& name, const string& number) {
        TrieNode* currentNode = root;
        
        for (char c : name) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                currentNode->children[c] = new TrieNode();
            }
            currentNode = currentNode->children[c];
        }
        
        currentNode->isEndOfContact = true;
        currentNode->contactNumbers.push_back(number);
        
        cout << "Contact added: " << name << " - " << number << endl;
    }
    
    // Function to search for a contact by name
    bool searchContact(const string& name) {
        TrieNode* currentNode = root;
        
        for (char c : name) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                return false;
            }
            currentNode = currentNode->children[c];
        }
        
        if (currentNode->isEndOfContact) {
            cout << "Contact found: " << name << endl;
            for (const string& number : currentNode->contactNumbers) {
                cout << "Number: " << number << endl;
            }
            return true;
        }
        
        return false;
    }
    
    // Recursive function to delete a contact from the trie
    bool deleteHelper(TrieNode* currentNode, const string& name, int index) {
        if (index == name.size()) {
            if (!currentNode->isEndOfContact) {
                return false; // Contact not found
            }
            
            currentNode->isEndOfContact = false;
            
            // If the node has no children, it can be deleted
            return currentNode->children.empty();
        }
        
        char c = name[index];
        if (currentNode->children.find(c) == currentNode->children.end()) {
            return false; // Contact not found
        }
        
        bool shouldDeleteChild = deleteHelper(currentNode->children[c], name, index + 1);
        
        if (shouldDeleteChild) {
            delete currentNode->children[c];
            currentNode->children.erase(c);
            
            return currentNode->children.empty() && !currentNode->isEndOfContact;
        }
        
        return false;
    }
    
    // Function to delete a contact by name
    void deleteContact(const string& name) {
        if (deleteHelper(root, name, 0)) {
            cout << "Contact deleted: " << name << endl;
        } else {
            cout << "Contact not found: " << name << endl;
        }
    }
    
    // Function to display contacts starting with a prefix
    void displayContactsWithPrefix(const string& prefix) {
        TrieNode* currentNode = root;
        
        for (char c : prefix) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                cout << "No contacts found with prefix: " << prefix << endl;
                return;
            }
            currentNode = currentNode->children[c];
        }
        
        displayAllContacts(currentNode, prefix);
    }
    
    // Recursive function to display all contacts starting from a given node
    void displayAllContacts(TrieNode* currentNode, const string& prefix) {
        if (currentNode->isEndOfContact) {
            cout << "Contact: " << prefix << endl;
            for (const string& number : currentNode->contactNumbers) {
                cout << "Number: " << number << endl;
            }
        }
        
        for (auto& pair : currentNode->children) {
            displayAllContacts(pair.second, prefix + pair.first);
        }
    }
};

// Main function
int main() {
    ContactBook contactBook;
    int choice;
    string name, number, prefix;
    
    while (true) {
        cout << "\n1. Add Contact\n2. Search Contact\n3. Delete Contact\n4. Display Contacts by Prefix\n5. Exit\nEnter your choice: ";
        cin >> choice;
        
        // Check if the input is valid
        if (cin.fail()) {
            cin.clear(); // Clear error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid input! Please enter a number between 1 and 5.\n";
            continue;
        }
        
        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter number: ";
                cin >> number;
                contactBook.addContact(name, number);
                break;
            case 2:
                cout << "Enter name to search: ";
                cin >> name;
                if (!contactBook.searchContact(name)) {
                    cout << "Contact not found!\n";
                }
                break;
            case 3:
                cout << "Enter name to delete: ";
                cin >> name;
                contactBook.deleteContact(name);
                break;
            case 4:
                cout << "Enter prefix to display contacts: ";
                cin >> prefix;
                contactBook.displayContactsWithPrefix(prefix);
                break;
            case 5:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice! Please enter a number between 1 and 5.\n";
        }
    }
}
