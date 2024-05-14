#include <bits/stdc++.h>
#include "Header.h"
using namespace std ;


void CBC_TEST(){
    ifstream file("input.txt");
    string str;
    string file_contents;
    while (getline(file, str)){
        file_contents += str;
        file_contents.push_back('\n');
    }
    string encryptedText = cbcEncryption( file_contents );
    string decryptedText = cbcDecryption( encryptedText );
    cout << "Encrypted file is generated as \"CBC-Encrypted.txt\" and Decrypted file is generated as \"CBC-Deccrypted.txt\". Thank You!" << endl;
}

void COUNTER_TEST(){
    ifstream file("input.txt");
    string str;
    string file_contents;
    while (getline(file, str)){
        file_contents += str;
        file_contents.push_back('\n');
    }
    string encryptedText = counterEncryption( file_contents );
    string decryptedText = counterDecryption( encryptedText );
    cout << "Encrypted file is generated as \"Counter-Encrypted.txt\" and Decrypted file is generated as \"Counter-Deccrypted.txt\". Thank You!" << endl;
}

void HASH_TEST(){
    ifstream file("input.txt");
    string str;
    string file_contents;
    while (getline(file, str)){
        file_contents += str;
    }
    string hashValue = SHA(file_contents);
    cout << "Hash file is generated as \"Hash-Value.txt\". Thank You!" << endl;
}


int main(){
    // CBC_TEST();
    // COUNTER_TEST();
    HASH_TEST();
}