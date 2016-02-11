#include "RootComponent.hpp"
#include "Actor.hpp"

NRootComponent::NRootComponent(NActor* actor)
{
    mParent = nullptr;
    mActor = actor;
}

void NRootComponent::save(pugi::xml_node& node)
{
    node.append_attribute("pos") = NVector::toString(getPosition()).c_str();
    node.append_attribute("sca") = NVector::toString(getScale()).c_str();
    node.append_attribute("rot") = NVector::toString(getRotation()).c_str();
}
