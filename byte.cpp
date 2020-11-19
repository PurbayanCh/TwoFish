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

unsigned char Byte::getValue() {
	return this->value;
}

string Byte::getString()
{
	string ans = "";
	ans = ans + (char)this->value;
	return ans;
}

//+ve = left shift; -ve = right shift
Byte Byte::byteShift(int shift)
{
	Byte ans = *this;
	if(shift == 0)
		return ans;
	if(shift<0)
	{
		shift *= -1;
		while(shift--)
			ans.value = ans.value/2;
	}
	else
	{
		while(shift--)
			ans.value = 2*ans.value;
	}
	return ans;
}

Byte Byte::byteROR(int bits, int shift) 
{
	Byte ans = *this;
	if(bits == 4) 
	{
		while(shift--) 
		{
			bool LSB = ans.getBit(0);
			ans = ans.byteShift(-1);
			ans = ans & Byte("0f");
			string temp = LSB?"08":"00";
			ans = ans | Byte(temp);
		}
	}
	else
	{
		while(shift--)
		{
			bool LSB = ans.getBit(0);
			ans = ans.byteShift(-1);
			string temp = LSB?"80":"00";
			ans = ans | Byte(temp);
		}
	}
	return ans;
}

Byte Byte::byteROL(int bits, int shift) 
{
	Byte ans = *this;
	if(bits == 4) 
	{
		while(shift--)
		{
			bool MSB = ans.getBit(3);
			ans = ans.byteShift(1);
			ans = ans & Byte("0f");
			string temp = MSB?"01":"00";
			ans = ans | Byte(temp);
		}
	}
	else
	{
		while(shift--)
		{
			bool MSB = ans.getBit(7);
			ans = ans.byteShift(1);
			string temp = MSB?"01":"00";
			ans = ans | Byte(temp);
		}
	}
	return ans;
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