#ifndef SIMPLE_HPP
#define SIMPLE_HPP

#include <iostream>
#include <string>

class TriSignal
{
	friend class TriVector;

private:
	char state;

public:
	TriSignal() noexcept;
	explicit TriSignal(const char& state);
	TriSignal(const TriSignal& other) noexcept = default;

	void setState(const char& state);
	[[nodiscard]] char getState() const noexcept;

	void print(std::ostream& out) const noexcept;
	void fprint(const std::string& filename) const;


	[[nodiscard]] TriSignal operator || (const TriSignal& other) const noexcept;
	[[nodiscard]] TriSignal operator && (const TriSignal& other) const noexcept;
	[[nodiscard]] TriSignal operator ^ (const TriSignal& other) const noexcept;
	[[nodiscard]] TriSignal operator ! () const noexcept;

	[[nodiscard]] bool operator == (const TriSignal& other) const noexcept;
	[[nodiscard]] bool operator != (const TriSignal& other) const noexcept;
	[[nodiscard]] bool operator > (const TriSignal& other) const noexcept;
	[[nodiscard]] bool operator < (const TriSignal& other) const noexcept;
	[[nodiscard]] bool operator >= (const TriSignal& other) const noexcept;
	[[nodiscard]] bool operator <= (const TriSignal& other) const noexcept;

	[[nodiscard]] TriSignal operator + (const TriSignal& other) const noexcept;
	[[nodiscard]] TriSignal operator - (const TriSignal& other) const noexcept;
	[[maybe_unused]] TriSignal& operator ++() noexcept;
	[[maybe_unused]] TriSignal& operator --() noexcept;
	[[maybe_unused]] TriSignal operator ++(int) noexcept;
	[[maybe_unused]] TriSignal operator --(int) noexcept;

	[[maybe_unused]] TriSignal& operator = (const TriSignal& other) noexcept;
	[[maybe_unused]] TriSignal& operator += (const TriSignal& other) noexcept;
	[[maybe_unused]] TriSignal& operator -= (const TriSignal& other) noexcept;

	[[nodiscard]] char chr() const noexcept;
	[[nodiscard]] operator char() const noexcept;

	friend std::ostream& operator << (std::ostream& out, const TriSignal& signal);
	friend std::istream& operator >> (std::istream& in, TriSignal& signal);
};

#endif
