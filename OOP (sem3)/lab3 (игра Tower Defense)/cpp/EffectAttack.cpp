#include "../hpp/EffectAttack.hpp"


EffectAttack::EffectAttack(EffectType type, int level) : type(type), level(level - 1)
	{ upgrade();}

EffectType EffectAttack::getType() const { return type; }
int EffectAttack::getLevel() const { return level; }
int EffectAttack::getAttribute() const { return attribute; }
int EffectAttack::getMinApplied() const { return minApplied; }
int EffectAttack::getDuration() const { return duration; }
void EffectAttack::setDuration(int newduration) { duration = newduration; }
void EffectAttack::addDuration(int addDuration) { duration += addDuration; }
bool EffectAttack::isExpired() const { return duration == 0; }

int EffectAttack::getAppliedValue(int value_to_apply_to) const
{
	if (type == EffectType::POISON)
		return attribute;

	int applied_val = value_to_apply_to * attribute / 100.0;

	if (applied_val < minApplied) {
		applied_val = minApplied;
	}

	return applied_val;
}


void EffectAttack::upgrade()
{
	if (level == 3)
		return;

	switch (level) {
	case 0: // 0 -> 1 (first time installing)
		switch (type) {
		case EffectType::POISON:
			attribute = 5;
			minApplied = 0;
			break;
		case EffectType::SLOWNESS:
			attribute = 10; // percentage
			minApplied = 0;
			break;
		case EffectType::WEAKNESS:
			attribute = 15; // percentage
			minApplied = 0;
			break;
		}

		duration = 4;
		break;

	case 1: // 1 -> 2
		switch (type) {
		case EffectType::POISON:
			attribute = 8;
			minApplied = 0;
			break;
		case EffectType::SLOWNESS:
			attribute = 20; // percentage
			minApplied = 0;
			break;
		case EffectType::WEAKNESS:
			attribute = 25; // percentage
			minApplied = 10;
			break;
		}

		duration = 6;
		break;

	case 2: // 2 -> 3
		switch (type) {
		case EffectType::POISON:
			attribute = 14;
			minApplied = 0;
			break;
		case EffectType::SLOWNESS:
			attribute = 50; // percentage
			minApplied = 1;
			break;
		case EffectType::WEAKNESS:
			attribute = 50; // percentage
			minApplied = 25;
			break;
		}

		duration = 3;
		break;
	}

	++level;
}


bool EffectAttack::operator == (const EffectAttack& other) const
{
	return (type == other.type) && (level == other.level) && (attribute == other.attribute) && 
		(minApplied == other.minApplied) && (duration == other.duration);
}
