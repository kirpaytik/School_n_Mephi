#include "../hpp/Castle.hpp"


Castle::Castle(const std::string& name, int maxhealth) :
	name(name), maxhealth(maxhealth), currhealth(maxhealth), gold(0) {}

Castle::Castle(const std::string& name, int maxhealth, int gold) :
	name(name), maxhealth(maxhealth), currhealth(maxhealth), gold(gold) {}


std::string Castle::getName() const { return name; }
int Castle::getMaxHealth() const { return maxhealth; }
int Castle::getCurrentHealth() const { return currhealth; }
int Castle::getGold() const { return gold; }

void Castle::addGold(int amount) { gold += amount; }
void Castle::reduceGold(int amount) { gold -= amount; }

// IDamagable
int Castle::damageTaken(int damage) const { return damage > currhealth ? currhealth : damage; }
void Castle::setHealth(int health) { currhealth = health > maxhealth ? maxhealth : (health > 0 ? health : 0); }
bool Castle::isAlive() const { return currhealth > 0; }
