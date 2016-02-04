#include <iostream>

#include "Source/Application/Application.hpp"
#include "Source/Core/World.hpp"

class EState : public ah::State
{
    public:
        EState(ah::StateManager& manager) : ah::State(manager)
        {
        }

        bool handleEvent(sf::Event const& event)
        {
            NWorld::addEvent(event);
            return true;
        }

        bool update(sf::Time dt)
        {
            NWorld::tick(dt);
            NWorld::update();
            return true;
        }

        void render(sf::RenderTarget& target, sf::RenderStates states)
        {
            NWorld::render(target);
        }
};

int main()
{
    ah::Application::getWindow().create(sf::VideoMode(800,600),"NodeEngine");

    ah::Application::getStates().registerState<EState>();
    ah::Application::getStates().pushState<EState>();

    ah::Application::run();

    return 0;
}
