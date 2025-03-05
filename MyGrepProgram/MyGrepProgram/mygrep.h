#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Mygrep
{
private:

public:
	Mygrep();
	~Mygrep();
	void init();
	std::string getUserInput(std::string message = "Try again: ");
	void locateAndReadUsersFile();
	bool fileExists(std::string& filename);
};
#pragma once
