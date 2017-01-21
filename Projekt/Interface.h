#pragma warning(disable:4996)
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <io.h>
#include "Image.h"

using namespace std;

class Interface
{
	Image imgObj;
	fstream file;
	vector <string> list; // tablica plikow w folderze
	int rep; // do prob wpisywania danych	
	char *g_img; // konwersja stringa z nazwa pliku bmp do char

	void lookforExtension(string&, string); //dopisywanie rozszerzen
	void filesList(char*); // robi liste plikow w folderze
	string getPathdir(char*); //sciezka katalogu projektu
public:

	char viewMenu();
	char *getImage(int = 0);
	string getPassword();
	string getMessage();

	Interface(Image &);
	~Interface();
};

