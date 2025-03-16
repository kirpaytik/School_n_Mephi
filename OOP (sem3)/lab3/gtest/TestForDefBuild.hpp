#ifndef TESTFORDEFBUILD_HPP
#define TESTFORDEFBUILD_HPP

#include "../hpp/DefBuild.hpp"

class TestForDefBuild : public DefBuild
{
public:
	TestForDefBuild(int cost, int level, int radius, int damage, AttackStrategy strat) :
		DefBuild(cost, level, radius, damage, strat) {}

	BuildType getType() const override { return BuildType::TOWER; }

	// IControlMyselfOnLand
	std::pair<int, int> getCoord(const Landscape* land) const override { return std::pair<int, int>(0, 0); }
	void installOnCell(Landscape* land, int x, int y) override {}

	// IBuildAttacker
	BuildAttack* attack() const override { return new BuildAttack(0, nullptr); }
};

#endif
