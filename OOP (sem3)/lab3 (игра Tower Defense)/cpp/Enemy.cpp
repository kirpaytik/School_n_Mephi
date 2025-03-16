#include "../hpp/Enemy.hpp"

#include "../hpp/EffectAttack.hpp"

#include <algorithm>


Enemy::Enemy(int health, int speed, int gold, EnemyType type) :
	maxhealth(health), currhealth(health), speed(speed), gold(gold), effects(), type(type) {}

Enemy::~Enemy() { for(EffectAttack* effect : effects) delete effect; }

int Enemy::getMaxHealth() const { return maxhealth; }
void Enemy::setMaxHealth(int health) { if (health > 0) maxhealth = health; if (currhealth > maxhealth) currhealth = maxhealth; }

int Enemy::getHealth() const { return currhealth; }
void Enemy::setHealth(int health) { if (health < 0) health = 0; else if (health > maxhealth) health = maxhealth; currhealth = health; }

int Enemy::getSpeed() const { return speed; }
void Enemy::setSpeed(int newspeed) { if (newspeed < 1) newspeed = 1; speed = newspeed; }

int Enemy::getGold() const { return gold; }
void Enemy::setGold(int newgold) { if (newgold < 0) newgold = 0; gold = newgold; }

std::vector<EffectAttack*> Enemy::getEffects() const { return effects; }

EnemyType Enemy::getType() const { return type; }


int Enemy::move() const
{
	int real_speed = speed;
	for (EffectAttack* effect : effects) {
		if (effect->getType() == EffectType::SLOWNESS) {
			real_speed -= effect->getAppliedValue(speed);
			break;
		}
	}

	return real_speed > 0 ? real_speed : 0;
}


int Enemy::damageTaken(int damage) const { return damage; }
bool Enemy::isAlive() const { return currhealth > 0; }


void Enemy::applyEffect(EffectAttack* neweffect)
{
	for (auto it = effects.begin(); it != effects.end(); ++it) {
		EffectAttack* effect = *it;
		if (effect->getType() == neweffect->getType()) {
			if (neweffect->getLevel() > effect->getLevel()) {
				delete effect;
				*it = neweffect;
			} else {
				int newduration = std::max(effect->getDuration(), neweffect->getDuration());
				effect->setDuration(newduration);
				delete neweffect;
			}

			return;
		}
	}

	effects.push_back(neweffect);
}


void Enemy::processEffects()
{
	// for (EffectAttack* effect : effects) {
	for (auto it = effects.begin(); it != effects.end(); ) {
		EffectAttack* effect = *it;

		if (effect->getType() == EffectType::POISON) {
			setHealth(currhealth - effect->getAppliedValue(currhealth));
		}

		effect->setDuration(effect->getDuration() - 1);
		if (effect->isExpired()) {
			it = effects.erase(it);
			delete effect;
		} else {
			++it;
		}
	}
}


bool Enemy::hasEffect(EffectType type) const
{
	for (EffectAttack* effect : effects) {
		if (effect->getType() == type)
			return true;
	}

	return false;
}


int Enemy::attack() const
{
	for (EffectAttack* effect : effects) {
		if (effect->getType() == EffectType::WEAKNESS)
			return currhealth - effect->getAppliedValue(currhealth);
	}

	return currhealth;
}
