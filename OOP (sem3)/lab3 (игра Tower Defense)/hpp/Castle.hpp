#ifndef CASTLE_HPP
#define CASTLE_HPP

#include "../interfaces/IDamagable.hpp"

#include <string>

class Castle : public IDamagable
{
private:
	std::string name;
	int maxhealth;
	int currhealth;
	int gold;

public:
	Castle(const std::string& name, int maxhealth);
	Castle(const std::string& name, int maxhealth, int gold);

	std::string getName() const;
	int getMaxHealth() const;
	int getCurrentHealth() const;
	int getGold() const;
	
	void addGold(int amount);
	void reduceGold(int amount);

	// IDamagable
	int damageTaken(int damage) const override;
	void setHealth(int health) override;
	bool isAlive() const override;
};

#endif
