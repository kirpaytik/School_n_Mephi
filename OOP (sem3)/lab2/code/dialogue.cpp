#include "mylib.hpp"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <limits>


void dialogue(TriVector& vector)
{
	while(true) {
		std::cout << "Choose an option from the menu below:" << std::endl
			<< "(1) Set a vector" << std::endl
			<< "(2) Print the vector" << std::endl
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

		dialog_switch(vector, panel);
	}
}


void dialog_switch(TriVector& vector, const int& panel)
{
	switch (panel) {
	case 1:
		dialog_set(vector);
		dialog_print(vector);
		break;
	case 2:
		dialog_print(vector);
		break;
	case 3:
		dialog_operators(vector);
		break;
	}
}


void dialog_set(TriVector& vector)
{
	std::string input;

	std::cout << "Input a vector" << std::endl;
	std::cin >> input;
	cout_check();

	job_setVector(vector, input);
}


void dialog_print(const TriVector& vector)
{
	std::cout << "The vector now is:" << std::endl;
	job_printVector(vector);
}


void dialog_operators(TriVector& vector)
{
	std::string oper;
	std::vector<std::string> opers = {"|", "&", "~", "==", "!=", ">", ">=", "<", "<=", "+", "-", "a++", "a--", "=", "+=", "-="};
	while (true) {
		std::cout << "Which operator to use?" << std::endl
			<< "|, &, ~, ==, !=, >, >=, <, <=, +, -, a--, a++, =, +=, -=" << std::endl;
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

	std::vector<std::string> single_opers = {"!", "++", "--", "a++", "a--"};
	if (std::find(single_opers.begin(), single_opers.end(), oper) == single_opers.end()) {
		std::cout << "The second operand is needed for this operator" << std::endl;
		// the 2nd oper will be set in job_oper()
	}

	bool result = job_oper(vector, oper);
	std::cout << "The result of operation is: " << std::endl;

	std::vector<std::string> bool_opers = {"==", "!=", ">", ">=", "<", "<="};
	if (std::find(bool_opers.begin(), bool_opers.end(), oper) != bool_opers.end()) {
		std::cout << result << std::endl;
	} else {
		job_printVector(vector);
	}
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
