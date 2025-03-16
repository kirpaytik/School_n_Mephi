/**
 * @file Field.hpp
 * @brief Defines the Field class, which represents a field-type cell for building towers or defenses.
 */

#ifndef FIELD_HPP
#define FIELD_HPP

#include "Cell.hpp"
#include "DefBuild.hpp"

/**
 * @class Field
 * @brief Represents a cell on the field where towers or defenses can be built.
 */
class Field : public Cell
{
private:
	DefBuild* defbuild; ///< Pointer to the defense or tower built on this field cell (if any, nullptr otherwise).

public:
	/**
	 * @brief Constructs a field cell with specified coordinates.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 */
	Field(int x, int y);

	/**
	 * @brief Constructs a field cell with a defense or tower.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 * @param defbuild Pointer to the defense or tower placed on this cell.
	 */
	Field(int x, int y, DefBuild* defbuild);

	/**
	 * @brief Destructor. Cleans up dynamic memory.
	 */
	~Field();

	/**
	 * @brief Gets the defense or tower on this cell.
	 * @return Pointer to the defense or tower, or nullptr if none exists.
	 */
	DefBuild* getBuild() const;

	/**
	 * @brief Sets a defense or tower on this cell.
	 * @param defbuild Pointer to the defense or tower to be placed.
	 */
	void setBuild(DefBuild* defbuild);

	/**
	 * @brief Checks if the cell is empty of defenses or towers.
	 * @return True if no defense or tower is present, false otherwise.
	 */
	bool isEmpty() const;
};

#endif
