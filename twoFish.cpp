#include <iostream>
#include "byteheader.hpp"

using namespace std;

int main()
{
	string plaintext = "abcdefgh";
	// cout<<"Enter the plaintext: ";
	// cin>>plaintext;

	string key = "zyxw";
	// cout<<"Enter the key: ";
	// cin>>key;

	vector<Byte> pbytes, kbytes;
	for(char c: plaintext)
		pbytes.push_back(Byte((int)c));
	for(char c: key)
		kbytes.push_back(Byte((int)c));
	
	ByteStream input_P = ByteStream(pbytes);
	ByteStream KEY = ByteStream(kbytes);

	ByteStream P[4];

	for(int i = 0; i<16; i+=4)
		P[i/4] = input_P.extractBytes(i, i+4);
	
	//input whitening
	for(int i = 0; i<16; i+=4)
		P[i/4] = P[i/4]^KEY.extractBytes(i,i+4);

	for(auto it: P)
		cout<<it<<endl;

	return 0;
}