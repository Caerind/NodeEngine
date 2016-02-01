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

        void attachComponent(Component* component);
        void detachComponent(Component* component);

    protected:
        NRootComponent mRootComponent;
};

#endif // NACTOR_HPP
