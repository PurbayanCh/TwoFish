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
	void byteShift(int shift);
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
	void byteStreamShift(int shift);
	ByteStream operator|(const ByteStream &bs);
	ByteStream operator&(const ByteStream &bs);
	ByteStream operator^(const ByteStream &bs);
	ByteStream& operator=(const ByteStream &bs);
	unsigned int getNumBytes();
	ByteStream getBytes(unsigned int start, unsigned int end);
	void setBytes(unsigned int start, ByteStream bs);
	bool getBit(unsigned int pos);
	void printBits();
	friend ostream& operator<<(ostream &os, const ByteStream &bs);
};

class KeySchedule
{
private:
	ByteStream M;
	vector<ByteStream>K;
public:
	KeySchedule();
	KeySchedule(ByteStream bs);
	void generateKeys();
};