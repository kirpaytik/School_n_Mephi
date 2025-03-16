#ifndef MYLIB_H
#define MYLIB_H

// dialogue.c
void dialogue_start();

// job.c
int is_valid_mask(const char *mask);
const char** words_from_mask(const char* mask);
int is_match_to_mask(const char *word, const char *mask);

#endif
