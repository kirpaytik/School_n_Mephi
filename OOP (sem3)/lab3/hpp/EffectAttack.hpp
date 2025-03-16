#ifndef EFFECTATTACK_HPP
#define EFFECTATTACK_HPP

#ifndef EFFECTTYPE
#define EFFECTTYPE

enum class EffectType {
	POISON, SLOWNESS, WEAKNESS
};

#endif


#include "../interfaces/IUpgradable.hpp"

class EffectAttack : public IUpgradable
{
private:
	EffectType type;
	int level;
	int attribute;
	int minApplied;
	int duration;
public:
	EffectAttack(EffectType type, int level);

	EffectType getType() const;
	int getLevel() const;
	int getAttribute() const;
	int getMinApplied() const;
	int getDuration() const;
	void setDuration(int newduration);
	void addDuration(int addDuration);
	bool isExpired() const;

	int getAppliedValue(int value_to_apply_to) const;

	// IUpgradable
	void upgrade() override;
	bool isUpgraded() const override { return level == 3; }

	bool operator == (const EffectAttack& other) const;
};

#endif
