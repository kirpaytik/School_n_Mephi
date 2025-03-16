#ifndef ICONTROLLIVES_HPP
#define ICONTROLLIVES_HPP

class Enemy;
class BuildAttack;

class IControlLives
{
public:
    virtual int checkMoveDistance(Enemy* enemy) const = 0;

    virtual bool moveEnemy(Enemy* enemy, int move_dist) = 0;

    virtual void dealDamage(Enemy* enemy, BuildAttack* battack) = 0;

    virtual void killEnemy(Enemy* enemy) = 0;
};

#endif
