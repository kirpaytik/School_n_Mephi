#include "../mvc/View.hpp"

#include <cmath>

#include <iostream>


View::View(sf::RenderWindow& win, int width, int height) : window(win), uiView(sf::FloatRect(0, 0, win.getSize().x, win.getSize().y))
{
	font.loadFromFile("res/font.ttf");

	gameRenderTexture.create(width * 50 + 100, height * 50 + 150);
	uiRenderTexture.create(width * 50 + 100, height * 50 + 150);

	gameRenderSprite.setTexture(gameRenderTexture.getTexture());
	uiRenderSprite.setTexture(uiRenderTexture.getTexture());

	loadTextures();
	initializeSprites();

	cellSize = 50;

	gridOffset = {50, 50};
	menuPosition = {0, 500};
	levelListPosition = {-1, -1};
	stratListPosition = {-1, -1};
}


void View::loadTextures()
{
	roadTexture.loadFromFile("res/road.png");
	fieldTexture.loadFromFile("res/field.png");
	lairTexture.loadFromFile("res/lair.png");
	castleTexture.loadFromFile("res/castle.png");

	for (int i = 0; i < 3; ++i)
		enemyTextures[i].loadFromFile("res/enemy" + std::to_string(i + 1) + ".png");
	for (int i = 0; i < 7; ++i)
		buildTextures[i].loadFromFile("res/build" + std::to_string(i + 1) + ".png");

	menuTexture.loadFromFile("res/menu.png");
	for (int i = 0; i < 7; ++i)
		buildButtonTextures[i].loadFromFile("res/buildButton" + std::to_string(i + 1) + ".png");
	upgradeButtonTexture.loadFromFile("res/upgradeButton.png");
	
	for (int i = 0; i < 3; ++i) {
		levelButtonTextures[i].loadFromFile("res/levelButton" + std::to_string(i + 1) + ".png");
	}

	for (int i = 0; i < 5; ++i) {
		stratButtonTextures[i].loadFromFile("res/stratButton" + std::to_string(i + 1) + ".png");
	}

	goldIconTexture.loadFromFile("res/goldIcon.png");
	levelIconTexture.loadFromFile("res/levelIcon.png");



	levelListTexture.loadFromFile("res/levelList.png");
	stratListTexture.loadFromFile("res/stratList.png");
}


void View::initializeSprites()
{
	roadSprite.setTexture(roadTexture);
	fieldSprite.setTexture(fieldTexture);
	lairSprite.setTexture(lairTexture);
	castleSprite.setTexture(castleTexture);

	for (int i = 0; i < 3; ++i) {
		enemySprites[i].setTexture(enemyTextures[i]);
	}
	for (int i = 0; i < 7; ++i) {
		buildSprites[i].setTexture(buildTextures[i]);
	}

	mainMenuSprite.setTexture(menuTexture);
	levelListSprite.setTexture(levelListTexture);
	stratListSprite.setTexture(stratListTexture);
	for (int i = 0; i < 7; ++i) {
		buildButtonSprites[i].setTexture(buildButtonTextures[i]);
	}
	upgradeButtonSprite.setTexture(upgradeButtonTexture);
	for (int i = 0; i < 3; ++i) {
		levelButtonSprites[i].setTexture(levelButtonTextures[i]);
	}
	for (int i = 0; i < 5; ++i) {
		stratButtonSprites[i].setTexture(stratButtonTextures[i]);
	}

	goldIconSprite.setTexture(goldIconTexture);
	levelIconSprite.setTexture(levelIconTexture);
}


void View::clearGameLayer()
	{ gameRenderTexture.clear(sf::Color::Transparent); }


void View::clearUILayer()
{
	uiRenderTexture.clear(sf::Color::Transparent);

	// set UI elements out of the window's bounds so that they wouldn't be invisible but still on screen
	mainMenuSprite.setPosition(0 - mainMenuSprite.getGlobalBounds().width, 0 - mainMenuSprite.getGlobalBounds().height);
	levelListSprite.setPosition(0 - levelListSprite.getGlobalBounds().width, 0 - levelListSprite.getGlobalBounds().height);
	stratListSprite.setPosition(0 - stratListSprite.getGlobalBounds().width, 0 - stratListSprite.getGlobalBounds().height);

	for (int i = 0; i < 7; ++i) {
		buildButtonSprites[i].setPosition(0 - buildButtonSprites[i].getGlobalBounds().width, 0 - buildButtonSprites[i].getGlobalBounds().height);
	}
	upgradeButtonSprite.setPosition(0 - upgradeButtonSprite.getGlobalBounds().width, 0 - upgradeButtonSprite.getGlobalBounds().height);

	for (int i = 0; i < 3; ++i) {
		levelButtonSprites[i].setPosition(0 - levelButtonSprites[i].getGlobalBounds().width, 0 - levelButtonSprites[i].getGlobalBounds().height);
	}
	for (int i = 0; i < 5; ++i) {
		stratButtonSprites[i].setPosition(0 - stratButtonSprites[i].getGlobalBounds().width, 0 - stratButtonSprites[i].getGlobalBounds().height);
	}
}


void View::display(sf::View& gameView)
{
	gameRenderTexture.display();
	uiRenderTexture.display();

	window.clear(sf::Color::White);

	window.setView(gameView);
	window.draw(gameRenderSprite);
	window.setView(uiView);
	window.draw(uiRenderSprite);

	window.display();
}


std::pair<int, int> View::getClickedCell(int x, int y, sf::View& gameView) const
{
	sf::Vector2f worldCoords = window.mapPixelToCoords(sf::Vector2i(x, y), gameView);

	if (getClickedButton(x, y) > -1)
		return {-1, -1};

	int adjustedX = worldCoords.x - gridOffset.x;
	int adjustedY = worldCoords.y - gridOffset.y;
	if (adjustedX < 0 || adjustedY < 0)
		return {-1, -1};

	return {adjustedX / cellSize, adjustedY / cellSize};
}


int View::getClickedButton(int x, int y) const
{
	for (int i = 0; i < 7; ++i) {
		if (buildButtonSprites[i].getGlobalBounds().contains(x, y))
			return i + 1;
	}

	if (upgradeButtonSprite.getGlobalBounds().contains(x, y))
		return 8;

	for (int i = 0; i < 3; ++i) {
		if (levelButtonSprites[i].getGlobalBounds().contains(x, y))
			return 9 + i;
	}

	for (int i = 0; i < 5; ++i) {
		if (stratButtonSprites[i].getGlobalBounds().contains(x, y))
			return 12 + i;
	}

	return -1;
}



void View::drawBackground() { gameRenderTexture.clear(sf::Color::Blue); }


void View::drawGrid()
{
	sf::RectangleShape line(sf::Vector2f(1, gameRenderTexture.getSize().y));
	line.setFillColor(sf::Color::Black);

	for (int x = gridOffset.x; x < gameRenderTexture.getSize().x; x += 50) {
		line.setPosition((float)(x), 0);
		gameRenderTexture.draw(line);
	}

	line.setSize(sf::Vector2f(gameRenderTexture.getSize().x, 1));
	for (int y = gridOffset.y; y < gameRenderTexture.getSize().y; y += 50) {
		line.setPosition(0, (float)(y));
		gameRenderTexture.draw(line);
	}
}


void View::drawFields(const std::vector<std::pair<int, int>>& fields)
{
	for (const std::pair<int, int>& field : fields) {
		fieldSprite.setPosition(gridOffset.x + field.first * 50.f, gridOffset.y + field.second * 50.f);
		gameRenderTexture.draw(fieldSprite);
	}
}


void View::drawRoads(const std::vector<std::pair<int, int>>& roads)
{
	for (const std::pair<int, int>& road : roads) {
		roadSprite.setPosition(gridOffset.x + road.first * 50.f, gridOffset.y + road.second * 50.f);
		gameRenderTexture.draw(roadSprite);
	}
}


void View::drawCastle(int castleX, int castleY)
{
	castleSprite.setPosition(gridOffset.x + castleX * 50.f, gridOffset.y + castleY * 50.f);
	gameRenderTexture.draw(castleSprite);
}


void View::drawLairs(const std::vector<std::pair<int, int>>& lairs)
{
	for (const std::pair<int, int>& lair : lairs) {
		lairSprite.setPosition(gridOffset.x + lair.first * 50.f, gridOffset.y + lair.second * 50.f);
		gameRenderTexture.draw(lairSprite);
	}
}


void View::drawBuilds(const std::vector<std::tuple<int, int, BuildType, EffectType>>& builds)
{
	for (const std::tuple<int, int, BuildType, EffectType>& build : builds) {
		int buildX = std::get<0>(build);
		int buildY = std::get<1>(build);
		int type = static_cast<int>(std::get<2>(build));
		int effect = static_cast<int>(std::get<3>(build));

		int texture = type == 0 ? 0 : ((type - 1) * 3 + effect + 1);

		buildSprites[texture].setPosition(gridOffset.x + buildX * 50.f, gridOffset.y + buildY * 50.f);
		gameRenderTexture.draw(buildSprites[texture]);
	}
}


void View::drawEnemies(const std::vector<std::tuple<int, int, EnemyType>>& enemies)
{
	for (const std::tuple<int, int, EnemyType>& enemy : enemies) {
		int enemyX = std::get<0>(enemy);
		int enemyY = std::get<1>(enemy);
		int type = static_cast<int>(std::get<2>(enemy));

		enemySprites[type].setPosition(gridOffset.x + enemyX * 50.f, gridOffset.y + enemyY * 50.f);
		gameRenderTexture.draw(enemySprites[type]);
	}
}


void View::showMenu(bool isColored)
{
	sf::Sprite menuSprite = mainMenuSprite;
	menuSprite.setColor(isColored ? sf::Color::White : sf::Color::Black);
	menuSprite.setPosition(menuPosition);

	uiRenderTexture.draw(menuSprite);
}


void View::showBuildMenu()
{
	// float buttonSpacing = buildButtonTextures[0].getSize().x * buildButtonSprites[0].getScale().x;
	for (int i = 0; i < 7; ++i) {
		buildButtonSprites[i].setPosition(menuPosition.x + i * 100.f, menuPosition.y);
		uiRenderTexture.draw(buildButtonSprites[i]);
	}
}


void View::showSecondMenu()
{
	upgradeButtonSprite.setPosition(menuPosition.x, menuPosition.y);
	uiRenderTexture.draw(upgradeButtonSprite);
}


void View::showLevelList(int button)
{
	for (int i = 0; i < 3; ++i) {
		// cuz 1-3 from top to bottom
		levelButtonSprites[2 - i].setPosition(menuPosition.x + 100.f * (button - 1), menuPosition.y - (i + 1) * 50.f);

		uiRenderTexture.draw(levelButtonSprites[2 - i]);
	}
}


void View::showStratList(int button)
{
	for (int i = 0; i < 5; ++i) {
		// bcs from top to bottom
		stratButtonSprites[4 - i].setPosition(menuPosition.x + 100.f * (button - 1), menuPosition.y - (i + 1) * 50.f);

		uiRenderTexture.draw(stratButtonSprites[4 - i]);
	}
}


void View::highlightSelectedCell(const std::pair<int, int>& cell, sf::View& gameView)
{
	if (cell.first == -1)
		return;

	sf::Vector2f worldPos(gridOffset.x + cell.first * cellSize, gridOffset.y + cell.second * cellSize);
	sf::Vector2i screenPosInt = window.mapCoordsToPixel(worldPos, gameView);
	sf::Vector2f screenPos(float(screenPosInt.x), float(screenPosInt.y));

	sf::RectangleShape highlight(sf::Vector2f(cellSize, cellSize));
	highlight.setFillColor(sf::Color(255, 255, 0, 128)); // Transparent yellow
	highlight.setPosition(screenPos);

	uiRenderTexture.draw(highlight);
}



void View::setButtonState(int button, bool isEnabled)
{
	sf::Sprite buttonSprite = buildButtonSprites[button - 1];
	buttonSprite.setColor(isEnabled ? sf::Color::White : sf::Color::Black); // Gray
	buttonSprite.setPosition(menuPosition.x + 100.f * (button - 1), menuPosition.y);

	uiRenderTexture.draw(buttonSprite);
}


void View::drawHealthBar(int x, int y, int health, int maxHealth, sf::Color color)
{
	float width = 46.f;
	float height = 10.f;

	sf::RectangleShape background(sf::Vector2f(width, height));
	background.setPosition(x + 2, y - height);
	background.setFillColor(sf::Color(50, 50, 50)); // Gray
	gameRenderTexture.draw(background);

	if (maxHealth > 0) {
		sf::RectangleShape bar(sf::Vector2f(width * health / maxHealth - width * 0.05f, height - 2));
		bar.setPosition(x + 2 + width * 0.025f, y - height + 1);
		bar.setFillColor(color);

		if (bar.getSize().x > 0) {
			gameRenderTexture.draw(bar);
		}
	}
}


void View::updateCastleInfo(int x, int y, int gold, int health, int maxHealth)
{
	int x_real = gridOffset.x + x * 50.f, y_real = gridOffset.y + y * 50.f;
	drawHealthBar(x_real, y_real - 5, health, maxHealth, sf::Color::Green); // darker Green

	// 15 healthBar + 5 offset and 16 height
	goldIconSprite.setPosition(x_real, y_real - 36);
	gameRenderTexture.draw(goldIconSprite);

	sf::Text goldText;
	goldText.setFont(font);
	goldText.setString(std::to_string(gold));
	goldText.setCharacterSize(12);
	goldText.setFillColor(sf::Color::White);
	goldText.setPosition(x_real + 21, y_real - 34);
	gameRenderTexture.draw(goldText);
}


void View::updateLairsInfo(int x, int y, int amount, int maxAmount)
	{ drawHealthBar(gridOffset.x + x * 50.f, gridOffset.y + y * 50.f - 5, amount, maxAmount, sf::Color::Red); }


void View::updateEnemyInfo(int x, int y, int health, int maxHealth, const std::vector<EffectType>& effects)
{
	int x_real = gridOffset.x + x * 50.f, y_real = gridOffset.y + y * 50.f;
	drawHealthBar(x_real, y_real - 5, health, maxHealth, sf::Color::Red);

	float effectRadius = (cellSize / 5) / 2;
	float spacing = effectRadius * 2;

	for (size_t i = 0; i < effects.size(); ++i) {
		sf::CircleShape effectCircle(effectRadius);
		effectCircle.setPosition(x_real + i * spacing, y_real - 30);
		effectCircle.setFillColor(sf::Color::Red);

		switch (effects[i]) {
		case EffectType::POISON:
			effectCircle.setFillColor(sf::Color::Green);
			break;
		case EffectType::SLOWNESS:
			effectCircle.setFillColor(sf::Color::Blue);
			break;
		case EffectType::WEAKNESS:
			effectCircle.setFillColor(sf::Color::Black);
			break;
		}

		gameRenderTexture.draw(effectCircle);
	}
}


void View::updateBuildInfo(int x, int y, int level)
{
	int x_real = gridOffset.x + x * 50.f, y_real = gridOffset.y + y * 50.f;
	levelIconSprite.setPosition(x_real, y_real - 23);
	gameRenderTexture.draw(levelIconSprite);

	sf::Text levelText;
	levelText.setFont(font);
	levelText.setString(std::to_string(level));
	levelText.setCharacterSize(14);
	levelText.setFillColor(sf::Color::White);
	levelText.setPosition(x_real + 21, y_real - 19);
	gameRenderTexture.draw(levelText);
}
