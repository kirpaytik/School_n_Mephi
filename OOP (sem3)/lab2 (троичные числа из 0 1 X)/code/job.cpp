#include "mylib.hpp"
#include "complex.hpp"


void start_program()
{
	TriVector vector;

	dialogue(vector);
}


TriVector job_createVector()
{
	return TriVector();
}


void job_setVector(TriVector& vector, const std::string& str)
{
	vector.setVector(str);
}


void job_printVector(const TriVector& vector)
{
	vector.print(std::cout);
}


bool job_oper(TriVector& vector, const std::string& oper)
{
	if(oper == "~") 
		vector = ~vector;
	else if(oper == "a++")
		vector++;
	else if(oper == "a--")
		vector--;

	else {
		TriVector second;
		dialog_set(second);

		if(oper == "|") vector = vector | second;
		else if(oper == "&") vector = vector & second;
		else if(oper == "==") return vector == second;
		else if(oper == "!=") return vector != second;
		else if(oper == ">") return vector > second;
		else if(oper == "<") return vector < second;
		else if(oper == ">=") return vector >= second;
		else if(oper == "<=") return vector <= second;
		else if(oper == "+") vector = vector + second;
		else if(oper == "-") vector = vector - second;
		else if(oper == "=") vector = second;
		else if(oper == "+=") vector += second;
		else if(oper == "-=") vector -= second;
	}

	return true;
}
