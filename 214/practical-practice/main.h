#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <cstring>

namespace Constants {
	const char CHARACTER { 'K' };
	const std::string NAME { "Kiefer Kyler Killer" };
	char CSTRING[] { "Kiefer Kyler Killer" };
	const int ARRAYNUM[] { 1, 2, 9, 4, 3 };
	const int SIZE { sizeof(ARRAYNUM) / sizeof(ARRAYNUM[0]) };
	const char VOWELS[]{ 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
}

struct Student {
	int id;
	std::string name;
};

#endif