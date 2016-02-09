#ifndef NTRANSFORMABLE_HPP
#define NTRANSFORMABLE_HPP

#include "../Utils/Vector.hpp"
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Transform.hpp>

class NTransformable
{
    public:
        NTransformable();

        NVector getPosition() const;
        void setPosition(NVector const& position);
        void setPosition(float x, float y, float z = 0.f);

        NVector getScale() const;
        void setScale(NVector const& scale);
        void setScale(float x, float y);

        float getRotation() const;
        void setRotation(float rotation);

        sf::Transform getTransform() const;

    private:
        sf::Transformable mTransformable;
        float mZ;
};

#endif // NTRANSFORMABLE_HPP
