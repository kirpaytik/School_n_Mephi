/**
 * @file PriceTable.hpp
 * @brief Defines the PriceTable class, managing the costs and statistics of buildings in the game.
 */

#ifndef PRICETABLE_HPP
#define PRICETABLE_HPP

#include <unordered_map>

/**
 * @enum BuildType
 * @brief Represents different types of buildings in the game.
 */
enum class BuildType { 
	TOWER,      ///< Regular tower for physical attacks.
	MAGICTOWER, ///< Tower with magical effects.
	MAGICTRAP   ///< Trap with magical effects.
};

/**
 * @enum EffectType
 * @brief Represents different types of magical effects.
 */
enum class EffectType { 
	POISON,   ///< Inflicts poison damage over time.
	SLOWNESS, ///< Reduces enemy speed.
	WEAKNESS  ///< Reduces enemy attack power.
};

/**
 * @enum AttackStrategy
 * @brief Represents different strategies for targeting enemies.
 */
enum class AttackStrategy {
	NearestToTower,      ///< Targets the enemy closest to the tower.
	FurthestFromTower,   ///< Targets the enemy furthest from the tower.
	NearestToCastle,     ///< Targets the enemy closest to the castle.
	LowestHP,            ///< Targets the enemy with the lowest HP.
	HighestHP            ///< Targets the enemy with the highest HP.
};

/**
 * @struct PriceBuildKey
 * @brief A key used to uniquely identify the price and stats of a building.
 */
struct PriceBuildKey {
	BuildType type;          ///< The type of the building.
	AttackStrategy strat;    ///< The attack strategy (ignored for price lookup).
	EffectType effect;       ///< The effect type (only for magic towers and traps).
	int level;               ///< The level of the building.

	/**
	 * @brief Equality operator for comparing two keys.
	 * @param other The other key to compare with.
	 * @return True if the keys are equal, false otherwise.
	 */
	bool operator==(const PriceBuildKey& other) const {
		if (type == BuildType::TOWER)
			return (type == other.type) && (level == other.level);
		return (type == other.type) && (effect == other.effect) && (level == other.level);
	}
};

/**
 * @namespace std
 * @brief Provides a hash specialization for the `PriceBuildKey` structure.
 */
namespace std {
	template <>
	struct hash<PriceBuildKey> {
		/**
		 * @brief Hash function for the PriceBuildKey structure.
		 * @param key The key to hash.
		 * @return A hash value for the given key.
		 */
		std::size_t operator()(const PriceBuildKey& key) const {
			size_t h1 = std::hash<int>()(static_cast<int>(key.type));
			size_t h2 = (key.type == BuildType::TOWER) ? 0 : std::hash<int>()(static_cast<int>(key.effect));
			size_t h3 = std::hash<int>()(key.level);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
}

/**
 * @struct BuildStats
 * @brief Stores the statistics and cost of a building.
 */
struct BuildStats {
	int cost;         ///< The cost of the building.
	int radius;       ///< The attack radius of the building.
	int damage;       ///< The damage dealt by the building.
	int attackspeed;  ///< The attack speed of the building.
};

/**
 * @class PriceTable
 * @brief Manages the costs and statistics of buildings in the game.
 */
class PriceTable
{
private:
	/**
	 * @brief Private constructor to prevent instantiation (singleton pattern).
	 */
	PriceTable();

public:
	/**
	 * @brief A static table containing the price and stats of all buildings.
	 */
	static std::unordered_map<PriceBuildKey, BuildStats> priceBuildTable;

	/**
	 * @brief Retrieves the singleton instance of the PriceTable.
	 * @return A reference to the singleton instance.
	 */
	static PriceTable& instance() {
		static PriceTable instance;
		return instance;
	}

	/**
	 * @brief Retrieves the statistics for a building based on its key.
	 * @param key The key representing the building.
	 * @return The statistics of the building.
	 * @throw std::out_of_range if the key is not found in the priceBuildTable.
	 */
	static BuildStats getBuildStats(PriceBuildKey key);

	/**
	 * @brief Retrieves the statistics for a building based on its type, strategy, and level.
	 * @param type The type of the building.
	 * @param strat The attack strategy.
	 * @param level The level of the building.
	 * @return The statistics of the building.
	 * @throw std::out_of_range if the key is not found in the priceBuildTable.
	 */
	static BuildStats getBuildStats(BuildType type, AttackStrategy strat, int level);

	/**
	 * @brief Retrieves the statistics for a building based on its type, strategy, effect, and level.
	 * @param type The type of the building.
	 * @param strat The attack strategy.
	 * @param effect The effect type.
	 * @param level The level of the building.
	 * @return The statistics of the building.
	 * @throw std::out_of_range if the key is not found in the priceBuildTable.
	 */
	static BuildStats getBuildStats(BuildType type, AttackStrategy strat, EffectType effect, int level);

	/**
	 * @brief Retrieves the cost for a building based on its key.
	 * @param key The key representing the building.
	 * @return The cost of the building.
	 * @throw std::out_of_range if the key is not found in the priceBuildTable.
	 */
	static int getBuildCost(PriceBuildKey key);

	/**
	 * @brief Retrieves the cost for a building based on its type, strategy, and level.
	 * @param type The type of the building.
	 * @param strat The attack strategy.
	 * @param level The level of the building.
	 * @return The cost of the building.
	 * @throw std::out_of_range if the key is not found in the priceBuildTable.
	 */
	static int getBuildCost(BuildType type, AttackStrategy strat, int level);

	/**
	 * @brief Retrieves the cost for a building based on its type, strategy, effect, and level.
	 * @param type The type of the building.
	 * @param strat The attack strategy.
	 * @param effect The effect type.
	 * @param level The level of the building.
	 * @return The cost of the building.
	 * @throw std::out_of_range if the key is not found in the priceBuildTable.
	 */
	static int getBuildCost(BuildType type, AttackStrategy strat, EffectType effect, int level);
};

#endif
