#include "headers.hpp"

using namespace std;

extern vector<vector<Byte>>MDS;

Byte q(Byte x, vector<vector<Byte>>&T) {

	Byte a0 = x.byteShift(-4);
	Byte b0 = x & Byte("0f");
	Byte a1 = a0 ^ b0;
	Byte b1 = a0 ^ b0.ROR(4, 1) ^ (((Byte("08")*a0)) & Byte("0f"));
	Byte a2 = T[0][a1.getValue()];
	Byte b2 = T[1][b1.getValue()];
	Byte a3 = a2 ^ b2;
	Byte b3 = a2 ^ b2.ROR(4, 1) ^ (((Byte("08")*a2)) & Byte("0f"));
	Byte a4 = T[2][a3.getValue()];
	Byte b4 = T[3][b3.getValue()];
	Byte y = (Byte(16)*b4) + a4;
	return y;
}

Byte q0(Byte x)
{
	vector<vector<Byte>>T;
	T = 
	{
		{Byte("08"), Byte("01"), Byte("07"), Byte("0d"), Byte("06"), Byte("0f"), Byte("03"), Byte("02"), Byte("00"), Byte("0b"), Byte("05"), Byte("09"), Byte("0e"), Byte("0c"), Byte("0a"), Byte("04")},
		{Byte("0e"), Byte("0c"), Byte("0b"), Byte("08"), Byte("01"), Byte("02"), Byte("03"), Byte("05"), Byte("0f"), Byte("04"), Byte("0a"), Byte("06"), Byte("07"), Byte("00"), Byte("09"), Byte("0d")},
		{Byte("0b"), Byte("0a"), Byte("05"), Byte("0e"), Byte("06"), Byte("0d"), Byte("09"), Byte("00"), Byte("0c"), Byte("08"), Byte("0f"), Byte("03"), Byte("02"), Byte("04"), Byte("07"), Byte("01")},
		{Byte("0d"), Byte("07"), Byte("0f"), Byte("04"), Byte("01"), Byte("02"), Byte("06"), Byte("0e"), Byte("09"), Byte("0b"), Byte("03"), Byte("00"), Byte("08"), Byte("05"), Byte("0c"), Byte("0a")}	
	};
	return q(x, T);
}

Byte q1(Byte x)
{
	vector<vector<Byte>>T;
	T = 
	{
		{Byte("02"), Byte("08"), Byte("0b"), Byte("0d"), Byte("0f"), Byte("07"), Byte("06"), Byte("0e"), Byte("03"), Byte("01"), Byte("09"), Byte("04"), Byte("00"), Byte("0a"), Byte("0c"), Byte("05")},
		{Byte("01"), Byte("0e"), Byte("02"), Byte("0b"), Byte("04"), Byte("0c"), Byte("03"), Byte("07"), Byte("06"), Byte("0d"), Byte("0a"), Byte("05"), Byte("0f"), Byte("09"), Byte("00"), Byte("08")},
		{Byte("04"), Byte("0c"), Byte("07"), Byte("05"), Byte("01"), Byte("06"), Byte("09"), Byte("0a"), Byte("00"), Byte("0e"), Byte("0d"), Byte("08"), Byte("02"), Byte("0b"), Byte("03"), Byte("0f")},
		{Byte("0b"), Byte("09"), Byte("05"), Byte("01"), Byte("0c"), Byte("03"), Byte("0d"), Byte("0e"), Byte("06"), Byte("04"), Byte("07"), Byte("0f"), Byte("02"), Byte("00"), Byte("08"), Byte("0a")}
	};
	return q(x, T);
}

ByteStream h(ByteStream x, vector<ByteStream> L)
{
	unsigned int k = L.size();

	vector<Byte>y2(4, 0);
	vector<Byte>y3(4, 0);
	vector<Byte>y4(4, 0);
	vector<Byte>y(4);
	vector<Byte>z(4);

	if(k == 4)
	{
		for(int i = 0; i<4; i++)
			y4[i] = x.getByte(i);
	}
	else if(k == 3)
	{
		for(int i = 0; i<4; i++)
			y3[i] = x.getByte(i);
	}
	else
	{
		for(int i = 0; i<4; i++)
		{
			y2[i] = x.getByte(i);
		}
	}

	if(k == 4)
	{
		y3[0] = q1(y4[0])^L[3].getByte(0);
		y3[1] = q0(y4[1])^L[3].getByte(1);
		y3[2] = q0(y4[2])^L[3].getByte(2);
		y3[3] = q1(y4[3])^L[3].getByte(3);
	}
	if(k>=3)
	{
		y2[0] = q1(y3[0])^L[2].getByte(0);
		y2[1] = q1(y3[1])^L[2].getByte(1);
		y2[2] = q0(y3[2])^L[2].getByte(2);
		y2[3] = q0(y3[3])^L[2].getByte(3);
	}
	y[0] = q1(q0(q0(y2[0])^L[1].getByte(0))^L[0].getByte(0));
	y[1] = q0(q0(q1(y2[1])^L[1].getByte(1))^L[0].getByte(1));
	y[2] = q1(q1(q0(y2[2])^L[1].getByte(2))^L[0].getByte(2));
	y[3] = q0(q1(q1(y2[3])^L[1].getByte(3))^L[0].getByte(3));

	for(int i = 0; i<4; i++)
		for(int j = 0; j<4; j++)
			z[i] = z[i] + MDS[i][j]*y[j];

	return ByteStream(z);
}