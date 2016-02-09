#include "SpriteComponent.hpp"

NSpriteComponent::NSpriteComponent()
{
}

void NSpriteComponent::setTexture(sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

void NSpriteComponent::setTextureRect(sf::IntRect const& rect)
{
    mSprite.setTextureRect(rect);
}

void NSpriteComponent::render(sf::RenderTarget& target)
{
    sf::RenderStates states;
    states.transform *= getFinalTransform();
    target.draw(mSprite, states);
}
