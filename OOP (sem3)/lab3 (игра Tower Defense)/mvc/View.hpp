#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>

#include <vector>
#include <utility>

#ifndef BUILDTYPE
#define BUILDTYPE
enum class BuildType { TOWER, MAGICTOWER, MAGICTRAP };
#endif

#ifndef EFFECTTYPE
#define EFFECTTYPE
enum class EffectType { POISON, SLOWNESS, WEAKNESS };
#endif

#ifndef ENEMYTYPE
#define ENEMYTYPE
enum class EnemyType { NORMAL, FAST, TANK };
#endif


class View
{
private:
	sf::RenderWindow& window;
	sf::View uiView;

	int cellSize;

	sf::Font font;

	// Textures
	sf::Texture roadTexture;
	sf::Texture fieldTexture;
	sf::Texture enemyTextures[3];
	sf::Texture buildTextures[7];
	sf::Texture lairTexture;
	sf::Texture castleTexture;

	sf::Texture menuTexture;
	sf::Texture buildButtonTextures[7];
	sf::Texture upgradeButtonTexture;
	sf::Texture levelButtonTextures[3];
	sf::Texture stratButtonTextures[5];

	sf::Texture goldIconTexture;
	sf::Texture levelIconTexture;

	// Sprites
	sf::Sprite roadSprite;
	sf::Sprite fieldSprite;
	sf::Sprite enemySprites[3];
	sf::Sprite buildSprites[7];
	sf::Sprite lairSprite;
	sf::Sprite castleSprite;

	sf::Sprite mainMenuSprite;
	sf::Sprite levelListSprite;
	sf::Sprite stratListSprite;

	sf::Sprite buildButtonSprites[7];
	sf::Sprite upgradeButtonSprite;
	sf::Sprite levelButtonSprites[3];
	sf::Sprite stratButtonSprites[5];

	sf::Sprite goldIconSprite;
	sf::Sprite levelIconSprite;



	sf::Texture levelListTexture;
	sf::Texture stratListTexture;



	// grid and menu coords
	sf::Vector2i gridOffset;
	sf::Vector2f menuPosition;
	sf::Vector2f levelListPosition;
	sf::Vector2f stratListPosition;

	// 2 layers of everything on screen: objects and UI
	sf::RenderTexture gameRenderTexture;
	sf::RenderTexture uiRenderTexture;
	sf::Sprite gameRenderSprite;
	sf::Sprite uiRenderSprite;

	void loadTextures();
	void initializeSprites();

	void drawHealthBar(int x, int y, int health, int maxHealth, sf::Color color);

public:
	View(sf::RenderWindow& win, int height, int width);

	sf::RenderWindow* getWindow() const { return &window; }

	void clearGameLayer();
	void clearUILayer();
	void display(sf::View& gameView);

	// input
	std::pair<int, int> getClickedCell(int x, int y, sf::View& gameView) const;
	int getClickedButton(int x, int y) const;


	// Drawing
	void drawBackground();
	void drawGrid();

	// objects
	void drawFields(const std::vector<std::pair<int, int>>& fields);
	void drawRoads(const std::vector<std::pair<int, int>>& roads);
	void drawCastle(int castleX, int castleY);
	void drawLairs(const std::vector<std::pair<int, int>>& lairs);
	void drawBuilds(const std::vector<std::tuple<int, int, BuildType, EffectType>>& builds);
	void drawEnemies(const std::vector<std::tuple<int, int, EnemyType>>& enemies);

	// menu
	void showMenu(bool isColored = true);
	void showBuildMenu();
	void showSecondMenu();
	void showLevelList(int button);
	void showStratList(int button);

	// other smaller stuff
	// selections
	void highlightSelectedCell(const std::pair<int, int>& cell, sf::View& gameView);
	void setButtonState(int button, bool isEnabled);

	// object's info
	void updateCastleInfo(int x, int y, int gold, int health, int maxhealth);
	void updateLairsInfo(int x, int y, int amount, int maxamount);
	void updateEnemyInfo(int x, int y, int health, int maxhealth, const std::vector<EffectType>& effects);
	void updateBuildInfo(int x, int y, int level);
};

#endif
