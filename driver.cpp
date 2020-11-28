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
	cout<<ByteStream(64)<<endl;
	cout<<X.getString()<<endl;
}

int main()
{
	// test();
	string MSG (16, 'B'), KEY (16,'A');
	// MSG = "ishan";
	// KEY = "purbayan";
	cout<<"Enter the Message: ";
	cin>>MSG;
	cout<<"Enter the Key: ";
	cin>>KEY;
	TwoFish tf = TwoFish(KEY);
	cout<<"ENCRYTPION:"<<endl;
	cout<<tf.encrypt(MSG)<<endl;
	cout<<"DECRYPTION:"<<endl;
	cout<<tf.decrypt(tf.encrypt(MSG).getString()).getString()<<endl;
	return 0;
}