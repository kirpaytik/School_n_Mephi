#ifndef ROAD_HPP
#define ROAD_HPP

#include "Cell.hpp"
#include "Enemy.hpp"
#include "MagicTrap.hpp"

class Road : public Cell
{
private:
	Enemy* enemy;
	MagicTrap* mtrap;
	Road* nextroad;

public:
	Road(int x, int y);
	Road(int x, int y, Enemy* enemy);
	Road(int x, int y, MagicTrap* mtrap);
	Road(int x, int y, Enemy* enemy, MagicTrap* mtrap);
	~Road();

	Enemy* getEnemy() const;
	void setEnemy(Enemy* enemy);
	bool isEmptyEnemy() const;

	MagicTrap* getMTrap() const;
	void setMTrap(MagicTrap* mtrap);
	bool isEmptyMTrap() const;

	Road* getNextRoad() const;
	Road* getNextRoad(unsigned int dist) const;
	void setNextRoad(Road* road);
};

#endif
