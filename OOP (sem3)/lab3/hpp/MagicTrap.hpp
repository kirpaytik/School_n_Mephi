#ifndef MAGICTRAP_HPP
#define MAGICTRAP_HPP

#include "DefBuild.hpp"
#include "BuildAttack.hpp"
#include "EffectAttack.hpp"

class Landscape;

class MagicTrap : public DefBuild
{
private:
	EffectType effect;

public:
	MagicTrap(int cost, int level, int radius, int damage, AttackStrategy strat, EffectType effect);

	EffectType getEffect() const override;
	void setEffect(EffectType neweffect);

	// DefBuild methods
	std::pair<int, int> getCoord(const Landscape* land) const override;
	void installOnCell(Landscape* land, int x, int y) override;
	BuildType getType() const override { return BuildType::MAGICTRAP; }

	BuildAttack* attack() const override;
	void onAttackComplete(Landscape* land) override;

	virtual void upgrade() override;
};

#endif
