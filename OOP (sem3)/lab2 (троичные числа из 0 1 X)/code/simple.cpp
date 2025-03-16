#include "simple.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>


TriSignal::TriSignal() noexcept: state('0') {}

TriSignal::TriSignal(const char& state)
{
	if (state == '0' || state == '1' || state == 'X') {
		this->state = state;
	} else {
		std::cerr << "Invalid state has been replaced with '0'. Use '0', '1', or 'X'" << std::endl;
		this->state = '0';
	}
}


void TriSignal::setState(const char& state)
{
	if (state == '0' || state == '1' || state == 'X') {
		this->state = state;
	} else {
		throw std::invalid_argument("Invalid state. Use '0', '1', or 'X'");
	}
}

char TriSignal::getState() const noexcept {return state;}


void TriSignal::print(std::ostream& out) const noexcept
{
	out << state << std::endl;
}

void TriSignal::fprint(const std::string& filename) const
{
	std::ofstream fout(filename);
	if (!fout.is_open()) {
		throw std::ios_base::failure("Could not open file");
	}

	print(fout);
}


TriSignal TriSignal::operator || (const TriSignal& other) const noexcept
{
	if (state == '1' || other.state == '1')
		return TriSignal('1');

	if (state == 'X' || other.state == 'X')
		return TriSignal('X');

	return TriSignal('0');
}


TriSignal TriSignal::operator && (const TriSignal& other) const noexcept
{
	if (state == '0' || other.state == '0') return TriSignal('0');
	if (state == 'X' || other.state == 'X') return TriSignal('X');
	return TriSignal('1');
}


TriSignal TriSignal::operator ^ (const TriSignal& other) const noexcept
{
	if (state == '0') return TriSignal(other.state);
	if (other.state == '0') return TriSignal(state);
	if (state == other.state) return TriSignal('0');
	return TriSignal('X');
}


TriSignal TriSignal::operator ! () const noexcept
{
	if (state == 'X')
		return TriSignal('X');

	return TriSignal(char(!bool(state - '0')) + '0');
}


bool TriSignal::operator == (const TriSignal& other) const noexcept
{
	return state == 'X' || other.state == 'X' || state == other.state;
}


bool TriSignal::operator != (const TriSignal& other) const noexcept
{
	return state == 'X' || other.state == 'X' || state != other.state;
}


bool TriSignal::operator > (const TriSignal& other) const noexcept
{
	if ((state == 'X' && other.state == '1') ||
		(state == '0' && other.state == 'X'))
		return false;
	return state == 'X' || other.state == 'X' || state > other.state;
}


bool TriSignal::operator < (const TriSignal& other) const noexcept
{
	if ((state == '1' && other.state == 'X') ||
		(state == 'X' && other.state == '0'))
		return false;
	return state == 'X' || other.state == 'X' || state < other.state;
}


bool TriSignal::operator >= (const TriSignal& other) const noexcept
{
	return state == 'X' || other.state == 'X' || state >= other.state;
}


bool TriSignal::operator <= (const TriSignal& other) const noexcept
{
	return state == 'X' || other.state == 'X' || state <= other.state;
}


TriSignal TriSignal::operator + (const TriSignal& other) const noexcept
{
	if (state == 'X' || other.state == 'X')
		return TriSignal('X');

	if (state == other.state)
		return TriSignal('0');

	return TriSignal('1');
}


TriSignal TriSignal::operator - (const TriSignal& other) const noexcept
{
	if (state == 'X' || other.state == 'X')
		return TriSignal('X');

	if (state == other.state)
		return TriSignal('0');

	return TriSignal('1');
}


TriSignal& TriSignal::operator ++() noexcept
{
	if (state != 'X')
		state = 1 - (state - '0') + '0';

	return *this;
}


TriSignal& TriSignal::operator --() noexcept
{
	if (state != 'X')
		state = 1 - (state - '0') + '0';

	return *this;
}


TriSignal TriSignal::operator ++(int) noexcept
{
	TriSignal saved(*this);
	if (state != 'X')
		state = 1 - (state - '0') + '0';

	return saved;
}


TriSignal TriSignal::operator --(int) noexcept
{
	TriSignal saved(*this);
	if (state != 'X')
		state = 1 - (state - '0') + '0';

	return saved;
}


TriSignal& TriSignal::operator = (const TriSignal& other) noexcept
{
	if (this != &other) {
		state = other.state;
	}
	return *this;
}


TriSignal& TriSignal::operator += (const TriSignal& other) noexcept
{
	if (state == 'X' || other.state == 'X') {
		state = 'X';
	} else if (state == other.state) {
		state = '0';
	} else {
		state = '1';
	}

	return *this;
}


TriSignal& TriSignal::operator -= (const TriSignal& other) noexcept
{
	if (state == 'X' || other.state == 'X') {
		state = 'X';
	} else if (state == other.state) {
		state = '0';
	} else {
		state = '1';
	}

	return *this;
}


char TriSignal::chr() const noexcept
{
	return state;
}


TriSignal::operator char() const noexcept
{
	return state;
}


std::ostream& operator << (std::ostream& out, const TriSignal& signal)
{
	out << signal.getState();
	return out;
}


std::istream& operator >> (std::istream& in, TriSignal& signal)
{
	char input;
	in >> input;

	signal.setState(input);
	return in;
}
