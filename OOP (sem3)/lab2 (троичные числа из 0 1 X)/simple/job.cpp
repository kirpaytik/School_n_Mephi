#include "mylib.hpp"
#include "simple.hpp"


void start_program()
{
	TriSignal signal;

	dialogue(signal);
}


TriSignal job_createSignal()
{
	return TriSignal();
}


void job_setState(TriSignal& signal, const char& state)
{
	try {
		signal.setState(state);
	} catch (std::invalid_argument& e) {
		std::cerr << "Invalid state. Use '0', '1', or 'X'. State remains unchanged" << std::endl;
	}
}


void job_printState(const TriSignal& signal)
{
	signal.print(std::cout);
}


char job_oper(TriSignal& signal, const std::string& oper)
{
	char result;
	if(oper == "!") 
		result = char(!signal);
	else if(oper == "++a")
		result = char(++signal);
	else if(oper == "--a")
		result = char(--signal);
	else if(oper == "a++")
		result = char(signal++);
	else if(oper == "a--")
		result = char(signal--);

	else {
		TriSignal second;
		dialog_set(second);

		if(oper == "||") result = char(signal || second);
		else if(oper == "&&") result = char(signal && second);
		else if(oper == "==") result = signal == second ? 'T' : 'F';
		else if(oper == "!=") result = signal != second ? 'T' : 'F';
		else if(oper == ">") result = signal > second ? 'T' : 'F';
		else if(oper == "<") result = signal < second ? 'T' : 'F';
		else if(oper == ">=") result = signal >= second ? 'T' : 'F';
		else if(oper == "<=") result = signal <= second ? 'T' : 'F';
		else if(oper == "+") result = char(signal + second);
		else if(oper == "-") result = char(signal - second);
		else if(oper == "=") result = char(signal = second);
		else if(oper == "+=") result = char(signal += second);
		else if(oper == "-=") result = char(signal -= second);
	}

	return result;
}
