/**
 * @file Castle.hpp
 * @brief Defines the Castle class, which represents the player's castle.
 */

#ifndef CASTLE_HPP
#define CASTLE_HPP

#include "../interfaces/IDamagable.hpp"

#include <string>

/**
 * @class Castle
 * @brief Represents the player's castle, which can take damage and manage resources like gold.
 */
class Castle : public IDamagable
{
private:
	std::string name; ///< The name of the castle.
	int maxhealth; ///< The maximum health of the castle.
	int currhealth; ///< The current health of the castle.
	int gold; ///< The amount of gold the castle has.

public:
	/**
	 * @brief Constructs a castle with a name and maximum health.
	 * @param name The name of the castle.
	 * @param maxhealth The maximum health of the castle.
	 */
	Castle(const std::string& name, int maxhealth);

	/**
	 * @brief Constructs a castle with a name, maximum health, and initial gold.
	 * @param name The name of the castle.
	 * @param maxhealth The maximum health of the castle.
	 * @param gold The initial amount of gold.
	 */
	Castle(const std::string& name, int maxhealth, int gold);

	/**
	 * @brief Gets the name of the castle.
	 * @return The name of the castle.
	 */
	std::string getName() const;

	/**
	 * @brief Gets the maximum health of the castle.
	 * @return The maximum health.
	 */
	int getMaxHealth() const;

	/**
	 * @brief Gets the current health of the castle.
	 * @return The current health.
	 */
	int getCurrentHealth() const;

	/**
	 * @brief Gets the current amount of gold.
	 * @return The amount of gold.
	 */
	int getGold() const;

	/**
	 * @brief Adds a specified amount of gold to the castle's resources.
	 * @param amount The amount of gold to add.
	 */
	void addGold(int amount);

	/**
	 * @brief Reduces the castle's gold by a specified amount.
	 * @param amount The amount of gold to deduct.
	 */
	void reduceGold(int amount);

	/**
	 * @brief Calculates the actual damage taken by the castle.
	 * @param damage The amount of damage dealt.
	 * @return The amount of damage effectively taken.
	 */
	int damageTaken(int damage) const override;

	/**
	 * @brief Sets the castle's health to a specific value.
	 * @param health The new health value.
	 */
	void setHealth(int health) override;

	/**
	 * @brief Checks if the castle is still alive.
	 * @return True if the castle is alive, false otherwise.
	 */
	bool isAlive() const override;
};

#endif
