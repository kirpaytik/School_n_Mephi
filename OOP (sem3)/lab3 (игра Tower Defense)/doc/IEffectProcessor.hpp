#ifndef IEFFECTPROCESSOR_HPP
#define IEFFECTPROCESSOR_HPP

class EffectAttack;

/**
 * @brief Interface for processing and applying effects.
 * 
 * This interface defines methods for applying effects to an entity and processing
 * any active effects over time.
 */
class IEffectProcessor
{
public:
	/**
	 * @brief Apply a new effect to the entity.
	 * 
	 * This method should handle the logic of adding the specified effect to the entity,
	 * potentially stacking it or refreshing its duration.
	 * 
	 * @param effect A pointer to the EffectAttack object that represents the effect to be applied.
	 */
	virtual void applyEffect(EffectAttack* effect) = 0;

	/**
	 * @brief Process all active effects on the entity.
	 * 
	 * This method should update the state of all currently active effects,
	 * applying their ongoing effects (e.g., damage over time) and reducing their duration.
	 */
	virtual void processEffects() = 0;
};

#endif
