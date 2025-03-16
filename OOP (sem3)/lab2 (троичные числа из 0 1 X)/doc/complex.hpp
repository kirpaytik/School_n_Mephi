/**
 * @file Complex.hpp
 * @brief Header file for the TriVector class
 * 
 * This file defines the TriVector class, which represents a vector of TriSignal objects
 */

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include "simple.hpp"
#include <vector>
#include <string>
#include <compare>

/**
 * @class TriVector
 * @brief Class representing a vector of TriSignal objects
 * 
 * The TriVector class provides functionality for creating, managing, and manipulating
 * a vector of TriSignal objects, including arithmetic operations, accessors, and mutators
 */
class TriVector
{
private:
	int length;	///< Length of the vector
	TriSignal* coord;	///< Pointer to the array of TriSignal objects

	/**
	 * @brief Checks potential between two signals and updates the potential reference
	 * 
	 * Checks and updates potential for first of two compared vectors to be less or greater than 2nd one
	 * Used for spaceship operator
	 * 
	 * @param a First character representing TriSignal
	 * @param b Second character representing TriSignal
	 * @param potential Reference to an integer to store the potential
	 * @return true if theres still a potential to be greater or less,
	 * false if cant define which vector is greater
	 */
	bool checkPotential(const char& a, const char& b, int& potential) const noexcept;

	/**
	 * @brief Calculates the carry from two TriSignal objects
	 * 
	 * This method computes the carry resulting from the addition of two TriSignal objects
	 * and stores the result in the provided reference
	 * 
	 * @param a First TriSignal object
	 * @param b Second TriSignal object
	 * @param carry Reference to a TriSignal object to store the carry
	 */
	void calculateCarry(const TriSignal& a, const TriSignal& b, TriSignal& carry) const noexcept;

public:
	// Constructors

	/**
	 * @brief Default constructor for TriVector
	 * 
	 * Initializes an empty TriVector with no elements
	 * Length is set to 0 and coord is set to nullptr
	 */
	TriVector() noexcept;

	/**
	 * @brief Constructor for TriVector with specified length
	 * 
	 * Allocates a TriVector of a given length, initializing all elements to a default state
	 * 
	 * @param len Length of the vector
	 */
	explicit TriVector(const int& len);

	/**
	 * @brief Constructor for TriVector initialized with a TriSignal
	 * 
	 * Allocates a TriVector of a specified length, initializing all elements to the given TriSignal
	 * 
	 * @param len Length of the vector
	 * @param signal TriSignal object to initialize the vector
	 */
	explicit TriVector(const int& len, const TriSignal& signal);

	/**
	 * @brief Constructor for TriVector initialized with a string representation
	 * 
	 * Initializes the TriVector based on a string input that specifies the elements
	 * 
	 * @param arr String representation of the vector
	 */
	explicit TriVector(const std::string& arr);

	/**
	 * @brief Constructor for TriVector initialized with a pointer to TriSignal array
	 * 
	 * Initializes the TriVector copying an existing array of TriSignal objects
	 * 
	 * @param arr Pointer to an array of TriSignal objects
	 * @param len Length of the vector
	 */
	TriVector(const TriSignal* arr, const int& len);

	// Copy and Move Constructors
	/**
	 * @brief Copy constructor for TriVector
	 * 
	 * Creates a new TriVector as a copy of an existing TriVector
	 * 
	 * @param other The TriVector object to copy
	 */
	TriVector(const TriVector& other);

	/**
	 * @brief Move constructor for TriVector
	 * 
	 * Transfers ownership of resources from another TriVector to this one
	 * 
	 * @param other The TriVector object to move
	 */
	TriVector(TriVector&& other) noexcept;

	/**
	 * @brief Destructor for TriVector
	 * 
	 * Cleans up resources used by the TriVector
	 */
	~TriVector();

	// Getters, Setters, and Print Functions

	/**
	 * @brief Sets the vector using a string representation
	 * 
	 * Replaces the current contents of the vector with elements parsed from a string
	 * 
	 * @param arr String representation of the vector
	 * 
	 * @return Reference to this TriVector
	 */
	[[maybe_unused]] TriVector& setVector(const std::string& arr);

	/**
	 * @brief Sets the vector using a pointer to TriSignal array
	 * 
	 * Replaces the current contents of the vector copying elements from the specified array
	 * 
	 * @param arr Pointer to an array of TriSignal objects
	 * @param len Length of the vector
	 * 
	 * @return Reference to this TriVector
	 */
	[[maybe_unused]] TriVector& setVector(const TriSignal* arr, const int& len);

	/**
	 * @brief Sets a specific TriSignal in the vector
	 * 
	 * Updates the TriSignal at the specified index with the provided signal
	 * 
	 * @param signal TriSignal object to set
	 * @param index Index where the signal should be set
	 * 
	 * @return Reference to this TriVector
	 */
	[[maybe_unused]] TriVector& setSignal(const TriSignal& signal, const int& index);

	/**
	 * @brief Gets the length of the vector
	 * 
	 * @return Length of the vector
	 */
	[[nodiscard]] int getLength() const noexcept;

	/**
	 * @brief Gets the pointer to the vector of TriSignal objects
	 * 
	 * @return Pointer to the array of TriSignal objects
	 */
	[[nodiscard]] TriSignal* getVector() const noexcept;

	/**
	 * @brief Gets a specific TriSignal from the vector
	 * 
	 * @param index Index of the TriSignal to get
	 * @return The TriSignal at the specified index
	 */
	[[nodiscard]] TriSignal getSignal(const int& index) const;

	/**
	 * @brief Prints the vector to the specified output stream
	 * 
	 * @param out Output stream to print to
	 */
	void print(std::ostream& out) const noexcept;

	/**
	 * @brief Prints the vector to a file
	 * 
	 * @param filename Name of the file to print to
	 */
	void fprint(const std::string& filename) const;

	// Other Functions

	/**
	 * @brief Checks if the vector is defined (does not contain 'X' states)
	 * 
	 * This method returns true if the vector doesnt contain 'X' signals, and false if contains at least one 'X'
	 * 
	 * @return true if the vector is defined, false otherwise
	 */
	[[nodiscard]] bool isDefined() const noexcept;

	/**
	 * @brief      Gets the real length of vector without leading zeros
	 *
	 * @return     length of vector without zeros at its beginning
	 */
	[[nodiscard]] int real_length() const noexcept;

	/**
	 * @brief Converts the vector to a string representation
	 * 
	 * This method generates a string that represents the contents of the vector
	 * 
	 * @return String representation of the vector
	 */
	[[nodiscard]] std::string toString() const;

	/**
	 * @brief Adds a TriSignal to the end of the vector
	 * 
	 * This method appends the specified TriSignal to the end of the vector
	 * and increases the length
	 * 
	 * @param signal TriSignal object to add
	 */
	void push_back(const TriSignal& signal);

	/**
	 * @brief Removes the last TriSignal from the vector
	 * 
	 * This method removes the last element from the vector, reducing its size by one
	 */
	void pop_back();

	/**
	 * @brief Inserts a TriSignal at a specific index in the vector
	 * 
	 * This method inserts the specified TriSignal at the given index,
	 * shifting subsequent elements and increases the length
	 * 
	 * @param index Index at which to insert the signal
	 * @param signal TriSignal object to insert
	 */
	void insert(const int& index, const TriSignal& signal);

	/**
	 * @brief Erases a TriSignal at a specific index
	 * 
	 * This method removes the TriSignal at the specified index,
	 * shifting subsequent elements and decreases the length
	 * 
	 * @param index Index of the TriSignal to erase
	 */
	void erase(const int& index);

	/**
	 * @brief Clears all elements from the vector
	 * 
	 * This method removes all elements from the vector, leaving it empty
	 */
	void clear();

	/**
	 * @brief Gets the current size of the vector
	 * 
	 * This method returns the number of elements currently stored in the vector
	 * 
	 * @return Number of elements in the vector
	 */
	[[nodiscard]] int size() const noexcept;

	/**
	 * @brief Resizes the vector to a new size
	 * 
	 * This method changes the size of the vector to the specified size. If the new size is larger,
	 * new elements are initialized to a default state. If smaller, elements are removed
	 * Also updates the length to the new size
	 * 
	 * @param size New size of the vector
	 */
	void resize(const int& size);

	// Operators

	/**
	 * @brief Accesses a TriSignal at a specified index
	 * 
	 * This operator allows access to the TriSignal at the specified index
	 * 
	 * @param index Index of the TriSignal to access
	 * @return reference to the TriSignal at the specified index
	 */
	[[nodiscard]] TriSignal& operator [] (const int& index);

	/**
	 * @brief Accesses a TriSignal at a specified index (const)
	 * 
	 * This operator allows read-only access to the TriSignal at the specified index
	 * 
	 * @param index Index of the TriSignal to access
	 * @return const reference to the TriSignal at the specified index
	 */
	[[nodiscard]] const TriSignal& operator [] (const int& index) const;

	/**
	 * @brief Performs the logical OR operation with another TriVector
	 * 
	 * This operator combines the current TriVector with another using the logical OR operation
	 * 
	 * @param other The other TriVector to combine
	 * @return A new TriVector resulting from the OR operation
	 */
	[[nodiscard]] TriVector operator | (const TriVector& other) const;

	/**
	 * @brief Performs the logical AND operation with another TriVector
	 * 
	 * This operator combines the current TriVector with another using the logical AND operation
	 * 
	 * @param other The other TriVector to combine
	 * @return A new TriVector resulting from the AND operation
	 */
	[[nodiscard]] TriVector operator & (const TriVector& other) const;

	/**
	 * @brief Performs the logical NOT operation on the TriVector
	 * 
	 * This operator negates the current TriVector, producing a new TriVector
	 * 
	 * @return A new TriVector resulting from the NOT operation
	 */
	[[nodiscard]] TriVector operator ~ () const;

	/**
	 * @brief Compares this TriVector with another for ordering
	 * 
	 * This operator provides a strong ordering comparison between two TriVectors
	 * If its impossible to arrange two TriVectors in order (due to undefined states 'X')
	 * then they are considered equal
	 * 
	 * @param other The other TriVector to compare
	 * @return Strong ordering result
	 */
	[[nodiscard]] std::strong_ordering operator <=>(const TriVector& other) const noexcept;

	/**
	 * @brief      Equality operator
	 *
	 * @param  other  The other vector to compare with
	 *
	 * @return     The result of the equality of two vectors
	 */
	[[nodiscard]] bool operator == (const TriVector& other) const noexcept;

	/**
	 * @brief      Inequality operator
	 *
	 * @param  other  The other to compare with
	 *
	 * @return     The result of the inequality of two vectors
	 */
	[[nodiscard]] bool operator != (const TriVector& other) const noexcept;

	/**
	 * @brief Adds another TriVector to this one
	 * 
	 * This operator adds the specified TriVector to the current one using binary addition logic,
	 * producing a new TriVector. Addition is not associative
	 * 
	 * @param other The other TriVector to add
	 * @return A new TriVector resulting from the addition
	 */
	[[nodiscard]] TriVector operator + (const TriVector& other) const;

	/**
	 * @brief Subtracts another TriVector from this one
	 * 
	 * This operator subtracts the specified TriVector from the current one elementwise,
	 * producing a new TriVector
	 * 
	 * @param other The other TriVector to subtract
	 * @return A new TriVector resulting from the subtraction
	 */
	[[nodiscard]] TriVector operator - (const TriVector& other) const;

	/**
	 * @brief Pre-increment operator for the TriVector
	 * 
	 * This operator increments the current TriVector and returns a reference to it
	 * 
	 * @return Reference to the incremented TriVector
	 */
	[[maybe_unused]] TriVector& operator ++();

	/**
	 * @brief Pre-decrement operator for the TriVector
	 * 
	 * This operator decrements the current TriVector and returns a reference to it
	 * 
	 * @return Reference to the decremented TriVector
	 */
	[[maybe_unused]] TriVector& operator --();

	/**
	 * @brief Post-increment operator for the TriVector
	 * 
	 * This operator increments the current TriVector and returns a copy of the original one
	 * 
	 * @return A copy of the TriVector before increment
	 */
	[[maybe_unused]] TriVector operator ++(int);

	/**
	 * @brief Post-decrement operator for the TriVector
	 * 
	 * This operator decrements the current TriVector and returns a copy of the original one
	 * 
	 * @return A copy of the TriVector before decrement
	 */
	[[maybe_unused]] TriVector operator --(int);

	/**
	 * @brief Copy assignment operator for the TriVector
	 * 
	 * This operator assigns the contents of another TriVector to this one
	 * 
	 * @param other The TriVector to copy from
	 * @return Reference to this TriVector
	 */
	[[maybe_unused]] TriVector& operator = (const TriVector& other);

	/**
	 * @brief Move assignment operator for the TriVector
	 * 
	 * This operator transfers ownership of resources from another TriVector to this one
	 * 
	 * @param other The TriVector to move from
	 * @return Reference to this TriVector
	 */
	[[maybe_unused]] TriVector& operator = (TriVector&& other);

	/**
	 * @brief Adds another TriVector to this one using the += operator
	 * 
	 * This operator adds the specified TriVector to the current one and updates it
	 * 
	 * @param other The TriVector to add
	 * @return Reference to this updated TriVector
	 */
	[[maybe_unused]] TriVector& operator += (const TriVector& other);

	/**
	 * @brief Subtracts another TriVector from this one using the -= operator
	 * 
	 * This operator subtracts the specified TriVector from the current one and updates it
	 * 
	 * @param other The TriVector to subtract
	 * @return Reference to this updated TriVector
	 */
	[[maybe_unused]] TriVector& operator -= (const TriVector& other);

	/**
	 * @brief Converts the TriVector to a string representation
	 * 
	 * This conversion operator allows the TriVector to be used as a string
	 * 
	 * @return String representation of the TriVector
	 */
	[[nodiscard]] operator std::string() const;

	/**
	 * @brief Overloaded output stream operator for TriVector
	 * 
	 * This function allows the TriVector to be printed to an output stream
	 * 
	 * @param out Output stream to print to
	 * @param vector The TriVector to print
	 * @return Reference to the output stream after printing
	 */
	friend std::ostream& operator << (std::ostream& out, const TriVector& vector);

	/**
	 * @brief Overloaded input stream operator for TriVector
	 * 
	 * This function allows the TriVector to be read from an input stream
	 * 
	 * @param in Input stream to read from
	 * @param vector The TriVector to populate
	 * @return Reference to the input stream after inputting
	 */
	friend std::istream& operator >> (std::istream& in, TriVector& vector);
};

#endif
