/**
 * @file Tower.hpp
 * @brief Defines the Tower class, which represents a standard defensive structure.
 */

#ifndef TOWER_HPP
#define TOWER_HPP

#include "DefBuild.hpp"
#include "BuildAttack.hpp"

class Landscape;

/**
 * @class Tower
 * @brief Represents a standard tower that attacks enemies only with physical attacks.
 */
class Tower : public DefBuild
{
protected:
	int attackSpeed; ///< Speed of attacks (cooldown time between attacks).
	int overheat;    ///< Tracks the readiness of the tower for the next attack.

public:
	/**
	 * @brief Constructs a tower with specified attributes.
	 * @param cost The construction cost of the tower.
	 * @param level The initial level of the tower.
	 * @param radius The attack radius of the tower.
	 * @param damage The base damage dealt by the tower.
	 * @param strat The attack strategy of the tower.
	 * @param attackSpeed The speed of attacks (cooldown in ticks).
	 */
	Tower(int cost, int level, int radius, int damage, AttackStrategy strat, int attackSpeed);

	/**
	 * @brief Destructor.
	 */
	virtual ~Tower() {}

	/**
	 * @brief Gets the attack speed of the tower.
	 * @return The attack speed value.
	 */
	int getAttackSpeed() const;

	/**
	 * @brief Gets the coordinates of the tower on the landscape.
	 * @param land A pointer to the landscape object.
	 * @return A pair of integers representing the x and y coordinates.
	 */
	std::pair<int, int> getCoord(const Landscape* land) const override;

	/**
	 * @brief Installs the tower on a specified cell of the landscape.
	 * @param land A pointer to the landscape object.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 */
	void installOnCell(Landscape* land, int x, int y) override;

	/**
	 * @brief Gets the type of the defensive structure.
	 * @return BuildType::TOWER.
	 */
	virtual BuildType getType() const override { return BuildType::TOWER; }

	/**
	 * @bried Creates a BuildAttack object that will be aplied to an enemy.
	 * @return A pointer to a BuildAttack object representing the attack.
	 */
	virtual BuildAttack* attack() const override;

	/**
	 * @brief Checks if the tower is ready to attack.
	 * @return True if the tower is ready, false otherwise.
	 */
	bool isReady() const override;

	/**
	 * @brief Sets the tower's state to unready after an attack.
	 */
	void setUnready() override;

	/**
	 * @brief Advances the readiness of the tower, reducing its cooldown.
	 */
	void advanceReadiness() override;

	/**
	 * @brief Upgrades the tower, increasing its attributes.
	 */
	virtual void upgrade() override;
};

#endif
