#include "../mvc/Game.hpp"
#include <iostream>


void doPreGameStuff(Game& game);
void buildSomeTowers(Game& game, std::vector<Field*> fields);
void buildSomeTraps(Game& game, std::vector<Road*> roads);
void upgradeSomeBuilds(Game& game, std::vector<Field*> fields, std::vector<Road*> roads);


int main()
{
	Game game;

	std::ifstream levelFile("myland.txt");
	if (!levelFile.is_open()) {
		std::cerr << "No level flle?" << std::endl;
		return -1;
	}
	bool is_ok = game.initializeGame(levelFile);
	levelFile.close();
	if (!is_ok) {
		std::cout << "Something's not good wonk-wonk" << std::endl;
		return -1;
	}

	// initialize it so the table for prices now exists
	PriceTable::instance();

	doPreGameStuff(game);

	int clk = 0;

	while (!game.isGameOver()) {
		std::cout << "hii clk: --------------------------------------------------------------------" << clk << std::endl;

		if (clk % 20 == 0) {
			buildSomeTraps(game, game.getLandscape()->getRoads());
		}
		game.update();
		++clk;

		if (game.isGameOver()) {
			std::cout << "game...over? " << game.isGameOver() << std::endl;

			if (game.isGameOver() == -1) {
				std::cout << "Yooooouuuuuu Loooooooost!" << std::endl;
			} else if (game.isGameOver() == 1) {
				std::cout << "Congratulations! Youve Won!" << std::endl;
			}

			break;
		}
	}

	return 0;
}


void doPreGameStuff(Game& game)
{
	buildSomeTowers(game, game.getLandscape()->getFields());

	buildSomeTraps(game, game.getLandscape()->getRoads());

	upgradeSomeBuilds(game, game.getLandscape()->getFields(), game.getLandscape()->getRoads());
}


void buildSomeTowers(Game& game, std::vector<Field*> fields)
{
	for (Field* field : fields) {
		int x = field->getX();
		int y = field->getY();

		// для тестов для графика сравнения однопотока с многопотоком
		// if (y > 9 || x > 20 || x % 2 || c == 50)
		// if (y > 19 || x > 20 || x % 2 || c == 100)
		// if (y > 29 || x > 20 || x % 2 || c == 150)
		// if (y > 39 || x > 20 || x % 2 || c == 200)
		// if (y > 49 || x > 20 || x % 2 || c == 250)
		// if (y > 29 || x > 40 || x % 2 || c == 300)
		// if (y > 39 || x > 40 || x % 2 || c == 400)
		// if (y > 49 || x > 40 || x % 2 || c == 500)
		// if (y > 29 || x > 40 || c == 600)
		// if (y > 39 || x > 40 || c == 800)
		// if (y > 49 || x > 40 || c == 1000)
		//	continue;

		// строим башню с шаном 25%
		if (rand() % 4)
			continue;

		PriceBuildKey key;
		key.type = static_cast<BuildType>(rand() % 2);
		key.strat = static_cast<AttackStrategy>(rand() % 5);
		key.effect = static_cast<EffectType>(rand() % 3);
		key.level = rand() % 3 + 1;

		if (!game.canBuildHere(x, y)) {
			std::cout << "Cannot build anything at (" << x << ", " << y << ")" << std::endl;
			continue;
		}

		if (!game.canBuildHere(x, y, key.type)) {
			std::cout << "Cannot build specific build at (" << x << ", " << y << ")" << std::endl;
			continue;
		}

		int cost = PriceTable::getBuildCost(key);
		if (game.isEnoughGold(cost)) {
			std::cout << "Not enough gold! So adding the needed amount of gold..." << std::endl;
			game.getLandscape()->getCastle()->addGold(cost);
		}

		game.buildDefBuild(x, y, key);
	}
}


void buildSomeTraps(Game& game, std::vector<Road*> roads)
{
	for (Road* road : roads) {
		// строим ловушку с шаном 50%
		if (rand() % 2)
			continue;

		int x = road->getX();
		int y = road->getY();

		PriceBuildKey key;
		key.type = BuildType::MAGICTRAP;
		key.strat = static_cast<AttackStrategy>(rand() % 5);
		key.effect = static_cast<EffectType>(rand() % 3);
		key.level = rand() % 3 + 1;

		if (!game.canBuildHere(x, y)) {
			std::cout << "Cannot build anything at (" << x << ", " << y << ")" << std::endl;
			continue;
		}

		if (!game.canBuildHere(x, y, key.type)) {
			std::cout << "Cannot build specific build at (" << x << ", " << y << ")" << std::endl;
			continue;
		}

		int cost = PriceTable::getBuildCost(key);
		if (game.isEnoughGold(cost)) {
			std::cout << "Not enough gold! So adding the needed amount of gold..." << std::endl;
			game.getLandscape()->getCastle()->addGold(cost);
		}

		game.buildDefBuild(x, y, key);
	}
}


void upgradeSomeBuilds(Game& game, std::vector<Field*> fields, std::vector<Road*> roads)
{
	for (Field* field : fields) {
		// улучшаем с шаном 25%
		if (rand() % 4)
			continue;

		int x = field->getX();
		int y = field->getY();

		PriceBuildKey key;
		key.type = static_cast<BuildType>(rand() % 2);
		key.strat = static_cast<AttackStrategy>(rand() % 5);
		key.effect = static_cast<EffectType>(rand() % 3);
		key.level = rand() % 3 + 1;

		if (!game.canUpgradeHere(x, y)) {
			std::cout << "Cannot upgrade anything at (" << x << ", " << y << ")" << std::endl;
			continue;
		}

		int cost = game.getUpgradeCost(x, y);
		if (game.isEnoughGold(cost)) {
			std::cout << "Not enough gold! So adding the needed amount of gold..." << std::endl;
			game.getLandscape()->getCastle()->addGold(cost);
		}

		game.upgradeDefBuild(x, y, cost);
	}

	for (Road* road : roads) {
		// улучшаем с шаном 25%
		if (rand() % 4)
			continue;

		int x = road->getX();
		int y = road->getY();

		PriceBuildKey key;
		key.type = BuildType::MAGICTRAP;
		key.strat = static_cast<AttackStrategy>(rand() % 5);
		key.effect = static_cast<EffectType>(rand() % 3);
		key.level = rand() % 3 + 1;

		if (!game.canUpgradeHere(x, y)) {
			std::cout << "Cannot upgrade anything at (" << x << ", " << y << ")" << std::endl;
			continue;
		}

		int cost = game.getUpgradeCost(x, y);
		if (game.isEnoughGold(cost)) {
			std::cout << "Not enough gold! So adding the needed amount of gold..." << std::endl;
			game.getLandscape()->getCastle()->addGold(cost);
		}

		game.upgradeDefBuild(x, y, cost);
	}
}
