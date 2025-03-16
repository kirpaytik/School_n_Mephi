#ifndef IDAMAGABLE_HPP
#define IDAMAGABLE_HPP

class IDamagable
{
public:
    virtual int damageTaken(int damage) const = 0;

    virtual void setHealth(int health) = 0;

    virtual bool isAlive() const = 0;
};

#endif
