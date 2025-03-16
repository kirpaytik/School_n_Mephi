#ifndef ICONTROLSPAWNS_HPP
#define ICONTROLSPAWNS_HPP

class Enemy;

class IControlSpawns
{
public:
    virtual void spawnTimeProcess() = 0;

    virtual Enemy* spawnEnemy() = 0;
};

#endif
