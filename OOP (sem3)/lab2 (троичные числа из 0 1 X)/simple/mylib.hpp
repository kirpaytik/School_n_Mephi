#ifndef MYLIB_HPP
#define MYLIB_HPP

#include <string>
class TriSignal;

// job.cpp
void start_program();

TriSignal job_createSignal();
void job_setState(TriSignal& signal, const char& state);
void job_printState(const TriSignal& signal);
char job_oper(TriSignal& signal, const std::string& oper);

// dialogue.cpp
void dialogue(TriSignal& signal);
void dialog_switch(TriSignal& signal, const int& panel);

void dialog_set(TriSignal& signal);
void dialog_print(const TriSignal& signal);
void dialog_operators(TriSignal& signal);

void cout_check();

#endif
