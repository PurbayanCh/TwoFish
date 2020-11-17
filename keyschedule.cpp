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
	int N = this->M.getNumBytes()*8;
	int k = N/64;
	vector<ByteStream> M_arr(2*k);
	for(int i=0; i<2*k; i++) 
	{
		
	}
}