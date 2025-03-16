#include "complex.hpp"

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <compare>
#include <sstream>

#include "simple.hpp"


TriVector::TriVector() noexcept: length(0), coord(nullptr) {}

TriVector::TriVector(const int& len)
{
	if (len < 0)
		throw std::invalid_argument("Length must be >0 !");

	coord = new TriSignal[len];
	length = len;
}

TriVector::TriVector(const int& len, const TriSignal& signal)
{
	if (len < 0)
		throw std::invalid_argument("Length must be >0 !");

	coord = new TriSignal[len];
	for (int i = 0; i < len; ++i) {
		coord[i] = signal;
	}
	length = len;
}

TriVector::TriVector(const std::string& arr)
{
	coord = new TriSignal[arr.size()];
	std::transform(arr.begin(), arr.end(), coord,
		[] (const char& c) -> TriSignal { return TriSignal(c); });
	length = arr.size();
}

TriVector::TriVector(const TriSignal* arr, const int& len)
{
	if (len < 0)
		throw std::invalid_argument("Length must be >0 !");
	if (!arr)
		throw std::invalid_argument("Null-ptr occured!");

	coord = new TriSignal[len];
	std::copy(arr, arr + len, coord);
	length = len;
}

TriVector::TriVector(const TriVector& other)
{
	coord = new TriSignal[other.length];
	std::copy(other.coord, other.coord + other.length, coord);
	length = other.length;
}

TriVector::TriVector(TriVector&& other) noexcept:
	length(other.length), coord(other.coord)
	{ other.coord = nullptr; other.length = 0; }


TriVector::~TriVector()
{
	delete[] coord;
	coord = nullptr;
	length = 0;
}


TriVector& TriVector::setVector(const std::string& arr)
{
	TriSignal* temp = new TriSignal[arr.size()];
	std::transform(arr.begin(), arr.end(), temp,
		[] (const char& c) -> TriSignal { return TriSignal(c); });
	clear();
	coord = temp;
	length = arr.size();

	return *this;
}


TriVector& TriVector::setVector(const TriSignal* arr, const int& len)
{
	if (len < 0)
		throw std::invalid_argument("Length must be >0 !");
	if (!arr)
		throw std::invalid_argument("Null-ptr occured!");

	TriSignal* temp = new TriSignal[len];
	std::copy(arr, arr + len, temp);
	clear();
	coord = temp;
	length = len;

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


TriSignal* TriVector::getVector() const noexcept
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
	for (int i = 0; i < length; ++i) {
		out << coord[i];
	}
	out << std::endl;
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

	return std::equal(coord, coord + length, other.coord);
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

	if (carry.state != '0') {
		result.insert(0, TriSignal(carry.state));
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
	int k = other.length - 1;
	for (int j = length - 1; j > -1; --j, --k) {
		if (k > -1)
			result.coord[j] = coord[j] - other.coord[k];
		else
			result.coord[j] = coord[j];
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
		TriSignal* temp = new TriSignal[other.length];
		std::copy(other.coord, other.coord + other.length, temp);
		clear();
		coord = temp;
		length = other.length;
	}

	return *this;
}


TriVector& TriVector::operator = (TriVector&& other)
{
	if (this != &other) {
		clear();
		coord = other.coord;
		length = other.length;
		other.coord = nullptr;
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
	if (index < 0 || index >= length)
		throw std::out_of_range("Index is out of range");
	return coord[index];
}


const TriSignal& TriVector::operator [] (const int& index) const
{
	if (index < 0 || index >= length)
		throw std::out_of_range("Index is out of range");
	return coord[index];
}


TriVector::operator std::string() const
{
	return toString();
}


std::ostream& operator << (std::ostream& out, const TriVector& vector)
{
	int length = vector.getLength();
	for (int i = 0; i < length; ++i) {
		out << vector.coord[i];
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
	return ! std::any_of(coord, coord + length,
		[] (const TriSignal& signal) -> bool {
			return signal.state == 'X';
	});
}


std::string TriVector::toString() const
{
	std::ostringstream oss;
	for (int i = 0; i < length; ++i) {
		oss << coord[i].chr();
	}
	return oss.str();
}


void TriVector::push_back(const TriSignal& signal)
{
	TriSignal* newCoord = new TriSignal[length + 1];
	std::copy(coord, coord + length, newCoord);
	delete[] coord;
	coord = newCoord;
	coord[length] = signal;
	++length;
}


void TriVector::pop_back()
{
	if (length > 0) {
		TriSignal* newCoord = new TriSignal[length - 1];
		std::copy(coord, coord + length - 1, newCoord);
		delete[] coord;
		coord = newCoord;
		--length;
	}
}


void TriVector::insert(const int& index, const TriSignal& signal)
{
	if (index < 0 || index >= length) {
		throw std::out_of_range("Insert index is out of range (0-length)");
	}
	TriSignal* newCoord = new TriSignal[length + 1];
	std::copy(coord, coord + index, newCoord);
	newCoord[index] = signal;
	std::copy(coord + index, coord + length, newCoord + index + 1);
	delete[] coord;
	coord = newCoord;
	++length;
}


void TriVector::erase(const int& index)
{
	if (index < 0 || index >= length) {
		throw std::out_of_range("Erase index is out of range (0-length)");
	}
	TriSignal* newCoord = new TriSignal[length - 1];
	std::copy(coord, coord + index, newCoord);
	std::copy(coord + index + 1, coord + length, newCoord + index);
	delete[] coord;
	coord = newCoord;
	--length;
}


void TriVector::clear()
{
	delete[] coord;
	coord = nullptr;
	length = 0;
}


int TriVector::size() const noexcept
{
	return length;
}


void TriVector::resize(const int& size)
{
	if (size < 0)
		throw std::invalid_argument("Size must be >0 !");

	TriSignal* newCoord = new TriSignal[size];
	int minlen = std::min(length, size);
	std::copy(coord, coord + minlen, newCoord);
	delete[] coord;

	if (size > minlen) {
		for (int i = minlen; i < size; ++i)
			newCoord[i] = TriSignal('0');
	}

	coord = newCoord;
	length = size;
}
