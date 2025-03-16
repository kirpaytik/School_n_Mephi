#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include "simple.hpp"
#include <vector>
#include <string>
#include <compare>


class TriVector
{
private:
	int length;
	std::vector<TriSignal> coord;

	bool checkPotential(const char& a, const char& b, int& potential) const noexcept;
	void calculateCarry(const TriSignal& a, const TriSignal& b, TriSignal& carry) const noexcept;

public:
	// constructors
	TriVector();
	explicit TriVector(const int& len);
	explicit TriVector(const int& len, const TriSignal& signal);
	explicit TriVector(const std::string& arr);
	explicit TriVector(const std::vector<TriSignal>& arr);

	TriVector(const TriVector& other);
	TriVector(TriVector&& other);

	// get-set, print
	[[maybe_unused]] TriVector& setVector(const std::string& arr);
	[[maybe_unused]] TriVector& setVector(const std::vector<TriSignal>& arr);
	[[maybe_unused]] TriVector& setSignal(const TriSignal& signal, const int& index);

	[[nodiscard]] int getLength() const noexcept;
	[[nodiscard]] std::vector<TriSignal> getVector() const noexcept;
	[[nodiscard]] TriSignal getSignal(const int& index) const;

	void print(std::ostream& out) const noexcept;
	void fprint(const std::string& filename) const;

	// other funcs
	[[nodiscard]] bool isDefined() const noexcept;
	[[nodiscard]] int real_length() const noexcept;
	[[nodiscard]] std::string toString() const;
	void push_back(const TriSignal& signal);
	void pop_back();
	void insert(const int& index, const TriSignal& signal);
	void erase(const int& index);
	void clear();
	[[nodiscard]] int size() const noexcept;
	void resize(const int& size);

	// operators
	[[nodiscard]] TriSignal& operator [] (const int& index);
	[[nodiscard]] const TriSignal& operator [] (const int& index) const;

	[[nodiscard]] TriVector operator | (const TriVector& other) const;
	[[nodiscard]] TriVector operator & (const TriVector& other) const;
	[[nodiscard]] TriVector operator ~ () const;

	[[nodiscard]] std::strong_ordering operator <=>(const TriVector& other) const noexcept;
	[[nodiscard]] bool operator == (const TriVector& other) const noexcept;
	[[nodiscard]] bool operator != (const TriVector& other) const noexcept;

	[[nodiscard]] TriVector operator + (const TriVector& other) const;
	[[nodiscard]] TriVector operator - (const TriVector& other) const;
	// [[nodiscard]] TriVector operator - (TriVector other) const;
	[[maybe_unused]] TriVector& operator ++();
	[[maybe_unused]] TriVector& operator --();
	[[maybe_unused]] TriVector operator ++(int);
	[[maybe_unused]] TriVector operator --(int);

	[[maybe_unused]] TriVector& operator = (const TriVector& other);
	[[maybe_unused]] TriVector& operator = (TriVector&& other);
	[[maybe_unused]] TriVector& operator += (const TriVector& other);
	[[maybe_unused]] TriVector& operator -= (const TriVector& other);

	[[nodiscard]] operator std::string() const;

	friend std::ostream& operator << (std::ostream& out, const TriVector& vector);
	friend std::istream& operator >> (std::istream& in, TriVector& vector);
};

#endif
