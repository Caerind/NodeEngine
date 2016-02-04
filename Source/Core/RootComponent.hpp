#ifndef NROOTCOMPONENT_HPP
#define NROOTCOMPONENT_HPP

#include "Component.hpp"

class NActor;
class NRootComponent : public NComponent
{
    public:
        NRootComponent(NActor* actor);

    protected:
        NActor* mActor;
};

#endif // NROOTCOMPONENT_HPP
