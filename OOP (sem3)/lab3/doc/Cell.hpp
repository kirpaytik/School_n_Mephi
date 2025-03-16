/**
 * @file Cell.hpp
 * @brief Defines the Cell class, which represents a generic cell in the game grid.
 */

#ifndef CELL_HPP
#define CELL_HPP

/**
 * @class Cell
 * @brief Represents a basic cell in the game grid.
 */
class Cell
{
protected:
	int x; ///< The x-coordinate of the cell.
	int y; ///< The y-coordinate of the cell.

public:
	/**
	 * @brief Default constructor. Initializes the cell with default values.
	 */
	Cell();

	/**
	 * @brief Parameterized constructor. Initializes the cell with specified coordinates.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 */
	Cell(int x, int y);

	/**
	 * @brief Gets the x-coordinate of the cell.
	 * @return The x-coordinate.
	 */
	int getX() const;

	/**
	 * @brief Gets the y-coordinate of the cell.
	 * @return The y-coordinate.
	 */
	int getY() const;

	/**
	 * @brief Sets the x-coordinate of the cell.
	 * @param newx The new x-coordinate.
	 */
	void setX(int newx);

	/**
	 * @brief Sets the y-coordinate of the cell.
	 * @param newy The new y-coordinate.
	 */
	void setY(int newy);
};

#endif
