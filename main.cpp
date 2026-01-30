#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Helper function (Encrypts a single string)
string encryptVigenere(string password) {
    string key = "jones";
    string encryptedPassword = "";

    // Loops through every letter of the password
    for (int i = 0; i < password.length(); i++) {
        int pvalue;
        int kvalue;
        int cipher;

        // 1. Gets the math value of the password letter
        pvalue = password[i] - 97;

        // 2. Gets the math value of the key letter
        kvalue = key[i % key.length()] - 97;

        // 3. Adds them together 
        cipher = (pvalue + kvalue) % 26;

        // 4. Sets to encryptedPassword
        encryptedPassword = encryptedPassword + static_cast<char>(cipher + 97);
    }

    return encryptedPassword;
}

int main() {
    //Phase 1 - Step 1: Generates Raw Data

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

    // Closes  files to save rawdata.txt 
    inFile.close();
    outFile.close();

    cout << "Phase 1 - Step 1 Complete: rawdata.txt generated." << endl;


    //Phase 1 - Step 2: Encrypts Data 

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
    
    cout << "Phase 1 - Step 2 Complete: encrypteddata.txt generated." << endl;
    return 0;
}