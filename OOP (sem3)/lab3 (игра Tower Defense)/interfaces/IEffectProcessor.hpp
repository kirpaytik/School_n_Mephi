#ifndef IEFFECTPROCESSOR_HPP
#define IEFFECTPROCESSOR_HPP

class EffectAttack;

class IEffectProcessor
{
public:
    virtual void applyEffect(EffectAttack* effect) = 0;

    virtual void processEffects() = 0;
};

#endif
