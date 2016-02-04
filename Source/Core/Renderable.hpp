#ifndef NRENDERABLE_HPP
#define NRENDERABLE_HPP

#include <SFML/Graphics/RenderTarget.hpp>

class NRenderable
{
    public:
        NRenderable();

        virtual void render(sf::RenderTarget& target);
};

#endif // NRENDERABLE_HPP
