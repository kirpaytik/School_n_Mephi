#include "../mvc/Game.hpp"

#include "../hpp/Landscape.hpp"
#include "../hpp/Castle.hpp"
#include "../hpp/Lair.hpp"
#include "../hpp/Field.hpp"
#include "../hpp/Road.hpp"
#include "../hpp/Enemy.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>


Landscape* Game::parseLandscape(std::ifstream& file) const
{
	std::string line;

	// Check LANDSCAPE header
	while (std::getline(file, line) && line.empty());
	if (line != "LANDSCAPE:") {
		throw std::runtime_error("Expected 'LANDSCAPE:' at the beginning of the file. Found instead: \"" + line + "\"");
	}

	// Parse width and height
	int width, height;
	if (!(file >> width >> height)) {
		throw std::runtime_error("Failed to parse width and height of the landscape");
	}

	// Ignore empty lines
	while (std::getline(file, line) && line.empty());

	// Parse castle position
	if (line != "CASTLE:") {
		throw std::runtime_error("Expected 'CASTLE:' before castle coordinates. Found instead: \"" + line + "\"");
	}
	int castleX, castleY;
	if (!(file >> castleX >> castleY)) {
		throw std::runtime_error("Failed to parse castle coordinates");
	}

	// Ignore empty lines
	while (std::getline(file, line) && line.empty());

	// Parse castle details
	if (line != "CASTLE:") {
		throw std::runtime_error("Expected 'CASTLE:' before castle details. Found instead: \"" + line + "\"");
	}
	Castle* castle = parseCastle(file);

	std::tuple<Castle*, int, int> castleTuple = std::make_tuple(castle, castleX, castleY);

	// Parse lairs
	std::vector<std::tuple<Lair*, int, int>> lairs;
	while (std::getline(file, line) && line.empty());
	if (line != "LAIRS") {
		throw std::runtime_error("Expected 'LAIRS' before lair definitions. Found instead: \"" + line + "\"");
	}

	while (std::getline(file, line) && line != "END_LAIRS") {
		if (line.empty()) continue;
		if (line.rfind("LAIR:", 0) == 0) {
			std::istringstream iss(line);
			std::string temp;
			int x, y;
			if (!(iss >> temp >> x >> y)) {
				throw std::runtime_error("Failed to parse lair coordinates");
			}

			Lair* lair = parseLair(file);
			lairs.emplace_back(lair, x, y);
		} else {
			throw std::runtime_error("Unexpected line in lairs section: \"" + line + "\"");
		}
	}

	// Parse roads
	std::vector<Road*> roads;
	while (std::getline(file, line) && line.empty());
	if (line != "ROADS") {
		throw std::runtime_error("Expected 'ROADS' before road definitions. Found instead: \"" + line + "\"");
	}

	while (std::getline(file, line) && line != "END_ROADS") {
		if (line.empty()) continue;
		if (line.rfind("ROAD:", 0) == 0) {
			std::istringstream iss(line);
			std::string temp;
			int x, y;
			if (!(iss >> temp >> x >> y)) {
				throw std::runtime_error("Failed to parse road coordinates");
			}

			roads.emplace_back(new Road(x, y));
		} else {
			throw std::runtime_error("Unexpected line in roads section: \"" + line + "\"");
		}
	}

	// Parse fields
	std::vector<Field*> fields;
	while (std::getline(file, line) && line.empty());
	if (line != "FIELDS") {
		throw std::runtime_error("Expected 'FIELDS' before field definitions. Found instead: \"" + line + "\"");
	}

	while (std::getline(file, line) && line != "END_FIELDS") {
		if (line.empty()) continue;
		if (line.rfind("FIELD:", 0) == 0) {
			std::istringstream iss(line);
			std::string temp;
			int x, y;
			if (!(iss >> temp >> x >> y)) {
				throw std::runtime_error("Failed to parse field coordinates");
			}

			fields.emplace_back(new Field(x, y));
		} else {
			throw std::runtime_error("Unexpected line in fields section: \"" + line + "\"");
		}
	}

	return new Landscape(width, height, castleTuple, lairs, fields, roads);
}


Castle* Game::parseCastle(std::ifstream& file) const
{
	std::string name;
	int health, gold;
	if (!(file >> name >> health >> gold)) {
		throw std::runtime_error("Failed to parse castle details");
	}

	return new Castle(name, health, gold);
}


Lair* Game::parseLair(std::ifstream& file) const
{
	std::string line;
	while (std::getline(file, line) && line.empty());

	std::istringstream iss(line);
	std::string temp, name;
	if (!(iss >> temp >> name) || temp != "LAIR:") {
		throw std::runtime_error("Failed to parse lair name \"" + temp + "\"");
	}

	std::vector<std::pair<EnemyType, int>> enemies;
	while (std::getline(file, line) && line != "END_LAIR") {
		if (line.empty()) continue;
		if (line.rfind("ENEMY:", 0) == 0) {
			std::istringstream iss(line);
			std::string temp;
			int time;
			std::string enemyTypeStr;
			if (!(iss >> temp >> time >> enemyTypeStr)) {
				throw std::runtime_error("Failed to parse enemy details. Found instead: \"" + line + "\"");
			}

			EnemyType enemyType = Lair::stringToEnemyType(enemyTypeStr);
			enemies.emplace_back(enemyType, time);
		} else if (line.rfind("ENEMIES:", 0) == 0) {
			std::istringstream iss(line);
			std::string temp;
			int amount;
			if (!(iss >> temp >> amount)) {
				throw std::runtime_error("Failed to parse enemy count");
			}

			return new Lair(name, amount);
		} else {
			throw std::runtime_error("Unexpected line in lair section: \"" + line + "\"");
		}
	}

	return new Lair(name, enemies);
}
