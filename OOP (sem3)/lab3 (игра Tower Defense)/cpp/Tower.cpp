#include "../hpp/Tower.hpp"

#include "../hpp/DefBuild.hpp"
#include "../hpp/BuildAttack.hpp"
#include "../hpp/Landscape.hpp"

#include "../hpp/PriceTable.hpp"


Tower::Tower(int cost, int level, int radius, int damage, AttackStrategy strat, int attackSpeed) : 
	DefBuild(cost, level, radius, damage, strat), attackSpeed(attackSpeed), overheat(0) {}

int Tower::getAttackSpeed() const { return attackSpeed; }

// DefBuild methods
BuildAttack* Tower::attack() const { return new BuildAttack(damage, nullptr); }
bool Tower::isReady() const { return overheat == 0; }
void Tower::setUnready() {overheat = attackSpeed; }
void Tower::advanceReadiness() { --overheat; }

std::pair<int, int> Tower::getCoord(const Landscape* land) const
{
	Field* field = land->getField(this);
	return std::make_pair(field->getX(), field->getY());
}


void Tower::installOnCell(Landscape* land, int x, int y)
{
	land->getField(x, y)->setBuild(this);
}


void Tower::upgrade()
{
	DefBuild::upgrade(); // ++level;
	BuildStats stats = PriceTable::instance().getBuildStats(BuildType::TOWER, strat, level);

	cost = stats.cost;
	radius = stats.radius;
	damage = stats.damage;
	attackSpeed = stats.attackspeed;
}
