#pragma once
#pragma warning(disable:4996)
#include "Image.h"
#include <bitset>
#include <vector>

using namespace std;

class Steganography
{
	Image imgObj;

	unsigned short bitsToUShort(vector<bool>);
	int bitwiseMessageLength;
	int bitwisePasswordLength;

	vector<bool> usint;
	vector<bool> bitwisePasswordLengthB;
	vector<bool> bitwiseMessageLengthB;
	vector<bool> ushortToBits(unsigned short);
	vector<bool> intToBits(int);
	vector<SDL_Color> pixelsArray;

	void changePix(Uint8&, bool, bool);
	void makePixelsArray(char *);
	void saveCodedBMP(char *);

public:
	vector<bool> stringToBits(string);

	void code(vector<bool>, vector<bool>, char*);
	void decode(vector<bool>, char *);	

	Steganography(Image &);
	~Steganography();
};