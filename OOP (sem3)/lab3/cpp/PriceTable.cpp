#include "../hpp/PriceTable.hpp"

#include <unordered_map>

#include <iostream>


std::unordered_map<PriceBuildKey, BuildStats> PriceTable::priceBuildTable;

PriceTable::PriceTable() {
	priceBuildTable[{BuildType::TOWER, AttackStrategy::LowestHP, EffectType::POISON, 1}] = {100, 6, 20, 3};
	priceBuildTable[{BuildType::TOWER, AttackStrategy::LowestHP, EffectType::POISON, 2}] = {150, 7, 30, 2};
	priceBuildTable[{BuildType::TOWER, AttackStrategy::LowestHP, EffectType::POISON, 3}] = {200, 8, 40, 2};

	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::POISON, 1}] = {130, 4, 1, 4};
	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::POISON, 2}] = {180, 5, 1, 3};
	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::POISON, 3}] = {230, 6, 1, 3};

	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::SLOWNESS, 1}] = {130, 4, 5, 3};
	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::SLOWNESS, 2}] = {180, 4, 10, 3};
	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::SLOWNESS, 3}] = {230, 5, 15, 3};

	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::WEAKNESS, 1}] = priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::SLOWNESS, 1}];
	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::WEAKNESS, 2}] = priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::SLOWNESS, 2}];
	priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::WEAKNESS, 3}] = priceBuildTable[{BuildType::MAGICTOWER, AttackStrategy::LowestHP, EffectType::SLOWNESS, 3}];

	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::POISON, 1}] = {90, 2, 5, 0};
	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::POISON, 2}] = {110, 3, 7, 0};
	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::POISON, 3}] = {130, 3, 10, 0};

	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::SLOWNESS, 1}] = {90, 2, 4, 0};
	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::SLOWNESS, 2}] = {110, 3, 6, 0};
	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::SLOWNESS, 3}] = {130, 3, 8, 0};

	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::WEAKNESS, 1}] = priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::SLOWNESS, 1}];
	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::WEAKNESS, 2}] = priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::SLOWNESS, 2}];
	priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::WEAKNESS, 3}] = priceBuildTable[{BuildType::MAGICTRAP, AttackStrategy::LowestHP, EffectType::SLOWNESS, 3}];



}


BuildStats PriceTable::getBuildStats(PriceBuildKey key)
{
	return priceBuildTable.at(key);
}

BuildStats PriceTable::getBuildStats(BuildType type, AttackStrategy strat, int level)
{
	return priceBuildTable.at({type, strat, EffectType::POISON, level});
}

BuildStats PriceTable::getBuildStats(BuildType type, AttackStrategy strat, EffectType effect, int level)
{
	return priceBuildTable.at({type, strat, effect, level});
}


int PriceTable::getBuildCost(PriceBuildKey key)
{
	return getBuildStats(key).cost;
}

int PriceTable::getBuildCost(BuildType type, AttackStrategy strat, int level)
{
	return getBuildStats(type, strat, level).cost;
}

int PriceTable::getBuildCost(BuildType type, AttackStrategy strat, EffectType effect, int level)
{
	return getBuildStats(type, strat, effect, level).cost;
}
