#include "InputComponent.hpp"

NInputComponent::NInputComponent()
{
}

void NInputComponent::tick(sf::Time dt)
{
    NComponent::tick(dt);
    NActionTarget::tick(dt);
}
