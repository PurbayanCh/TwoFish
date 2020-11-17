#include "headers.hpp"

using namespace std;

ByteStream::ByteStream()
{
	this->values = {};
	this->num_bytes = 0;
}

ByteStream::ByteStream(vector<Byte> val)
{
	this->values = val;
	this->num_bytes = val.size();
}

ByteStream ByteStream::byteStreamShift(int shift)
{
	ByteStream ans = *this;
	if(shift == 0)
		return ans;
	bool ret_value;
	if(shift<0)
	{
		shift *= -1;
		while(shift--)
		{
			ret_value = 0;
			for(int n = 0; n<ans.num_bytes; n++)
			{
				bool LSB = ans.values[n].getBit(0);
				ans.values[n].byteShift(-1);
				ans.values[n] = ans.values[n]|(Byte(ret_value<<7));
				ret_value = LSB;
			}
		}
	}
	else
	{
		while(shift--)
		{
			ret_value = 0;
			for(int n = ans.num_bytes-1; n>=0; n--)
			{
				bool MSB = ans.values[n].getBit((ans.num_bytes*8)-1);
				ans.values[n].byteShift(1);
				ans.values[n] = ans.values[n]|Byte(ret_value);
				ret_value = MSB;
			}
		}	
	}
	return ans;
}

ByteStream ByteStream::operator|(const ByteStream &bs)
{
	vector<Byte> ans_bytes;
	for(int n = 0; n<this->num_bytes; n++)
		ans_bytes.push_back(this->values[n]|bs.values[n]);
	return ByteStream(ans_bytes);
}

ByteStream ByteStream::operator&(const ByteStream &bs)
{
	vector<Byte> ans_bytes;
	for(int n = 0; n<this->num_bytes; n++)
		ans_bytes.push_back(this->values[n]&bs.values[n]);
	return ByteStream(ans_bytes);
}

ByteStream ByteStream::operator^(const ByteStream &bs)
{
	vector<Byte> ans_bytes;
	for(int n = 0; n<this->num_bytes; n++)
		ans_bytes.push_back(this->values[n]^bs.values[n]);
	return ByteStream(ans_bytes);
}

ByteStream& ByteStream::operator=(const ByteStream &bs)
{
	this->values = bs.values;
	this->num_bytes = bs.num_bytes;
	return *this;
}

unsigned int ByteStream::getNumBytes()
{
	return this->num_bytes;
}

ByteStream ByteStream::getBytes(unsigned int start, unsigned int end)
{
	vector<Byte> bytes;
	for(int i = start; i<end; i++)
		bytes.push_back(this->values[i]);
	return ByteStream(bytes);
}
Byte ByteStream::getByte(unsigned int index) {
	return this->values[index];
}

void ByteStream::setBytes(unsigned int start, ByteStream bs)
{
	for(int i = start; i<start+bs.values.size(); i++)
		this->values[i] = bs.values[i-start];
}

bool ByteStream::getBit(unsigned int pos)
{
	unsigned int x = pos/8, y = pos%8;
	return this->values[num_bytes-x-1].getBit(y);
}

void ByteStream::printBits()
{
	for(Byte byte: values)
		byte.printBits();
	cout<<endl;
}

ostream& operator<<(ostream &out, const ByteStream &bs)
{
	for(Byte byte: bs.values)
		out<<byte;
	return out;
}