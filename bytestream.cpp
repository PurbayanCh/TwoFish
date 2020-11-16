#include "byteheader.hpp"

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

void ByteStream::byteStreamShift(int shift)
{
	if(shift == 0)
		return;
	bool ret_value;
	if(shift<0)
	{
		shift *= -1;
		while(shift--)
		{
			ret_value = 0;
			for(int n = 0; n<this->num_bytes; n++)
			{
				bool LSB = ((this->values[n]&Byte(1)) == Byte(1))?1:0;
				this->values[n].byteShift(-1);
				this->values[n] = this->values[n]|(Byte(ret_value<<7));
				ret_value = LSB;
			}
		}
	}
	else
	{
		while(shift--)
		{
			ret_value = 0;
			for(int n = this->num_bytes-1; n>=0; n--)
			{
				bool MSB = (this->values[n]>=128)?1:0;
				this->values[n].byteShift(1);
				this->values[n] = this->values[n]|Byte(ret_value);
				ret_value = MSB;
			}
		}	
	}
}

ByteStream ByteStream::operator^(const ByteStream &bs)
{
	vector<Byte> ans_bytes;
	for(int n = 0; n<this->num_bytes; n++)
	{
		ans_bytes.push_back(this->values[n]^bs.values[n]);
	}
	return ByteStream(ans_bytes);
}

ByteStream& ByteStream::operator=(const ByteStream &bs)
{
	this->values = bs.values;
	this->num_bytes = bs.num_bytes;
	return *this;
}

void ByteStream::printBits()
{
	for(Byte byte: values)
		byte.printBits();
	cout<<endl;
}

ByteStream ByteStream::extractBytes(unsigned int start, unsigned int end)
{
	vector<Byte> bytes;
	for(int i = start; i<end; i++)
		bytes.push_back(this->values[i]);
	return ByteStream(bytes);
}

ostream& operator<<(ostream &out, const ByteStream &bytestream)
{
	for(Byte byte: bytestream.values)
		out<<byte;
	return out;
}