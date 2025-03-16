/**
 * @file Simple.hpp
 * @brief Header file for the TriSignal class
 * This file defines the TriSignal class, which represents a tri-state signal
 */

#ifndef SIMPLE_HPP
#define SIMPLE_HPP

#include <iostream>
#include <string>

/**
 * @class TriSignal
 * @brief Represents a tri-state signal
 *
 * The TriSignal class encapsulates a char element that can hold one of three states
 * and some functions to manipulate this char
 */
class TriSignal
{
	friend class TriVector; ///< Allows TriVector to access private members

private:
	char state; ///< The state of the TriSignal

public:
	/**
	 * @brief Default constructor
	 * Initializes the TriSignal to a default state of '0'
	 */
	TriSignal() noexcept;

	/**
	 * @brief Parameterized constructor
	 * If state is not '0', '1' or 'X' then '0' will be set
	 * 
	 * @param state The initial state of the TriSignal
	 * 
	 * @throw std::cerr State is incorrect.
	 * Does not throw an exception and write a message in std::cerr instead
	 */
	explicit TriSignal(const char& state);

	/**
	 * @brief Copy constructor
	 * Initializes a new TriSignal as a copy of another TriSignal
	 * 
	 * @param other The TriSignal to copy from
	 */
	TriSignal(const TriSignal& other) noexcept = default;

	/**
	 * @brief Sets the state of the TriSignal
	 * 
	 * @param state The new state to set
	 * 
	 * @throw std::invalid_argument If the state is incorrect
	 */
	void setState(const char& state);

	/**
	 * @brief Gets the current state of the TriSignal
	 * 
	 * @return The current state as a character
	 */
	[[nodiscard]] char getState() const noexcept;

	/**
	 * @brief Prints the TriSignal to an output stream
	 * 
	 * @param out The output stream to print to
	 */
	void print(std::ostream& out) const noexcept;

	/**
	 * @brief Prints the TriSignal to a file
	 * 
	 * @param filename The name of the file to print to
	 * 
	 * @throw std::ios_base::failure If file was not open
	 */
	void fprint(const std::string& filename) const;

	// Logical operators
	/**
	 * @brief Logical OR operator
	 * 
	 * @param other The other TriSignal to perform OR operation with
	 * @return A new TriSignal representing the result of the OR operation
	 */
	[[nodiscard]] TriSignal operator || (const TriSignal& other) const noexcept;

	/**
	 * @brief Logical AND operator
	 * 
	 * @param other The other TriSignal to perform AND operation with
	 * @return A new TriSignal representing the result of the AND operation
	 */
	[[nodiscard]] TriSignal operator && (const TriSignal& other) const noexcept;

	/**
	 * @brief Logical XOR operator
	 * 
	 * @param other The other TriSignal to perform XOR operation with
	 * @return A new TriSignal representing the result of the XOR operation
	 */
	[[nodiscard]] TriSignal operator ^ (const TriSignal& other) const noexcept;

	/**
	 * @brief Logical NOT operator
	 * 
	 * @return A new TriSignal representing the negation of the current signal
	 */
	[[nodiscard]] TriSignal operator ! () const noexcept;

	// Comparison operators
	/**
	 * @brief Equality operator
	 * 
	 * @param other The other TriSignal to compare with
	 * @return boolean value: true if both TriSignals are equal; otherwise false
	 */
	[[nodiscard]] bool operator == (const TriSignal& other) const noexcept;

	/**
	 * @brief Inequality operator
	 * 
	 * @param other The other TriSignal to compare with
	 * @return boolean value: true if both TriSignals are not equal; otherwise false
	 */
	[[nodiscard]] bool operator != (const TriSignal& other) const noexcept;

	/**
	 * @brief Greater than operator
	 * 
	 * @param other The other TriSignal to compare with
	 * @return boolean value: true if the current TriSignal is greater; otherwise false
	 */
	[[nodiscard]] bool operator > (const TriSignal& other) const noexcept;

	/**
	 * @brief Less than operator
	 * 
	 * @param other The other TriSignal to compare with
	 * @return true if the current TriSignal is less; otherwise false
	 */
	[[nodiscard]] bool operator < (const TriSignal& other) const noexcept;

	/**
	 * @brief Greater than or equal to operator
	 * 
	 * @param other The other TriSignal to compare with
	 * @return boolean value: true if the current TriSignal is greater than or equal; otherwise false
	 */
	[[nodiscard]] bool operator >= (const TriSignal& other) const noexcept;

	/**
	 * @brief Less than or equal to operator
	 * 
	 * @param other The other TriSignal to compare with
	 * @return boolean value: true if the current TriSignal is less than or equal; otherwise false
	 */
	[[nodiscard]] bool operator <= (const TriSignal& other) const noexcept;

	// Arithmetic operators
	/**
	 * @brief Addition operator
	 * 
	 * @param other The TriSignal to add
	 * @return A new TriSignal representing the result of the addition
	 */
	[[nodiscard]] TriSignal operator + (const TriSignal& other) const noexcept;

	/**
	 * @brief Subtraction operator
	 * 
	 * @param other The TriSignal to subtract
	 * @return A new TriSignal representing the result of the subtraction
	 */
	[[nodiscard]] TriSignal operator - (const TriSignal& other) const noexcept;

	/**
	 * @brief Prefix increment operator
	 * 
	 * @return A reference to the incremented TriSignal
	 */
	TriSignal& operator ++() noexcept;

	/**
	 * @brief Prefix decrement operator
	 * 
	 * @return A reference to the decremented TriSignal
	 */
	TriSignal& operator --() noexcept;

	/**
	 * @brief Postfix increment operator
	 * 
	 * @param unused An unused integer parameter to distinguish from prefix increment
	 * @return The TriSignal before increment
	 */
	TriSignal operator ++(int) noexcept;

	/**
	 * @brief Postfix decrement operator
	 * 
	 * @param unused An unused integer parameter to distinguish from prefix decrement
	 * @return The TriSignal before decrement
	 */
	TriSignal operator --(int) noexcept;

	/**
	 * @brief Assignment operator
	 * 
	 * @param other The TriSignal to assign from
	 * @return A reference to this TriSignal
	 */
	TriSignal& operator = (const TriSignal& other) noexcept;

	/**
	 * @brief Addition assignment operator
	 * 
	 * @param other The TriSignal to add
	 * @return A reference to this TriSignal after addition
	 */
	TriSignal& operator += (const TriSignal& other) noexcept;

	/**
	 * @brief Subtraction assignment operator
	 * 
	 * @param other The TriSignal to subtract
	 * @return A reference to this TriSignal after subtraction
	 */
	TriSignal& operator -= (const TriSignal& other) noexcept;

	/**
	 * @brief Converts the TriSignal to a character representation
	 * 
	 * @return The character representation of the TriSignal
	 */
	[[nodiscard]] char chr() const noexcept;

	/**
	 * @brief Implicit conversion to char
	 * 
	 * @return The state of the TriSignal as a character
	 */
	operator char() const noexcept;

	// Friend functions for input/output
	/**
	 * @brief Overloaded output stream operator
	 * 
	 * @param out The output stream
	 * @param signal The TriSignal to output
	 * @return A reference to the output stream
	 */
	friend std::ostream& operator << (std::ostream& out, const TriSignal& signal);

	/**
	 * @brief Overloaded input stream operator
	 * 
	 * @param in The input stream
	 * @param signal The TriSignal to input
	 * @return A reference to the input stream
	 * 
	 * @throw std::invalid_argument If input state is incorrect (not '0', '1' or 'X')
	 */
	friend std::istream& operator >> (std::istream& in, TriSignal& signal);
};

#endif
