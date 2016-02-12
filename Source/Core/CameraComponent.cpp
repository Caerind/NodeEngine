#include "CameraComponent.hpp"
#include "World.hpp"
#include "../Application/Application.hpp"

NCameraComponent::NCameraComponent()
{
    NWorld::getCameraManager().addCamera(this);
    mView = ah::Application::getWindow().getDefaultView();
}

NCameraComponent::~NCameraComponent()
{
    NWorld::getCameraManager().removeCamera(this);
}

sf::View NCameraComponent::getView()
{
    mView.setCenter(NVector::NToSFML2F(getFinalPosition()));
    return mView;
}

void NCameraComponent::tick(sf::Time dt)
{
}

void NCameraComponent::setRotation(float rotation)
{
    NComponent::setRotation(rotation);
    mView.setRotation(rotation);
}
