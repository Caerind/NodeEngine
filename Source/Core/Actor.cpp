#include "Actor.hpp"

NActor::NActor() : mRootComponent(this)
{
}

NVector NActor::getPosition() const
{
    return mRootComponent.position;
}

NVector NActor::getScale() const
{
    return mRootComponent.scale;
}

NVector NActor::getRotation() const
{
    return mRootComponent.rotation;
}

void NActor::attachComponent(NComponent* component)
{
    mRootComponent.attachComponent(component);
}

void NActor::detachComponent(NComponent* component)
{
    mRootComponent.detachComponent(component);
}
