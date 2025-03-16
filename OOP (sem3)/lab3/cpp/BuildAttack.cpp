#include "../hpp/BuildAttack.hpp"

#include "../hpp/EffectAttack.hpp"

BuildAttack::BuildAttack(int damage, EffectAttack* effect) : damage(damage), effect(effect) {}
BuildAttack::BuildAttack(int damage) : damage(damage), effect(nullptr) {}
BuildAttack::BuildAttack(EffectAttack* effect) : damage(0), effect(effect) {}
BuildAttack::~BuildAttack() { delete effect; }

int BuildAttack::getDamage() const { return damage; }
void BuildAttack::setDamage(int newdamage) { damage = newdamage; }

EffectAttack* BuildAttack::getEffect() const { return effect; }
void BuildAttack::setEffect(EffectAttack* neweffect) { delete effect; effect = neweffect; }
void BuildAttack::setEffectNoMemory(EffectAttack* neweffect) { effect = neweffect; }
