#ifndef NSCENECOMPONENT_HPP
#define NSCENECOMPONENT_HPP

#include "Component.hpp"
#include "Renderable.hpp"

class NSceneComponent : public NComponent, public NRenderable
{
    public:
        NSceneComponent();
};

#endif // NSCENECOMPONENT_HPP
