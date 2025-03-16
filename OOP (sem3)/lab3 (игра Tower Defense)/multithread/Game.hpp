#ifndef GAME_HPP
#define GAME_HPP

#include "../hpp/Landscape.hpp"
#include "../hpp/PriceTable.hpp"

#include "../interfaces/IGameControl.hpp"
// #include "IControlBuilding.hpp"

#include <fstream>


enum class GameStatus { WIN, RUNNING, LOSS };

class Game : public IGameControl
// , public IControlBuilding
{
private:
	Landscape* land;
	GameStatus status;

public:
	Game();
	~Game();

	Landscape* getLandscape() const;
	
	Landscape* parseLandscape(std::ifstream& file) const;
	Castle* parseCastle(std::ifstream& file) const;
	Lair* parseLair(std::ifstream& file) const;
	void connectRoads();

	// IGameControl
	bool initializeGame(std::ifstream& file) override;
	bool checkGameLevel() const override;
	void checkGameStatus() override;
	int isGameOver() override;
	void update() override;

	void moveEnemies();
	void enemiesProcessEffects();
	void attackDefBuilds();
	void killCorpses();
	bool killIfCorpse(Enemy* enemy);
	bool isCorpse(Enemy* enemy);

	// IControlBuilding
	bool canBuildHere(int x, int y) const;
	bool canBuildHere(int x, int y, BuildType type) const;
	bool isDefBuildHere(int x, int y) const;
	bool isEnoughGold(int cost) const;
	void buildDefBuild(int x, int y, PriceBuildKey key);

	bool canUpgradeHere(int x, int y) const;
	int getUpgradeCost(int x, int y) const;
	void upgradeDefBuild(int x, int y, int cost);
};

#endif
