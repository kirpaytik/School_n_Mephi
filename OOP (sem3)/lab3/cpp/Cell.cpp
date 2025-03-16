#include "../hpp/Cell.hpp"


Cell::Cell() : x(0), y(0) {}

Cell::Cell(int x, int y) : x(x), y(y) {}


int Cell::getX() const { return x; }


int Cell::getY() const { return y; }


void Cell::setX(int newx) { x = newx;}


void Cell::setY(int newy) {y = newy; }
