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
	Byte byteShift(int shift);
	Byte ROR(int bits, int shift);
	Byte ROL(int bits, int shift);
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
	unsigned char getValue();
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
	ByteStream byteStreamShift(int shift);
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

class KeySchedule
{
private:
	ByteStream M;
	vector<ByteStream> K;
	vector<ByteStream> Me;
	vector<ByteStream> Mo;
	vector<ByteStream> S;
public:
	KeySchedule();
	KeySchedule(ByteStream bs);
	Byte q(Byte x, vector<vector<Byte>>T);
	Byte q0(Byte x);
	Byte q1(Byte x);
	void generateKeys();
};