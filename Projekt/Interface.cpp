#include "Interface.h"

//----------------------------------------
//Menu zwracajace wybrana opcje
char Interface::viewMenu()
{
	char choice = 0;
	int rep = 0;

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
	fstream file;
	int rep = 0;
	//wyszukiwanie txt w folderze
	fileObj.filesList("*.txt");

	while (rep < 5)
	{

		cout << "Podaj nazwe pliku z wiadomoscia:" << endl << "-> ";
		cin >> messageF; cout << endl;

		if (messageF != "")
		{
			fileObj.lookforExtension(messageF, ".txt");

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
				else {
					file.close();
					return message;
				}
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
		file.close();
		cerr << "Blad otwierania pliku. Program zakonczy dzialanie." << endl;
		exit(1);
	}

}

//----------------------------------------
//Zwraca haslo
string Interface::getPassword()
{
	string password = "";
	int rep = 0;

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
	int rep = 0;
	char *g_img = nullptr;
	//wyszukiwanie bmp w folderze
	fileObj.filesList("*.bmp");
	list = fileObj.returnList();

	while (rep < 5)
	{

		cout << endl << "Podaj nazwe pliku bmp:" << endl << "-> ";
		cin >> bitM; cout << endl;

		fileObj.lookforExtension(bitM, ".bmp");

		/*sprawdzanie czy taki plik znajduje sie w folderze*/
		for (size_t i = 0; i < list.size(); i++)
		{
			/*jesli jest*/
			if (list[i] == bitM)
			{
				g_img = converObj.stringToChar(bitM);

				if (bMessageSize)
				{
					/*Sprawdza czy bmp ma wystarczajšco pikseli*/
					if (!imgObj.isMessageFittedIn(bMessageSize, g_img))
					{
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
Interface::Interface(Image &im, File &file_, Conversion &conver) :imgObj(im), fileObj(file_), converObj(conver)
{}

//----------------------------------------
Interface::~Interface()
{}