#include <iostream>

#include <SFML/Window/Mouse.hpp>

#include "Source/Application/Application.hpp"
#include "Source/Core/World.hpp"
#include "Source/Core/SpriteComponent.hpp"
#include "Source/Core/InputComponent.hpp"
#include "Source/Core/CameraComponent.hpp"

class EActor : public NActor
{
    public:
        EActor()
        {
            mSpriteComponent.setTexture(ah::Application::getResources().getTexture("icon"));
            attachComponent(&mSpriteComponent);
        }

        bool contains(NVector const& position)
        {
            return mSpriteComponent.contains(position);
        }

        void save(pugi::xml_node& node)
        {
            pugi::xml_node n = node.append_child("Sprite");
            mSpriteComponent.save(n);
        }

        NSpriteComponent mSpriteComponent;
};

class TestActor : public NActor
{
    public:
        TestActor()
        {
            setPosition(400,300);

            mSpriteComponent.setTexture(ah::Application::getResources().getTexture("icon"));
            attachComponent(&mSpriteComponent);

            mSpriteComponent.attachComponent(&mCameraComponent);

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
        NCameraComponent mCameraComponent;
};

class EState : public ah::State
{
    public:
        EState(ah::StateManager& manager) : ah::State(manager)
        {
            mPlayer = NWorld::createActor<TestActor>();
            mController.setAction("c1",sf::Mouse::Left,NAction::Pressed);
            mController.bind("c1",[&](sf::Time dt)
            {
                NWorld::createActor<EActor>()->setPosition(NWorld::getMousePositionView() - 10.f * NVector::UpVector());
                std::cout << "added" << std::endl;
            });

            mController.setAction("c2",sf::Mouse::Right,NAction::Pressed);
            mController.bind("c2",[&](sf::Time dt)
            {
                NWorld::save("t.xml");
                std::cout << "saved" << std::endl;
            });

            mController.setAction("d",sf::Mouse::Middle,NAction::Pressed);
            mController.bind("d",[&](sf::Time dt)
            {
                std::size_t size = NWorld::getActorCount();
                for (std::size_t i = 0; i < size; i++)
                {
                    NActor::Ptr a = NWorld::getActor(i);
                }
            });
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
            ah::Application::getWindow().setDebugInfo("Actors",std::to_string(NWorld::getActorCount()));
            ah::Application::getWindow().setDebugInfo("Tickables",std::to_string(NWorld::getTickableCount()));
            ah::Application::getWindow().setDebugInfo("Renderables",std::to_string(NWorld::getRenderableCount()));
            return true;
        }

        void render(sf::RenderTarget& target, sf::RenderStates states)
        {
            NWorld::render(target);
        }

    private:
        TestActor::Ptr mPlayer;
        NActionTarget mController;
};

int main()
{
    ah::Application::getResources().loadTexture("icon","icon.png");

    ah::Application::getWindow().create(sf::VideoMode(800,600),"NodeEngine");
    ah::Application::getWindow().showDebugInfo(true);
    ah::Application::getWindow().setDebugInfoFont("sansation.ttf");

    ah::Application::getStates().registerState<EState>();
    ah::Application::getStates().pushState<EState>();

    ah::Application::run();

    return 0;
}
