#include <iostream>
#include "mylib.hpp"

#include "simple.hpp"
#include "complex.hpp"
#include <string>

int main()
{
 	try {
 		start_program();
 	} catch (const std::exception& e) {
 		std::cerr << "Ending the program" << std::endl;
 	}

 	std::cout << "Successfully reached the end of program!" << std::endl;
 	return 0;
}


// int main()
// {
//	std::string s1, s2;
//	std::cout << "s1 please:" << std::endl << ">>> ";
//	std::cin >> s1;
//	std::cout << "s2 please:" << std::endl << ">>> ";
//	std::cin >> s2;
//
//	TriVector v1(s1), v2(s2);
//
//	TriVector v3;
//
//	return 0;
//}
