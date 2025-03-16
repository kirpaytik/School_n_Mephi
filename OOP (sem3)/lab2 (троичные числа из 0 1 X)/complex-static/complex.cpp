#include "complex.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <compare>
#include <sstream>

#include "simple.hpp"


TriVector::TriVector(): length(0), coord() {}

TriVector::TriVector(const int& len) : length(len), coord(length) {}

TriVector::TriVector(const int& len, const TriSignal& signal) :
	length(len), coord(len, signal) {}

TriVector::TriVector(const std::string& arr) :
	length(arr.size()), coord(arr.size())
{
	std::transform(arr.begin(), arr.end(), coord.begin(),
		[] (const char& c) -> TriSignal { return TriSignal(c);} );
}

TriVector::TriVector(const std::vector<TriSignal>& arr) :
	length(arr.size()), coord(arr) {}

TriVector::TriVector(const TriVector& other) :
	length(other.length), coord(other.coord) {}

TriVector::TriVector(TriVector&& other):
	length(other.length), coord(std::move(other.coord))
	{ other.length = 0; }


TriVector& TriVector::setVector(const std::string& arr)
{
	coord.clear();
	coord.resize(arr.size());
	std::transform(arr.begin(), arr.end(), coord.begin(),
		[] (const char& c) -> TriSignal { return TriSignal(c);} );
	length = arr.size();

	return *this;
}


TriVector& TriVector::setVector(const std::vector<TriSignal>& arr)
{
	coord = arr;
	length = coord.size();

	return *this;
}


TriVector& TriVector::setSignal(const TriSignal& signal, const int& index)
{
	if (index < 0 || index >= length)
		throw std::out_of_range("Index is out of range");

	coord[index] = signal;
	return *this;
}


int TriVector::getLength() const noexcept
{
	return length;
}


std::vector<TriSignal> TriVector::getVector() const noexcept
{
	return coord;
}


TriSignal TriVector::getSignal(const int& index) const
{
	if (index < 0 || index >= length)
		throw std::out_of_range("Index is out of range");

	return coord[index];
}


void TriVector::print(std::ostream& out) const noexcept
{
	for (const TriSignal& signal : coord) {
		out << signal;
	}
}


void TriVector::fprint(const std::string& filename) const
{
	std::ofstream fout(filename);
	if (!fout.is_open()) {
		throw std::ios_base::failure("Could not open file");
	}

	print(fout);
}


TriVector TriVector::operator | (const TriVector& other) const
{
	if (length != other.length) {
		throw std::invalid_argument("Vectors must be the same length");
	}

	TriVector result(length);
	for (int i = 0; i < length; ++i) {
		result.coord[i] = coord[i] || other.coord[i];
	}

	return result;
}


TriVector TriVector::operator & (const TriVector& other) const
{
	if (length != other.length) {
		throw std::invalid_argument("Vectors must be the same length");
	}

	TriVector result(length);
	for (int i = 0; i < length; ++i) {
		result.coord[i] = coord[i] && other.coord[i];
	}

	return result;
}


TriVector TriVector::operator ~ () const
{
	TriVector result(length);

	for (int i = 0; i < length; ++i) {
		result.coord[i] = !coord[i];
	}

	return result;
}


std::strong_ordering TriVector::operator <=>(const TriVector& other) const noexcept
{
	if (real_length() > other.real_length())
		return std::strong_ordering::greater;

	if (real_length() < other.real_length())
		return std::strong_ordering::less;

	int potential = 0;
	for (int j = length - 1, k = other.length - 1; j > -1 && k > -1; --j, --k) {
		char a = coord[j].state;
		char b = other.coord[k].state;
		if (a == 'X' || b == 'X') {
			if (checkPotential(coord[j].state, other.coord[k].state, potential)) {
				return std::strong_ordering::equal;
			}
			continue;
		}

		if (coord[j] > other.coord[k]) {
			if (potential < 0) return std::strong_ordering::equal;
			return std::strong_ordering::greater;
		}

		if (coord[j] < other.coord[k]) {
			if (potential > 0) return std::strong_ordering::equal;
			return std::strong_ordering::less;
		}
	}

	return std::strong_ordering::equal;
}


bool TriVector::operator == (const TriVector& other) const noexcept
{
	if (length != other.length)
		return false;

	return std::equal(coord.begin(), coord.end(), other.coord.begin());
}


bool TriVector::operator != (const TriVector& other) const noexcept
{
	return !(*this == other);
}


bool TriVector::checkPotential(const char& a, const char& b, int& potential) const noexcept
{
	// potential: X < 1 => less, 0 < X => less
	if ((a == 'X' && b == '1') || (a == '0' && b == 'X')) {
		if (potential > 0) return true;
		potential = -1;
	// potential: X > 0 => greater, 1 > X => greater
	} else if ((a == 'X' && b == '0') || (a == '1' && b == 'X')) {
		if (potential < 0) return true;
		potential = 1;
	}

	return false;
}


TriVector TriVector::operator + (const TriVector& other) const
{
	int maxlen = std::max(length, other.length);
	TriVector result(maxlen);

	TriSignal carry('0');
	int j = length - 1;
	int k = other.length - 1;

	for (int i = maxlen - 1; i > -1; --i, --j, --k) {
		TriSignal a(j > -1 ? coord[j] : TriSignal('0'));
		TriSignal b(k > -1 ? other.coord[k] : TriSignal('0'));

		result.coord[i] = a + b + carry;
		calculateCarry(a, b, carry);
	}
	// расширить result, если carry ещё остался
	if (carry.state != '0') {
		result.coord.insert(result.coord.begin(), TriSignal(carry.state));
		++result.length;
	}

	return result;
}
// ОФИГЕТЬ АССОЦИАТИВНОСТЬ ПОТЕРЯЛАСЬ, пример:
// (001X + 111X) + 1 = 100XX + 1 = 10XXX
// 001X + (111X + 1) = 001X + XXXXX = XXXXX

void TriVector::calculateCarry(const TriSignal& a, const TriSignal& b, TriSignal& carry) const noexcept
{
	if (( (a && b) || (a && carry) || (b && carry) ).state == '1') {
		carry.state = '1';
	} else if (( (a || b) && (a || carry) && (b || carry) ).state == '0') {
		carry.state = '0';
	} else { carry.state = 'X'; } // 7+6=13 случаев из 27
}


// TriVector TriVector::operator - (TriVector other) const
// {
// 	if (coord < other.coord)
// 		return TriVector("0");

// 	if (length > other.length) {
// 		int cond = length - other.length;
// 		for (int i = 0; i < cond; ++i) {
// 			other.coord.insert(other.coord.begin(), TriSignal('0'));
// 			++other.length;
// 		}
// 	}

// 	return (*this) + ~other + TriVector(1, '1');
// }
// Нельзя использовать обычное вычитание через дополнительный код, пример:
// 001X - 000X = я хочу, чтобы было 00XX, 
// потому что X-X=неопределено, и ещё неопределено, нужно ли занимать из 1
// но через сложение с дополнительным кодом выйдет:
// 000X ->(invert) 111X ->(+1) XXXXX;  001X + XXXXX = XXXXX


TriVector TriVector::operator - (const TriVector& other) const
{
	if (length < other.length) {
		return TriVector("0");
	}

	TriVector result(length);
	int j = length - 1;
	for (int k = other.length - 1; k > -1; --j, --k) {
		result.coord[j] = coord[j] - other.coord[k];
	}

	return result;
}


TriVector& TriVector::operator ++()
{
	*this = *this + TriVector("1");
	return *this;
}


TriVector& TriVector::operator --()
{
	*this = *this - TriVector("1");
	return *this;
}


TriVector TriVector::operator ++(int)
{
	TriVector saved(*this);
	*this = *this + TriVector("1");

	return saved;
}


TriVector TriVector::operator --(int)
{
	TriVector saved(*this);
	*this = *this - TriVector("1");

	return saved;
}


TriVector& TriVector::operator = (const TriVector& other)
{
	if (this != &other) {
		coord = other.coord;
		length = other.length;
	}

	return *this;
}


TriVector& TriVector::operator = (TriVector&& other)
{
	if (this != &other) {
		coord = std::move(other.coord);
		length = other.length;
		other.length = 0;
	}

	return *this;
}


TriVector& TriVector::operator += (const TriVector& other)
{
	*this = *this + other;
	return *this;
}


TriVector& TriVector::operator -= (const TriVector& other)
{
	*this = *this - other;
	return *this;
}


TriSignal& TriVector::operator [] (const int& index)
{
	return coord[index];
}


const TriSignal& TriVector::operator [] (const int& index) const
{
	return coord[index];
}


TriVector::operator std::string() const
{
	return toString();
}


std::ostream& operator << (std::ostream& out, const TriVector& vector)
{
	const std::vector<TriSignal>& signals = vector.getVector();
	for (const TriSignal& signal : signals) {
		out << signal;
	}

	return out;
}


std::istream& operator >> (std::istream& in, TriVector& vector)
{
	std::string input;
	in >> input;

	vector.setVector(input);
	return in;
}


int TriVector::real_length() const noexcept
{
	int real = length;
	for (int i = 0; i < length; ++i) {
		if (coord[i].getState() == '0') {
			--real;
			continue;
		}
		break;
	}

	return real > 0 ? real : 1;
}


bool TriVector::isDefined() const noexcept
{
	return ! std::any_of(coord.begin(), coord.end(),
		[] (const TriSignal& signal) -> bool {
			return signal.state == 'X';
	});
}


std::string TriVector::toString() const
{
	std::ostringstream oss;
	for (const TriSignal& signal : coord) {
		oss << signal.chr();
	}
	return oss.str();
}


void TriVector::push_back(const TriSignal& signal)
{
	coord.push_back(signal);
	++length;
}


void TriVector::pop_back()
{
	if (length > 0) {
		coord.pop_back();
		--length;
	}
}


void TriVector::insert(const int& index, const TriSignal& signal)
{
	if (index < 0 || index >= length) {
		throw std::out_of_range("Insert index is out of range (0-length)");
	}
	coord.insert(coord.begin() + index, signal);
	++length;
}


void TriVector::erase(const int& index)
{
	if (index < 0 || index >= length) {
		throw std::out_of_range("Erase index is out of range (0-length)");
	}
	coord.erase(coord.begin() + index);
	--length;
}


void TriVector::clear()
{
	coord.clear();
	length = 0;
}


int TriVector::size() const noexcept
{
	return length;
}


void TriVector::resize(const int& size)
{
	coord.resize(size);
	length = size;
}
