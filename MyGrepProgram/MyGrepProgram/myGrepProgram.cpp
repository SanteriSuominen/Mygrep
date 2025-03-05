#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

void searchFromString(std::string&, std::string&, int, bool, bool);
void searchFromFile(std::string&, std::string&, std::string&);
bool fileExists(std::string&);

int main(int argc, char** argv)
{
	std::string path, searchTerm, command;
	if (argc > 3)
	{
		command = argv[1];
		searchTerm = argv[2];
		path = argv[3];
	}

	searchFromFile(command, searchTerm, path);

    return 0;
}

void searchFromFile(std::string& command,std::string& searchTerm,std::string& path) // inkrementti 2
{
	bool lineNumbers = 0;
	bool reverseSearch = 0;
	bool endTotalFound = 0;
	bool noCase = 0;

	for (int i = 2; i < command.length(); i++)
	{
		lineNumbers = command[i] == 'l';
		reverseSearch = command[i] == 'o';
		endTotalFound = command[i] == 'r';
		noCase = command[i] == 'i';
	}

	int lineCount = 1;
	if (fileExists(path))
	{
		std::cout << "File has been found" << std::endl;;

		std::ifstream userFile(path);

		if (userFile.is_open())
		{
			std::string line;

			while (std::getline(userFile, line))
			{
				searchFromString(line, searchTerm, lineCount, lineNumbers, reverseSearch);
				lineCount++;
			}
			userFile.close();
		}

		else
			std::cout << "File could not be opened for reading!";
	}
	else
		std::cout << "File could not be found \n File doesnt exist or path is wrong! :(";
}

bool fileExists(std::string& filename)
{
	std::ifstream file(filename);
	return file.good();
}

void searchFromString(std::string& line, std::string& search, int lineCount, bool lineNumbers, bool reverseSearch) // inkrementti 1
{
	

	if (!reverseSearch)
	{
		size_t position = line.find(search);
		if (position != std::string::npos)
		{
			if (lineNumbers)
				std::cout << lineCount << ":";

			std::cout << line;
			std::cout << " || " << search << " found in postion: " << position << std::endl;
		}
	}
	
	else
	{
		size_t position = line.find(search);
		if (position == std::string::npos)
		{
			if (lineNumbers)
				std::cout << lineCount << ":";

			std::cout << line;
			std::cout << " || " << search << " found in postion: " << position << std::endl;
		}
	}
}
