#include "World.hpp"
#include "../Application/Application.hpp"

NWorld NWorld::mInstance;

NWorld& NWorld::instance()
{
    return mInstance;
}

void NWorld::addEvent(sf::Event const& event)
{
    mInstance.mEvents.add(event);
}

/*
bool NWorld::testEvent(sf::Event const& event)
{
    for (std::size_t i = 0; i < mInstance.mEvents.size(); i++)
    {
        if (event == mInstance.mEvents[i])
        {
            return true;
        }
    }
    return false;
}*/

bool NWorld::testAction(NAction const& action)
{
    for (std::size_t i = 0; i < mInstance.mEvents.size(); i++)
    {
        if (action == mInstance.mEvents[i])
        {
            return true;
        }
    }
    return false;
}

void NWorld::tick(sf::Time dt)
{
    for (auto itr = mInstance.mTickables.begin(); itr != mInstance.mTickables.end(); itr++)
    {
        (*itr)->tick(dt);
    }
}

void NWorld::render(sf::RenderTarget& target)
{
    mInstance.mRenderables.sort([](NSceneComponent* a, NSceneComponent* b) -> bool
    {
       if (a != nullptr && b != nullptr)
       {
           if (a->getFinalZ() < b->getFinalZ())
           {
                return true;
           }
           else if (a->getFinalZ() > b->getFinalZ())
           {
               return false;
           }
           else
           {
               return (a->getFinalPosition().y < b->getFinalPosition().y);
           }
       }
       return true;
    });

    sf::View old = target.getView();
    target.setView(mInstance.mCameraManager.getActiveView());
    for (auto itr = mInstance.mRenderables.begin(); itr != mInstance.mRenderables.end(); itr++)
    {
        (*itr)->render(target);
    }
    target.setView(old);
}

void NWorld::update()
{
    // Events
    mInstance.mEvents.clear();

    // Renderables
    for (std::size_t i = 0; i < mInstance.mRenderablesAdditions.size(); i++)
    {
        mInstance.mRenderables.add(mInstance.mRenderablesAdditions[i]);
    }
    mInstance.mRenderablesAdditions.clear();
    for (std::size_t i = 0; i < mInstance.mRenderablesDeletions.size(); i++)
    {
        mInstance.mRenderables.remove(mInstance.mRenderablesDeletions[i]);
    }
    mInstance.mRenderablesDeletions.clear();

    // Tickables
    for (std::size_t i = 0; i < mInstance.mTickablesAdditions.size(); i++)
    {
        mInstance.mTickables.add(mInstance.mTickablesAdditions[i]);
    }
    mInstance.mTickablesAdditions.clear();
    for (std::size_t i = 0; i < mInstance.mTickablesDeletions.size(); i++)
    {
        mInstance.mTickables.remove(mInstance.mTickablesDeletions[i]);
    }
    mInstance.mTickablesDeletions.clear();

    // Actors
    for (std::size_t i = 0; i < mInstance.mActorsAdditions.size(); i++)
    {
        mInstance.mActors.add(mInstance.mActorsAdditions[i]);
    }
    mInstance.mActorsAdditions.clear();
    for (std::size_t i = 0; i < mInstance.mActorsDeletions.size(); i++)
    {
        mInstance.mActors.remove(mInstance.mActorsDeletions[i]);
    }
    mInstance.mActorsDeletions.clear();
}

void NWorld::removeActor(NActor::Ptr actor)
{
    mInstance.mActorsDeletions.add(actor);
}

NCameraManager& NWorld::getCameraManager()
{
    return mInstance.mCameraManager;
}

std::size_t NWorld::getActorCount()
{
    return mInstance.mActors.size();
}

std::size_t NWorld::getRenderableCount()
{
    return mInstance.mRenderables.size();
}

std::size_t NWorld::getTickableCount()
{
    return mInstance.mTickables.size();
}

NVector NWorld::getMousePositionScreen()
{
    return NVector::SFML2FToN(ah::Application::getWindow().getMousePosition());
}

NVector NWorld::getMousePositionView()
{
    return NVector::SFML2FToN(ah::Application::getWindow().getMousePositionView(mInstance.mCameraManager.getActiveView()));
}


void NWorld::addRenderable(NSceneComponent* renderable)
{
    mRenderablesAdditions.add(renderable);
}

void NWorld::removeRenderable(NSceneComponent* renderable)
{
    mRenderablesDeletions.add(renderable);
}

void NWorld::addTickable(NTickable* tickable)
{
    mTickablesAdditions.add(tickable);
}

void NWorld::removeTickable(NTickable* tickable)
{
    mTickablesDeletions.add(tickable);
}

NWorld::NWorld()
{
}

NWorld::~NWorld()
{
}
