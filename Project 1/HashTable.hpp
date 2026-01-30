#ifndef HASHTABLE_HPP 
#define HASHTABLE_HPP 
#include <iostream>
#include <string>

using namespace std;

// 1. Node structure for linked list
struct Node {
    string userid;
    string password; 
    Node* next;      
};

// 2. Hash Table Class Definition
class HashTable {
private:
    // Size of the table (Prime number to reduce collisions)
    static const int TABLE_SIZE = 101;

    // Array of pointers to Nodes
    Node* table[TABLE_SIZE];

    // Converts string key to index
    int hashFunction(string key);

public:
    // Constructor
    HashTable();

    // Adds a user to the table
    void insert(string userid, string password);

    // Searches for user and returns password
    string search(string userid);
    
    // Destructor
    ~HashTable();
};

#endif 