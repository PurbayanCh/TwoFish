#include <bits/stdc++.h>

using namespace std;

class Byte
{
private:
	unsigned char value;
public:
	Byte();
	Byte(string hex_val);
	Byte(unsigned char val);
	unsigned char getValue();
	string getString();
	Byte byteShift(int shift);
	Byte byteROR(int bits, int shift);
	Byte byteROL(int bits, int shift);
	Byte operator|(const Byte &byte);
	Byte operator&(const Byte &byte);
	Byte operator^(const Byte &byte);
	Byte operator+(const Byte &byte);
	Byte operator*(const Byte &byte);
	bool operator>(const Byte &byte);
	bool operator>=(const Byte &byte);
	bool operator==(const Byte &byte);
	Byte& operator=(const Byte &byte);
	bool getBit(unsigned int pos);
	void printBits();
	friend ostream& operator<<(ostream &os, const Byte &byte);
};

class ByteStream
{
private:
	vector<Byte> values;
	unsigned int num_bytes;
public:
	ByteStream();
	ByteStream(vector<Byte> bs);
	ByteStream(unsigned int bs);
	ByteStream(string bs);
	unsigned int getValue();
	string getString();
	ByteStream byteStreamShift(int shift);
	ByteStream byteStreamROR(int shift);
	ByteStream byteStreamROL(int shift);
	ByteStream operator|(const ByteStream &bs);
	ByteStream operator&(const ByteStream &bs);
	ByteStream operator^(const ByteStream &bs);
	ByteStream& operator=(const ByteStream &bs);
	unsigned int getNumBytes();
	ByteStream getBytes(unsigned int start, unsigned int end);
	Byte getByte(unsigned int index);
	void setBytes(unsigned int start, ByteStream bs);
	bool getBit(unsigned int pos);
	void printBits();
	friend ostream& operator<<(ostream &os, const ByteStream &bs);
};

class TwoFish
{
private:
	ByteStream M;
	vector<ByteStream> K;
	vector<ByteStream> S;

	vector<vector<Byte>>RS;
	vector<vector<Byte>>MDS;

	Byte q(Byte x, vector<vector<Byte>>&T);
	Byte q0(Byte x);
	Byte q1(Byte x);
	ByteStream h(ByteStream x, vector<ByteStream>L);
	ByteStream g(ByteStream x);
	ByteStream f(ByteStream R0, ByteStream R1, unsigned int r);

	ByteStream round(ByteStream x, unsigned int r);
	ByteStream swap(ByteStream x);

	void generateKeys();
public:
	TwoFish(string KEY);
	vector<ByteStream> getKeys();
	ByteStream inputPreprocessing(string x);
	ByteStream inputWhitening(ByteStream x);
	ByteStream outputWhitening(ByteStream x);
	ByteStream encrypt(string plaintext);
	ByteStream decrypt(string ciphertext);
};