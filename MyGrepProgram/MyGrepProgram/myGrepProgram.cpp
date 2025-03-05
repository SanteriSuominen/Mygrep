#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <fstream>
#include <sstream>

bool searchFromString(std::string&, std::string&, int, bool, bool, bool);
void searchFromFile(std::string&, std::string&, std::string&);
std::string convertToLowerCase(std::string&);
bool fileExists(std::string&);

int main(int argc, char** argv) // otetaan vastaan komentorivin k�skyt ja k�ytet��n niit� index j�rjestyksess�
{
	std::string path, searchTerm, command;
	if (argc > 3)
	{
		command = argv[1];
		searchTerm = argv[2];
		path =	argv[3];
	}

	searchFromFile(command, searchTerm, path);

    return 0;
}

void searchFromFile(std::string& command,std::string& searchTerm,std::string& path) 
{
	bool lineNumbers = 0;
	bool reverseSearch = 0;
	bool endTotalFound = 0;
	bool noCase = 0;

	for (int i = 2; i < command.length(); i++) // tarkistetaan l�sn�olevat komennot
	{
		if(command[i] == 'l') // esim oliko kyseinen char positio i = l, jos on ly�d�� p��lle  || ei ota huomioon kahta ekaa indexi� jotka ovat vakiot -o
			lineNumbers = true;

		if (command[i] == 'o')
			endTotalFound = true;

		if (command[i] == 'r')
			reverseSearch = true;

		if (command[i] == 'i')
			noCase = true;
	}

	int lineCount = 1;
	int hitCount = 0;
	if (fileExists(path))	// onko tiedosto olemassa
	{
		std::cout << "\nFile has been found" << std::endl;;

		std::ifstream userFile(path);

		if (userFile.is_open())
		{
			std::string line;

			while (std::getline(userFile, line)) // k�yd��n jokainen rivi l�pi
			{
				if (searchFromString(line, searchTerm, lineCount, lineNumbers, reverseSearch, noCase))
					hitCount++;

				lineCount++;
			}
				// raportti
			if (endTotalFound && !reverseSearch)
				std::cout << "\n\nOccurrences of lines containing " << "\"" << searchTerm << "\": " << hitCount; // lukum��r� mik�li sis�lsi search termin

			if(endTotalFound && reverseSearch)
				std::cout << "\n\nOccurrences of lines NOT containing " << "\"" << searchTerm << "\": " << hitCount; // mik�li reverce search lukum��r� riveist� mitk� ei sis�ll� search term
			
			if (hitCount == 0)
				std::cout << "\n\nNo lines contain your search term: " << "\" " << searchTerm << "\""; // yksik��n rivi ei t�sm��

			userFile.close();
		}

		else
			std::cout << "\nFile could not be opened for reading!";
	}
	else
		std::cout << "\nFile could not be found \n File doesnt exist or path is wrong! :(";
}

bool fileExists(std::string& filename) // tiedoston olemassa olon tarkistus
{
	std::ifstream file(filename);
	return file.good();
}

bool searchFromString(std::string& line, std::string& search, int lineCount, bool lineNumbers, bool reverseSearch, bool noCase) // oikea ty� tapahtuu t��l�. bool koska palauttaa osuman mik�li rivill� on search term
{
	if (noCase) // mik�li noCase on p��ll� muutetaan tutkittava line ja search term lowercaseen
	{
		search = convertToLowerCase(search);
		line = convertToLowerCase(line);
	}

	if (!reverseSearch) // normaali toiminta jos reverse searchi� ei ole pyydetty
	{
		size_t position = line.find(search);
		if (position != std::string::npos)
		{
			if (lineNumbers) // lis�� joka rivin alkuun sille kuuluvan rivi numeron
				std::cout << lineCount << ":";

			std::cout << line;
			std::cout << " || " << search << " found in postion: " << position << std::endl;
			return true;
		}
	}
	
	else // mik�li reverse search on p��ll� hyp�t��n t�nne ja tuloseteaan ne rivit jotka ei sis�ll� search termi�
	{
		if (line.find(search) == std::string::npos)
		{
			if (lineNumbers) // lis�� joka rivin alkuun sille kuuluvan rivi numeron
				std::cout << lineCount << ":";

			std::cout << line << std::endl;
			return true;
		}
	}
	return false;
}

std::string convertToLowerCase(std::string& str) // muunnos funktio muuntaa stringin jokaisen Char:in lowercaseen sill� string on vain jono charactereita!
{
	for (char& c : str) {
		c = std::tolower(c);
	}
	return str;
}
