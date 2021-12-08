#include<iostream>
#include<cstdlib>
#include"IniFile.h"
#include<string>
#include<map>

int main(int argc, char** argv) {

	IniFile a(argv[1]);
	auto value = a.Read("player", "x", 0);
	std::cout << "The section is 'player', the key is 'x' "
		"and the value is " << value << "\n";
	std::string change = "666";
	a.Write("player", "x", change);

	value = a.Read("player", "x", 0);
	std::cout << "NOW! The section is 'player', the key is 'x' "
		"and the value is " << value << "\n";

	return 0;
}