/**
 * @file BuildAttack.hpp
 * @brief Defines the BuildAttack class, representing an attack initiated by a defensive building.
 */

#ifndef BUILDATTACK_HPP
#define BUILDATTACK_HPP

#include "EffectAttack.hpp"

/**
 * @class BuildAttack
 * @brief Represents an attack performed by a defensive building, which may include physical damage and optional effects.
 */
class BuildAttack
{
private:
	int damage; ///< The base damage dealt by the attack.
	EffectAttack* effect; ///< The effect applied by the attack, if any.

public:
	/**
	 * @brief Constructs a BuildAttack with specified damage and effect to be aplied.
	 * @param damage The amount of damage dealt by the attack.
	 * @param effect A pointer to the effect applied by the attack (can be nullptr).
	 */
	BuildAttack(int damage, EffectAttack* effect);

	/**
	 * @brief Constructs a BuildAttack with only physical damage.
	 * @param damage The amount of damage dealt by the attack.
	 */
	BuildAttack(int damage);

	/**
	 * @brief Constructs a BuildAttack with only an effect.
	 * @param effect A pointer to the effect applied by the attack.
	 */
	BuildAttack(EffectAttack* effect);

	/**
	 * @brief Destructor. Cleans up the dynamically allocated effect, if any.
	 */
	~BuildAttack();

	/**
	 * @brief Gets the amount of damage dealt by the attack.
	 * @return The damage value.
	 */
	int getDamage() const;

	/**
	 * @brief Sets the amount of damage dealt by the attack.
	 * @param newdamage The new damage value.
	 */
	void setDamage(int newdamage);

	/**
	 * @brief Gets the effect applied by the attack, if any.
	 * @return A pointer to the EffectAttack object.
	 */
	EffectAttack* getEffect() const;

	/**
	 * @brief Sets a new effect for the attack.
	 * @param neweffect A pointer to the new EffectAttack object.
	 */
	void setEffect(EffectAttack* neweffect);
};

#endif
