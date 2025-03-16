#include "mylib.hpp"

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>


void dialogue(TriSignal& signal)
{
	while(true) {
		std::cout << "Choose an option from the menu below:" << std::endl
			<< "(1) Set a state to signal" << std::endl
			<< "(2) Get the signal's state" << std::endl
			<< "(3) do some operators..." << std::endl
			<< "(4) Finish the program" << std::endl;
		std::cout << ">>> ";
		std::flush(std::cout);

		int panel;
		std::cin >> panel;
		cout_check();

		if (panel < 1 || panel > 4) {
			std::cout << "Incorrect menu option! Please choose 1-3" << std::endl;
			continue;
		}
		if (panel == 4) return;

		dialog_switch(signal, panel);
	}
}


void dialog_switch(TriSignal& signal, const int& panel)
{
	switch (panel) {
	case 1:
		dialog_set(signal);
		dialog_print(signal);
		break;
	case 2:
		dialog_print(signal);
		break;
	case 3:
		dialog_operators(signal);
		break;
	}
}


void dialog_set(TriSignal& signal)
{
	char state;

	std::cout << "Enter a state to signal:" << std::endl;
	std::cin >> state;
	cout_check();

	job_setState(signal, state);
}


void dialog_print(const TriSignal& signal)
{
	std::cout << "The state now is:" << std::endl;
	job_printState(signal);
}


void dialog_operators(TriSignal& signal)
{
	std::string oper;
	std::vector<std::string> opers = {"||", "&&", "!", "==", "!=", ">", ">=", "<", "<=", "+", "-", "++a", "--a", "a++", "a--", "=", "+=", "-="};
	while (true) {
		std::cout << "Which operator to use?" << std::endl
			<< "||, &&, !, ==, !=, >, >=, <, <=, +, -, ++a, --a, a++, a--, =, +=, -=" << std::endl;
		std::cout << ">>> ";
		std::flush(std::cout);

		std::cin >> oper;
		cout_check();

		if (std::find(opers.begin(), opers.end(), oper) == opers.end()) {
			std::cerr << "Invalid operator!" << std::endl;
			continue;
		}
		break;
	}

	std::vector<std::string> single_opers = {"!", "++", "--", "++a", "--a", "a++", "a--"};
	if (std::find(single_opers.begin(), single_opers.end(), oper) == single_opers.end()) {
		std::cout << "The second operand is needed for this operator" << std::endl;
		// the 2nd oper will be set in job_oper()
	}

	char result = job_oper(signal, oper);
	std::cout << "The result of operation is: " << result << std::endl;
}


void cout_check()
{
	if (std::cin.eof()) {
		std::cout << "Ctrl+D detected. Finishing the program" << std::endl;
		throw std::runtime_error("EOF occured, oki-doki then");
	}
	if (std::cin.bad()) {
		throw std::runtime_error("Smth bad happened during console reading, xd");
	}
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
}
