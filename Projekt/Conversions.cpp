#include "Steganography.h"

vector<bool> Steganography::stringToBits(string str)
{
	bitset<8> b;
	vector<bool> bitArray;

	for (size_t i = 0; i < str.size(); ++i)
	{
		b = bitset<8>(str.c_str()[i]);

		for (int j = 7; j >= 0; j--)
			bitArray.push_back(b[j]);
	}
	return bitArray;
}

vector<bool> Steganography::intToBits(int num)
{
	bitset<32> a(num);
	vector<bool> bitArray;

	for (int j = 0; j < 32; ++j)
		bitArray.push_back(a[j]);

	return bitArray;
}

vector<bool> Steganography::ushortToBits(unsigned short num)
{
	bitset<8> a(num);
	vector<bool> bitArray;

	for (int i = 0; i<8; i++)
		bitArray.push_back(a[i]);

	return bitArray;
}

unsigned short Steganography::bitsToUShort(vector <bool> vec)
{
	unsigned short a = 0;
	for (int i = 7; i >= 0; i--)
		a += (unsigned short)(vec[i] * pow(2, i));

	return a;
}
