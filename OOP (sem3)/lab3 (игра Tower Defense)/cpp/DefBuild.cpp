#include "../hpp/DefBuild.hpp"

#include "../hpp/Cell.hpp"
#include "../hpp/BuildAttack.hpp"


DefBuild::DefBuild(int cost, int level, int radius, int damage, AttackStrategy strat) :
	cost(cost), level(level), radius(radius), damage(damage), strat(strat) {}

int DefBuild::getCost() const { return cost; }
int DefBuild::getLevel() const { return level; }
int DefBuild::getRadius() const { return radius; }
int DefBuild::getDamage() const { return damage; }
AttackStrategy DefBuild::getStrategy() const { return strat; }
void DefBuild::setStrategy(AttackStrategy newstrat) { strat = newstrat; }
