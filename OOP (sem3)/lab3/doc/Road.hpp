/**
 * @file Road.hpp
 * @brief Defines the Road class, which represents a road-type cell for enemies and traps.
 */

#ifndef ROAD_HPP
#define ROAD_HPP

#include "Cell.hpp"
#include "Enemy.hpp"
#include "MagicTrap.hpp"

/**
 * @class Road
 * @brief Represents a cell on the road where enemies can walk and traps can be placed.
 */
class Road : public Cell
{
private:
	Enemy* enemy; ///< Pointer to an enemy occupying this road cell (if any, nullptr otherwise).
	MagicTrap* mtrap; ///< Pointer to a magic trap placed on this road cell (if any, nullptr otherwise).
	Road* nextroad; ///< Pointer to the next road cell in the path (if any, nullptr for the last adjasent to the castle road).

public:
	/**
	 * @brief Constructs a road cell with specified coordinates.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 */
	Road(int x, int y);

	/**
	 * @brief Constructs a road cell with an enemy.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 * @param enemy Pointer to the enemy on this cell.
	 */
	Road(int x, int y, Enemy* enemy);

	/**
	 * @brief Constructs a road cell with a magic trap.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 * @param mtrap Pointer to the magic trap placed on this cell.
	 */
	Road(int x, int y, MagicTrap* mtrap);

	/**
	 * @brief Constructs a road cell with both an enemy and a magic trap.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 * @param enemy Pointer to the enemy on this cell.
	 * @param mtrap Pointer to the magic trap placed on this cell.
	 */
	Road(int x, int y, Enemy* enemy, MagicTrap* mtrap);

	/**
	 * @brief Destructor. Cleans up dynamic memory.
	 */
	~Road();

	/**
	 * @brief Gets the enemy on this cell.
	 * @return Pointer to the enemy on current road, or nullptr if none exists.
	 */
	Enemy* getEnemy() const;

	/**
	 * @brief Sets an enemy on this cell.
	 * @param enemy Pointer to the enemy to be placed.
	 */
	void setEnemy(Enemy* enemy);

	/**
	 * @brief Checks if the cell is empty of enemies.
	 * @return True if no enemy is present, false otherwise.
	 */
	bool isEmptyEnemy() const;

	/**
	 * @brief Gets the magic trap on this cell.
	 * @return Pointer to the magic trap on current road, or nullptr if none exists.
	 */
	MagicTrap* getMTrap() const;

	/**
	 * @brief Sets a magic trap on this cell.
	 * @param mtrap Pointer to the magic trap to be placed.
	 */
	void setMTrap(MagicTrap* mtrap);

	/**
	 * @brief Checks if the cell is empty of magic traps.
	 * @return True if no magic trap is present, false otherwise.
	 */
	bool isEmptyMTrap() const;

	/**
	 * @brief Gets the next road cell in the path to the castle.
	 * @return Pointer to the next road cell.
	 */
	Road* getNextRoad() const;

	/**
	 * @brief Sets the next road cell in the path to the castle.
	 * @param road Pointer to the next road cell.
	 */
	void setNextRoad(Road* road);
};

#endif
