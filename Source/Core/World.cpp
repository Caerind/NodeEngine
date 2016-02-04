#include "World.hpp"

NWorld NWorld::mInstance;

NWorld& NWorld::instance()
{
    return mInstance;
}

void NWorld::addEvent(sf::Event const& event)
{
    mInstance.mEvents.add(event);
}

void NWorld::tick(sf::Time dt)
{
    for (auto itr = mInstance.mTickables.begin(); itr != mInstance.mTickables.end(); itr++)
    {
        (*itr)->tick(dt);
    }
}

bool NWorld::input(sf::Event const& event)
{
    for (auto itr = mInstance.mEvents.begin(); itr != mInstance.mEvents.end(); itr++)
    {
        // TODO : Compare event
        //if (*itr == event)
        {
            //return true;
        }
    }
    return false;
}

void NWorld::render(sf::RenderTarget& target)
{
    // TODO : Sort

    for (auto itr = mInstance.mRenderables.begin(); itr != mInstance.mRenderables.end(); itr++)
    {
        (*itr)->render(target);
    }
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

void NWorld::addActor(NActor* actor)
{
    mInstance.mActorsAdditions.add(actor);
}

void NWorld::removeActor(NActor* actor)
{
    mInstance.mActorsDeletions.add(actor);
}

void NWorld::addRenderable(NRenderable* renderable)
{
    mRenderablesAdditions.add(renderable);
}

void NWorld::removeRenderable(NRenderable* renderable)
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
