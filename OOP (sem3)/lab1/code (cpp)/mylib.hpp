#ifndef MYLIB_H
#define MYLIB_H

#include <fstream>
#include <vector>

// dialogue.cpp
int get_start_num();

char* mask_input();
void mask_input(std::string& mask);
void word_fread(std::ifstream& fin, char* word);
void word_fread(std::ifstream& fin, std::string& word);
void words_print(const char** words);
void words_print(std::vector<std::string> words);

// job.cpp
void job_start_old();
void job_start_std();
void words_delete(const char** words);

int is_valid_mask(const char *mask);
int is_valid_mask(const std::string& mask);
const char** words_from_mask(const char* mask);
std::vector<std::string> words_from_mask(const std::string& mask);
int is_match_to_mask(const char *word, const char *mask);
int is_match_to_mask(const std::string& word, const std::string& mask);

#endif
