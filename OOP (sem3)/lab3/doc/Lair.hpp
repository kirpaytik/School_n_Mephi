/**
 * @file Lair.hpp
 * @brief Defines the Lair class, which manages enemy spawns.
 */

#ifndef LAIR_HPP
#define LAIR_HPP

#include "Enemy.hpp"

#include "../interfaces/IControlSpawns.hpp"

#include <string>
#include <unordered_map>

/**
 * @enum EnemyType
 * @brief Represents the types of enemies that can be spawned.
 */
enum class EnemyType {
	NORMAL, ///< A standard enemy.
	FAST,   ///< A fast-moving enemy.
	TANK    ///< A heavily armored enemy.
};

/**
 * @struct EnemyParams
 * @brief Holds parameters for a specific enemy type.
 */
struct EnemyParams {
	int maxhealth; ///< The maximum health of the enemy.
	int speed; ///< The speed of the enemy.
	int gold; ///< The gold awarded for defeating the enemy.
};

/**
 * @class Lair
 * @brief Represents a lair that spawns enemies.
 */
class Lair : public IControlSpawns
{
private:
	std::string name; ///< The name of the lair.
	std::vector<std::pair<Enemy*, int>> enemies; ///< List of enemies and their spawn times.
	int maxenemies; ///< The maximum number of enemies the lair can hold.
	std::unordered_map<EnemyType, EnemyParams> enemyParams; ///< Parameters for each enemy type.

public:
	/**
	 * @brief Constructs a lair with a name and a list of enemies.
	 * @param name The name of the lair.
	 * @param enemies Vector of enemy pointers and their spawn times.
	 */
	Lair(const std::string& name, std::vector<std::pair<Enemy*, int>>& enemies);

	/**
	 * @brief Constructs a lair with a name and a list of enemy types.
	 * @param name The name of the lair.
	 * @param enemies Vector of enemy types and their spawn times.
	 */
	Lair(const std::string& name, const std::vector<std::pair<EnemyType, int>>& enemies);

	/**
	 * @brief Constructs a lair with a name and a maximum number of enemies.
	 * @param name The name of the lair.
	 * @param numEnemies The maximum number of enemies.
	 */
	Lair(const std::string& name, int numEnemies);

	/**
	 * @brief Generates an enemy of the specified type.
	 * @param type The type of enemy to generate.
	 * @return A pointer to the generated enemy.
	 */
	Enemy* generateEnemy(EnemyType type);

	/**
	 * @brief Destructor. Cleans up dynamic memory.
	 */
	~Lair();

	/**
	 * @brief Gets the name of the lair.
	 * @return The name of the lair.
	 */
	std::string getName() const;

	/**
	 * @brief Gets the next enemy to be spawned. nullptr if no enemies left to spawn.
	 * @return Pointer to the next enemy or nullptr.
	 */
	Enemy* getEnemy() const;

	/**
	 * @brief Gets the spawn time of the next enemy. -1 if no enemies left to spawn.
	 * @return The time until the next spawn or -1.
	 */
	int getSpawnTime() const;

	/**
	 * @brief Gets the number of enemies left to spawn.
	 * @return The number of enemies left.
	 */
	int getNumberOfEnemiesLeft() const;

	/**
	 * @brief Gets the maximum number of enemies allowed in the lair.
	 * @return The maximum number of enemies.
	 */
	int getMaxEnemies() const;

	/**
	 * @brief Converts a string to an EnemyType.
	 * @param type The string representing the enemy type.
	 * @return The corresponding EnemyType.
	 */
	static EnemyType stringToEnemyType(const std::string& type);

	/**
	 * @brief Processes the spawn timers of all enemies.
	 */
	void spawnTimeProcess() override;

	/**
	 * @brief Spawns the next enemy, if ready.
	 * @return Pointer to the spawned enemy, or nullptr if no enemy is ready.
	 */
	Enemy* spawnEnemy() override;
};

#endif
