#ifndef ICONTROLMYSELFONLAND_HPP
#define ICONTROLMYSELFONLAND_HPP

class Landscape;

#include <utility>

class IControlMyselfOnLand
{
public:
    virtual std::pair<int, int> getCoord(const Landscape* land) const = 0;

    virtual void installOnCell(Landscape* land, int x, int y) = 0;
};

#endif
