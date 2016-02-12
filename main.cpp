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
            mSpriteComponent.setTexture(ah::Application::getResources().getTexture("icon"));
            mSpriteComponent.setOrigin(64,64);
            attachComponent(&mSpriteComponent);
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

            mSpriteComponent.setTexture(ah::Application::getResources().getTexture("icon"));
            mSpriteComponent.setOrigin(64,64);
            attachComponent(&mSpriteComponent);

            attachComponent(&mCameraComponent);

            mInputComponent.setAction("mp",sf::Keyboard::D);
            mInputComponent.bind("mp",[&](sf::Time dt)
            {
                mSpriteComponent.setPosition(mSpriteComponent.getPosition() + 90 * dt.asSeconds() * NVector::RightVector());
            });
            mInputComponent.setAction("mm",sf::Keyboard::Q);
            mInputComponent.bind("mm",[&](sf::Time dt)
            {
                mSpriteComponent.setPosition(mSpriteComponent.getPosition() - 90 * dt.asSeconds() * NVector::RightVector());
            });

            mInputComponent.setAction("rp",sf::Keyboard::Z);
            mInputComponent.bind("rp",[&](sf::Time dt)
            {
                mInputComponent.setActorRotation(mInputComponent.getActorRotation() + 180 * dt.asSeconds());
            });
            mInputComponent.setAction("rm",sf::Keyboard::S);
            mInputComponent.bind("rm",[&](sf::Time dt)
            {
                mInputComponent.setActorRotation(mInputComponent.getActorRotation() - 180 * dt.asSeconds());
            });
            attachComponent(&mInputComponent);
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
                NLog::log("failed");
            }

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
