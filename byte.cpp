#include "byteheader.hpp"

using namespace std;

Byte::Byte()
{
	this->value = 0;
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


void Byte::printBits()
{
	cout<<bitset<8>(this->value);
}

ostream& operator<<(ostream &out, const Byte &byte)
{
	out<<hex<<(unsigned int)byte.value;
	return out;
}