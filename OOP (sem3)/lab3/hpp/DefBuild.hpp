#ifndef DEFBUILD_HPP
#define DEFBUILD_HPP

#include "Cell.hpp"
#include "BuildAttack.hpp"

#include "../interfaces/IControlMyselfOnLand.hpp"
#include "../interfaces/IBuildAttacker.hpp"
#include "../interfaces/IUpgradable.hpp"

class Landscape;

#include <utility> // std::pair

#ifndef ATTACKSTRATEGY
#define ATTACKSTRATEGY
enum class AttackStrategy {
	NearestToTower,
	FurthestFromTower,
	NearestToCastle,
	LowestHP,
	HighestHP
};
#endif

#ifndef BUILDTYPE
#define BUILDTYPE
enum class BuildType { TOWER, MAGICTOWER, MAGICTRAP };
#endif


class DefBuild : public IControlMyselfOnLand, public IBuildAttacker, public IUpgradable
{
protected:
	int cost;
	int level;
	int radius;
	int damage;
	AttackStrategy strat;

public:
	DefBuild(int cost, int level, int radius, int damage, AttackStrategy strat);
	virtual ~DefBuild() {}

	int getCost() const;
	int getLevel() const;
	int getRadius() const;
	int getDamage() const;
	AttackStrategy getStrategy() const;
	void setStrategy(AttackStrategy newstrat);

	virtual BuildType getType() const = 0;
	virtual EffectType getEffect() const { return EffectType::POISON; }

	// IControlMyselfOnLand
	virtual std::pair<int, int> getCoord(const Landscape* land) const override = 0;
	virtual void installOnCell(Landscape* land, int x, int y) override = 0;

	// IBuildAttacker
	virtual BuildAttack* attack() const override = 0;
	virtual bool isReady() const override { return true; } // like mtrap is always ready
	virtual void setUnready() override {}
	virtual void advanceReadiness() override {}
	virtual void onAttackComplete([[maybe_unused]] Landscape* land) override {} // Tower doesnt need this, only for mtrap

	// IUpgradable
	virtual void upgrade() override { ++level; }
	bool isUpgraded() const override { return level == 3; }
};

#endif
