#include "Renderable.hpp"
#include "World.hpp"

NRenderable::NRenderable()
{
    NWorld::instance().addRenderable(this);
}

NRenderable::~NRenderable()
{
    NWorld::instance().removeRenderable(this);
}

void NRenderable::render(sf::RenderTarget& target)
{
}
