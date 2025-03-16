#include "../hpp/Field.hpp"

#include "../hpp/Cell.hpp"
#include "../hpp/DefBuild.hpp"


Field::Field(int x, int y) : Cell(x, y), defbuild(nullptr) {}
Field::Field(int x, int y, DefBuild* defbuild) : Cell(x, y), defbuild(defbuild) {}
Field::~Field() { delete defbuild; }

DefBuild* Field::getBuild() const { return defbuild; }
void Field::setBuild(DefBuild* newdefbuild) { defbuild = newdefbuild; }
bool Field::isEmpty() const { return defbuild == nullptr; }
