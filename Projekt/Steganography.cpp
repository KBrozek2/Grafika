#include "Steganography.h"

void Steganography::changePix(Uint8 & pix, bool number, bool number2)
{
	usint.clear();
	unsigned short a = (unsigned short)pix;
	usint = ushortToBits(a);
	usint[0] = (number ^ number2);
	pix = (Uint8)bitsToUShort(usint);
}

//----------------------------------------
void Steganography::code(vector<bool> messageB, vector<bool> passwordB, char *img)
{
	//dlugosc (inty) wiadomosci i hasla w postaci BITOWEJ
	bitwiseMessageLength = messageB.size();
	bitwisePasswordLength = passwordB.size();

	//dlugosc (vector<bool>) wiadomosci i hasla w postaci BITOWEJ
	bitwiseMessageLengthB = intToBits(bitwiseMessageLength);
	bitwisePasswordLengthB = intToBits(bitwisePasswordLength);

	/*Umieszcza w atrybucie vector<SDL_Color>pixelsArray wyznaczon¹ liczbê pikseli z bmp o œcie¿ce char*img */
	makePixelsArray(img);

	//ktory bit wiadomosci, ktory pixel oraz ktory bit hasla
	int w = 0, p = 0, h = 0;

	//kodowanie hasla, zaczynamy od green bo potrzeba 32 bity z 11 pikseli (33bitow)
	while (1)
	{
		changePix(pixelsArray[p].g, bitwiseMessageLengthB[w++], 1);
		changePix(pixelsArray[p++].b, bitwiseMessageLengthB[w++], 1);
		//jesli ostatni bit rozmiaru zostal wpisany wyjdzie z while, jesli nie to robi dalej
		if (w == bitwiseMessageLengthB.size())  break;
		changePix(pixelsArray[p].r, bitwiseMessageLengthB[w++], 1);
	}
	//kodowanie tresci wiadomosci
	w = 0; h = 0; p = 11;
	while (1)
	{
		changePix(pixelsArray[p].r, messageB[w++], passwordB[h++]);
		if (h == passwordB.size()) 	h = 0;
		if (w == bitwiseMessageLength)	break;
		changePix(pixelsArray[p].g, messageB[w++], passwordB[h++]);
		if (h == passwordB.size())	h = 0;
		if (w == bitwiseMessageLength)	break;
		changePix(pixelsArray[p].b, messageB[w++], passwordB[h++]);
		if (h == passwordB.size()) 	h = 0;
		if (w == bitwiseMessageLength)	break;
		p++;
	}
	saveCodedBMP(img);
}

//----------------------------------------
void Steganography::decode(vector<bool> passwordB, char * img_path)
{}

//----------------------------------------

/*Dorobic obsluge bledów w srodku!*/
void Steganography::saveCodedBMP(char *img)
{
	/*  wczytywanie do char, getline, sprawdzanie czy jest rozszerzenie*/
	Image obj;

	string bmpFile = "";
	cout << "Podaj nazwe pliku bmp do stworzenia" << endl;
	cout << "->"; cin >> bmpFile; cout << endl;

	char *bmpFileChar = new char[bmpFile.length() + 1];
	strcpy(bmpFileChar, bmpFile.c_str());

	char *newBmpPath = bmpFileChar;
	strcat(newBmpPath, ".bmp");

	//wczytanie do nowej bitmapy pikseli z pixelsArray
	SDL_Surface *bmp = obj.loadBitMap(img);
	int loop_cond = ((bitwiseMessageLength + 32) / 3) + 1;
	int j = 1;

	//wypelnienie zmienionymi pixelami
	for (int i = bmp->w - 1, y = 0; y < loop_cond; i--, y++)
	{
		if (i + 1 == 0)
		{
			j += 1;
			i = bmp->w - 1;
			obj.setPixel(i, bmp->h - j, pixelsArray[y].r, pixelsArray[y].g, pixelsArray[y].b);
		}

		else
		{
			obj.setPixel(i, bmp->h - j, pixelsArray[y].r, pixelsArray[y].g, pixelsArray[y].b);
		}
	}

	//zapis
	SDL_SaveBMP(bmp, newBmpPath);

	cout << "Zakonczono kodowanie wiadomosci. Rezultat zostal zapisany w pliku '" << newBmpPath << "'" << endl;
}


//----------------------------------------
void Steganography::makePixelsArray(char *img)
{
	SDL_Surface *bmp = imgObj.loadBitMap(img);

	int loop_cond = ((bitwiseMessageLength + 32) / 3) + 1;
	int j = 1;

	//pobiera wymagana liczbe pikseli od dolnego prawego rogu
	for (int i = bmp->w - 1, y = 0; y < loop_cond; i--, ++y)
	{
		if (i + 1 == 0)
		{
			j += 1;
			i = bmp->w;
			pixelsArray.push_back(imgObj.getPixel(i, bmp->h - j));
		}
		else pixelsArray.push_back(imgObj.getPixel(i, bmp->h - j));
	}
}



Steganography::Steganography(Image &obj) :bitwiseMessageLength(0), bitwisePasswordLength(0), imgObj(obj)
{}


Steganography::~Steganography()
{}