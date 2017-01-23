
#include "File.h"

//Wypelnia wektor plikami o danym rozszerzeniu i je wypisuje
void File::filesList(char *extension)
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
		

		//wypis i dodanie reszty (jesli istnieje)
		while (_findnext(files, &found_file) != -1)
		{
			list.push_back(found_file.name);
			cout << list.size() << " - " << found_file.name << endl;
		}
	}
	_findclose(files);
}

vector<string> File::returnList() const
{
	return list;
}

//----------------------------------------
//Po wprowadzeniu nazwy pliku sprawdza, czy zawiera ona rozszerzenie
void File::lookforExtension(string &text, string search)
{
	size_t found = text.find(search);

	if (found == string::npos) // jesli nie ma -> dodaje
		text += search;
}
//----------------------------------------
//Zwraca adres katalogu z programem
string File::getPathdir(char* maxpath)
{
	GetModuleFileName(NULL, maxpath, MAX_PATH);
	string::size_type pos = string(maxpath).find_last_of("\\/");
	return string(maxpath).substr(0, pos);
}

void File::saveStrToFile(string str)
{
	fstream file;
	string a = "";

	cout << "Podaj nazwe pliku w ktorym chcesz zapisac wynik dekodowania" << endl;
	cout << "->"; cin >> a; cout << endl;
	
	lookforExtension(a, ".txt");
	
	file.open(a, fstream::out);
	
	if (file) {
		file << str;
		cout << "Zapis w pliku '" << a << "' zakonczony powodzeniem" << endl;
		file.close();
	}
	else {
		cerr << "Blad w trakcie otwierania/tworzenia pliku txt" << endl;
		exit(1);
	}
}
