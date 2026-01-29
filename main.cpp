#include <iostream>  
#include <fstream>   
#include <string>   
#include <cstdlib>  
#include <ctime>    

using namespace std;

int main() {
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
        
        // Create empty password for userid
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

        //Writes to the new file
        outFile << userid << " " << password << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}