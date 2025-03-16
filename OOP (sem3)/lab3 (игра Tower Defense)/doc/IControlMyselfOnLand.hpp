#ifndef ICONTROLMYSELFONLAND_HPP
#define ICONTROLMYSELFONLAND_HPP

class Landscape;

#include <utility>

/**
 * @brief Interface for controlling the placement and positioning of structures on the landscape.
 * 
 * This interface provides methods for placing a structure on a specific cell in the landscape
 * and for obtaining the current position of it.
 */
class IControlMyselfOnLand
{
public:
	/**
	 * @brief Install the object on a specific cell in the landscape.
	 * 
	 * This method should handle the logic of placing the object at the specified coordinates
	 * on the landscape, updating any necessary internal or landscape state.
	 * 
	 * @param land A pointer to the Landscape object where the entity will be installed.
	 * @param x The x-coordinate of the cell.
	 * @param y The y-coordinate of the cell.
	 */
	virtual void installOnCell(Landscape* land, int x, int y) = 0;

	/**
	 * @brief Get the coordinates of the object on the landscape.
	 * 
	 * This method should return the current position of the object as a pair of integers
	 * representing the x and y coordinates.
	 * 
	 * @param land A pointer to the Landscape object where the entity resides.
	 * @return A pair of integers representing the x and y coordinates of the object.
	 */
	virtual std::pair<int, int> getCoord(const Landscape* land) const = 0;
};

#endif
