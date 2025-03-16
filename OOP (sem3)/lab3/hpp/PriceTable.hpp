#ifndef PRICETABLE_HPP
#define PRICETABLE_HPP

#include <unordered_map>

#ifndef BUILDTYPE
#define BUILDTYPE
enum class BuildType { TOWER, MAGICTOWER, MAGICTRAP };
#endif

#ifndef EFFECTTYPE
#define EFFECTTYPE
enum class EffectType { POISON, SLOWNESS, WEAKNESS };
#endif

#ifndef ATTACKSTRATEGY
#define ATTACKSTRATEGY
enum class AttackStrategy {
	NearestToTower,
	FurthestFromTower,
	NearestToCastle,
	LowestHP,
	HighestHP
};
#endif

struct PriceBuildKey {
	BuildType type;
	AttackStrategy strat;
	EffectType effect;
	int level;

	bool operator == (const PriceBuildKey& other) const {
		if (type == BuildType::TOWER)
			return (type == other.type) && (level == other.level);
		return (type == other.type) && (effect == other.effect) && (level == other.level);
	}
};

namespace std {
	template <>
	struct hash<PriceBuildKey> {
		std::size_t operator()(const PriceBuildKey& key) const {
			size_t h1 = std::hash<int>()(static_cast<int>(key.type));
			size_t h2 = (key.type == BuildType::TOWER) ? 0 : std::hash<int>()(static_cast<int>(key.effect));
			// don't use key.strat
			size_t h3 = std::hash<int>()(key.level);
			return h1 ^ (h2 << 1) ^ (h3 << 2);
		}
	};
}

struct BuildStats {
	int cost;
	int radius;
	int damage;
	int attackspeed;
};

class PriceTable
{
private:


	PriceTable();
public:
	static std::unordered_map<PriceBuildKey, BuildStats> priceBuildTable;
	static PriceTable& instance() {
		static PriceTable instance;
		return instance;
	}

	static BuildStats getBuildStats(PriceBuildKey key);
	static BuildStats getBuildStats(BuildType type, AttackStrategy strat, int level);
	static BuildStats getBuildStats(BuildType type, AttackStrategy strat, EffectType effect, int level);

	static int getBuildCost(PriceBuildKey key);
	static int getBuildCost(BuildType type, AttackStrategy strat, int level);
	static int getBuildCost(BuildType type, AttackStrategy strat, EffectType effect, int level);
		
};

#endif
