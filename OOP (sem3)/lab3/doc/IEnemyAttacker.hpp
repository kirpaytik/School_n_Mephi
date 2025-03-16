#ifndef IENEMYATTACKER_HPP
#define IENEMYATTACKER_HPP

/**
 * @brief Interface for objects that can attack enemies.
 * 
 * Classes implementing this interface must define the attack logic
 * and return the amount of damage to be dealt to the enemy.
 */
class IEnemyAttacker
{
public:
	/**
	 * @brief Perform an attack on an enemy.
	 *
	 * @return The amount of damage to be dealt to the enemy.
	 */
	virtual int attack() const = 0;
};

#endif
