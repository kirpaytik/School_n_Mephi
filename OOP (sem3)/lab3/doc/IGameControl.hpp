#ifndef IGAMECONTROL_HPP
#define IGAMECONTROL_HPP

#include <fstream>

/**
 * @brief Interface for controlling the main game flow and logic.
 * 
 * This interface provides methods for initializing the game, checking its status, 
 * and updating the state during gameplay. It acts as the core manager for the game's lifecycle.
 */
class IGameControl
{
public:
    /**
     * @brief Initialize the game using the provided configuration file.
     * 
     * This method reads and processes a configuration file to set up the initial game state.
     * It should handle tasks like creating the game map, placing entities, and initializing
     * key variables.
     * 
     * @param file A reference to the input file stream containing the game configuration.
     * @return True if the game was successfully initialized; otherwise, false.
     */
    virtual bool initializeGame(std::ifstream& file) = 0;

    /**
     * @brief Check if the current game level is valid or complete.
     * 
     * This method verifies whether the game is in a state where the level is complete
     * or if any conditions make the level invalid (e.g. no castle on the landscape or no lairs that can spawn enemies)
     * 
     * @return True if the level is valid or complete; otherwise, false.
     */
    virtual bool checkGameLevel() const = 0;

    /**
     * @brief Check and update the current game status.
     * 
     * This method determines the overall status of the game, such as whether the player
     * has won, lost, or if the game is still ongoing. It should update internal flags
     * or variables accordingly.
     */
    virtual void checkGameStatus() = 0;

    /**
     * @brief Check if the game is over.
     * 
     * This method returns a status code indicating whether the game has ended:
     * - 0: Game is ongoing.
     * - 1: Player has won.
     * - -1: Player has lost.
     * 
     * @return An integer representing the game-over status.
     */
    virtual int isGameOver() = 0;

    /**
     * @brief Update the game state.
     * 
     * This method advances the game by one tick or step. It should handle logic such as
     * moving enemies, processing attacks, updating the readiness of builds and effects and other.
     */
    virtual void update() = 0;
};

#endif
