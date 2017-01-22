#pragma once
#pragma warning(disable:4996)
#include "Image.h"
#include "Conversions.h"
#include "Files.h"
#include <bitset>
#include <vector>

using namespace std;

class Steganography
{
	Image imgObj;
	Conversion converObj;
	Files fileObj;

	int bitwiseMessageLength;
	int bitwisePasswordLength;
	vector <bool> usint;
	vector<bool> bitwisePasswordLengthB;
	vector<bool> bitwiseMessageLengthB;
	vector<SDL_Color> pixelsArray;
	vector<SDL_Color> getMessageLengthFromBMP(char*);

public:
	void Code(vector<bool>, vector<bool>, char*);
	void changePix(Uint8&, bool, bool);
	void Decode(vector<bool>, char *);
	bool getTextBit(Uint8, bool);
	void saveCoded(char *);
	void makePixelsArray(char *, int);

	Steganography(Image &, Conversion &);
	~Steganography();
};