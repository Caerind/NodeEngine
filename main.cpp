#include <iostream>

#include <SFML/Window/Mouse.hpp>

#include "Source/Application/Application.hpp"
#include "Source/Core/World.hpp"
#include "Source/Core/SpriteComponent.hpp"
#include "Source/Core/InputComponent.hpp"
#include "Source/Core/CameraComponent.hpp"
#include "Source/Core/PointComponent.hpp"

class EActor : public NActor
{
    public:
        EActor()
        {
            attachComponent(&mSpriteComponent);

            mSpriteComponent.setTexture("icon");
            mSpriteComponent.setOrigin(64,64);
        }

        bool contains(NVector const& position)
        {
            return mSpriteComponent.contains(position);
        }

        void load(pugi::xml_node& node)
        {
            mSpriteComponent.load(node,"SpriteC");
        }

        void save(pugi::xml_node& node)
        {
            node.append_attribute("type") = "EActor";
            mSpriteComponent.save(node,"SpriteC");
        }

        NSpriteComponent mSpriteComponent;
};

class TestActor : public NActor
{
    public:
        TestActor()
        {
            attachComponent(&mPointComponent);
            attachComponent(&mInputComponent);
            attachComponent(&mSpriteComponent);
            mSpriteComponent.attachComponent(&mCameraComponent);

            mSpriteComponent.setTexture("icon");
            mSpriteComponent.setOrigin(64,64);

            mInputComponent.setAction("mp",sf::Keyboard::A);
            mInputComponent.setAction("mm",sf::Keyboard::Z);
            mInputComponent.setAction("rp",sf::Keyboard::E);
            mInputComponent.setAction("rm",sf::Keyboard::R);
            mInputComponent.bind("mp",[&](sf::Time dt)
            {
                mSpriteComponent.setPosition(mSpriteComponent.getPosition() + 90 * dt.asSeconds() * NVector::RightVector());
            });
            mInputComponent.bind("mm",[&](sf::Time dt)
            {
                mSpriteComponent.setPosition(mSpriteComponent.getPosition() - 90 * dt.asSeconds() * NVector::RightVector());
            });
            mInputComponent.bind("rp",[&](sf::Time dt)
            {
                mInputComponent.setActorRotation(mInputComponent.getActorRotation() + 180 * dt.asSeconds());
            });
            mInputComponent.bind("rm",[&](sf::Time dt)
            {
                mInputComponent.setActorRotation(mInputComponent.getActorRotation() - 180 * dt.asSeconds());
            });
        }

        void load(pugi::xml_node& node)
        {
            mSpriteComponent.load(node,"Sprite");
            mInputComponent.load(node,"Input");
        }

        void save(pugi::xml_node& node)
        {
            node.append_attribute("type") = "TestActor";
            mSpriteComponent.save(node,"Sprite");
            mInputComponent.save(node,"Input");
        }

    private:
        NPointComponent mPointComponent;
        NInputComponent mInputComponent;
        NSpriteComponent mSpriteComponent;
        NCameraComponent mCameraComponent;
};

class EState : public ah::State
{
    public:
        EState(ah::StateManager& manager) : ah::State(manager)
        {
            NWorld::registerActor<TestActor>();
            NWorld::registerActor<EActor>();

            //mPlayer = NWorld::createActor<TestActor>();
            //mPlayer->setPosition(400,300);

            if (!NWorld::load("t.xml"))
            {
                NLog::log("failed to load");
            }

            mController.setAction("c",sf::Mouse::Left,NAction::Pressed);
            mController.bind("c",[&](sf::Time dt)
            {
                NWorld::createActor<EActor>()->setPosition(NWorld::getMousePositionView() - 10.f * NVector::UpVector());
                NLog::log("added");
            });

            // TODO : test remove actor
            mController.setAction("r",sf::Mouse::Middle,NAction::Pressed);
            mController.bind("r",[&](sf::Time dt)
            {
                std::size_t size = NWorld::getActorCount();
                for (std::size_t i = 0; i < size; i++)
                {
                    NActor::Ptr a = NWorld::getActor(i);
                }
            });

            mController.setAction("quit",sf::Event::Closed);
            mController.bind("quit",[&](sf::Time dt){NWorld::save("t.xml");NLog::log("saved");});
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
        //TestActor::Ptr mPlayer;
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
