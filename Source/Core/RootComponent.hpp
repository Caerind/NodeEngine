#ifndef NROOTCOMPONENT_HPP
#define NROOTCOMPONENT_HPP

#include "Component.hpp"

class NActor;
class NRootComponent : public NComponent
{
    public:
        NRootComponent(NActor* actor);

        virtual void save(pugi::xml_node& node);

    protected:
        NActor* mActor;
};

#endif // NROOTCOMPONENT_HPP
