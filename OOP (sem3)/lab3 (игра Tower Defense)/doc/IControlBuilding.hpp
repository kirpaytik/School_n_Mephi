#ifndef ICONTROLBUILDING_HPP
#define ICONTROLBUILDING_HPP

enum class BuildType;
struct PriceBuildKey;

/**
 * @brief Interface for managing the construction and upgrading of defensive buildings.
 * 
 * This interface defines methods for verifying the possibility of building a defensive structure
 * and for performing the construction itself.
 */
class IControlBuilding
{
public:
	/**
	 * @brief Check if a defensive building can be built at the specified location.
	 * 
	 * This method should determine if it is possible to build a defensive building based on
	 * factors like the building's type, its cost, and the availability of space.
	 * 
	 * @param x The X-coordinate of the intended build location.
	 * @param y The Y-coordinate of the intended build location.
	 * @param cost The cost of the building.
	 * @param type The type of the defensive building.
	 * @return True if the building can be constructed, false otherwise.
	 */
	virtual bool canBuildDefBuild(int x, int y, int cost, BuildType type) const = 0;

	/**
	 * @brief Construct a defensive building at the specified location.
	 * 
	 * This method should handle the logic for creating a defensive building,
	 * including updating the game state and resources.
	 * 
	 * @param x The X-coordinate of the build location.
	 * @param y The Y-coordinate of the build location.
	 * @param key The price key containing information about the building to construct.
	 */
	virtual void buildDefBuild(int x, int y, PriceBuildKey key) = 0;
};

#endif
