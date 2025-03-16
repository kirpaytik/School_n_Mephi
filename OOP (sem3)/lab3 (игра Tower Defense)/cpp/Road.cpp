#include "../hpp/Road.hpp"

#include "../hpp/Cell.hpp"
#include "../hpp/Enemy.hpp"
#include "../hpp/MagicTrap.hpp"


Road::Road(int x, int y) : Cell(x, y), enemy(nullptr), mtrap(nullptr), nextroad(nullptr) {}

Road::Road(int x, int y, Enemy* enemy) : Cell(x, y), enemy(enemy), mtrap(nullptr), nextroad(nullptr) {}

Road::Road(int x, int y, MagicTrap* mtrap): Cell(x, y), enemy(nullptr), mtrap(mtrap), nextroad(nullptr) {}

Road::Road(int x, int y, Enemy* enemy, MagicTrap* mtrap) : Cell(x, y), enemy(enemy), mtrap(mtrap), nextroad(nullptr) {}

Road::~Road() { delete enemy; delete mtrap; }


Enemy* Road::getEnemy() const { return enemy; }
void Road::setEnemy(Enemy* newenemy) { enemy = newenemy; }
bool Road::isEmptyEnemy() const { return enemy == nullptr; }

MagicTrap* Road::getMTrap() const { return mtrap; }
void Road::setMTrap(MagicTrap* newmtrap) { mtrap = newmtrap; }
bool Road::isEmptyMTrap() const { return mtrap == nullptr; }

Road* Road::getNextRoad() const { return nextroad; }
void Road::setNextRoad(Road* road) { nextroad = road; }
Road* Road::getNextRoad(unsigned int dist) const
{
	const Road* road = this;
	for (unsigned int i = 0; i < dist && road != nullptr; ++i) {
		road = road->nextroad;
	}

	return const_cast<Road*>(road);
}
