#ifndef NTRANSFORMABLE_HPP
#define NTRANSFORMABLE_HPP

#include "../Utils/Vector.hpp"

class NTransformable
{
    public:
        NTransformable();

        NVector position;
        NVector scale;
        float rotation;

        //sf::Transform getTransform();
};

#endif // NTRANSFORMABLE_HPP
