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
    if (component)
    {
        component->mParent = nullptr;
    }
    mComponents.remove(component);
}

float NComponent::getFinalZ() const
{
    if (mParent != nullptr)
    {
        return getPosition().z + mParent->getFinalZ();
    }
    else
    {
        return getPosition().z;
    }
}

NVector NComponent::getFinalPosition() const
{
    NVector v = NVector::SFML2FToN(getFinalTransform().transformPoint(0,0));
    v.z = getFinalZ();
    return v;
}

NVector NComponent::getActorPosition() const
{
    if (mParent != nullptr)
    {
        return mParent->getActorPosition();
    }
    else
    {
        return getPosition();
    }
}

NVector NComponent::getActorScale() const
{
    if (mParent != nullptr)
    {
        return mParent->getActorScale();
    }
    else
    {
        return getScale();
    }
}

float NComponent::getActorRotation() const
{
    if (mParent != nullptr)
    {
        return mParent->getActorRotation();
    }
    else
    {
        return getRotation();
    }
}

sf::Transform NComponent::getFinalTransform() const
{
    if (mParent != nullptr)
    {
        return mParent->getFinalTransform() * getTransform();
    }
    else
    {
        return getTransform();
    }
}

void NComponent::setActorPosition(NVector const& position)
{
    if (mParent != nullptr)
    {
        mParent->setActorPosition(position);
    }
    else
    {
        setPosition(position);
    }
}

void NComponent::setActorScale(NVector const& scale)
{
    if (mParent != nullptr)
    {
        mParent->setActorScale(scale);
    }
    else
    {
        setPosition(scale);
    }
}

void NComponent::setActorRotation(float rotation)
{
    if (mParent != nullptr)
    {
        mParent->setActorRotation(rotation);
    }
    else
    {
        setRotation(rotation);
    }
}
