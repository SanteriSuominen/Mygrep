#include "Mygrep.h"


Mygrep::Mygrep()
{
	this->init();
}

Mygrep::~Mygrep()
{
}

void Mygrep::init()
{
}

void Mygrep::locateAndReadUsersFile()
{
	std::cout << "File location?\nExample C:/Documents/..." << std::endl;
	std::string path = getUserInput();

	if (fileExists(path))
	{
		std::cout << "File has been found" << std::endl;;

		std::ifstream userFile(path);

		if (userFile.is_open())
		{
			std::string line;

			while (std::getline(userFile, line))
			{
				std::cout << line << "\n";
			}
			userFile.close();
		}

		else
			std::cout << "File could not be opened for reading!";
	}

	else
		std::cout << "File could not be found \n File doesnt exist or path is wrong! :(";

}

bool Mygrep::fileExists(std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}

std::string Mygrep::getUserInput(std::string message)
{
	std::string temp = "";
	std::cin >> temp;
	while (true)
	{
		if (std::cin.fail())	// jos syötteen lukeminen epäonnistui
		{
			std::cin.clear();	// tyhjennetään virhetila
			std::cin.ignore(INT_MAX, '\n');	// tyhjennetään syöte puskuri
			std::cout << message << std::endl;	// tulostetaan virhe viesti
			std::cin >> temp;	//yritetään uudelleen
		}
		else
			break;
	}
	return temp;
}
