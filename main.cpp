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
            setPosition(400,300);

            mSpriteComponent.setTexture(ah::Application::getResources().getTexture("icon"));
            attachComponent(&mSpriteComponent);

            mInputComponent.setAction("m+",sf::Keyboard::D);
            mInputComponent.bind("m+",[&](sf::Time dt)
            {
                mSpriteComponent.setPosition(mSpriteComponent.getPosition() + 90 * dt.asSeconds() * NVector::RightVector());
            });
            mInputComponent.setAction("m-",sf::Keyboard::Q);
            mInputComponent.bind("m-",[&](sf::Time dt)
            {
                mSpriteComponent.setPosition(mSpriteComponent.getPosition() - 90 * dt.asSeconds() * NVector::RightVector());
            });

            mInputComponent.setAction("r+",sf::Keyboard::Z);
            mInputComponent.bind("r+",[&](sf::Time dt)
            {
                mInputComponent.setActorRotation(mInputComponent.getActorRotation() + 180 * dt.asSeconds());
            });
            mInputComponent.setAction("r-",sf::Keyboard::S);
            mInputComponent.bind("r-",[&](sf::Time dt)
            {
                mInputComponent.setActorRotation(mInputComponent.getActorRotation() - 180 * dt.asSeconds());
            });
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
