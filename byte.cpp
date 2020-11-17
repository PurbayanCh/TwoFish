#include "headers.hpp"

using namespace std;

Byte::Byte()
{
	this->value = 0;
}

Byte::Byte(string hex_val)
{
	unsigned char val = 0;
	for(int i = 0; i<2; i++)
	{
		val = (val<<4);
		if(hex_val[i]>='0' && hex_val[i]<='9')
			val += hex_val[i]-'0';
		else
			val += hex_val[i]-'a'+10;
	}
	this->value = val;
}

Byte::Byte(unsigned char val)
{
	this->value = val;
}

void Byte::byteShift(int shift)
{
	if(shift == 0)
		return;
	if(shift<0)
	{
		shift *= -1;
		while(shift--)
			this->value = this->value/2;
	}
	else
	{
		while(shift--)
			this->value = 2*this->value;
	}
}

Byte Byte::operator|(const Byte &byte)
{
	Byte ans = Byte(this->value | byte.value);
	return ans;
}

Byte Byte::operator&(const Byte &byte)
{
	Byte ans = Byte(this->value & byte.value);
	return ans;
}

Byte Byte::operator^(const Byte &byte)
{
	Byte ans = Byte(this->value ^ byte.value);
	return ans;
}

Byte Byte::operator+(const Byte &byte)
{
	int x = this->value, y = byte.value;
	int z = (x+y)%(1<<8);
	Byte ans = Byte((unsigned char)z);
	return ans;
}

Byte Byte::operator*(const Byte &byte)
{
	int x = this->value, y = byte.value;
	int z = (x*y)%(1<<8);
	Byte ans = Byte((unsigned char)z);
	return ans;
}

bool Byte::operator>(const Byte &byte)
{
	return this->value > byte.value;
}

bool Byte::operator>=(const Byte &byte)
{
	return this->value >= byte.value;
}

bool Byte::operator==(const Byte &byte)
{
	return this->value == byte.value;
}

Byte& Byte::operator=(const Byte &byte)
{	
	this->value = byte.value;
	return *this;
}

bool Byte::getBit(unsigned int pos)
{
	bool bit = (this->value&(1<<pos));
	return bit;
}

void Byte::printBits()
{
	cout<<bitset<8>(this->value);
}

ostream& operator<<(ostream &out, const Byte &byte)
{
	out<<hex<<setfill('0')<<setw(2)<<(unsigned int)byte.value;
	return out;
}