#include "Conversions.h"

/*----------------------------------------*/
vector<bool> Conversion::stringToBits(string str)
{
	bitset<8> b;
	vector<bool> bitArray;

	for (size_t i = 0; i < str.size(); ++i)
	{
		b = bitset<8>(str.c_str()[i]);

		for (int j = 7; j >= 0; j--)
			bitArray.push_back(b[j]);
	}
	if(bitArray.size() > pow(2,29))
	{
		cout << "Plik tekstowy jest za du�y! Program konczy dzialanie." << endl;
		system("pause");
		exit(0);
	}
	return bitArray;
}
/*----------------------------------------*/
string Conversion::bitsToString(vector<bool> bytes)
{
	cout << endl;

	//vector<bool>::iterator it;
	string str = "";
	for (size_t i = 0; i < bytes.size(); i++)
	{
		if (i % 8 == 7)
		{
			str += bytes;

	}
	str += bytes[i];
}
	cout << str;
	stringstream sstream(str);
	string output;
	while (sstream.good())
	{
		bitset<8> bits;
		sstream >> bits;
		char c = char(bits.to_ulong());
		output += c;
	}

	return output;
}
/*----------------------------------------*/
char * Conversion::stringToChar(string str)
{
	char *a = new char[str.length() + 1];
	strcpy(a, str.c_str());

	return a;
}
/*----------------------------------------*/
vector<bool> Conversion::intToBits(int num)
{
	bitset<32> a(num);
	vector<bool> bitArray;

	for (int j = 0; j < 32; ++j)
		bitArray.push_back(a[j]);

	return bitArray;
}
/*----------------------------------------*/
int Conversion::bitToInt(vector<bool> bytes)
{
	int a = 0;
	for (int i = 7; i >= 0; i--)
		a += (int)(bytes[i] * pow(2, i));

	return a;
}
/*----------------------------------------*/
vector<bool> Conversion::ushortToBits(unsigned short num)
{
	bitset<8> a(num);
	vector<bool> bitArray;

	for (int i = 0; i<8; i++)
		bitArray.push_back(a[i]);

	return bitArray;
}
/*----------------------------------------*/
unsigned short Conversion::bitsToUShort(vector <bool> vec)
{
	unsigned short a = 0;
	for (int i = 7; i >= 0; i--)
		a += (unsigned short)(vec[i] * pow(2, i));

	return a;
}

