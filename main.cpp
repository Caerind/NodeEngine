#include <iostream>

#include "Source/Application/Application.hpp"
#include "Source/Core/World.hpp"
#include "Source/Core/SpriteComponent.hpp"
#include "Source/Core/InputComponent.hpp"

class TestActor : public NActor
{
    public:
        TestActor() : NActor()
        {
            mSpriteComponent.setTexture(ah::Application::getResources().getTexture("icon"));
            attachComponent(&mSpriteComponent);

            mInputComponent.setAction("m",sf::Keyboard::D,1);
            mInputComponent.bind("m",[&](sf::Time dt){std::cout << "t" << std::endl;});
            attachComponent(&mInputComponent);
        }

    private:
        NInputComponent mInputComponent;
        NSpriteComponent mSpriteComponent;
};

class EState : public ah::State
{
    public:
        EState(ah::StateManager& manager) : ah::State(manager)
        {
            NWorld::addActor(&t);
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

    private:
        TestActor t;
};

int main()
{
    ah::Application::getResources().loadTexture("icon","icon.png");

    ah::Application::getWindow().create(sf::VideoMode(800,600),"NodeEngine");

    ah::Application::getStates().registerState<EState>();
    ah::Application::getStates().pushState<EState>();

    ah::Application::run();

    return 0;
}
