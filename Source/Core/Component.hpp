#ifndef NCOMPONENT_HPP
#define NCOMPONENT_HPP

#include "../Utils/Array.hpp"

#include "Tickable.hpp"
#include "Transformable.hpp"

class NComponent : public NTickable, public NTransformable
{
    public:
        NComponent();

        void attachComponent(NComponent* component);
        void detachComponent(NComponent* component);

    protected:
        NArray<NComponent*> mComponents;
        NComponent* mParent;
};

#endif // NCOMPONENT_HPP
