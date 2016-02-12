#include "SpriteComponent.hpp"

NSpriteComponent::NSpriteComponent()
{
}

void NSpriteComponent::setOrigin(float x, float y, float z)
{
    setOrigin(NVector(x,y,z));
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
    target.draw(mSprite,states);
}

bool NSpriteComponent::contains(NVector const& position)
{
    sf::FloatRect r = mSprite.getLocalBounds();
    r = getFinalTransform().transformRect(r);
    return r.contains(NVector::NToSFML2F(position));
}

void NSpriteComponent::load(pugi::xml_node& node, std::string const& name)
{
    pugi::xml_node n = node.child(name.c_str());
    setPosition(NVector::fromString(n.attribute("pos").value()));
    setScale(NVector::fromString(n.attribute("sca").value()));
    setRotation(n.attribute("rot").as_float());
    setOrigin(NVector::fromString(n.attribute("ori").value()));
}

void NSpriteComponent::save(pugi::xml_node& node, std::string const& name)
{
    pugi::xml_node n = node.append_child(name.c_str());
    n.append_attribute("pos") = NVector::toString(getPosition()).c_str();
    n.append_attribute("sca") = NVector::toString(getScale()).c_str();
    n.append_attribute("rot") = getRotation();
    n.append_attribute("ori") = NVector::toString(mOrigin).c_str();
}
