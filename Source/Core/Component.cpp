#include "Component.hpp"

NComponent::NComponent()
{
    mParent = nullptr;
}

void NComponent::attachComponent(NComponent* component)
{
    if (component)
    {
        component->mParent = this;
        mComponents.add(component);
    }
}

void NComponent::detachComponent(NComponent* component)
{
    mComponents.remove(component);
}
