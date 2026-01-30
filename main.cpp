#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>     
#include <iomanip>    // Required for output formatting
#include "HashTable.hpp" 

using namespace std;

// Helper function (Encrypts a single string)
string encryptVigenere(string password) {
    string key = "jones";
    string encryptedPassword = "";

    // Loops through every letter of the password
    for (int i = 0; i < password.length(); i++) {

        // 1. Gets the math value of the password letter
        int pvalue = password[i] - 97;

        // 2. Gets the math value of the key letter
        int kvalue = key[i % key.length()] - 97;

        // 3. Adds them together 
        int cipher = (pvalue + kvalue) % 26;

        // 4. Sets to encryptedPassword
        encryptedPassword = encryptedPassword + static_cast<char>(cipher + 97);
    }

    return encryptedPassword;
}

int main() {
    // Phase 1 - Step 1: Generates Raw Data

    // Seeds the random generator 
    srand(time(0)); 

    // Reads and write files
    ifstream inFile("names.txt");   
    ofstream outFile("rawdata.txt"); 

    // Check if names.txt actually has name
    if (!inFile.is_open()) {
        cout << "Error: Could not find names.txt" << endl;
        return 1; 
    }

    string userid;

    // Checks userids
    while (inFile >> userid) {
        
        // Creates empty password for userid
        string password = "";

        // Generates a 9 length random character string
        for (int i = 0; i < 9; i++) {
            // Generates a random number between 0 and 25
            int randomOffset = rand() % 26;
            
            // Add 97 (which is the ASCII value for 'a')
            int value = 97 + randomOffset;

            // Changes integer to letter
            char randomChar = static_cast<char>(value);

            // Creates password
            password = password + randomChar;
        }

        // Writes to the new file
        outFile << userid << " " << password << endl;
    }

    // Closes files to save rawdata.txt 
    inFile.close();
    outFile.close();

    // Phase 1 - Step 2: Encrypts Data 

    // Reads updated rawdata.txt and creates the encrypted file
    ifstream rawInput("rawdata.txt");
    ofstream encryptedFile("encrypteddata.txt");

    string rUser;
    string rPass;

    // Checks rawdata
    while (rawInput >> rUser >> rPass) {
        
        // Encrypts the password using helper function
        string securePass = encryptVigenere(rPass);
        
        // Writes userid and encrypted password to new file
        encryptedFile << rUser << " " << securePass << endl;
    }

    // Close the files to save
    rawInput.close();
    encryptedFile.close();
    
    // Phase 2: Hash Table & Testing

    // 1. Builds the Hash Table
    HashTable myTable;
    
    ifstream dbFile("encrypteddata.txt");
    string dbUser, dbPass;
    
    // Load every single user into the table
    while (dbFile >> dbUser >> dbPass) {
        myTable.insert(dbUser, dbPass);
    }
    dbFile.close();

    // 2. Get Test Cases from rawdata.txt
    vector<string> testUsers;
    vector<string> testPasses;

    ifstream rawTest("rawdata.txt");
    string tUser;
    string tPass;
    int counter = 0;

    while (rawTest >> tUser >> tPass) {
        counter++;
        // Checks if this is the 1st, 3rd, 5th, 7th, or 9th entry
        if (counter == 1 || counter == 3 || counter == 5 || counter == 7 || counter == 9) {
            testUsers.push_back(tUser);
            testPasses.push_back(tPass);
        }
    }
    rawTest.close();

    // 3. Runs Legal Tests 
    cout << "Legal:\n\n" 
         << left << setw(15) << "Userid" 
         << left << setw(20) << "Password (file)" 
         << left << setw(25) << "Password (table/un)" 
         << "Result" << endl;

    for (int i = 0; i < testUsers.size(); i++) {
        string user = testUsers[i];
        string rawPass = testPasses[i];
        
        // Encrypts the raw password 
        string encPass = encryptVigenere(rawPass);
        
        // Searchs for it in the table
        string tablePass = myTable.search(user);

        // Check if it matches
        string result = (tablePass == encPass) ? "match" : "no match";

        // Output results
        cout << left << setw(15) << user 
             << left << setw(20) << rawPass 
             << left << setw(25) << tablePass 
             << result << endl;
    }
/*
    // 4. Run Illegal Tests (Expect No Match)
    cout << "\nIllegal:\n\n"
         << left << setw(15) << "Userid" 
         << left << setw(20) << "Password (mod)" 
         << left << setw(25) << "Password (table/un)" 
         << "Result" << endl;

    for (int i = 0; i < testUsers.size(); i++) {
        string user = testUsers[i];
        string rawPass = testPasses[i];

        // Modifies the password (
        if (rawPass[0] == 'z') { 
            rawPass[0] = 'y'; 
        } else { 
            rawPass[0] = 'z'; 
        }

        // Encrypts the temp password
        string tempPass = encryptVigenere(rawPass);

        // Searches for the correct user
        string tablePass = myTable.search(user);

        // Compares: tablePass (Real) vs badEncPass (Fake)
        string result = (tablePass == tempPass) ? "match" : "no match";

        // Output results
        cout << left << setw(15) << user 
             << left << setw(20) << rawPass 
             << left << setw(25) << tablePass 
             << result << endl;
    }
*/
    return 0;
}