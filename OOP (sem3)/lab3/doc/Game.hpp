/**
 * @file Game.hpp
 * @brief Defines the Game class, representing the Model and core game logic and management.
 */

#ifndef GAME_HPP
#define GAME_HPP

#include "../hpp/Landscape.hpp"
#include "../hpp/PriceTable.hpp"
#include "../interfaces/IGameControl.hpp"

#include <fstream>

/**
 * @enum GameStatus
 * @brief Represents the status of the game.
 */
enum class GameStatus { 
	WIN,    ///< The player has won the game.
	RUNNING,///< The game is in progress.
	LOSS    ///< The player has lost the game.
};

/**
 * @class Game
 * @brief Core Model class managing the game, its initialization, updates, and interactions.
 */
class Game : public IGameControl
{
private:
	Landscape* land; ///< The game landscape (map).
	GameStatus status; ///< Current status of the game.

public:
	/**
	 * @brief Default constructor. Initializes a new game instance.
	 */
	Game();

	/**
	 * @brief Destructor. Cleans up dynamically allocated resources.
	 */
	~Game();

	/**
	 * @brief Retrieves the game landscape.
	 * @return A pointer to the Landscape object.
	 */
	Landscape* getLandscape() const;

	/**
	 * @brief Parses the game landscape from a file.
	 * @param file Input file stream containing the landscape data.
	 * @return A pointer to the parsed Landscape object.
	 */
	Landscape* parseLandscape(std::ifstream& file) const;

	/**
	 * @brief Parses the castle information from a file.
	 * @param file Input file stream containing the castle data.
	 * @return A pointer to the parsed Castle object.
	 */
	Castle* parseCastle(std::ifstream& file) const;

	/**
	 * @brief Parses a lair's information from a file.
	 * @param file Input file stream containing the lair data.
	 * @return A pointer to the parsed Lair object.
	 */
	Lair* parseLair(std::ifstream& file) const;

	/**
	 * @brief Establishes connections between roads in the landscape.
	 */
	void connectRoads();

	// IGameControl methods

	/**
	 * @brief Initializes the game by loading data from a file.
	 * @param file Input file stream containing the game initialization data.
	 * @return True if initialization is successful, false otherwise.
	 */
	bool initializeGame(std::ifstream& file) override;

	/**
	 * @brief Checks the current game level for completion conditions.
	 * @return True if the level is complete, false otherwise.
	 */
	bool checkGameLevel() const override;

	/**
	 * @brief Checks the overall game status (win, loss, or still running).
	 */
	void checkGameStatus() override;

	/**
	 * @brief Determines if the game is over.
	 * @return 1 if the game is won, -1 if lost, and 0 if still running.
	 */
	int isGameOver() override;

	/**
	 * @brief Updates the game state, processing all ongoing events.
	 */
	void update() override;

	/**
	 * @brief Moves all enemies along their paths.
	 */
	void moveEnemies();

	/**
	 * @brief Processes all ongoing effects on enemies (e.g., poison, slowness).
	 */
	void enemiesProcessEffects();

	/**
	 * @brief Handles all attacks performed by defensive buildings.
	 */
	void attackDefBuilds();

	/**
	 * @brief Removes all dead enemies from the game.
	 */
	void killIfCorpses();

	/**
	 * @brief Checks and removes a specific enemy if it is dead.
	 * @param enemy A pointer to the enemy to check.
	 * @return True if the enemy was removed, false otherwise.
	 */
	bool killIfCorpse(Enemy* enemy);

	// Building-related methods

	/**
	 * @brief Checks if a defensive building can be placed at the specified coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return True if a building can be placed, false otherwise.
	 */
	bool canBuildHere(int x, int y) const;

	/**
	 * @brief Checks if a specific type of defensive building can be placed at the specified coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @param type The type of building to place.
	 * @return True if the building can be placed, false otherwise.
	 */
	bool canBuildHere(int x, int y, BuildType type) const;

	/**
	 * @brief Checks if a defensive building at the specified coordinates can be upgraded.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return True if the building can be upgraded, false otherwise.
	 */
	bool canUpgradeHere(int x, int y) const;

	/**
	 * @brief Checks if there is a defensive building at the specified coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return True if there is a building, false otherwise.
	 */
	bool isDefBuildHere(int x, int y) const;

	/**
	 * @brief Retrieves the upgrade cost for a defensive building at the specified coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @return The cost of upgrading the building.
	 */
	int getUpgradeCost(int x, int y) const;

	/**
	 * @brief Checks if the player has enough gold to afford a specified cost.
	 * @param cost The cost to check.
	 * @return True if the player has enough gold, false otherwise.
	 */
	bool isEnoughGold(int cost) const;

	/**
	 * @brief Builds a defensive building at the specified coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @param key The key indicating the type of building to construct.
	 */
	void buildDefBuild(int x, int y, PriceBuildKey key);

	/**
	 * @brief Upgrades a defensive building at the specified coordinates.
	 * @param x The X coordinate.
	 * @param y The Y coordinate.
	 * @param cost The cost of the upgrade.
	 */
	void upgradeDefBuild(int x, int y, int cost);
};

#endif
