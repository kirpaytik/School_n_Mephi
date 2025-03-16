#ifndef ICONTROLLIVES_HPP
#define ICONTROLLIVES_HPP

class Enemy;
class Road;
class DefBuild;
#include <set>
class BuildAttack;

class IControlLives
{
public:
    virtual bool moveEnemy(Enemy* enemy, Road* curr_road, std::set<DefBuild*>& mtraps) = 0;

    virtual void dealDamage(Enemy* enemy, BuildAttack* battack) = 0;

    virtual void killEnemy(Enemy* enemy) = 0;
};

#endif
