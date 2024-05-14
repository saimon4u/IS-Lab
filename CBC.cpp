#include"structures.h"
#include<bits/stdc++.h>
using namespace std;
void encrypt(){
    freopen("input.txt","r",stdin);
    char message[14];

    cout << "Enter the message to encrypt: ";
    cin.getline(message, sizeof(message));
    cout << message << endl;

    // Pad message to 16 bytes
    int originalLen = strlen((const char *)message);

    int paddedMessageLen = originalLen;

    if ((paddedMessageLen % 16) != 0){
        paddedMessageLen = (paddedMessageLen / 16 + 1) * 16;
    }

    unsigned char * paddedMessage = new unsigned char[paddedMessageLen];

    int cnt=0;
    for (int i = 0; i < paddedMessageLen; i++){
        if (i >= originalLen){
            paddedMessage[i]=0;
        }
        else{
            paddedMessage[i]= message[i];
        }
        cnt++;
    }

    unsigned char * encryptedMessage = new unsigned char[paddedMessageLen];

    string str;
    string iv="1234567890123456";
    ifstream infile;
    infile.open("keyfile.txt", ios::in | ios::binary);

    if (infile.is_open()){
        getline(infile, str);
        infile.close();
    }

    else cout << "Unable to open file";

    istringstream hex_chars_stream(str);

    unsigned char key[16];
    int i = 0;
    unsigned int c;
    while (hex_chars_stream >> hex >> c)
    {
        key[i] = c;
        i++;
    }
    


    unsigned char expandedKey[176];

    KeyExpansion(key, expandedKey);

    for (int i = 0; i < paddedMessageLen; i += 16)     // here is changes
    {
        if(i==0)
        {
            for(int j=0;j<16;j++) paddedMessage[j]=paddedMessage[j]^iv[j];
            AESEncrypt(paddedMessage+i, expandedKey, encryptedMessage+i);
        }
        else
        {
            for(int j=0;j<16;j++) paddedMessage[j+i]=paddedMessage[j+i]^encryptedMessage[(i+j)-16];
            AESEncrypt(paddedMessage+i, expandedKey, encryptedMessage+i);
        }
    }

    cout << "Encrypted message in hex:" << endl;
    for (int i = 0; i < paddedMessageLen; i++)
    {
        cout << hex << (int) encryptedMessage[i];
        cout << " ";
    }

    cout << endl;

    ofstream outfile;
    outfile.open("message.aes", ios::out | ios::binary);
    if (outfile.is_open())
    {
        outfile << encryptedMessage;
        outfile.close();
        cout << "Wrote encrypted message to file message.aes" << endl;
    }

    else
        cout << "Unable to open file";

    // Free memory
    delete[] paddedMessage;
    delete[] encryptedMessage;
}

void decrypt(){
    string msgstr;
    ifstream infile;
    infile.open("message.aes", ios::in | ios::binary);

    if (infile.is_open())
    {
        getline(infile, msgstr); // The first line of file is the message
        cout << "Read in encrypted message from message.aes" << endl;
        infile.close();
    }

    else
        cout << "Unable to open file";

    char * msg = new char[msgstr.size()+1];

    strcpy(msg, msgstr.c_str());

    int n = strlen((const char*)msg);

    unsigned char * encryptedMessage = new unsigned char[n];

    for (int i = 0; i < n; i++)
    {
        encryptedMessage[i] = (unsigned char)msg[i];
    }

    // Free memory
    delete[] msg;

    // Read in the key
    string keystr;
    ifstream keyfile;
    keyfile.open("keyfile.txt", ios::in | ios::binary);

    if (keyfile.is_open())
    {
        getline(keyfile, keystr);
        cout << "Read in the 128-bit key from keyfile" << endl;
        keyfile.close();
    }

    else
        cout << "Unable to open file";
    istringstream hex_chars_stream(keystr);
    string s;
    string iv="shifatjahanshifa";

    unsigned char key[16];
    int i = 0;
    unsigned int c;
    while (hex_chars_stream >> hex >> c)
    {
        key[i] = c;
        i++;
    }

    unsigned char expandedKey[176];

    KeyExpansion(key, expandedKey);

    int messageLen = strlen((const char *)encryptedMessage);

    unsigned char * decryptedMessage = new unsigned char[messageLen];

    for (int i = 0; i < messageLen; i += 16)
    {
        AESDecrypt(encryptedMessage + i, expandedKey, decryptedMessage + i);

        if(i==0)
        {
            for(int j=0;j<16;j++) decryptedMessage[j]=decryptedMessage[j]^iv[j];
            //AESDecrypt(encryptedMessage + i, expandedKey, decryptedMessage + i);
        }
        else
        {
            for(int j=0;j<16;j++) decryptedMessage[j+i]=encryptedMessage[(i+j)-16]^decryptedMessage[j+i];
            //AESDecrypt(encryptedMessage + i, expandedKey, decryptedMessage + i);
        }
    }

    cout << "Decrypted message in hex:" << endl;
    for (int i = 0; i < messageLen; i++)
    {
        cout << hex << (int)decryptedMessage[i];
        if((int)decryptedMessage[i]==0) {
                messageLen=i;
                break;
        }
        cout << " ";
    }
    cout << endl;

    cout << "Decrypted message: ";
    for (int i = 0; i <= messageLen; i++)
    {
        cout << decryptedMessage[i];
    }
    cout << endl;
}
int main(){
    
    encrypt();
    decrypt();

}