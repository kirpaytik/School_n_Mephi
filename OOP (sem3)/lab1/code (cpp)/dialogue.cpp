#include <iostream>

#include <string>
#include <cstring>
#include <vector>

#include <limits>

#include "mylib.hpp"

namespace {
	unsigned int max_word_len = 30;
}


int get_start_num()
{
	int num = -1;
	std::cout << "Input a num 1 (old) or 2 (std)" << std::endl;
	while (true) {
		std::cout << ">>> " << std::flush;
		std::cin >> num;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		if (std::cin.eof()) {
			std::cout << "Ctrl+D detected. Finishing the program" << std::endl;
			throw std::runtime_error("EOF occured, oki-doki then");
		}
		if (std::cin.bad()) {
			throw std::runtime_error("Smth bad happened during console reading xd");
		}
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (num != 1 && num != 2) {
			std::cout << "Bro u r not THAT dumb. Just type 1 or 2 pleeease" << std::endl;
			continue;
		}
		break;
	}

	return num;
}


char* mask_input()
{
	std::cout << "Input a string template to search for words" << std::endl;
	char mask[::max_word_len + 1];

	while (true) {
		std::cout << ">>> " << std::flush;
		std::cin.getline(mask, ::max_word_len + 1);

		if (std::cin.eof()) {
			std::cout << "Ctrl+D detected. Finishing the program" << std::endl;
			throw std::runtime_error("EOF occured, oki-doki then");
		}
		if (std::cin.bad()) {
			throw std::runtime_error("Smth bad happened during console reading xd");
		}
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (!is_valid_mask(mask)) {
			std::cout << "The string contains unrecognised symbols!" << std::endl;
			continue;
		}

		break;
	}

	char* ptr = new char[strlen(mask) + 1];
	strcpy(ptr, mask);
	return ptr;
}


void mask_input(std::string& mask)
{
	std::cout << "Input a string template to search for words" << std::endl;

	while (true) {
		std::cout << ">>> " << std::flush;
		std::cin >> mask;

		if (std::cin.eof()) {
			std::cout << "Ctrl+D detected. Finishing the program" << std::endl;
			throw std::runtime_error("EOF occured, oki-doki then");
		}
		if (std::cin.bad()) {
			throw std::runtime_error("Smth bad happened during console reading xd");
		}
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}

		if (!is_valid_mask(mask)) {
			std::cout << "The string contains unrecognised symbols!" << std::endl;
			continue;
		}

		break;
	}
}


void word_fread(std::ifstream& fin, char* word)
{
	fin.getline(word, ::max_word_len + 1);
	if (fin.eof()) {
		return;
	}
	if (fin.bad()) {
		throw std::runtime_error("Smth bad happened during freading xd");
	}
	if (fin.fail()) {
		fin.clear();
		fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}


void word_fread(std::ifstream& fin, std::string& word)
{
	std::getline(fin, word);
	if (fin.eof()) {
		return;
	}
	if (fin.bad()) {
		throw std::runtime_error("Smth bad happened during freading xd");
	}
	if (fin.fail()) {
		fin.clear();
		fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}


void words_print(const char** words)
{
	if (words[0] == nullptr) {
		std::cout << "No words mathed!" << std::endl;
		return;
	}

	std::cout << "Words found:" << std::endl;
	unsigned int i = 0;
	while (words[i]) {
		std::cout << "\"" << words[i] << "\"" << std::endl;
		i++;
	}
}


void words_print(std::vector<std::string> words)
{
	if (words.empty()) {
		std::cout << "No words mathed!" << std::endl;
		return;
	}

	std::cout << "Words found:" << std::endl;
	for (const std::string& word : words) {
		std::cout << "\"" << word << "\"" << std::endl;
	}
}
