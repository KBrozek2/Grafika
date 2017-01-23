#pragma once
#pragma warning(disable:4996)
#include <bitset>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

class Conversion
{
	

public:
	vector<bool> ushortToBits(unsigned short);
	vector<bool> stringToBits(string); //zwraca vector ze stringiem w bitach
	vector<bool> intToBits(int); //zwraca vector<bool>(32 bit) w ktorych zapisany jest przyjmowany int 
	unsigned short bitsToUShort(vector<bool>);
	string bitsToString(vector<bool>);
	char *stringToChar(string);
	int bitToInt(vector<bool> bytes);
	
};
