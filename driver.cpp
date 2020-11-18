#include "headers.hpp"

using namespace std;

void test()
{
	Byte w("ff");
	Byte x("ff");
	Byte y("ff");
	Byte z("ff");
	ByteStream X({w,x,y,z});
	X.printBits();
	cout<<X.getValue()<<endl;
}

int main()
{
	// test();
	TwoFish tf = TwoFish("4fag48tg");
	tf.encrypt("crypto bad");
	return 0;
}