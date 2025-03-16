/**
 * @file Landscape.hpp
 * @brief Defines the Landscape class, representing the game map, including its castle, lairs, fields, roads, and entities.
 */

#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP

#include "Castle.hpp"
#include "Lair.hpp"
#include "Road.hpp"
#include "Field.hpp"
#include "Enemy.hpp"
#include "DefBuild.hpp"
#include "BuildAttack.hpp"

#include "../interfaces/IControlSpawns.hpp"
#include "../interfaces/IControlLives.hpp"
#include "../interfaces/IControlBuildAttacks.hpp"

#include <tuple>
#include <vector>

/**
 * @class Landscape
 * @brief Represents the game map and manages its components, such as the castle, lairs, fields, and roads.
 */
class Landscape : public IControlSpawns, public IControlLives, public IControlBuildAttacks
{
private:
	int width; ///< Width of the map.
	int height; ///< Height of the map.
	std::tuple<Castle*, int, int> castle; ///< The castle on the map and its coordinates.
	std::vector<std::tuple<Lair*, int, int>> lairs; ///< List of lairs and their coordinates.
	std::vector<Field*> fields; ///< List of fields on the map.
	std::vector<Road*> roads; ///< List of roads on the map.

public:
	/**
	 * @brief Default constructor. Initializes an empty map.
	 */
	Landscape();

	/**
	 * @brief Constructs a Landscape with specified parameters.
	 * @param width Width of the map.
	 * @param height Height of the map.
	 * @param castle The castle and its coordinates.
	 * @param lairs List of lairs and their coordinates.
	 * @param fields List of fields on the map.
	 * @param roads List of roads on the map.
	 */
	Landscape(int width, int height, std::tuple<Castle*, int, int> castle,
		std::vector<std::tuple<Lair*, int, int>> lairs, std::vector<Field*> fields, std::vector<Road*> roads);

	/**
	 * @brief Destructor. Cleans up dynamically allocated components.
	 */
	~Landscape();

	/**
	 * @brief Gets the width of the map.
	 * @return The map width.
	 */
	int getWidth() const;

	/**
	 * @brief Gets the height of the map.
	 * @return The map height.
	 */
	int getHeight() const;

	/**
	 * @brief Retrieves the castle object.
	 * @return A pointer to the castle.
	 */
	Castle* getCastle() const;

	/**
	 * @brief Gets the X coordinate of the castle.
	 * @return The X coordinate of the castle.
	 */
	int getCastleX() const;

	/**
	 * @brief Gets the Y coordinate of the castle.
	 * @return The Y coordinate of the castle.
	 */
	int getCastleY() const;

	/**
	 * @brief Retrieves a specific lair by its index.
	 * @param indx The index of the lair.
	 * @return A pointer to the lair.
	 */
	Lair* getLair(int indx) const;

	/**
	 * @brief Retrieves all lairs and their coordinates.
	 * @return A vector of tuples containing lairs and their coordinates.
	 */
	std::vector<std::tuple<Lair*, int, int>> getLairs() const;

	/**
	 * @brief Checks if there are any enemies left on the map.
	 * @return True if there are enemies left, false otherwise.
	 */
	bool areEnemiesLeft() const;

	/**
	 * @brief Retrieves all fields on the map.
	 * @return A vector of Field pointers.
	 */
	std::vector<Field*> getFields() const;

	/**
	 * @brief Retrieves all roads on the map.
	 * @return A vector of Road pointers.
	 */
	std::vector<Road*> getRoads() const;

	/**
	 * @brief Retrieves a field by its index.
	 * @param indx The index of the field.
	 * @return A pointer to the field.
	 */
	Field* getField(int indx) const;

	/**
	 * @brief Retrieves a field by its coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return A pointer to the field.
	 */
	Field* getField(int x, int y) const;

	/**
	 * @brief Retrieves the field containing a specific defensive building.
	 * @param defbuild A pointer to the defensive building.
	 * @return A pointer to the field containing the building.
	 */
	Field* getField(const DefBuild* defbuild) const;

	/**
	 * @brief Retrieves a road by its index.
	 * @param indx The index of the road.
	 * @return A pointer to the road.
	 */
	Road* getRoad(int indx) const;

	/**
	 * @brief Retrieves a road by its coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return A pointer to the road.
	 */
	Road* getRoad(int x, int y) const;

	/**
	 * @brief Retrieves an empty road near a specific lair.
	 * @param lairTuple The lair and its coordinates.
	 * @return A pointer to an empty road.
	 */
	Road* getEmptyRoad(std::tuple<Lair*, int, int> lairTuple) const;

	/**
	 * @brief Retrieves the road containing a specific enemy.
	 * @param enemy A pointer to the enemy.
	 * @return A pointer to the road containing the enemy.
	 */
	Road* getRoad(const Enemy* enemy) const;

	/**
	 * @brief Retrieves the road containing a specific magic trap.
	 * @param mtrap A pointer to the magic trap.
	 * @return A pointer to the road containing the magic trap.
	 */
	Road* getRoad(const MagicTrap* mtrap) const;

	/**
	 * @brief Retrieves the defensive building at specific coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return A pointer to the defensive building at the given coordinates, or nullptr if none exists.
	 */
	DefBuild* getBuild(int x, int y) const;

	/**
	 * @brief Processes the spawning of enemies over time.
	 * @note Overrides IControlSpawns::spawnTimeProcess.
	 */
	void spawnTimeProcess() override;

	/**
	 * @brief Spawns an enemy at a random lair.
	 * @note Overrides IControlSpawns::spawnEnemy.
	 * @return A pointer to the spawned enemy.
	 */
	Enemy* spawnEnemy() override;

	/**
	 * @brief Spawns an enemy at a specific lair.
	 * @param lairTuple The lair and its coordinates.
	 */
	void spawnEnemyAtLair(std::tuple<Lair*, int, int> lairTuple);

	/**
	 * @brief Moves an enemy along its path.
	 * @note Overrides IControlLives::moveEnemy.
	 * @param enemy A pointer to the enemy.
	 * @return True if the enemy successfully moves, false if it reaches the castle.
	 */
	bool moveEnemy(Enemy* enemy) override;

	/**
	 * @brief Applies damage to an enemy from a defensive building's attack.
	 * @note Overrides IControlLives::dealDamage.
	 * @param enemy A pointer to the enemy.
	 * @param battack A pointer to the attack.
	 */
	void dealDamage(Enemy* enemy, BuildAttack* battack) override;

	/**
	 * @brief Kills an enemy and removes it from the game.
	 * @note Overrides IControlLives::killEnemy.
	 * @param enemy A pointer to the enemy to kill.
	 */
	void killEnemy(Enemy* enemy) override;

	/**
	 * @brief Checks if an enemy has reached the castle.
	 * @param enemy A pointer to the enemy.
	 * @return True if the enemy reaches the castle, false otherwise.
	 */
	bool isCastleReached(Enemy* enemy) const;

	/**
	 * @brief Initiates an attack from a defensive building.
	 * @note Overrides IControlBuildAttacks::attack.
	 * @param defbuild A pointer to the defensive building initiating the attack.
	 */
	void attack(DefBuild* defbuild) override;

	/**
	 * @brief Selects a target for a defensive building to attack based on its strategy.
	 * @note Overrides IControlBuildAttacks::attack_strategy.
	 * @param defbuild A pointer to the defensive building.
	 * @return A pointer to the selected enemy.
	 */
	Enemy* attack_strategy(DefBuild* defbuild) const override;

	/**
	 * @brief Updates the readiness of all defensive buildings.
	 * @note Overrides IControlBuildAttacks::processBuildsReadiness.
	 */
	void processBuildsReadiness() override;

	/**
	 * @brief Finds the enemy nearest to a defensive building.
	 * @param defbuild A pointer to the defensive building.
	 * @return A pointer to the nearest enemy.
	 */
	Enemy* attack_nearest_to_tower(DefBuild* defbuild) const;

	/**
	 * @brief Finds the enemy furthest from a defensive building.
	 * @param defbuild A pointer to the defensive building.
	 * @return A pointer to the furthest enemy.
	 */
	Enemy* attack_furthest_from_tower(DefBuild* defbuild) const;

	/**
	 * @brief Finds the enemy nearest to the castle.
	 * @param defbuild A pointer to the defensive building.
	 * @return A pointer to the nearest enemy to the castle.
	 */
	Enemy* attack_nearest_to_castle(DefBuild* defbuild) const;

	/**
	 * @brief Finds the enemy with the lowest HP.
	 * @param defbuild A pointer to the defensive building.
	 * @return A pointer to the enemy with the lowest HP.
	 */
	Enemy* attack_lowest_hp(DefBuild* defbuild) const;

	/**
	 * @brief Finds the enemy with the highest HP.
	 * @param defbuild A pointer to the defensive building.
	 * @return A pointer to the enemy with the highest HP.
	 */
	Enemy* attack_highest_hp(DefBuild* defbuild) const;

	/**
	 * @brief Calculates the distance between two points.
	 * @param x1 The X coordinate of the first point.
	 * @param y1 The Y coordinate of the first point.
	 * @param x2 The X coordinate of the second point.
	 * @param y2 The Y coordinate of the second point.
	 * @return The Euclidean distance between the two points.
	 */
	static float calculateDistance(int x1, int y1, int x2, int y2);
};

#endif
