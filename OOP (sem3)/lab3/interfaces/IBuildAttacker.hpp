#ifndef IBUILDATTACKER_HPP
#define IBUILDATTACKER_HPP

class BuildAttack;
class Landscape;

class IBuildAttacker
{
public:
    virtual BuildAttack* attack() const = 0;

    virtual bool isReady() const = 0;

    virtual void setUnready() = 0;

    virtual void advanceReadiness() = 0;

    virtual void onAttackComplete(Landscape* land) = 0;
};

#endif
