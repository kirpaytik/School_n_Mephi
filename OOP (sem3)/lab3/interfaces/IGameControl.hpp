#ifndef IGAMECONTROL_HPP
#define IGAMECONTROL_HPP

#include <fstream>

class IGameControl
{
public:
    virtual bool initializeGame(std::ifstream& file) = 0;

    virtual bool checkGameLevel() const = 0;

    virtual void checkGameStatus() = 0;

    virtual int isGameOver() = 0;

    virtual void update() = 0;
};

#endif
