#ifndef IMOVABLE_HPP
#define IMOVABLE_HPP

/**
 * @brief Interface for objects that can move.
 * 
 * Classes implementing this interface must define the logic for movement
 * and return the number of cells to be moved along.
 */
class IMovable
{
public:
	/**
	 * @brief Move the object to a new position.
	 *
	 * @return The difference in number of cells between current and new position of the object after moving.
	 */
	virtual int move() const = 0;
};

#endif
