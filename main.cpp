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

            mInputComponent.bind("mp",[&](sf::Time dt)
            {
                mSpriteComponent.setPosition(mSpriteComponent.getPosition() + 90 * dt.asSeconds() * NVector::RightVector());
            },sf::Keyboard::A);
            mInputComponent.bind("mm",[&](sf::Time dt)
            {
                mSpriteComponent.setPosition(mSpriteComponent.getPosition() - 90 * dt.asSeconds() * NVector::RightVector());
            },sf::Keyboard::Z);
            mInputComponent.bind("rp",[&](sf::Time dt)
            {
                setRotation(getRotation() + 180 * dt.asSeconds());
            },sf::Keyboard::E);
            mInputComponent.bind("rm",[&](sf::Time dt)
            {
                setRotation(getRotation() - 180 * dt.asSeconds());
            },sf::Keyboard::R);
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

class GState : public ah::State
{
    public:
        GState(ah::StateManager& manager) : ah::State(manager)
        {
            mSprite.setTexture(NWorld::getResources().getTexture("icon"));
            mSprite.setScale(4.f,2.f);
            mSprite.setOrigin(mSprite.getGlobalBounds().width / 2.f, mSprite.getGlobalBounds().height / 2.f);
            mSprite.setPosition((sf::Vector2f)NWorld::getWindow().getSize() * 0.5f);
            NLog::log("t " + std::to_string(mSprite.getPosition().x));
        }

        bool handleEvent(sf::Event const& event)
        {
            return true;
        }

        bool update(sf::Time dt)
        {
            return true;
        }

        void render(sf::RenderTarget& target, sf::RenderStates)
        {
            target.setView(target.getDefaultView());
            target.draw(mSprite);
        }

    private:
        sf::Sprite mSprite;
};

class EState : public ah::State
{
    public:
        EState(ah::StateManager& manager) : ah::State(manager)
        {
            mGuiOpened = false;

            NWorld::registerActor<TestActor>();
            NWorld::registerActor<EActor>();

            //mPlayer = NWorld::createActor<TestActor>();
            //mPlayer->setPosition(400,300);

            if (!NWorld::load("t.xml"))
            {
                NLog::log("failed to load");
            }

            mController.bind("c",[&](sf::Time dt)
            {
                EActor::Ptr e = NWorld::createActor<EActor>();
                std::string id;
                if (e != nullptr)
                {
                    e->setPosition(NWorld::getMousePositionView() - 10.f * NVector::UpVector());
                    id = e->getId();
                }

                NWorld::setTimer(sf::seconds(2.f),[id]()
                {
                    NWorld::removeActor(id);
                    NLog::log("removed");
                });

                NLog::log("added");
            },sf::Mouse::Left,NAction::Pressed);

            mController.bind("quit",[&](sf::Time dt){NWorld::save("t.xml");NLog::log("saved");},sf::Event::Closed);

            mController.bind("gui",[&](sf::Time dt)
            {
                mGuiOpened = !mGuiOpened;
                if (mGuiOpened)
                {
                    requestPush(NString::type<GState>());
                }
                else
                {
                    requestPop();
                }
            },sf::Keyboard::E,NAction::Pressed);
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

        bool mGuiOpened;
};

int main()
{
    ah::Application::getResources().loadTexture("icon","icon.png");

    ah::Application::getWindow().create(sf::VideoMode(800,600),"NodeEngine");
    ah::Application::getWindow().showDebugInfo(true);
    ah::Application::getWindow().setDebugInfoFont("sansation.ttf");

    ah::Application::getStates().registerState<EState>();
    ah::Application::getStates().registerState<GState>();
    ah::Application::getStates().pushState<EState>();

    ah::Application::run();

    return 0;
}
