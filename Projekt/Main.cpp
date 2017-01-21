#include "Image.h"
#include "Interface.h"
#include "Steganography.h"

void choice_1(Interface &inter, Image &im, Steganography &steg)
{
	string message = inter.getMessage();
	string password = inter.getPassword();

	vector<bool>messageB = steg.stringToBits(message);
	vector<bool>passwordB = steg.stringToBits(password);

	/*pobiera nazwe pliku bmp do otworzenia + obsluga sytuacji granicznych*/
	char *img = inter.getImage((messageB.size() + 32) / 3 + 1);

	steg.code(messageB, passwordB, img);
}

void choice_2(Interface &inter, Image &im, Steganography &steg)
{
	char *img = inter.getImage();
	string password = inter.getPassword();
	vector<bool>passwordB = steg.stringToBits(password);
	steg.decode(passwordB, img);

}

int main(int argc, char** argv)
{
	Image image;
	Interface interface_(image);
	Steganography steganography(image);
	char choice = interface_.viewMenu();

	if (choice == '1')
		choice_1(interface_, image, steganography);

	else if (choice == '2')
		choice_2(interface_, image, steganography);

	else
	{
		cout << "Program konczy dzialanie." << endl;
		system("pause");
		exit(0);
	}
	system("pause");
	return 0;
}