#include <iostream>
#include "mylib.hpp"

int main()
{
	int num;
	try {
		num = get_start_num();
	}
	catch (std::runtime_error& e) {
		std::cout << "Wth..." << std::endl;
		return 1;
	}

	try {
		if (num == 1)
			job_start_old();
		else
			job_start_std();
	}
	catch (std::runtime_error& e) {
		std::cout << "Ending the program!xd" << std::endl;
		return 1;
	}

	std::cout << "Successfully reached the end of program" << std::endl;	
	return 0;
}
