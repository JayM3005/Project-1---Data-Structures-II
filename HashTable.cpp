#include "HashTable.hpp"

// Constructor: Initializes table buckets to nullptr
HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }
}

// Hash Function: Calculates index based on ASCII sum
int HashTable::hashFunction(string key) {
    int sum = 0;
    
    // Sum ASCII values of characters
    for (int i = 0; i < key.length(); i++) {
        sum = sum + key[i];
    }

    //Locks range for table size
    return sum % TABLE_SIZE;
}

// Inserts a new user into the table to the front
void HashTable::insert(string userid, string password) {
    // 1. Gets bucket index
    int index = hashFunction(userid);

    // 2. Allocate memory for new node
    Node* newNode = new Node;
    newNode->userid = userid;
    newNode->password = password;

    // 3. Links new node to current head of list
    newNode->next = table[index];

    // 4. Updates bucket to point to new node
    table[index] = newNode;
}

// Destructor: Frees allocated memory
HashTable::~HashTable() {
    // Checks through all buckets
    for (int i = 0; i < TABLE_SIZE; i++) {
        
        Node* current = table[i];
        
        // Deletes all nodes in the list
        while (current != nullptr) {
            Node* trash = current;      
            current = current->next;    
            delete trash;               
        }
        
        table[i] = nullptr;
    }
}

// Search: Finds user and returns encrypted password
string HashTable::search(string userid) {
    // 1. Gets bucket index
    int index = hashFunction(userid);
    
    Node* current = table[index];

    // 2. Cross checks the linked list
    while (current != nullptr) {
        
        // Checks if it matches
        if (current->userid == userid) {
            return current->password; 
        }
        
        current = current->next;
    }

    // 3. User not found
    return ""; 
}