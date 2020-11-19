#include "headers.hpp"

#define KEY_LENGTH 128
#define word(x, i) x.getBytes(4*i, 4*i+4)

Byte TwoFish::q(Byte x, vector<vector<Byte>>&T) {

	Byte a0 = x.byteShift(-4);
	Byte b0 = x & Byte("0f");
	Byte a1 = a0 ^ b0;
	Byte b1 = a0 ^ b0.byteROR(4, 1) ^ (((Byte("08")*a0)) & Byte("0f"));
	Byte a2 = T[0][a1.getValue()];
	Byte b2 = T[1][b1.getValue()];
	Byte a3 = a2 ^ b2;
	Byte b3 = a2 ^ b2.byteROR(4, 1) ^ (((Byte("08")*a2)) & Byte("0f"));
	Byte a4 = T[2][a3.getValue()];
	Byte b4 = T[3][b3.getValue()];
	Byte y = (Byte(16)*b4) + a4;
	return y;
}

Byte TwoFish::q0(Byte x)
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

Byte TwoFish::q1(Byte x)
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

ByteStream TwoFish::h(ByteStream x, vector<ByteStream> L)
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
			z[i] = z[i] + this->MDS[i][j]*y[j];

	return ByteStream(z);
}

ByteStream TwoFish::g(ByteStream x) {
	return h(x, this->S);
}

ByteStream TwoFish::f(ByteStream R0, ByteStream R1, unsigned int r) {
	ByteStream T0 = g(R0);
	ByteStream T1 = g(R1.byteStreamROL(8));
	long long int t0 = T0.getValue(), t1 = T1.getValue();
	long long int k0 = this->K[2*r + 8].getValue();
	long long int k1 = this->K[2*r + 9].getValue();
	long long int f0 = (t0 + t1 + k0)%(1LL<<32);
	long long int f1 = (t0 + t1 + t1 + k1)%(1LL<<32);
	ByteStream F0(f0);
	ByteStream F1(f1);
	vector<Byte> f;
	for(int i=0; i<4; i++)
		f.push_back(f0.getByte(i));
	for(int i=0; i<4; i++)
		f.push_back(f1.getByte(i));
	return ByteStream(f);
}

ByteStream TwoFish::round(ByteStream x, unsigned int r) {
	ByteStream x0, x1, x2, x3;
	x0 = word(x, 0);
	x1 = word(x, 1);
	x2 = word(x, 2);
	x3 = word(x, 3);

	ByteStream output = f(x0, x1, r);
	ByteStream o0 = word(output, 0);
	ByteStream o1 = word(output, 1);
	x3 = (o0^x3).byteStreamROR(1);
	x4 = (o1^(x3.byteStreamROL(1)));

	vector<Byte> ans;
	for(int i=0; i<4; i++)
		ans.push_back(x0.getByte(i));
	for(int i=0; i<4; i++)
		ans.push_back(x1.getByte(i));
	for(int i=0; i<4; i++)
		ans.push_back(x2.getByte(i));
	for(int i=0; i<4; i++)
		ans.push_back(x3.getByte(i));
	return ByteStream(ans);
}

ByteStream TwoFish::swap(ByteStream x) {
	ByteStream x0, x1, x2, x3;
	x0 = word(x, 0);
	x1 = word(x, 1);
	x2 = word(x, 2);
	x3 = word(x, 3);

	vector<Byte> ans;
	for(int i=0; i<4; i++)
		ans.push_back(x2.getByte(i));
	for(int i=0; i<4; i++)
		ans.push_back(x3.getByte(i));
	for(int i=0; i<4; i++)
		ans.push_back(x0.getByte(i));
	for(int i=0; i<4; i++)
		ans.push_back(x1.getByte(i));
	return ByteStream(ans);
}

void TwoFish::generateKeys() 
{
	vector<ByteStream>Me, Mo;

	unsigned int N = this->M.getNumBytes()*8;
	unsigned int k = N/64;
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
			Me.push_back(M_arr[i]);
		else
			Mo.push_back(M_arr[i]);
	}

	for(int i=0; i<k; i++) {
		vector<Byte> S_arr(4);
		for(int s = 0; s<4; s++)
		{
			for(int j=0; j<8; j++) {
				S_arr[s] = S_arr[s] + this->RS[s][j]*M.getByte(8*i + j);
			}
		}
		reverse(S_arr.begin(), S_arr.end());
		this->S.push_back(ByteStream(S_arr));
	}
	reverse(this->S.begin(), this->S.end());

	unsigned int rho = (1<<24) + (1<<16) + (1<<8) + 1;

	for(unsigned int i = 0; i<20; i++)
	{
		ByteStream Ai;
		ByteStream Bi;
		Ai = h(ByteStream(2*i*rho), Me);
		Bi = h((2*i+1)*rho, Mo).byteStreamROL(8);
		long long int ai = Ai.getValue(), bi = Bi.getValue();
		long long int ci = (ai+bi)%((1LL<<32));
		long long int di = (ai+2*bi)%((1LL<<32));
		this->K[2*i] = ByteStream(ci);
		this->K[2*i+1] = (ByteStream(di)).byteStreamROL(9);
	}

	// for(int i = 0; i<40; i++)
	// {
	// 	cout<<"K["<<dec<<setfill('0')<<setw(2)<<i<<"]: ";
	// 	cout<<this->K[i]<<endl;
	// }
}

ByteStream TwoFish::inputPreprocessing(string x)
{
	vector<Byte>bytes;
	for(char c: x)
		bytes.push_back(Byte((unsigned char)c));
	while(bytes.size()<KEY_LENGTH/8)
		bytes.push_back(Byte(0));
	return ByteStream(bytes);
}

ByteStream TwoFish::inputWhitening(ByteStream x)
{
	for(int i = 0; i<4; i++)
		x.setBytes(4*i, word(x,i)^this->K[i]);
	return x;
}

ByteStream TwoFish::outputWhitening(ByteStream x)
{
	for(int i = 0; i<4; i++)
		x.setBytes(4*i, word(x,i)^this->K[i+4]);
	return x;
}

TwoFish::TwoFish(string KEY)
{
	this->M = this->inputPreprocessing(KEY);

	this->K.resize(40, ByteStream());

	this->RS.resize(4, vector<Byte>(8));
	this->RS = 
	{
		{Byte("01"), Byte("a4"), Byte("55"), Byte("87"), Byte("5a"), Byte("58"), Byte("db"), Byte("9e")},
		{Byte("a4"), Byte("56"), Byte("82"), Byte("f3"), Byte("1e"), Byte("c6"), Byte("68"), Byte("e5")},
		{Byte("02"), Byte("a1"), Byte("fc"), Byte("c1"), Byte("47"), Byte("ae"), Byte("3d"), Byte("19")},
		{Byte("a4"), Byte("55"), Byte("87"), Byte("5a"), Byte("58"), Byte("db"), Byte("9e"), Byte("03")}
	};

	this->MDS.resize(4, vector<Byte>(4));
	this->MDS = 
	{
		{Byte("01"), Byte("ef"), Byte("5b"), Byte("5b")},
		{Byte("5b"), Byte("ef"), Byte("ef"), Byte("01")},
		{Byte("ef"), Byte("5b"), Byte("01"), Byte("ef")},
		{Byte("ef"), Byte("01"), Byte("ef"), Byte("5b")}
	};

	this->generateKeys();
}

vector<ByteStream> TwoFish::getKeys()
{
	return this->K;
}



ByteStream TwoFish::encrypt(string plaintext)
{
	ByteStream P = inputPreprocessing(plaintext);
	P = this->inputWhitening(P);
	for(int i=0; i<16; i++) {
		P = this->round(P, i);
		P = this->swap(P);
	}
	P = this->swap(P);
	P = this->outputWhitening(P);
	
	return P;
}

ByteStream TwoFish::decrypt(string ciphertext)
{
	
}