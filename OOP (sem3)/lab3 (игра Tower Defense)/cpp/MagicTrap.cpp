#include "../hpp/MagicTrap.hpp"

#include "../hpp/DefBuild.hpp"
#include "../hpp/BuildAttack.hpp"
#include "../hpp/EffectAttack.hpp"
#include "../hpp/Landscape.hpp"

#include "../hpp/PriceTable.hpp"


MagicTrap::MagicTrap(int cost, int level, int radius, int damage, AttackStrategy strat, EffectType effect) :
	DefBuild(cost, level, radius, damage, strat), effect(effect) {}

EffectType MagicTrap::getEffect() const { return effect; }
void MagicTrap::setEffect(EffectType neweffect) { effect = neweffect; }

// DefBuild methods
std::pair<int, int> MagicTrap::getCoord(const Landscape* land) const
{
	Road* road = land->getRoad(this);
	return std::make_pair(road->getX(), road->getY());
}


void MagicTrap::installOnCell(Landscape* land, int x, int y)
{
	land->getRoad(x, y)->setMTrap(this);
}


void MagicTrap::onAttackComplete(Landscape* land)
{
	std::pair<int, int> pair = getCoord(land);
	int x = pair.first, y = pair.second;
	Road* road = land->getRoad(x, y);
	if (road) {
		road->setMTrap(nullptr);
	}
	delete this;
}

BuildAttack* MagicTrap::attack() const { return new BuildAttack(damage, new EffectAttack(effect, level)); }

void MagicTrap::upgrade()
{
	DefBuild::upgrade(); // ++level;
	BuildStats stats = PriceTable::instance().getBuildStats(BuildType::MAGICTRAP, strat, effect, level);

	cost = stats.cost;
	radius = stats.radius;
	damage = stats.damage;
}
