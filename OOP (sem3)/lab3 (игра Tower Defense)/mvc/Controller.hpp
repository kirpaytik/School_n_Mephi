#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

class Game;
class View;

#include <SFML/Graphics.hpp>
#include <utility>


class Controller
{
public:
	Controller(Game* game, View* view, sf::View* gameView);

	bool handleUserInput();

	void updateUI();
	void updateGameView();

private:
	Game* game;
	View* view;
	sf::View* gameView;

	std::pair<int, int> selectedCell; // (-1, -1) if none
	int selectedType; // -1 if none
	int selectedEffect; // -1 if none
	int selectedLevel; // -1 if none
	int selectedStrategy; // -1 if none


	void handleCellSelection(const std::pair<int, int>& clickedCell);
	void handleTypeEffectSelection(int button);
	void handleLevelSelection(int button);
	void handleStrategySelection(int button);
	void handleUpgrade();
	void resetSelections();

	int calculateMainButtonByTypeAndEffect() const;
};

#endif
