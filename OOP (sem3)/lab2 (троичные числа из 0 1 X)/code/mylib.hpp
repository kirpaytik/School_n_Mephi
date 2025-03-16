#ifndef MYLIB_HPP
#define MYLIB_HPP

#include <string>
class TriVector;

// job.cpp
void start_program();

TriVector job_createVector();
void job_setVector(TriVector& vector, const std::string& str);
void job_printVector(const TriVector& vector);
bool job_oper(TriVector& vector, const std::string& oper);

// dialogue.cpp
void dialogue(TriVector& vector);
void dialog_switch(TriVector& vector, const int& panel);

void dialog_set(TriVector& vector);
void dialog_print(const TriVector& vector);
void dialog_operators(TriVector& vector);

void cout_check();

#endif
