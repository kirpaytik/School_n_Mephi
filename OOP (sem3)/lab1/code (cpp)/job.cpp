#include <iostream>
#include <fstream>

#include <string>
#include <cstring>
#include <vector>

#include <algorithm>
#include <cctype>

#include "mylib.hpp"

namespace {
	unsigned int max_word_len = 30;
}


void job_start_old()
{
	char *mask = mask_input();

	const char** words = nullptr;
	try {
		words = words_from_mask(mask);
		delete[] mask;
	}
	catch (const std::runtime_error& e) {
		delete[] mask;
		throw;
	}

	words_print(words);

	words_delete(words);

	return;
}


void job_start_std()
{
	std::string mask;
	mask_input(mask);

	std::vector<std::string> words;
	words = words_from_mask(mask);

	words_print(words);

	return;
}


void words_delete(const char** words)
{
	unsigned int i = 0;
	while (words[i]) {
		delete[] words[i];
		i++;
	}
	delete[] words;
}


int is_valid_mask(const char *mask)
{
	while (*mask) {
		if (!isalpha(*mask) && *mask != '?') {
			return 0;
		}
		mask++;
	}
	return 1;
}


int is_valid_mask(const std::string& mask)
{
	for (char ch : mask) {
		if (!isalpha(ch) && ch != '?') {
			return 0;
		}
	}
	return 1;
}



const char** words_from_mask(const char* mask)
{
	std::ifstream fin("words.txt");
	if (!fin.is_open()) {
		std::cout << "Failed to open file" << std::endl;
		throw std::runtime_error("Smth bad happened with fopening during words reading xd");
	}

	char **words = nullptr;
	size_t capacity = 0;
	size_t count = 0;
	char word[::max_word_len + 1];

	while (!fin.eof()) {
		try {
			word_fread(fin, word);
		}
		catch (const std::runtime_error& e) {
			if (words) words_delete((const char **)words);
			throw;
		}
		if (strlen(word) == 0) continue;

		if (is_match_to_mask(word, mask)) {
			if (count + 1 >= capacity) {
				capacity = capacity ? capacity * 2 : 2;

				char **newWords = new char*[capacity];
				std::copy(words, words + count, newWords);
				delete[] words;
				words = newWords;
			}
			words[count] = new char[strlen(word) + 1];
			strcpy(words[count], word);
			words[count + 1] = nullptr;
			count++;
		}
	}

	fin.close();

	const char **newWords = new const char*[count + 1];
	for (size_t i = 0; i < count; i++) {
		newWords[i] = words[i];
	}
	delete[] words;
	newWords[count] = nullptr;

	return newWords;
}


std::vector<std::string> words_from_mask(const std::string& mask)
{
	std::ifstream fin("words.txt");
	if (!fin.is_open()) {
		std::cout << "Failed to open file" << std::endl;
		throw std::runtime_error("Smth bad happened with fopening during words reading xd");
	}

	std::vector<std::string> words;
	std::string word;
	while (!fin.eof()) {
		word_fread(fin, word);
		if (word.length() == 0) continue;

		if (is_match_to_mask(word, mask)) {
			words.push_back(word);
		}
	}

	return words;
}


int is_match_to_mask(const char *word, const char *mask)
{
	while (*mask) {
		if (*mask != '?' && *mask != *word) {
			return 0;
		}
		mask++;
		word++;
	}
	return *word == '\0';
}


int is_match_to_mask(const std::string& word, const std::string& mask) {
	unsigned int wordLength = word.length();
	unsigned int maskLength = mask.length();
	
	for (unsigned int i = 0; i < maskLength; ++i) {
		if (i >= wordLength) {
			return 0;
		}
		if (mask[i] != '?' && mask[i] != word[i]) {
			return 0;
		}
	}
	
	return wordLength == maskLength;
}
