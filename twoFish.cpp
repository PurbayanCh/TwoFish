#include <iostream>
#include "headers.hpp"

using namespace std;

#define KEY_LENGTH 128
#define word(x, i) x.getBytes(4*i, 4*i+4)

vector<Byte>freeBytes;
vector<vector<Byte>>RS;
vector<vector<Byte>>MDS;

ByteStream P;
ByteStream M;

void initialise(unsigned int N)
{
	string plaintext = "abcdefgh";
	// cout<<"Enter the plaintext: ";
	// cin>>plaintext;

	string key = "zyxw";
	// cout<<"Enter the key: ";
	// cin>>key;

	vector<Byte> pbytes, mbytes;
	for(char c: plaintext)
		pbytes.push_back(Byte((unsigned char)c));
	for(char c: key)
		mbytes.push_back(Byte((unsigned char)c));
	
	while(pbytes.size()<16)
		pbytes.push_back(Byte(0));
	while(mbytes.size()<16)
		mbytes.push_back(Byte(0));


	P = ByteStream(pbytes);
	M = ByteStream(mbytes);

	RS.resize(4, vector<Byte>(8));
	RS = 
	{
		{Byte("01"), Byte("a4"), Byte("55"), Byte("87"), Byte("5a"), Byte("58"), Byte("db"), Byte("9e")},
		{Byte("a4"), Byte("56"), Byte("82"), Byte("f3"), Byte("1e"), Byte("c6"), Byte("68"), Byte("e5")},
		{Byte("02"), Byte("a1"), Byte("fc"), Byte("c1"), Byte("47"), Byte("ae"), Byte("3d"), Byte("19")},
		{Byte("a4"), Byte("55"), Byte("87"), Byte("5a"), Byte("58"), Byte("db"), Byte("9e"), Byte("03")}
	};

	MDS.resize(4, vector<Byte>(4));
	MDS = 
	{
		{Byte("01"), Byte("ef"), Byte("5b"), Byte("5b")},
		{Byte("5b"), Byte("ef"), Byte("ef"), Byte("01")},
		{Byte("ef"), Byte("5b"), Byte("01"), Byte("ef")},
		{Byte("ef"), Byte("01"), Byte("ef"), Byte("5b")}
	};
}

void inputWhitening()
{
	cout<<P<<endl;
	cout<<M<<endl;
	for(int i = 0; i<4; i++)
		P.setBytes(4*i, word(P,i)^word(M,i));
	cout<<P<<endl;
}

int main()
{
	// initialise(KEY_LENGTH);
	// inputWhitening();
	Byte x("ff");
	Byte y("14");
	ByteStream X({x,y});
	return 0;
}