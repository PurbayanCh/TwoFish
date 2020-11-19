#include "headers.hpp"

using namespace std;

void test()
{
	Byte w("63");
	Byte x("64");
	Byte y("65");
	Byte z("66");
	ByteStream X({w,x,y,z});
	X.printBits();
	cout<<X.getString()<<endl;
}

int main()
{
	// test();
	string KEY, MSG;
	cout<<"Enter the Key: ";
	cin>>KEY;
	cout<<"Enter the Message: ";
	cin>>MSG;
	TwoFish tf = TwoFish(KEY);
	cout<<tf.encrypt(MSG)<<endl;
	cout<<tf.encrypt(tf.encrypt(MSG).getString()).getString()<<endl;
	return 0;
}