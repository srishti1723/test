#include<bits/stdc++.h>
using namespace std;
string key;
map<int,int> keyMap;
void setPermutationOrder(){
for(int i=0;i<key.length();i++)
{
keyMap[key[i]] = i;
}
}
string encryptMessage(string msg){
int row,col,j,k=0;
string cipher = "";
row = ceil((float) msg.length()/key.length());
col = key.length();
if (msg.length() % col)
row += 1;
char matrix[row][col],mat[row][col];
cout << "\nTransposition Encryption Matrix :" << endl;
cout << "-----------------------------------" << endl;
for(int i=0; i<row ; i++){
for(int j=0; j<col; j++){
if(k < msg.length())
cout << (mat[i][j] = msg[k++]) << " ";
else
cout << (mat[i][j] = 'x') << " " ;
}
cout << endl;
}
for (int i=0,k=0;i<row;i++){
for (int j=0;j<col;){
if(msg[k] == '\0'){
matrix[i][j] = 'x';
j++;
}
if( isalpha(msg[k])){
matrix[i][j] = msg[k];
j++;
}
k++;
}
}
for (auto ii=keyMap.begin();ii!=keyMap.end();++ii){
j=ii->second;
for (int i=0; i<row; i++){
if( isalpha(matrix[i][j]))
cipher += matrix[i][j];
}
}
return cipher;
}
string decryptMessage(string cipher){
int col = key.length();
int row = cipher.length()/col;
char cipherMat[row][col];
for (int j=0,k=0; j<col; j++)
for (int i=0; i<row; i++)
cipherMat[i][j] = cipher[k++];
int index = 0;
for( auto ii=keyMap.begin();ii!=keyMap.end();++ii)
ii->second = index++;
char deCipher[row][col];
auto ii=keyMap.begin();
int k = 0;
for (int l=0,j; key[l]!='\0'; k++){
j = keyMap[key[l++]];
for (int i=0; i<row; i++){
deCipher[i][k]=cipherMat[i][j];
}
}
cout << "\nTransposition Decryption Matrix :" << endl;
cout << "-----------------------------------" << endl;
for(int i=0;i<row ;i++){
for(int j=0;j<col ;j++){
if(cipherMat[i][j] != 'x')
cout<<cipherMat[i][j]<< " ";
}
cout<<endl;
}
string msg = "";
cout << "\nTransposition Decryption Matrix :" << endl;
cout << "-----------------------------------" << endl;
for (int i=0; i<row; i++){
for(int j=0; j<col; j++){
if(deCipher[i][j] != 'x'){
cout << deCipher[i][j]<< " ";
msg += deCipher[i][j];
}
}
cout << endl;
}
return msg;
}
int main(void)
{
string msg,cipher,decipher;
cout << "Enter the message: ";
cin >> msg;
cout<<"Enter the key: ";
cin >> key;
cout <<endl;
setPermutationOrder();
cipher = encryptMessage(msg);
cout << "Encrypted Message: " << cipher << endl;
decipher = decryptMessage(cipher);
cout << "Decrypted Message: " << decipher << endl;
return 0;
}
