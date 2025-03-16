/**
 * @file MagicTower.hpp
 * @brief Defines the MagicTower class, a specialized tower with magical effects.
 */

#ifndef MAGICTOWER_HPP
#define MAGICTOWER_HPP

#include "Tower.hpp"
#include "BuildAttack.hpp"
#include "EffectAttack.hpp"

/**
 * @class MagicTower
 * @brief Represents a tower that attacks with magical effects.
 */
class MagicTower : public Tower
{
private:
	EffectType effect; ///< The type of magical effect applied by the tower's attacks.

public:
	/**
	 * @brief Constructs a magic tower with specified attributes.
	 * @param cost The construction cost of the tower.
	 * @param level The initial level of the tower.
	 * @param radius The attack radius of the tower.
	 * @param damage The base damage dealt by the tower.
	 * @param strat The attack strategy of the tower.
	 * @param attackspeed The speed of attacks (cooldown in ticks).
	 * @param effect The type of magical effect applied by the tower.
	 */
	MagicTower(int cost, int level, int radius, int damage, AttackStrategy strat, int attackspeed, EffectType effect);

	/**
	 * @brief Gets the magical effect applied by the tower's attacks.
	 * @return The effect type.
	 */
	EffectType getEffect() const override;

	/**
	 * @brief Sets a new magical effect for the tower's attacks.
	 * @param neweffect The new effect type the tower will attack with.
	 */
	void setEffect(EffectType neweffect);

	/**
	 * @brief Gets the type of the defensive structure.
	 * @return BuildType::MAGICTOWER.
	 */
	BuildType getType() const override { return BuildType::MAGICTOWER; }

	/**
	 * @bried Creates a BuildAttack object with magical effect that will be aplied to an enemy.
	 * @return A pointer to a BuildAttack object representing the attack.
	 */
	BuildAttack* attack() const override;

	/**
	 * @brief Upgrades the magic tower, increasing its attributes and potentially enhancing its effect.
	 */
	virtual void upgrade() override;
};

#endif
