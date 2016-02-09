#include "RootComponent.hpp"
#include "Actor.hpp"

NRootComponent::NRootComponent(NActor* actor)
{
    mParent = nullptr;
    mActor = actor;
}


