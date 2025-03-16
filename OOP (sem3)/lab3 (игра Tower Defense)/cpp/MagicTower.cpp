#include "../hpp/MagicTower.hpp"

#include "../hpp/Tower.hpp"
#include "../hpp/BuildAttack.hpp"
#include "../hpp/EffectAttack.hpp"

#include "../hpp/PriceTable.hpp"


MagicTower::MagicTower(int cost, int level, int radius, int damage, AttackStrategy strat, int attackspeed, EffectType effect) :
	Tower(cost, level, radius, damage, strat, attackspeed), effect(effect) {}

EffectType MagicTower::getEffect() const { return effect; }
void MagicTower::setEffect(EffectType neweffect) { effect = neweffect; }

// Tower methods
BuildAttack* MagicTower::attack() const { return new BuildAttack(damage, new EffectAttack(effect, level)); }

void MagicTower::upgrade()
{
	Tower::upgrade(); // ++level;
	BuildStats stats = PriceTable::instance().getBuildStats(BuildType::MAGICTOWER, strat, effect, level);

	cost = stats.cost;
	radius = stats.radius;
	damage = stats.damage;
	attackSpeed = stats.attackspeed;
}
