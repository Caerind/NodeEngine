#include "RootComponent.hpp"
#include "Actor.hpp"

NRootComponent::NRootComponent(NActor* actor)
{
    mParent = nullptr;
    mActor = actor;
}

void NRootComponent::load(pugi::xml_node& node, std::string const& name)
{
    setPosition(NVector::fromString(node.attribute("pos").value()));
    setScale(NVector::fromString(node.attribute("sca").value()));
    setRotation(node.attribute("rot").as_float());
}

void NRootComponent::save(pugi::xml_node& node, std::string const& name)
{
    node.append_attribute("pos") = NVector::toString(getPosition()).c_str();
    node.append_attribute("sca") = NVector::toString(getScale()).c_str();
    node.append_attribute("rot") = getRotation();
}
