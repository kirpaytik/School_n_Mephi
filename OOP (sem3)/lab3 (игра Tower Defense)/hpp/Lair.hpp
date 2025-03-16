#ifndef LAIR_HPP
#define LAIR_HPP

#include "Enemy.hpp"

#include "../interfaces/IControlSpawns.hpp"

#include <string>
#include <unordered_map>

#ifndef ENEMYTYPE
#define ENEMYTYPE
enum class EnemyType {
	NORMAL, FAST, TANK, CUSTOM
};
#endif

struct EnemyParams {
	int maxhealth;
	int speed;
	int gold;
};

class Lair : public IControlSpawns
{
private:
	std::string name;
	std::vector<std::pair<Enemy*, int>> enemies; // enemy and its time until spawn
	int maxenemies;

	std::unordered_map<EnemyType, EnemyParams> enemyParams;

public:
	Lair(const std::string& name, std::vector<std::pair<Enemy*, int>>& enemies);
	Lair(const std::string& name, const std::vector<std::pair<EnemyType, int>>& enemies);
	Lair(const std::string& name, int numEnemies);
	Enemy* generateEnemy(EnemyType type);
	~Lair();

	std::string getName() const;
	Enemy* getEnemy() const;
	int getSpawnTime() const;
	int getNumberOfEnemiesLeft() const;
	int getMaxEnemies() const;

	static EnemyType stringToEnemyType(const std::string& type);

	// IControlSpawns
	void spawnTimeProcess() override;
	Enemy* spawnEnemy() override;
};

#endif
