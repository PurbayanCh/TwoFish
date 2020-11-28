#include "headers.hpp"

using namespace std;

ByteStream::ByteStream()
{
	this->values = {};
	this->num_bytes = 0;
}

ByteStream::ByteStream(vector<Byte> bs)
{
	this->values = bs;
	this->num_bytes = bs.size();
}

ByteStream::ByteStream(unsigned int bs)
{
	vector<Byte>bytes;
	for(int i = 8; i<=32; i+=8)
	{
		unsigned int mask = (1LL<<i)-1;
		unsigned char x = (bs & mask)>>(i-8);
		bytes.push_back(Byte(x));
	}
	reverse(bytes.begin(), bytes.end());
	this->values = bytes;
	this->num_bytes = bytes.size();
}

ByteStream::ByteStream(string bs)
{
	vector<Byte>bytes;
	for(int i = 0; i<bs.length(); i+=2)
		bytes.push_back(Byte(bs.substr(i,2)));
	this->values = bytes;
	this->num_bytes = bytes.size();
}

unsigned int ByteStream::getValue()
{
	unsigned int value = 0;
	for(int n = 0; n<this->num_bytes; n++)
	{
		unsigned int mask = (1<<((this->num_bytes-n-1)*8));
		value += (mask * this->values[n].getValue());
	}
	return value;
}

string ByteStream::getString()
{
	string ans = "";
	for(Byte byte: this->values)
		ans = ans + byte.getString();
	return ans;
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
				ans.values[n] = ans.values[n].byteShift(-1);
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
				bool MSB = ans.values[n].getBit(7);
				ans.values[n] = ans.values[n].byteShift(1);
				ans.values[n] = ans.values[n]|Byte(ret_value);
				ret_value = MSB;
			}
		}	
	}
	return ans;
}

ByteStream ByteStream::byteStreamROR(int shift)
{
	ByteStream ans = *this;
	while(shift--) 
	{
		bool LSB = ans.getByte(ans.num_bytes-1).getBit(0);
		ans = ans.byteStreamShift(-1);
		string temp = LSB?"80":"00";
		for(int i = 0; i<num_bytes-1; i++)
			temp += "00";
		ans = ans | ByteStream(temp);
	}
	return ans;
}

ByteStream ByteStream::byteStreamROL(int shift)
{
	ByteStream ans = *this;
	while(shift--) 
	{
		bool MSB = ans.getByte(0).getBit(7);
		ans = ans.byteStreamShift(1);
		string temp = MSB?"01":"00";
		for(int i = 0; i<num_bytes-1; i++)
			temp = "00" + temp;
		ans = ans | ByteStream(temp);
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

vector<Byte> ByteStream::getValues()
{
	return this->values;
}

ByteStream ByteStream::getBytes(unsigned int start, unsigned int end)
{
	vector<Byte> bytes;
	for(int i = start; i<end; i++)
		bytes.push_back(this->values[i]);
	return ByteStream(bytes);
}

Byte ByteStream::getByte(unsigned int index) 
{
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