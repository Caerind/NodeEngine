#include "Vector.hpp"

const NVector NVector::UpVector()
{
    return NVector(0.f,0.f,1.f);
}

const NVector NVector::RightVector()
{
    return NVector(0.f,1.f,0.f);
}

const NVector NVector::ForwardVector()
{
    return NVector(1.f,0.f,0.f);
}

const NVector NVector::ZeroVector()
{
    return NVector(0.f,0.f,0.f);
}

NVector::NVector()
{
    x = 0.f;
    y = 0.f;
    z = 0.f;
}

NVector::NVector(float value)
{
    x = value;
    y = value;
    z = value;
}

NVector::NVector(float xA, float yA, float zA)
{
    x = xA;
    y = yA;
    z = zA;
}

bool NVector::isZero() const
{
    return (x == 0.f && y == 0.f && z == 0.f);
}

bool NVector::isNormalized() const
{
    return size() == 1.f;
}

void NVector::normalize()
{
    float n = size();
    if (n != 0.f)
    {
        x /= n;
        y /= n;
        z /= n;
    }
}

float NVector::size() const
{
    return std::sqrt(sizeSquared());
}

float NVector::sizeSquared() const
{
    return (x*x + y*y + z*z);
}

float NVector::size2D() const
{
    return std::sqrt(sizeSquared2D());
}

float NVector::sizeSquared2D() const
{
    return (x*x + y*y);
}
