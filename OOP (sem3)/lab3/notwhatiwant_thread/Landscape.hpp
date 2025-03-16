#ifndef LANDSCAPE_HPP
#define LANDSCAPE_HPP

#include "Castle.hpp"
#include "Lair.hpp"
#include "Road.hpp"
#include "Field.hpp"
#include "Enemy.hpp"
#include "DefBuild.hpp"
#include "BuildAttack.hpp"

#include "../interfaces/IControlSpawns.hpp"
#include "../interfaces/IControlLives.hpp"
#include "../interfaces/IControlBuildAttacks.hpp"


class Landscape : public IControlSpawns, public IControlLives, public IControlBuildAttacks
{
private:
	int width;
	int height;
	std::tuple<Castle*, int, int> castle;
	std::vector<std::tuple<Lair*, int, int>> lairs;
	std::vector<Field*> fields;
	std::vector<Road*> roads;

public:
	Landscape();
	Landscape(int width, int height, std::tuple<Castle*, int, int> castle,
		std::vector<std::tuple<Lair*, int, int>> lairs, std::vector<Field*> fields, std::vector<Road*> roads);
	~Landscape();

	int getWidth() const;
	int getHeight() const;
	Castle* getCastle() const;
	int getCastleX() const;
	int getCastleY() const;
	Lair* getLair(int indx) const;
	std::vector<std::tuple<Lair*, int, int>> getLairs() const;
	bool areEnemiesLeft() const;
	std::vector<Field*> getFields() const;
	std::vector<Road*> getRoads() const;

	Field* getField(int indx) const;
	Field* getField(int x, int y) const;
	Field* getField(const DefBuild* defbuild) const;
	Road* getRoad(int indx) const;
	Road* getRoad(int x, int y) const;
	Road* getEmptyRoad(std::tuple<Lair*, int, int> lairTuple) const;
	Road* getRoad(const Enemy* enemy) const;
	Road* getRoad(const MagicTrap* mtrap) const;
	DefBuild* getBuild(int x, int y) const;
	// void setDefBuild(DefBuild* defbuild);

	// std::pair<int, int> getCoord(DefBuild* defbuild) const;

	// IControlSpawns
	void spawnTimeProcess() override;
	Enemy* spawnEnemy() override;

	void spawnEnemyAtLair(std::tuple<Lair*, int, int> lairTuple);

	// IControlLives
	bool moveEnemy(Enemy* enemy, int move_dist) override;  // needs to be called even if moveDist == 0 cuz of reasons inside it
	int checkMoveDistance(Enemy* enemy) const override;
	void dealDamage(Enemy* enemy, BuildAttack* battack) override;
	void killEnemy(Enemy* enemy) override;

	bool isCastleReached(Enemy* enemy) const;
	void activateTrapIfEnemy(Road* road);

	// IControlBuildAttacks
	void attack(DefBuild* defbuild) override;
	Enemy* attack_strategy(DefBuild* defbuild) const override;
	void processBuildsReadiness() override;

	Enemy* attack_nearest_to_tower(DefBuild* defbuild) const;
	Enemy* attack_furthest_from_tower(DefBuild* defbuild) const;
	Enemy* attack_nearest_to_castle(DefBuild* defbuild) const;
	Enemy* attack_lowest_hp(DefBuild* defbuild) const;
	Enemy* attack_highest_hp(DefBuild* defbuild) const;


	static float calculateDistance(int x1, int y1, int x2, int y2);
};

#endif
