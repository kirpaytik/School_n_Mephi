/**
 * @file MagicTrap.hpp
 * @brief Defines the MagicTrap class, a defensive structure that can be placed on a road and applies magical effects to enemies.
 */

#ifndef MAGICTRAP_HPP
#define MAGICTRAP_HPP

#include "DefBuild.hpp"
#include "BuildAttack.hpp"
#include "EffectAttack.hpp"

class Landscape;

/**
 * @class MagicTrap
 * @brief Represents a trap that triggers magical effects when enemies step on it.
 */
class MagicTrap : public DefBuild
{
private:
	EffectType effect; ///< The type of magical effect applied by the trap.

public:
	/**
	 * @brief Constructs a magic trap with specified attributes.
	 * @param cost The construction cost of the trap.
	 * @param level The initial level of the trap.
	 * @param radius The activation radius of the trap.
	 * @param damage The base damage dealt by the trap.
	 * @param strat The activation strategy of the trap.
	 * @param effect The type of magical effect applied by the trap.
	 */
	MagicTrap(int cost, int level, int radius, int damage, AttackStrategy strat, EffectType effect);

	/**
	 * @brief Gets the magical effect applied by the trap.
	 * @return The effect type.
	 */
	EffectType getEffect() const override;

	/**
	 * @brief Sets a new magical effect for the trap.
	 * @param neweffect The new effect type to apply.
	 */
	void setEffect(EffectType neweffect);

	/**
	 * @brief Gets the coordinates of the trap on the landscape.
	 * @param land A pointer to the landscape.
	 * @return A pair of integers representing the x and y coordinates.
	 */
	std::pair<int, int> getCoord(const Landscape* land) const override;

	/**
	 * @brief Installs the trap on a specific cell of the landscape.
	 * @param land A pointer to the landscape.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 */
	void installOnCell(Landscape* land, int x, int y) override;

	/**
	 * @brief Gets the type of the defensive structure.
	 * @return BuildType::MAGICTRAP.
	 */
	BuildType getType() const override { return BuildType::MAGICTRAP; }

	/**
	 * @brief Activates the trap, creating a BuildAttack object to apply its effects.
	 * @return A pointer to a BuildAttack object representing the trap's activation.
	 */
	BuildAttack* attack() const override;

	/**
	 * @brief Handles the completion of the trap's attack, deleting it from the landscape.
	 * @param land A pointer to the landscape, used for interaction after the attack.
	 */
	void onAttackComplete(Landscape* land) override;

	/**
	 * @brief Upgrades the trap, increasing its attributes and potentially enhancing its effect.
	 */
	virtual void upgrade() override;
};

#endif
