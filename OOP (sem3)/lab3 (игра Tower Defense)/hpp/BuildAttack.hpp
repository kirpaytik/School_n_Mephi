#ifndef BUILDATTACK_HPP
#define BUILDATTACK_HPP

#include "EffectAttack.hpp"

class BuildAttack
{
private:
	int damage;
	EffectAttack* effect;
public:
	BuildAttack(int damage, EffectAttack* effect);
	BuildAttack(int damage);
	BuildAttack(EffectAttack* effect);
	~BuildAttack();

	int getDamage() const;
	void setDamage(int newdamage);

	EffectAttack* getEffect() const;
	void setEffect(EffectAttack* neweffect);
	void setEffectNoMemory(EffectAttack* neweffect);
};

#endif
