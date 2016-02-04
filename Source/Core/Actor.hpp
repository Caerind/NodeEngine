#ifndef NACTOR_HPP
#define NACTOR_HPP

#include "RootComponent.hpp"

class NActor
{
    public:
        NActor();

        NVector getPosition() const;
        NVector getScale() const;
        float getRotation() const;

        void attachComponent(NComponent* component);
        void detachComponent(NComponent* component);

    protected:
        NRootComponent mRootComponent;
};

#endif // NACTOR_HPP
