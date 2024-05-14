#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int int64;

int64 A = 0x6a09e667f3bcc908;
int64 B = 0xbb67ae8584caa73b;
int64 C = 0x3c6ef372fe94f82b;
int64 D = 0xa54ff53a5f1d36f1;
int64 E = 0x510e527fade682d1;
int64 F = 0x9b05688c2b3e6c1f;
int64 G = 0x1f83d9abfb41bd6b;
int64 H = 0x5be0cd19137e2179;

const int64 Constants[80] = { 
    0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910,
	0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

map<string, string> hexaDigits = {
    {"0000", "0"},
    {"0001", "1"},
    {"0010", "2"},
    {"0011", "3"},
    {"0100", "4"},
    {"0101", "5"},
    {"0110", "6"},
    {"0111", "7"},
    {"1000", "8"},
    {"1001", "9"},
    {"1010", "a"},
    {"1011", "b"},
    {"1100", "c"},
    {"1101", "d"},
    {"1110", "e"},
    {"1111", "f"}
};

void addPadding(string &input){
    string binaryOfInput = "";
    for(auto i: input){
        binaryOfInput += bitset<8>(i).to_string();
    }

    int lenOfInput = binaryOfInput.length();
    int lenOfPadding;
    int extraLen = lenOfInput % 1024;

    if(1024 - extraLen >= 128){
        lenOfPadding = 1024 - extraLen;
    }
    else if(1024 - extraLen < 128){
        lenOfPadding = 2048 - extraLen;
    }

    binaryOfInput += "1";

    for(int i=0; i<lenOfPadding-129; i++){
        binaryOfInput += "0";
    }

    binaryOfInput += bitset<128>(lenOfInput).to_string();
    input.clear();
    input = binaryOfInput;
}

void createBlocks(vector<string> &blocks, string &input, int &chunkNumber){
    for(int i=0; i<input.length(); i+=1024, ++chunkNumber){
		blocks[chunkNumber] = input.substr(i, 1024);
	}
}

int64 binaryToDecimal(string binary){
	int64 value = bitset<64>(binary).to_ullong();
	return value;
}

int64 rotateRight(int64 word, int bitsNum){
	return (word >> bitsNum) | (word << (64 - bitsNum));
}

int64 shiftRight(int64 word, int bitsNum){
	return (word >> bitsNum);
}

void makeWords(string block, vector<int64> &words){
    int chunkNumber = 0;
	for(unsigned int i=0; i<block.length(); i+=64, ++chunkNumber){
		words[chunkNumber] = binaryToDecimal(block.substr(i, 64));
	}

    for(int i=16; i<80; i++){
		int64 WordA = rotateRight(words[i - 2], 19) ^ rotateRight(words[i - 2], 61) ^ shiftRight(words[i - 2], 6);
		int64 WordB = words[i - 7];
		int64 WordC = rotateRight(words[i - 15], 1) ^ rotateRight(words[i - 15], 8) ^ shiftRight(words[i - 15], 7);
		int64 WordD = words[i - 16];
		int64 word = WordA + WordB + WordC + WordD;
		words[i] = word;
	}
}

int64 ch(int64 e, int64 f, int64 g){
	return (e & f) ^ (~e & g);
}

int64 sigmaE(int64 e){
	return rotateRight(e, 14) ^ rotateRight(e, 18) ^ rotateRight(e, 41);
}

int64 sigmaA(int64 a){
	return rotateRight(a, 28) ^ rotateRight(a, 34) ^ rotateRight(a, 39);
}

int64 maj(int64 a, int64 b, int64 c){
	return (a & b) ^ (b & c) ^ (c & a);
}

void roundFunction(int roundNumber, int64 word){
    int64 T1 = H + ch(E, F, G) + sigmaE(E) + word + Constants[roundNumber];
    int64 T2 = sigmaA(A) + maj(A, B, C);
    int64 a = A, b = B, c = C, d = D, e = E, f = F, g = G, h = H;
    A = T1 + T2;
    B = a;
    C = b;
    D = c;
    E = d + T1;
    F = e;
    G = f;
    H = g;
}

string decimalToHexa(int64 decimal){
	string binary = bitset<64>(decimal).to_string();
	string hexstring = "";
	string temp;

	for (unsigned int i=0; i<binary.length(); i+=4){
		temp = binary.substr(i, 4);
		hexstring += hexaDigits[temp];
	}
	return hexstring;
}

void addConstants(int64 a, int64 b, int64 c, int64 d, int64 e, int64 f, int64 g, int64 h){
    A += a;
    B += b;
    C += c;
    D += d;
    E += e;
    F += f;
    G += g;
    H += h;
}

string generateOutput(){
    return decimalToHexa(A) + decimalToHexa(B) + decimalToHexa(C)
        + decimalToHexa(D) + decimalToHexa(E) + decimalToHexa(F)
        + decimalToHexa(G) + decimalToHexa(H);
}

string SHA(string input){
    addPadding(input);
    int blockNumber = input.length() / 1024;
    int chunkNumber = 0;

    vector<string> blocks(blockNumber);
    createBlocks(blocks, input, chunkNumber);

    vector<int64> words(80);

    for(auto block : blocks){
        words.clear();
        makeWords(block, words);

        int64 a = A, b = B, c = C, d = D, e = E, f = F, g = G, h = H;        

        for(int i=0; i<80; i++){
            roundFunction(i, words[i]);
        }
        addConstants(a, b, c, d, e, f, g, h);
    }
    return generateOutput();
}


int main(){
    // string input = "Saimon Bhuiyan";
    // // string hash = "b6d8d325c2f65b99fe2befce82261078b7dd0a0ad8365dc79a9b0428661ed13591fc2725928e392932cf37d676b0ade7c21f8008aa2bb5547961807b0902fbb0";
    // string hashValue = SHA(input);
    // cout << "Hash Value: " + hashValue << endl;

    ifstream file("keyfile.txt");
    string str;
    string file_contents;
    while (getline(file, str)){
        file_contents += str;
    }


	string res = SHA(file_contents);
	cout << res << endl;

	string val = "342ddbf7f7796d52e76c8dc3e7196d325147b9ee45a8f80c0b4925d05c29281aeacd76253d55bb7c95aa2e0cbce77b075ae95c51c69c39fefc83ec3bc657a511";
    // bool res = val == SHA(file_contents);
    // cout << res << endl;
}