#include <bits/stdc++.h>

using namespace std;

class Byte
{
private:
	unsigned char value;
public:
	Byte();
	Byte(unsigned char val);
	void byteShift(int shift);
	Byte operator|(const Byte &byte);
	Byte operator&(const Byte &byte);
	Byte operator^(const Byte &byte);
	bool operator>(const Byte &byte);
	bool operator>=(const Byte &byte);
	bool operator==(const Byte &byte);
	Byte& operator=(const Byte &byte);
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
	void byteStreamShift(int shift);
	ByteStream operator^(const ByteStream &bs);
	ByteStream& operator=(const ByteStream &bs);
	void printBits();
	ByteStream extractBytes(unsigned int start, unsigned int end);
	friend ostream& operator<<(ostream &os, const ByteStream &bytestream);
};