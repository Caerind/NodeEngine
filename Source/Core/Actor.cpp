#include "Actor.hpp"

NActor::NActor() : NRootComponent(this)
{
    static int x = 0;
    x++;
    mId = std::to_string(x);
}

void NActor::load(pugi::xml_node& node)
{
}

void NActor::save(pugi::xml_node& node)
{
}

std::string NActor::getId() const
{
    return mId;
}
