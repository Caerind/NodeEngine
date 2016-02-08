#ifndef NINPUTCOMPONENT_HPP
#define NINPUTCOMPONENT_HPP

#include "Component.hpp"
#include "ActionTarget.hpp"

class NInputComponent : public NComponent, public NActionTarget
{
    public:
        NInputComponent();

        void tick(sf::Time dt);
};

#endif // NINPUTCOMPONENT_HPP
