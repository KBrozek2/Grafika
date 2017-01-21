#include "Interface.h"

//----------------------------------------
//Menu zwracajace wybrana opcje
char Interface::viewMenu()
{
	char choice = 0;
	rep = 0;

	cout << "========KODOWANIE WIADOMOSCI W BITMAPIE========" << endl;

	while (choice != '1' && choice != '2' && choice != '3' && rep < 3)
	{
		cout << "Wybierz opcje" << endl;
		cout << "1 - zakodowac wiadomosc" << endl;
		cout << "2 - odkodowac wiadomosc" << endl;
		cout << "3 - wyjscie" << endl << "-> ";
		cin >> choice;
		rep++;
	}

	//limit powtorzen
	if (rep == 3)
		choice = 3;

	return choice;
}

//----------------------------------------
//Zwraca wiadomosc
string Interface::getMessage()
{
	string messageF = "";
	string message = "";
	rep = 0;
	//wyszukiwanie txt w folderze
	filesList("*.txt");

	while (rep < 5)
	{

		cout << "Podaj nazwe pliku z wiadomoscia:" << endl << "-> ";
		cin >> messageF; cout << endl;

		if (messageF != "")
		{
			lookforExtension(messageF, ".txt");

			file.open(messageF);
			if (file)
			{
				string msg;

				//odczyt z pliku
				while (getline(file, msg)) {
					message += msg;
					message += "\n";
				}
				message.resize(message.size() - 1);

				//jesli pusty
				if (message == "")
				{
					cerr << ("Blad! Plik jest pusty!") << endl;
					rep++;
					file.close();
				}
				//jesli nie jest pusty, zwraca
				else
					return message;
			}
			//jesli nie ma takiego pliku
			else
				rep++;
			//jesli ktos nie podal nazwy
		}
		else
			rep++;


	}

	//jesli nie znalazl kilka razy
	if (message == "" && rep == 5)
	{
		cerr << "Blad otwierania pliku. Program zakonczy dzialanie." << endl;
		system("pause");
		exit(1);
	}
}

//----------------------------------------
//Zwraca haslo
string Interface::getPassword()
{
	string password = "";
	rep = 0;

	while (password == "" && rep < 3)
	{
		cout << "Podaj haslo do kodowania:" << endl << "-> ";
		cin >> password; cout << endl;
		rep++;
	}

	if (password != "")
		return password;

	else
	{
		cerr << "Blad wpisywania hasla. Program zakonczy dzialanie." << endl;
		system("pause");
		exit(1);
	}
}

//----------------------------------------
//Zwraca nazwe pliku bmp w ktorym zostanie zakodowana wiadomosc
char *Interface::getImage(int bMessageSize)
{
	string bitM = "";
	rep = 0;

	//wyszukiwanie bmp w folderze
	filesList("*.bmp");

	while (rep < 5)
	{

		cout << endl << "Podaj nazwe pliku bmp:" << endl << "-> ";
		cin >> bitM; cout << endl;

		lookforExtension(bitM, ".bmp");

		//sprawdzanie czy taki plik znajduje sie w folderze
		for (size_t i = 0; i < list.size(); i++)
		{
			//jesli jest
			if (list[i] == bitM)
			{
				g_img = new char[bitM.length() + 1];
				strcpy(g_img, bitM.c_str());

				if (bMessageSize) {
					/*Sprawdza czy bmp ma wystarczaj¹co pikseli*/
					if (!imgObj.isMessageFittedIn(bMessageSize, g_img)) {
						cout << "Wybrany plik bmp jest za maly by pomiescic zadana wiadomosc!" << endl;
						delete[] g_img;
						break;
					}
					/*Sprawdza czy bmp przekracza 1920x1080*/
					if (!imgObj.isBmpRightSize(g_img)) {
						cout << "Wybrany plik bmp jest za duzy!" << endl;
						delete[]g_img;
						break;
					}
				}
				return g_img;
			}
		}
		rep++;
	}

	if (rep == 5)
	{
		cerr << "Nie wskazales zadnego z plikow .bmp. Program zakonczy dzialanie." << endl;
		system("pause");
		exit(1);
	}
}

//----------------------------------------
//Wypelnia wektor plikami o danym rozszerzeniu i je wypisuje
void Interface::filesList(char *extension)
{
	list.clear();
	long files;

	//adres katalogu z plikami
	char q[MAX_PATH];
	string dirpath = getPathdir(q);

	//wyszukiwanie plikow w katalogu projektu z danym rozszerzeniem
	_finddata_t found_file;

	//jesli nie ma zadnych
	if ((files = _findfirst(extension, &found_file)) == -1)
	{
		cerr << "W folderze: " << dirpath << " nie ma zadnych plikow " << extension << ". Program zakonczy dzialanie." << endl;
		system("pause");
		exit(1);
	}

	//jesli jakis istnieje
	else
	{
		//dodanie i wypis pierwszego
		list.push_back(found_file.name);

		cout << "Pliki znajdujace sie w katalogu: " << endl << dirpath << endl;
		cout << list.size() << " - " << found_file.name << endl;
		rep++;

		//wypis i dodanie reszty (jesli istnieje)

		while (_findnext(files, &found_file) != -1)
		{
			list.push_back(found_file.name);
			cout << list.size() << " - " << found_file.name << endl;
		}
	}
	_findclose(files);
}

//----------------------------------------
//Po wprowadzeniu nazwy pliku sprawdza, czy zawiera ona rozszerzenie
void Interface::lookforExtension(std::string &text, std::string search)
{
	size_t found = text.find(search);

	if (found == string::npos) // jesli nie ma -> dodaje
	{
		text += search;
	}
	else return;
}

//----------------------------------------
//Zwraca adres katalogu z programem
string Interface::getPathdir(char* maxpath)
{
	GetModuleFileName(NULL, maxpath, MAX_PATH);
	string::size_type pos = string(maxpath).find_last_of("\\/");
	return string(maxpath).substr(0, pos);
}

//----------------------------------------
Interface::Interface(Image &im) :imgObj(im), rep(0), g_img(nullptr)
{}

//----------------------------------------
Interface::~Interface()
{
	delete[] g_img;
	file.close();
}