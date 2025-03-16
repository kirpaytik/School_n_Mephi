/**
 * @file EffectAttack.hpp
 * @brief Defines the EffectAttack class, which represents a status effect applied during an attack.
 */

#ifndef EFFECTATTACK_HPP
#define EFFECTATTACK_HPP

#ifndef EFFECTTYPE
#define EFFECTTYPE

/**
 * @enum EffectType
 * @brief Represents different types of effects that can be applied during an attack.
 */
enum class EffectType {
	POISON,   ///< Inflicts poison damage over time.
	SLOWNESS, ///< Reduces the target's movement speed.
	WEAKNESS  ///< Reduces the target's damage output.
};

#endif

#include "../interfaces/IUpgradable.hpp"

/**
 * @class EffectAttack
 * @brief Represents an effect applied to a target during an attack.
 */
class EffectAttack : public IUpgradable
{
private:
	EffectType type; ///< The type of the effect.
	int level; ///< The level of the effect, determining its strength.
	int attribute; ///< The attribute value associated with the effect (e.g., damage reduction or slow percentage).
	int minApplied; ///< The minimum attribute value applied by the effect.
	int duration; ///< The duration of the effect in game ticks or seconds.

public:
	/**
	 * @brief Constructs an EffectAttack with a specific type and level.
	 * @param type The type of the effect.
	 * @param level The level of the effect.
	 */
	EffectAttack(EffectType type, int level);

	/**
	 * @brief Gets the type of the effect.
	 * @return The effect type.
	 */
	EffectType getType() const;

	/**
	 * @brief Gets the current level of the effect.
	 * @return The effect level.
	 */
	int getLevel() const;

	/**
	 * @brief Gets the attribute value of the effect.
	 * @return The attribute value.
	 */
	int getAttribute() const;

	/**
	 * @brief Gets the minimum attribute value applied by the effect.
	 * @return The minimum applied value.
	 */
	int getMinApplied() const;

	/**
	 * @brief Gets the duration of the effect.
	 * @return The effect's duration in game ticks or seconds.
	 */
	int getDuration() const;

	/**
	 * @brief Sets a new duration for the effect.
	 * @param newduration The new duration value.
	 */
	void setDuration(int newduration);

	/**
	 * @brief Increases the effect's duration by a specified amount.
	 * @param addDuration The amount to increase the duration by.
	 */
	void addDuration(int addDuration);

	/**
	 * @brief Checks if the effect has expired.
	 * @return True if the effect's duration is 0 or less, false otherwise.
	 */
	bool isExpired() const;

	/**
	 * @brief Calculates the effect's applied value based on a target value.
	 * @param value_to_apply_to The target value to which the effect will be applied.
	 * @return The calculated applied value.
	 */
	int getAppliedValue(int value_to_apply_to) const;

	/**
	 * @brief Upgrades the effect, increasing its level and attributes.
	 * @note Overrides IUpgradable::upgrade.
	 */
	void upgrade() override;

	/**
	 * @brief Checks if the effect is fully upgraded.
	 * @return True if the effect level is 3, false otherwise.
	 * @note Overrides IUpgradable::isUpgraded.
	 */
	bool isUpgraded() const override { return level == 3; }

	/**
	 * @brief Compares two effects for equality.
	 * @param other The other EffectAttack to compare with.
	 * @return True if the effects have the same type and level, false otherwise.
	 */
	bool operator == (const EffectAttack& other) const;
};

#endif
