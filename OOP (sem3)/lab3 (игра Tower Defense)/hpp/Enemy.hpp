#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "EffectAttack.hpp"

#include "../interfaces/IMovable.hpp"
#include "../interfaces/IDamagable.hpp"
#include "../interfaces/IEffectProcessor.hpp"
#include "../interfaces/IEnemyAttacker.hpp"

#include <vector>

#ifndef ENEMYTYPE
#define ENEMYTYPE
enum class EnemyType {
	NORMAL, FAST, TANK, CUSTOM
};
#endif


class Enemy : public IMovable, public IDamagable, public IEffectProcessor, public IEnemyAttacker
{
private:
	int maxhealth;
	int currhealth;
	int speed;
	int gold;
	std::vector<EffectAttack*> effects;

	EnemyType type;

public:
	Enemy(int health, int speed, int gold, EnemyType type);
	~Enemy();

	int getMaxHealth() const;
	void setMaxHealth(int health);

	int getHealth() const;
	// setter in IDamagable

	int getSpeed() const;
	void setSpeed(int speed);

	int getGold() const;
	void setGold(int gold);

	std::vector<EffectAttack*> getEffects() const;
	bool hasEffect(EffectType type) const;

	EnemyType getType() const;

	// IMovable
	int move() const override;

	// IDamagable
	int damageTaken(int damage) const override;
	void setHealth(int health) override;
	bool isAlive() const override;

	// IEffectProcessor
	void applyEffect(EffectAttack* neweffect) override;
	void processEffects() override;

	// IEnemyAttacker
	int attack() const override;
};

#endif
