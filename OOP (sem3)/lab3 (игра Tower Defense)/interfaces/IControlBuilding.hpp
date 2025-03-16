#ifndef ICONTROLBUILDING_HPP
#define ICONTROLBUILDING_HPP

enum class BuildType;
struct PriceBuildKey;

class IControlBuilding
{
    virtual bool canBuildDefBuild(int x, int y, int cost, BuildType type) const = 0;

    virtual void buildDefBuild(int x, int y, PriceBuildKey key) = 0;
};

#endif
