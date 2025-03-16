#ifndef TOWER_HPP
#define TOWER_HPP

#include "DefBuild.hpp"
#include "BuildAttack.hpp"

class Landscape;

class Tower : public DefBuild
{
protected:
	int attackSpeed;
	int overheat;

public:
	Tower(int cost, int level, int radius, int damage, AttackStrategy strat, int attackSpeed);
	virtual ~Tower() {}

	int getAttackSpeed() const;

	// DefBuild methods
	std::pair<int, int> getCoord(const Landscape* land) const override;
	void installOnCell(Landscape* land, int x, int y) override;
	virtual BuildType getType() const override { return BuildType::TOWER; }

	virtual BuildAttack* attack() const override;
	bool isReady() const override;
	void setUnready() override;
	void advanceReadiness() override;

	virtual void upgrade() override;
};

#endif
