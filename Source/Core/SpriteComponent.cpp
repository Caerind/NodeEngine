#include "SpriteComponent.hpp"

NSpriteComponent::NSpriteComponent()
{
}

void NSpriteComponent::setOrigin(NVector const& origin)
{
    mOrigin = origin;
    mSprite.setOrigin(NVector::NToSFML2F(origin));
}

NVector NSpriteComponent::getOrigin() const
{
    return NVector::SFML2FToN(mSprite.getOrigin());
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

bool NSpriteComponent::contains(NVector const& position)
{
    sf::FloatRect r = mSprite.getLocalBounds();
    r = getFinalTransform().transformRect(r);
    return r.contains(NVector::NToSFML2F(position));
}

void NSpriteComponent::save(pugi::xml_node& node)
{
    node.append_attribute("pos") = NVector::toString(getPosition()).c_str();
    node.append_attribute("sca") = NVector::toString(getScale()).c_str();
    node.append_attribute("rot") = NVector::toString(getRotation()).c_str();
    node.append_attribute("ori") = NVector::toString(mOrigin).c_str();
}
