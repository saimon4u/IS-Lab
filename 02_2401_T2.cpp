#include<bits/stdc++.h>
using namespace std;

string output;
vector <bool> characters(26);


void generateMatrix(vector<vector<char>> &matrix, string key){
    int i = 0, j = 0;
    characters['I' - 'A'] = true;
    for(auto k: key){
        if(characters[k-'A']) continue;
        matrix[i][j] = k;
        characters[k-'A'] = true;
        j++;
        if(j==5){
            j = 0;
            i++;
        }
    }
    int k = 0;
    while(i<5){
        for(; j<5; j++){
            while(characters[k]){
                k++;
            }
            matrix[i][j] = toupper(k+'A');
            characters[k] = true;
        }
        j = 0;
        i++;
    }
}

void groupInputText(string input, vector<string> &group){
    string res;
    for(int i=0; i<input.size(); i++){
        if(input[i] == ' '){
            group.push_back(" ");
            continue;
        }
        int j = i+1;
        if(input[i] == input[j] or i == input.size()-1){
            res.push_back(input[i]);
            res.push_back('x');
        }
        else{
            res.push_back(input[i]);
            res.push_back(input[j]);
            i++;
        }
        group.push_back(res);
        res.clear();
    }
}


void encrypt(string diag, vector<vector<char>> &matrix){
    if(diag == " "){
        output += diag;
        return;
    }
    int index[2][2];

    for(int i=0; i<diag.size(); i++){
        for(int j=0; j<matrix.size(); j++){
            for(int k=0; k<matrix[j].size(); k++){
                if(toupper(diag[i]) == matrix[j][k]){
                    index[i][0] = j;
                    index[i][1] = k;
                    break;
                }
            }
        }
    }
    string res;

    if(index[0][0] == index[1][0]){
        res.push_back(matrix[index[0][0]][index[0][1]+1]);
        res.push_back(matrix[index[1][0]][index[1][1]+1]);
    }
    else if(index[0][1] == index[1][1]){
        res.push_back(matrix[index[0][0]+1][index[0][1]]);
        res.push_back(matrix[index[1][0]+1][index[1][1]]);
    }
    else{
        res.push_back(matrix[index[0][0]][index[1][1]]);
        res.push_back(matrix[index[1][0]][index[0][1]]);
    }
    output += res;
}

int main(){
    string key = "MONARCHY";

    vector<vector<char>> matrix(5, vector<char>(5));

    generateMatrix(matrix, key);
    


    cout << "Enter your input text: ";
    string input;
    getline(cin, input);
    replace(input.begin(), input.end(), 'i', 'j');
    vector<string> diag;

    groupInputText(input, diag);



    for(auto d: diag){
        encrypt(d,matrix);
    }

    cout << "Encrypted text: " +  output << endl;
    //JBSUPMNA
}