/**
 * @file DefBuild.hpp
 * @brief Defines the base expandable class for defensive structures in the game.
 */

#ifndef DEFBUILD_HPP
#define DEFBUILD_HPP

#include "Cell.hpp"
#include "BuildAttack.hpp"

#include "../interfaces/IControlMyselfOnLand.hpp"
#include "../interfaces/IBuildAttacker.hpp"
#include "../interfaces/IUpgradable.hpp"

class Landscape;

#include <utility>

/**
 * @enum AttackStrategy
 * @brief Represents different attack strategies for defensive structures.
 */
enum class AttackStrategy {
	NearestToTower,    ///< Targets the enemy closest to the tower.
	FurthestFromTower, ///< Targets the enemy furthest from the tower.
	NearestToCastle,   ///< Targets the enemy closest to the castle.
	LowestHP,          ///< Targets the enemy with the lowest health.
	HighestHP          ///< Targets the enemy with the highest health.
};

/**
 * @enum BuildType
 * @brief Represents the type of defensive structure.
 */
enum class BuildType { 
	TOWER,       ///< Regular tower.
	MAGICTOWER,  ///< Tower with magic-based attacks.
	MAGICTRAP    ///< Trap with magic-based attacks.
};

/**
 * @class DefBuild
 * @brief Base class for defensive structures in the game.
 * 
 * Defensive structures can attack enemies, upgrade their capabilities, and interact with the game field.
 */
class DefBuild : public IControlMyselfOnLand, public IBuildAttacker, public IUpgradable
{
protected:
	int cost;             ///< Cost of constructing the defensive structure.
	int level;            ///< Current level of the structure.
	int radius;           ///< Attack radius of the structure.
	int damage;           ///< Base damage dealt by the structure.
	AttackStrategy strat; ///< Current attack strategy of the structure.

public:
	/**
	 * @brief Constructs a defensive structure with specified parameters.
	 * @param cost The construction cost of the structure.
	 * @param level The level of the structure.
	 * @param radius The attack radius of the structure.
	 * @param damage The physical damage dealt by the structure.
	 * @param strat The attack strategy of the structure.
	 */
	DefBuild(int cost, int level, int radius, int damage, AttackStrategy strat);

	/**
	 * @brief Virtual destructor.
	 */
	virtual ~DefBuild() {}

	/**
	 * @brief Gets the construction cost of the structure.
	 * @return The construction cost.
	 */
	int getCost() const;

	/**
	 * @brief Gets the current level of the structure.
	 * @return The current level.
	 */
	int getLevel() const;

	/**
	 * @brief Gets the attack radius of the structure.
	 * @return The attack radius.
	 */
	int getRadius() const;

	/**
	 * @brief Gets the base damage dealt by the structure.
	 * @return The damage value.
	 */
	int getDamage() const;

	/**
	 * @brief Gets the current attack strategy of the structure.
	 * @return The attack strategy.
	 */
	AttackStrategy getStrategy() const;

	/**
	 * @brief Sets a new attack strategy for the structure.
	 * @param newstrat The new attack strategy.
	 */
	void setStrategy(AttackStrategy newstrat);

	/**
	 * @brief Gets the type of the defensive structure.
	 * @return The BuildType of the structure.
	 */
	virtual BuildType getType() const = 0;

	/**
	 * @brief Gets the effect type associated with the structure's attacks, POISON as default if structure doesn't have magic powers.
	 * @return The EffectType of the structure's attacks (default is POISON).
	 */
	virtual EffectType getEffect() const { return EffectType::POISON; }

	/**
	 * @brief Gets the coordinates of the structure on the game field.
	 * @param land Pointer to the landscape object.
	 * @return A pair of integers representing the coordinates.
	 */
	virtual std::pair<int, int> getCoord(const Landscape* land) const override = 0;

	/**
	 * @brief Installs the structure on a specific cell of the game field.
	 * @param land Pointer to the landscape object.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 */
	virtual void installOnCell(Landscape* land, int x, int y) override = 0;

	/**
	 * @bried Creates a BuildAttack object that will be aplied to an enemy.
	 * @return A pointer to a BuildAttack object representing the attack.
	 */
	virtual BuildAttack* attack() const override = 0;

	/**
	 * @brief Checks if the structure is ready to attack. Default true for always-ready structures.
	 * @return True if the structure is ready, false otherwise.
	 */
	virtual bool isReady() const override { return true; }

	/**
	 * @brief Marks the structure as unready to attack, doesn't do anything for always-ready structures.
	 */
	virtual void setUnready() override {}

	/**
	 * @brief Advances the readiness state of the structure for its next attack, doesn't do anything for always-ready structures.
	 */
	virtual void advanceReadiness() override {}

	/**
	 * @brief Handles post-attack actions for the structure, doesn't do anything for structures that doesn't have post-attack actions.
	 * @param land Pointer to the landscape object (optional for some structures).
	 */
	virtual void onAttackComplete([[maybe_unused]] Landscape* land) override {}

	/**
	 * @brief Upgrades the structure, increasing its level.
	 * 
	 * Needs to increase structures' statistics which depends on the current structure type.
	 */
	virtual void upgrade() override { ++level; }

	/**
	 * @brief Checks if the structure has reached its maximum upgrade level.
	 * @return True if the structure is fully upgraded, false otherwise.
	 */
	bool isUpgraded() const override { return level == 3; }
};

#endif
