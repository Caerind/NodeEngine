#ifndef NACTIONTARGET_HPP
#define NACTIONTARGET_HPP

#include "ActionMap.hpp"
#include "Tickable.hpp"

class NActionTarget : public NActionMap, public NTickable
{
    public:
        NActionTarget();

        typedef std::function<void(sf::Time dt)> ActionCallback;

        void bind(std::string const& id, ActionCallback function);
        void unbind(std::string const& id);

        bool isActive(std::string const& id);

        void tick(sf::Time dt);

    protected:
        NMap<std::string,ActionCallback> mFunctions;
};

#endif // NACTIONTARGET_HPP
