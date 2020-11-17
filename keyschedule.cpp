#include "headers.hpp"

using namespace std;

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
	cout<<"Me : "<<endl;
	for(auto i:Me) {
		cout<<i<<endl;
	}
	cout<<"Mo : "<<endl;
	for(auto i:Mo) {
		cout<<i<<endl;
	}
	// S
	vector<vector<Byte>>RS;
	RS = 
	{
		{Byte("01"), Byte("a4"), Byte("55"), Byte("87"), Byte("5a"), Byte("58"), Byte("db"), Byte("9e")},
		{Byte("a4"), Byte("56"), Byte("82"), Byte("f3"), Byte("1e"), Byte("c6"), Byte("68"), Byte("e5")},
		{Byte("02"), Byte("a1"), Byte("fc"), Byte("c1"), Byte("47"), Byte("ae"), Byte("3d"), Byte("19")},
		{Byte("a4"), Byte("55"), Byte("87"), Byte("5a"), Byte("58"), Byte("db"), Byte("9e"), Byte("03")}
	};


	for(int i=0; i<k; i++) {
		Byte s0(0);
		for(int j=0; j<8; j++) {
			s0 = s0 + RS[0][j]*M.getByte(8*i + j);
		}
		Byte s1(0);
		for(int j=0; j<8; j++) {
			s1 = s1 + RS[1][j]*M.getByte(8*i + j);
		}
		Byte s2(0);
		for(int j=0; j<8; j++) {
			s2 = s2 + RS[2][j]*M.getByte(8*i + j);
		}
		Byte s3(0);
		for(int j=0; j<8; j++) {
			s3 = s3 + RS[3][j]*M.getByte(8*i + j);
		}
		this->S.push_back(ByteStream({s3, s2, s1, s0}));
	}
	reverse(S.begin(), S.end());
	cout<<"S : "<<endl;
	for(auto i:S) {
		cout<<i<<endl;
	}


	return;
}