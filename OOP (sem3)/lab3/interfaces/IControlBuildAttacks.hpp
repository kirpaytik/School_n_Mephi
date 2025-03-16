#ifndef ICONTROLBUILDATTACKS_HPP
#define ICONTROLBUILDATTACKS_HPP

class DefBuild;
class Enemy;

class IControlBuildAttacks
{
public:
    virtual void attack(DefBuild* defbuild) = 0;

    virtual Enemy* attack_strategy(DefBuild* defbuild) const = 0;

    virtual void processBuildsReadiness() = 0;
};

#endif
