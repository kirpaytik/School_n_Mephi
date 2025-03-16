#ifndef MAGICTOWER_HPP
#define MAGICTOWER_HPP

#include "Tower.hpp"
#include "BuildAttack.hpp"
#include "EffectAttack.hpp"

class MagicTower : public Tower
{
private:
	EffectType effect;

public:
	MagicTower(int cost, int level, int radius, int damage, AttackStrategy strat, int attackspeed, EffectType effect);

	EffectType getEffect() const override;
	void setEffect(EffectType neweffect);

	// Tower methods
	BuildType getType() const override { return BuildType::MAGICTOWER; }
	BuildAttack* attack() const override;
	virtual void upgrade() override;
};

#endif
