#include "../mvc/Controller.hpp"
#include "../mvc/View.hpp"
#include "../mvc/Game.hpp"
#include "../hpp/PriceTable.hpp"
#include <SFML/Window/Event.hpp>

#include <iostream>
#include <utility>


Controller::Controller(Game* game, View* view, sf::View* gameView) :
	game(game), view(view), gameView(gameView),
	selectedCell(-1, -1), selectedType(-1), selectedEffect(-1), selectedLevel(-1), selectedStrategy(-1) {}


bool Controller::handleUserInput()
{
	sf::Event event;
	while (view->getWindow()->pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			view->getWindow()->close();
			return false;
		}

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			std::pair<int, int> clickedCell = view->getClickedCell(event.mouseButton.x, event.mouseButton.y, *gameView);

			// cell is clicked
			if (clickedCell.first > -1) {
				handleCellSelection(clickedCell);
				continue;
			}

			// menu is clicked
			int clickedButton = view->getClickedButton(event.mouseButton.x, event.mouseButton.y);
			if (clickedButton > -1) {
				// upgrade menu is clicked
				if (game->canUpgradeHere(selectedCell.first, selectedCell.second) && clickedButton == 8) {
					handleUpgrade();
					continue;
				}

				// main menu is clicked
				if (selectedType == -1) {
					handleTypeEffectSelection(clickedButton);
				} else if (selectedLevel == -1) {
					handleLevelSelection(clickedButton);
				} else {
					handleStrategySelection(clickedButton);
				}
				continue;
			}
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				if (selectedType == -1) {
					selectedCell = {-1, -1};
				} else {
					resetSelections();
				}
				continue;
			}

			if (game->canUpgradeHere(selectedCell.first, selectedCell.second) && event.key.code == sf::Keyboard::Num1) {
				handleUpgrade();
				continue;
			}

			if (selectedCell.first > -1) {
				if (selectedType == -1) {
					handleTypeEffectSelection(event.key.code - sf::Keyboard::Num1 + 1);
					continue;
				}

				if (selectedLevel == -1) {
					handleLevelSelection(event.key.code - sf::Keyboard::Num1 + 9);
					continue;
				}

				if (selectedStrategy == -1) {
					handleStrategySelection(event.key.code - sf::Keyboard::Num1 + 12);
					continue;
				}
			}

			if (event.key.code == sf::Keyboard::Left) {
				gameView->move(-10.f, 0.f);
			}
			else if (event.key.code == sf::Keyboard::Right) {
				gameView->move(10.f, 0.f);
			}
			else if (event.key.code == sf::Keyboard::Up) {
				gameView->move(0.f, -10.f);
			}
			else if (event.key.code == sf::Keyboard::Down) {
				gameView->move(0.f, 10.f);
			}
			else if (event.key.code == sf::Keyboard::A) {
				gameView->move(-25.f, 0.f);
			}
			else if (event.key.code == sf::Keyboard::D) {
				gameView->move(25.f, 0.f);
			}
			else if (event.key.code == sf::Keyboard::W) {
				gameView->move(0.f, -25.f);
			}
			else if (event.key.code == sf::Keyboard::S) {
				gameView->move(0.f, 25.f);
			}
		}
	}

	return true;
}


void Controller::handleCellSelection(const std::pair<int, int>& clickedCell)
{
	if (selectedCell == clickedCell) {
		selectedCell = {-1, -1};
	}
	else if (game->canBuildHere(clickedCell.first, clickedCell.second) || game->isDefBuildHere(clickedCell.first, clickedCell.second)) {
		selectedCell = clickedCell;
	} else {
		selectedCell = {-1, -1};
	}

	resetSelections();
}


void Controller::handleTypeEffectSelection(int button)
{
	if (button == 1) {
		if (game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::TOWER)) {
			selectedType = static_cast<int>(BuildType::TOWER);
			selectedEffect = static_cast<int>(EffectType::POISON); // Default effect for TOWER
		}
	}
	else if (button >= 2 && button <= 4) {
		if (game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::MAGICTOWER)) {
			selectedType = static_cast<int>(BuildType::MAGICTOWER);
			selectedEffect = button - 2; // Map button 2-4 to POISON, SLOWNESS, WEAKNESS
		}
	}
	else if (button >= 5 && button <= 7) {
		if (game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::MAGICTRAP)) {
			selectedType = static_cast<int>(BuildType::MAGICTRAP);
			selectedEffect = button - 5; // Map button 5-7 to POISON, SLOWNESS, WEAKNESS
		}
	}
}


void Controller::handleLevelSelection(int button)
{
	if (button >= 9 && button <= 11) {
		int cost = PriceTable::getBuildCost(static_cast<BuildType>(selectedType),
						static_cast<AttackStrategy>(0), static_cast<EffectType>(selectedEffect), button - 9 + 1);

		if (game->isEnoughGold(cost)) {
			selectedLevel = button - 9 + 1;
		} else {
			std::cout << "Not enough gold to purchase:(" << std::endl;
		}
	}
}


void Controller::handleStrategySelection(int button)
{
	if (button >= 12 && button <= 16) {
		selectedStrategy = button - 12;
		PriceBuildKey key{static_cast<BuildType>(selectedType), static_cast<AttackStrategy>(selectedStrategy),
						  static_cast<EffectType>(selectedEffect), selectedLevel};
		game->buildDefBuild(selectedCell.first, selectedCell.second, key);
		resetSelections();
		selectedCell = {-1, -1};
	}
}


void Controller::handleUpgrade()
{
	int cost = game->getUpgradeCost(selectedCell.first, selectedCell.second);
	if (game->isEnoughGold(cost)) {
		game->upgradeDefBuild(selectedCell.first, selectedCell.second, cost);
	} else {
		std::cout << "Not enough gold to upgrade:(" << std::endl;
	}
}


void Controller::resetSelections()
{
	selectedType = -1;
	selectedEffect = -1;
	selectedLevel = -1;
	selectedStrategy = -1;
}


int Controller::calculateMainButtonByTypeAndEffect() const
	{ return selectedType == 0 ? 1 : ((selectedType - 1) * 3 + selectedEffect + 2); }


void Controller::updateUI()
{
	view->clearUILayer();
	view->highlightSelectedCell(selectedCell, *gameView);
	// if cell is not selected then build menu is gray
	if (selectedCell.first == -1) {
		view->showMenu(false); // is on screen but gray
		return;
	}
	view->showMenu(true);

	// if a build is on the selected cell
	if (game->isDefBuildHere(selectedCell.first, selectedCell.second)) {
		view->showSecondMenu();

		// if can upgrade then second menu is coloured, gray otherwise
		if (game->canUpgradeHere(selectedCell.first, selectedCell.second)) {
			view->setButtonState(1, true);
		} else {
			view->setButtonState(1, false);
		}
		return;
	}

	// no build on the selected cell
	view->showBuildMenu();

	view->setButtonState(1, game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::TOWER));
	view->setButtonState(2, game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::MAGICTOWER));
	view->setButtonState(3, game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::MAGICTOWER));
	view->setButtonState(4, game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::MAGICTOWER));
	view->setButtonState(5, game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::MAGICTRAP));
	view->setButtonState(6, game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::MAGICTRAP));
	view->setButtonState(7, game->canBuildHere(selectedCell.first, selectedCell.second, BuildType::MAGICTRAP));

	if (selectedType > -1) {
		if (selectedLevel == -1) {
			// std::cout << "LESSGOOOLEVEL" << std::endl;
			// std::cout << "button is " << selectedType <<  " " << selectedEffect << std::endl;
			// std::cout << "button is " << calculateMainButtonByTypeAndEffect() << std::endl;
			view->showLevelList(calculateMainButtonByTypeAndEffect());
		} else {
			// std::cout << "-----------strat" << std::endl;
			view->showStratList(calculateMainButtonByTypeAndEffect());
		}
	}
}


void Controller::updateGameView()
{
	Landscape* land = game->getLandscape();

	view->clearGameLayer();
	view->drawBackground();

	// Fields n Roads
	std::vector<Field*> fields = land->getFields();
	std::vector<Road*> roads = land->getRoads();

	std::vector<std::pair<int, int>> fields_int;
	std::vector<std::pair<int, int>> roads_int;

	for (Field* field : fields) {
		fields_int.push_back(std::make_pair(field->getX(), field->getY()));
	}
	for (Road* road : roads) {
		roads_int.push_back(std::make_pair(road->getX(), road->getY()));
	}

	view->drawFields(fields_int);
	view->drawRoads(roads_int);

	// Castle n Lairs
	int castleX = land->getCastleX();
	int castleY = land->getCastleY();
	view->drawCastle(castleX, castleY);

	std::vector<std::pair<int, int>> lairs;
	for (const std::tuple<Lair*, int, int>& lair : land->getLairs()) {
		lairs.push_back(std::make_pair(std::get<1>(lair), std::get<2>(lair)));
	}
	view->drawLairs(lairs);

	// DefBuilds
	std::vector<std::tuple<int, int, BuildType, EffectType>> builds;
	for (Field* field : fields) {
		DefBuild* defbuild = land->getBuild(field->getX(), field->getY());
		if (defbuild) {
			builds.push_back(std::tuple(field->getX(), field->getY(), defbuild->getType(), defbuild->getEffect()));
		}
	}
	for (Road* road : roads) {
		DefBuild* defbuild = land->getBuild(road->getX(), road->getY());
		if (defbuild) {
			builds.push_back(std::tuple(road->getX(), road->getY(), defbuild->getType(), defbuild->getEffect()));
		}
	}
	view->drawBuilds(builds);

	// Enemies
	std::vector<std::tuple<int, int, EnemyType>> enemies;
	for (Road* road : roads) {
		Enemy* enemy = road->getEnemy();
		if (enemy) {
			enemies.push_back(std::tuple(road->getX(), road->getY(), enemy->getType()));
		}
	}
	view->drawEnemies(enemies);

	// only after objets but before UI
	view->drawGrid();

	// Castle's info update
	int gold = land->getCastle()->getGold();
	int castleHealth = land->getCastle()->getCurrentHealth();
	int maxHealth = land->getCastle()->getMaxHealth();
	view->updateCastleInfo(castleX, castleY, gold, castleHealth, maxHealth);

	// Lair's info update
	for (const std::tuple<Lair*, int, int>& lair : land->getLairs()) {
		int amount = std::get<0>(lair)->getNumberOfEnemiesLeft();
		int maxAmount = std::get<0>(lair)->getMaxEnemies();
		view->updateLairsInfo(std::get<1>(lair), std::get<2>(lair), amount, maxAmount);
	}

	// Enemies' info update
	for (Road* road : roads) {
		Enemy* enemy = road->getEnemy();
		if (enemy) {
			std::vector<EffectType> effectTypes;
			std::vector<EffectAttack*> effects = enemy->getEffects();
			std::transform(effects.begin(), effects.end(), std::back_inserter(effectTypes),
						   [](EffectAttack* effect) { return effect->getType(); });

			for (int i = 0; i < effects.size(); ++i) {
			}

			view->updateEnemyInfo(road->getX(), road->getY(), enemy->getHealth(), enemy->getMaxHealth(), effectTypes);
		}
	}

	// Builds' info update
	for (Field* field : fields) {
		DefBuild* defbuild = land->getBuild(field->getX(), field->getY());
		if (defbuild) {
			view->updateBuildInfo(field->getX(), field->getY(), defbuild->getLevel());
		}
	}
	for (Road* road : roads) {
		DefBuild* defbuild = land->getBuild(road->getX(), road->getY());
		if (defbuild) {
			view->updateBuildInfo(road->getX(), road->getY(), defbuild->getLevel());
		}
	}
}
