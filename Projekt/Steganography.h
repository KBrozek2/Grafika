#pragma once
#pragma warning(disable:4996)
#include "Image.h"
#include "Conversion.h"
#include "File.h"
#include <bitset>
#include <vector>

using namespace std;

class Steganography
{
	Image imgObj;
	Conversion converObj;
	File fileObj;

	const int messageSizeBMP;
	int bitwiseMessageLength;
	int bitwisePasswordLength;
	vector <bool> usint;
	vector<bool> bitwisePasswordLengthB;
	vector<bool> bitwiseMessageLengthB;
	vector<SDL_Color> pixelsArray;


	bool getTextBit(Uint8 pix, bool number2);
	vector<SDL_Color> getMessageLengthFromBMP(char *);
	void changePix(Uint8&, bool, bool);
	void saveCoded(char *);
	void makePixelsArray(char * img, int size);

public:
	void code(vector<bool>, vector<bool>, char*);
	void decode(vector<bool>, char *);

	Steganography(Image &,Conversion &,File &);
	~Steganography();
};