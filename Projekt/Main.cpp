#include "Image.h"
#include "Interface.h"
#include "Steganography.h"
#include "Files.h"
#include "Conversions.h"

void choice_1(Interface &inter, Image &im, Steganography &steg, Conversion &conver)
{
	string message = inter.getMessage();
	string password = inter.getPassword();

	vector<bool>messageB = conver.stringToBits(message);
	vector<bool>passwordB = conver.stringToBits(password);

	/*pobiera nazwe pliku bmp do otworzenia + obsluga sytuacji granicznych*/
	char *img = inter.getImage((messageB.size() + 32) / 3 + 1);

	steg.Code(messageB, passwordB, img);
}

void choice_2(Interface &inter, Image &im, Steganography &steg, Conversion &conver)
{
	char *img = inter.getImage();
	string password = inter.getPassword();
	vector<bool>passwordB = conver.stringToBits(password);
	steg.Decode(passwordB, img);



}



int main(int argc, char ** argv)
{
	Image image;
	Files file;
	Conversion conversion;
	Interface interface_(image, file, conversion);
	Steganography steganography(image, conversion);
	char choice = interface_.viewMenu();

	if (choice == '1')
		choice_1(interface_, image, steganography, conversion);

	else if (choice == '2')
		choice_2(interface_, image, steganography, conversion);

	else
	{
		cout << "Program konczy dzialanie." << endl;
		system("pause");
		exit(0);
	}
	system("pause");
	return 0;
}