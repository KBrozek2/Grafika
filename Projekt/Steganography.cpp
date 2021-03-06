#include "Steganography.h"
/*----------------------------------------*/
void Steganography::code(vector<bool> messageB, vector<bool> passwordB, char *img)
{
	/*dlugosc (int) wiadomosci w postaci BITOWEJ oraz dlugosc (vector<bool>) wiadomosci w postaci BITOWEJ*/
	bitwiseMessageLength = messageB.size();
	bitwisePasswordLength = passwordB.size();

	bitwiseMessageLengthB = converObj.intToBits(bitwiseMessageLength);

	/*Umieszcza w atrybucie vector<SDL_Color>pixelsArray wyznaczona liczbe pikseli z bmp o sciezce char*img */
	makePixelsArray(img, bitwiseMessageLength);

	/*ktory bit wiadomosci, ktory pixel oraz ktory bit hasla*/
	int w = 0, p = 0, h = 0;

	/*kodowanie hasla, 32 bity z 11 pikseli (33bitow)*/
	while (1)
	{
		changePix(pixelsArray[p].g, bitwiseMessageLengthB[w++], 1);
		changePix(pixelsArray[p].b, bitwiseMessageLengthB[w++], 1);	p++;
		/*jesli ostatni bit to wyjscie z petli*/
		if (w == bitwiseMessageLengthB.size())  break;
		changePix(pixelsArray[p].r, bitwiseMessageLengthB[w++], 1);
	}

	w = 0; p = messageSizeBMP;
	/*kodowanie tresci wiadomosci*/
	while (1)
	{
		changePix(pixelsArray[p].r, messageB[w++], passwordB[h++]);
		if (w == bitwiseMessageLength)	break;
		if (h == bitwisePasswordLength) h = 0;
		changePix(pixelsArray[p].g, messageB[w++], passwordB[h++]);
		if (w == bitwiseMessageLength)	break;
		if (h == bitwisePasswordLength)	h = 0;
		changePix(pixelsArray[p].b, messageB[w++], passwordB[h++]);
		if (w == bitwiseMessageLength)	break;
		if (h == bitwisePasswordLength) h = 0;
		p++;
	}
	saveCoded(img);
}
/*----------------------------------------*/
void Steganography::changePix(Uint8 & pix, bool number, bool number2)
{
	usint.clear();									//reset wartosci wektora
	unsigned short a = (unsigned short)pix;			//rgb -> unsigned short int
	usint = converObj.ushortToBits(a);				//unsigned short int -> wektor z bitami			
	usint[0] = (number ^ number2);					//xor
	pix = (Uint8)converObj.bitsToUShort(usint);		//wektor z bitami -> unsigned short int -> rgb
}
/*----------------------------------------*/
void Steganography::decode(vector<bool> passwordB, char * img_path)
{
	bitwisePasswordLength = passwordB.size();
	bitwisePasswordLengthB = converObj.intToBits(bitwisePasswordLength);

	/*wektory do pobrania dlugosci wiadomosci, samej wiadomosci oraz do pobrania pierwszych 11 pikseli z rozmiarem*/
	vector<bool> theLength;
	vector<bool> theMessage;
	vector<SDL_Color> first11Pix = getMessageLengthFromBMP(img_path);

	/*ktory bit wiadomosci, pixel oraz bit hasla*/
	int w = 0, p = 0, h = 0;

	while (1)
	{
		theLength.push_back(getTextBit(first11Pix[p].g, 1));
		theLength.push_back(getTextBit(first11Pix[p++].b, 1));
		if (p == messageSizeBMP) break;
		theLength.push_back(getTextBit(first11Pix[p].r, 1));
	}

	/* wczytanie dlugosci wiadomosci i ustawienie tej zmiennej jako warunku wyjscia z petli*/
	long length = converObj.bitToInt(theLength);
	makePixelsArray(img_path, length);
	p = messageSizeBMP;

	while (1)
	{
		theMessage.push_back(getTextBit(pixelsArray[p].r, passwordB[h++]));
		if (++w == length) break;
		if (h == bitwisePasswordLength)	h = 0;
		theMessage.push_back(getTextBit(pixelsArray[p].g, passwordB[h++]));
		if (++w == length) break;
		if (h == bitwisePasswordLength)	h = 0;
		theMessage.push_back(getTextBit(pixelsArray[p++].b, passwordB[h++]));
		if (++w == length) break;
		if (h == bitwisePasswordLength)	h = 0;
	}

	string originalStr = converObj.bitsToString(theMessage);
	fileObj.saveStrToFile(originalStr);

}
/*----------------------------------------*/
bool Steganography::getTextBit(Uint8 pix, bool number2)
{
	usint.clear();							//reset wartosci wektora
	unsigned short a = (unsigned short)pix;	//rgb -> unsigned short int
	usint = converObj.ushortToBits(a);		//unsigned short int -> wektor z bitami
	bool textbit = (usint[0] ^ number2);	//xor 
	return textbit;							//zwrocenie pierwotnego bitu przez push_back()
}
/*----------------------------------------*/
/*Zapisuje wynik kodowania do bmp*/
void Steganography::saveCoded(char *img)
{
	string tempPath = "";

	cout << "Podaj nazwe pliku bmp do stworzenia" << endl;
	cout << "->"; cin >> tempPath; cout << endl;

	fileObj.lookforExtension(tempPath, ".bmp");

	char *newBmpPath = converObj.stringToChar(tempPath);

	/*wczytanie do nowej bitmapy pikseli z pixelsArray*/
	SDL_Surface *bmp = imgObj.loadBitMap(img);
	int loop_cond = ((bitwiseMessageLength + 32) / 3) + 1;
	
	int j = 1; //zmiana wiersza
	/*wypelnienie zmienionymi pixelami*/
	for (int i = bmp->w - 1, y = 0; y < loop_cond; i--, y++)
	{
		if (i + 1 == 0)
		{
			j += 1;
			i = bmp->w - 1;
			imgObj.setPixel(i, bmp->h - j, pixelsArray[y].r, pixelsArray[y].g, pixelsArray[y].b);
		}
		else
			imgObj.setPixel(i, bmp->h - j, pixelsArray[y].r, pixelsArray[y].g, pixelsArray[y].b);
	}

	imgObj.saveBMP(bmp, newBmpPath);
	cout << "Zakonczono kodowanie wiadomosci. Rezultat zostal zapisany w pliku '" << newBmpPath << "'" << endl;
	delete[]newBmpPath;
}
/*----------------------------------------*/
void Steganography::makePixelsArray(char *img, int size)
{
	SDL_Surface *bmp = imgObj.loadBitMap(img);

	int loop_cond = ((size + 32) / 3) + 1;
	int j = 1;

	/*pobiera piksele, w razie potrzeby przechodzi wiersz wyzej*/
	for (int i = bmp->w - 1, y = 0; y < loop_cond; i--, ++y)
	{
		if (i + 1 == 0)
		{
			j += 1;
			i = bmp->w - 1;
			pixelsArray.push_back(imgObj.getPixel(i, bmp->h - j));
		}
		else
			pixelsArray.push_back(imgObj.getPixel(i, bmp->h - j));
	}
}
/*----------------------------------------*/
vector<SDL_Color> Steganography::getMessageLengthFromBMP(char * img_path)
{
	vector<SDL_Color> array;
	SDL_Surface *bmp = imgObj.loadBitMap(img_path);
	int j = 1;

	for (int i = bmp->w - 1, y = 0; y < messageSizeBMP; i--, ++y)
	{
		if (i + 1 == 0)
		{
			j += 1;
			i = bmp->w - 1;
			array.push_back(imgObj.getPixel(i, bmp->h - j));
		}
		else
			array.push_back(imgObj.getPixel(i, bmp->h - j));
	}
	return array;
}
Steganography::Steganography(Image &obj, Conversion &con,File &fil) :bitwiseMessageLength(0), converObj(con),fileObj(fil), bitwisePasswordLength(0), imgObj(obj), messageSizeBMP(11)
{}

Steganography::~Steganography()
{}