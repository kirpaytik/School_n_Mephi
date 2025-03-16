#ifndef IBUILDATTACKER_HPP
#define IBUILDATTACKER_HPP

class BuildAttack;
class Landscape;

/**
 * @brief Interface for buildings that can perform attacks.
 * 
 * Classes implementing this interface must define the behavior for initiating attacks,
 * managing readiness for attack, and handling post-attack logic.
 */
class IBuildAttacker
{
public:
	/**
	 * @brief Perform an attack.
	 * 
	 * This method should define the logic for creating and returning a BuildAttack instance
	 * that represents the attack to be aplied to the enemy.
	 * 
	 * @return A pointer to a BuildAttack object representing the attack.
	 */
	virtual BuildAttack* attack() const = 0;

	/**
	 * @brief Check if the building is ready to attack.
	 * 
	 * This method should return whether the object has completed cooldown
	 * and is ready to perform another attack.
	 * 
	 * @return True if ready, otherwise false.
	 */
	virtual bool isReady() const = 0;

	/**
	 * @brief Mark the object as unready after an attack.
	 * 
	 * This method should handle setting the object's state to unready,
	 * starting a cooldown or other readiness mechanism.
	 */
	virtual void setUnready() = 0;

	/**
	 * @brief Advance the readiness state of the object.
	 * 
	 * This method should handle the progression of time or other factors
	 * required to make the object ready for its next attack.
	 */
	virtual void advanceReadiness() = 0;

	/**
	 * @brief Handle post-attack logic.
	 * 
	 * This method should define any cleanup (e.g. deleting the one-use trap from landscape)
	 * or additional effects that occur after an attack is completed.
	 * 
	 * @param land A pointer to the Landscape object where the attack took place.
	 */
	virtual void onAttackComplete(Landscape* land) = 0;
};

#endif
