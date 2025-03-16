#ifndef IUPGRADABLE_HPP
#define IUPGRADABLE_HPP

/**
 * @brief Interface for objects that can be upgraded.
 * 
 * Classes implementing this interface must define upgrade logic and check 
 * whether the object has reached its maximum level of improvement.
 */
class IUpgradable
{
public:
	/**
	 * @brief Upgrade the object to the next level.
	 * 
	 * This method should handle the logic for enhancing the object's attributes.
	 */
	virtual void upgrade() = 0;

	/**
	 * @brief Check if the object is fully upgraded.
	 * 
	 * @return True if the object has reached its maximum level, otherwise false.
	 */
	virtual bool isUpgraded() const = 0;
};

#endif
