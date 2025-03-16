/**
 * @file Enemy.hpp
 * @brief Defines the Enemy class, which represents an enemy entity in the game.
 */

#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "EffectAttack.hpp"

#include "../interfaces/IMovable.hpp"
#include "../interfaces/IDamagable.hpp"
#include "../interfaces/IEffectProcessor.hpp"
#include "../interfaces/IEnemyAttacker.hpp"

#include <vector>

/**
 * @enum EnemyType
 * @brief Represents different types of enemies.
 */
enum class EnemyType {
	NORMAL, ///< Standard enemy type.
	FAST,   ///< Fast-moving enemy type.
	TANK    ///< Heavily armored enemy type.
};

/**
 * @class Enemy
 * @brief Represents an enemy entity with health, speed, gold, and effects applied to it.
 */
class Enemy : public IMovable, public IDamagable, public IEffectProcessor, public IEnemyAttacker
{
private:
	EnemyType type; ///< Type of the enemy.
	int maxhealth; ///< Maximum health of the enemy.
	int currhealth; ///< Current health of the enemy.
	int speed; ///< Movement speed of the enemy.
	int gold; ///< Gold reward for defeating the enemy.
	std::vector<EffectAttack*> effects; ///< List of effects currently applied to the enemy.

public:
	/**
	 * @brief Constructs an enemy with specified attributes.
	 * @param health Maximum health of the enemy.
	 * @param speed Movement speed of the enemy.
	 * @param gold Gold reward for defeating the enemy.
	 * @param type The type of the enemy.
	 */
	Enemy(int health, int speed, int gold, EnemyType type);

	/**
	 * @brief Destructor. Cleans up dynamically allocated effects.
	 */
	~Enemy();

	/**
	 * @brief Gets the maximum health of the enemy.
	 * @return The maximum health value.
	 */
	int getMaxHealth() const;

	/**
	 * @brief Sets the maximum health of the enemy.
	 * @param health The new maximum health value.
	 */
	void setMaxHealth(int health);

	/**
	 * @brief Gets the current health of the enemy.
	 * @return The current health value.
	 */
	int getHealth() const;

	/**
	 * @brief Gets the movement speed of the enemy.
	 * @return The movement speed value.
	 */
	int getSpeed() const;

	/**
	 * @brief Sets the movement speed of the enemy.
	 * @param speed The new movement speed value.
	 */
	void setSpeed(int speed);

	/**
	 * @brief Gets the amount of gold the enemy drops upon defeat.
	 * @return The gold reward value.
	 */
	int getGold() const;

	/**
	 * @brief Sets the amount of gold the enemy drops upon defeat.
	 * @param gold The new gold reward value.
	 */
	void setGold(int gold);

	/**
	 * @brief Retrieves all effects currently applied to the enemy.
	 * @return A vector of pointers to EffectAttack objects.
	 */
	std::vector<EffectAttack*> getEffects() const;

	/**
	 * @brief Checks if the enemy has a specific effect type applied.
	 * @param type The effect type to check for.
	 * @return True if the effect is applied, false otherwise.
	 */
	bool hasEffect(EffectType type) const;

	/**
	 * @brief Gets the type of the enemy.
	 * @return The EnemyType of the enemy.
	 */
	EnemyType getType() const;

	/**
	 * @brief Calculates the distance current enemy can travel.
	 * @return The distance moved by the enemy.
	 */
	int move() const override;

	/**
	 * @brief Calculates the actual damage taken by the enemy.
	 * @param damage The amount of damage dealt.
	 * @return The amount of damage effectively taken.
	 */
	int damageTaken(int damage) const override;

	/**
	 * @brief Sets the current health of the enemy.
	 * @param health The new current health value.
	 */
	void setHealth(int health) override;

	/**
	 * @brief Checks if the enemy is still alive.
	 * @return True if the enemy is alive, false otherwise.
	 */
	bool isAlive() const override;

	/**
	 * @brief Applies a new effect to the enemy.
	 * @param neweffect A pointer to the new EffectAttack object to be applied.
	 */
	void applyEffect(EffectAttack* neweffect) override;

	/**
	 * @brief Processes all effects currently applied to the enemy.
	 */
	void processEffects() override;

	/**
	 * @brief Performs an attack action for the enemy.
	 * @return The amount of damage dealt by the enemy's attack.
	 */
	int attack() const override;
};

#endif
