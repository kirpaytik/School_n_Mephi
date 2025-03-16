#ifndef IUPGRADABLE_HPP
#define IUPGRADABLE_HPP

class IUpgradable
{
public:
    virtual void upgrade() = 0;

    virtual bool isUpgraded() const = 0;
};

#endif
