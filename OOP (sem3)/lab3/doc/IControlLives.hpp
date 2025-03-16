#ifndef ICONTROLLIVES_HPP
#define ICONTROLLIVES_HPP

class Enemy;
class BuildAttack;

/**
 * @brief Interface for managing enemies' interactions with attacks and their health.
 * 
 * This interface is responsible for controlling the movement of enemies, applying damage from attacks,
 * and handling enemy deaths or removals when necessary.
 */
class IControlLives
{
public:
	/**
	 * @brief Move an enemy along its path.
	 * 
	 * This method should define the logic for advancing an enemy's position on the game map.
	 * 
	 * @param enemy A pointer to the enemy being moved.
	 * @return True if the enemy successfully moved, false if it can't be moved right now
	 * (e.g., it got stuck in traffic or strong slowness effect is aplied to it).
	 */
	virtual bool moveEnemy(Enemy* enemy) = 0;

	/**
	 * @brief Apply damage to the enemy.
	 * 
	 * This method should handle the process of applying damage from a `BuildAttack` to a specified enemy,
	 * including calculating effects and updating the enemy's health or status.
	 * 
	 * @param enemy A pointer to the enemy receiving damage.
	 * @param battack A pointer to the `BuildAttack` causing the damage.
	 */
	virtual void dealDamage(Enemy* enemy, BuildAttack* battack) = 0;

	/**
	 * @brief Remove an enemy from the game after death.
	 * 
	 * This method should handle all necessary cleanup and removal of an enemy when it is killed,
	 * including updating scores, releasing resources, or triggering effects.
	 * 
	 * @param enemy A pointer to the enemy being killed.
	 */
	virtual void killEnemy(Enemy* enemy) = 0;
};

#endif
