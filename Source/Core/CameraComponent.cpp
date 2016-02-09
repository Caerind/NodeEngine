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

sf::View NCameraComponent::getView() const
{
    return mView;
}

void NCameraComponent::tick(sf::Time dt)
{
    mView.setCenter(NVector::NToSFML2F(getFinalPosition()));
    mView.setRotation(getRotation());
}
