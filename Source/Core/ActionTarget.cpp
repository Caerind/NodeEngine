#include "ActionTarget.hpp"
#include "World.hpp"

NActionTarget::NActionTarget()
{
}

void NActionTarget::bind(std::string const& id, NActionTarget::ActionCallback function)
{
    mFunctions[id] = function;
}

void NActionTarget::unbind(std::string const& id)
{
    mFunctions.remove(id);
}

bool NActionTarget::isActive(std::string const& id)
{
    if (mActions.contains(id))
    {
        NAction a = mActions[id];
        if (a.test() || NWorld::testAction(a))
        {
            return true;
        }
    }
    return false;
}

void NActionTarget::tick(sf::Time dt)
{
    for (auto itr = mFunctions.begin(); itr != mFunctions.end(); itr++)
    {
        if (isActive(itr->first) && itr->second)
        {
            itr->second(dt);
        }
    }
}
