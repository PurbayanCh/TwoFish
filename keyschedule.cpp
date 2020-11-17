#include "headers.hpp"

using namespace std;

extern vector<vector<Byte>>RS;

KeySchedule::KeySchedule(ByteStream bs) 
{
	this->M = bs;
	for(int i=0; i<40; i++) 
	{
		this->K.push_back(ByteStream());
	}
}

void KeySchedule::generateKeys() 
{

	//Me and Mo
	int N = this->M.getNumBytes()*8;
	int k = N/64;
	vector<ByteStream> M_arr(2*k);
	for(int i=0; i<2*k; i++) 
	{
		Byte t0 = M.getByte(4*i);
		Byte t1 = M.getByte(4*i + 1);
		Byte t2 = M.getByte(4*i + 2);
		Byte t3 = M.getByte(4*i + 3);
		M_arr[i] = ByteStream({t3, t2, t1, t0});
	}

	for(int i=0; i<M_arr.size(); i++) {
		if(i%2==0)
			this->Me.push_back(M_arr[i]);
		else
			this->Mo.push_back(M_arr[i]);
	}
	// cout<<"Me : "<<endl;
	// for(auto i:Me) {
	// 	cout<<i<<endl;
	// }
	// cout<<"Mo : "<<endl;
	// for(auto i:Mo) {
	// 	cout<<i<<endl;
	// }
	
	// S
	for(int i=0; i<k; i++) {
		vector<Byte> S_arr(4);
		for(int s = 0; s<4; s++)
		{
			for(int j=0; j<8; j++) {
				S_arr[s] = S_arr[s] + RS[s][j]*M.getByte(8*i + j);
			}
		}
		reverse(S_arr.begin(), S_arr.end());
		this->S.push_back(ByteStream(S_arr));
	}
	reverse(S.begin(), S.end());
	// cout<<"S : "<<endl;
	// for(auto i:S) {
	// 	cout<<i<<endl;
	// }
}

Byte KeySchedule::q(Byte x, vector<vector<Byte>>T) {

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

Byte KeySchedule::q0(Byte x)
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

Byte KeySchedule::q1(Byte x)
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