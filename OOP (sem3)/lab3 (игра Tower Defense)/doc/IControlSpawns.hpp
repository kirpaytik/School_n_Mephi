#ifndef ICONTROLSPAWNS_HPP
#define ICONTROLSPAWNS_HPP

class Enemy;

/**
 * @brief Interface for managing the spawning of enemies.
 * 
 * This interface defines methods for controlling the timing and creation of enemy units in the game.
 */
class IControlSpawns
{
public:
	/**
	 * @brief Process the spawning timer.
	 * 
	 * This method should be called periodically to update the timing logic for spawning new enemies.
	 * It ensures that enemies spawn at appropriate intervals.
	 */
	virtual void spawnTimeProcess() = 0;

	/**
	 * @brief Spawn a new enemy.
	 * 
	 * This method should create and return a new enemy instance when it is time to spawn one.
	 * 
	 * @return A pointer to the newly spawned enemy.
	 */
	virtual Enemy* spawnEnemy() = 0;
};

#endif
