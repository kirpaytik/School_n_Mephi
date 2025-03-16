#ifndef FIELD_HPP
#define FIELD_HPP

#include "Cell.hpp"
#include "DefBuild.hpp"

class Field : public Cell
{
private:
	DefBuild* defbuild;

public:
	Field(int x, int y);
	Field(int x, int y, DefBuild* defbuild);
	~Field();

	DefBuild* getBuild() const;
	void setBuild(DefBuild* defbuild);
	bool isEmpty() const;
};

#endif
