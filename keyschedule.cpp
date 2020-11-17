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
	return;
}

Byte KeySchedule::q0(Byte x)
{
	vector<vector<Byte>>T;

	T = {
		{},
		{},
		{},
		{}	
	}
}