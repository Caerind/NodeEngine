#ifndef NVECTOR_HPP
#define NVECTOR_HPP

#include <cmath>

class NVector
{
    public:
        float x;
        float y;
        float z;

        static const NVector UpVector(); // (0,0,1)
        static const NVector RightVector(); // (0,1,0)
        static const NVector ForwardVector(); // (1,0,0)
        static const NVector ZeroVector(); // (0,0,0)

        NVector(); // (0,0,0)
        NVector(float value); // (value,value,value)
        NVector(float x, float y, float z = 0.f); // (x,y,z)

        //NVector(b2Vec2 const& vec, float z = 0.f);
        //NVector(sf::Vector2f const& vec, float z = 0.f);
        //NVector(sf::Vector2i const& vec, float z = 0.f);
        //NVector(sf::Vector3f const& vec);

        // Operators

        // Functions
        bool isZero() const;

        bool isNormalized() const;
        void normalize();

        float size() const;
        float sizeSquared() const;

        float size2D() const;
        float sizeSquared2D() const;

        // Statics convertions with libs
};

#endif // NVECTOR_HPP
