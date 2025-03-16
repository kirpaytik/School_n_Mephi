#ifndef IDAMAGABLE_HPP
#define IDAMAGABLE_HPP

/**
 * @brief Interface for objects that can take damage.
 * 
 * This interface defines methods for managing health and damage for entities such as enemies or buildings.
 */
class IDamagable
{
public:
	/**
	 * @brief Calculate the damage taken by the object.
	 * 
	 * This method should compute the resulting object's health reduction after receiving damage.
	 * 
	 * @param damage The amount of damage inflicted on the object.
	 * @return The actual damage applied after any modifiers (e.g., resistance).
	 */
	virtual int damageTaken(int damage) const = 0;

	/**
	 * @brief Set the object's current health.
	 * 
	 * This method allows updating the object's health directly.
	 * 
	 * @param health The new health value for the object.
	 */
	virtual void setHealth(int health) = 0;

	/**
	 * @brief Check if the object is still alive.
	 * 
	 * This method should return whether the object has remaining health or is considered dead.
	 * 
	 * @return True if the object is alive, false otherwise.
	 */
	virtual bool isAlive() const = 0;
};

#endif
