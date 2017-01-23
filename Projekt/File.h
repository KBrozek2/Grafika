#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <io.h>

using namespace std;

class File 
{
	vector <string> list;
public:
	void lookforExtension(string&, string); //dopisywanie rozszerzen
	void filesList(char*); // robi liste plikow w folderze
	vector<string> returnList()const;
	string getPathdir(char*); //sciezka katalogu projektu
	void saveStrToFile(string);
};