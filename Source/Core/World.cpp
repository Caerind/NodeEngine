#include "World.hpp"
#include <SFML/Graphics/RenderTexture.hpp>

NWorld* NWorld::mInstance = nullptr;

NWorld& NWorld::instance()
{
	if (mInstance == nullptr)
	{
		mInstance = new NWorld();
	}
    return *mInstance;
}

void NWorld::addEvent(sf::Event const& event)
{
    add(instance().mEvents,event);
}

/*
bool NWorld::testEvent(sf::Event const& event)
{
    for (std::size_t i = 0; i < instance().mEvents.size(); i++)
    {
        if (event == instance().mEvents[i])
        {
            return true;
        }
    }
    return false;
}*/

/*
bool NWorld::testAction(NAction const& action)
{
    for (std::size_t i = 0; i < instance().mEvents.size(); i++)
    {
        if (action == instance().mEvents[i])
        {
            return true;
        }
    }
    return false;
}*/

void NWorld::tick(sf::Time dt)
{
    // Actors
    std::size_t s2, s1 = instance().mActorsDeletions.size();
    for (std::size_t i = 0; i < s1; i++)
    {
        s2 = instance().mActors.size();
        for (std::size_t j = 0; j < s2; j++)
        {
            if (instance().mActors[j]->getId() == instance().mActorsDeletions[i])
            {
                erase(instance().mActors,j);
                break;
            }
        }
    }
    instance().mActorsDeletions.clear();

    // Tickables
    s1 = instance().mTickableAdditions.size();
    for (std::size_t i = 0; i < s1; i++)
    {
        add(instance().mTickables,instance().mTickableAdditions[i]);
    }
    instance().mTickableAdditions.clear();

    s2 = instance().mTickableDeletions.size();
    for (std::size_t i = 0; i < s2; i++)
    {
        remove(instance().mTickables,instance().mTickableDeletions[i]);
    }
    instance().mTickableDeletions.clear();

    // Tickables
    for (auto itr = instance().mTickables.begin(); itr != instance().mTickables.end(); itr++)
    {
        if (!(*itr)->hasTicked())
        {
            (*itr)->tick(dt);
            (*itr)->ticked();
        }
        std::size_t s = instance().mTickableDeletions.size();
        if (s > 0)
        {
            for (std::size_t i = 0; i < s; i++)
            {
                remove(instance().mTickables,instance().mTickableDeletions[i]);
            }
            instance().mTickableDeletions.clear();
            itr = instance().mTickables.begin();
        }
    }
    for (auto itr = instance().mTickables.begin(); itr != instance().mTickables.end(); itr++)
    {
        (*itr)->unticked();
    }

    // Timers
    for (auto itr = instance().mTimers.begin(); itr != instance().mTimers.end(); itr++)
    {
        itr->second.update(dt);
    }

    // Events
    instance().mEvents.clear();
}

void NWorld::render()
{
    instance().mGraphics.render(getWindow());
}

void NWorld::clear()
{
    instance().mEvents.clear();
    instance().mActors.clear();
    instance().mActorsDeletions.clear();
    instance().mTickables.clear();
    instance().mTimers.clear();
    instance().mGraphics.clear();
    instance().mGraphics.updateRenderSize(getWindow().getSize());
}

NActor::Ptr NWorld::getActor(std::size_t index)
{
    if (validIndex(instance().mActors,index))
    {
        return instance().mActors[index];
    }
    return nullptr;
}

NActor::Ptr NWorld::getActor(std::string const& id)
{
    std::size_t size = instance().mActors.size();
    for (std::size_t i = 0; i < size; i++)
    {
        if (instance().mActors[i]->getId() == id)
        {
            return instance().mActors[i];
        }
    }
    return nullptr;
}

void NWorld::removeActor(std::size_t index)
{
    NActor::Ptr a = getActor(index);
    if (a != nullptr)
    {
        add(instance().mActorsDeletions,a->getId());
    }
}

void NWorld::removeActor(std::string const& id)
{
    add(instance().mActorsDeletions,id);
}

bool NWorld::load(std::string const& filename)
{
    pugi::xml_document doc;
    if (!doc.load_file(filename.c_str()))
    {
        return false;
    }
    pugi::xml_node actors = doc.child("Actors");
    if (!actors)
    {
        return false;
    }
    for (pugi::xml_node actor = actors.first_child(); actor; actor = actor.next_sibling())
    {
        std::string type = actor.attribute("type").value();
        if (contains(instance().mActorFactory,type))
        {
            auto a = instance().mActorFactory[type]();
            a->load(actor);
            a->NActor::load(actor);
            add(instance().mActors,a);
        }
    }

    return true;
}

bool NWorld::save(std::string const& filename)
{
    pugi::xml_document doc;
    pugi::xml_node actors = doc.append_child("Actors");
    std::size_t size = getActorCount();
    for (std::size_t i = 0; i < size; i++)
    {
        pugi::xml_node actor = actors.append_child("Actor");
        if (actor)
        {
            auto a = getActor(i);
            if (a != nullptr)
            {
                a->save(actor);
                a->NActor::save(actor);
            }
        }
    }
    doc.save_file(filename.c_str());
    return true;
}

NCameraManager& NWorld::getCameraManager()
{
    return instance().mGraphics.getCameraManager();
}

sf::View& NWorld::getActiveView()
{
    return instance().mGraphics.getCameraManager().getActiveView();
}

std::size_t NWorld::getActorCount()
{
    return instance().mActors.size();
}

std::size_t NWorld::getRenderableCount()
{
    return instance().mGraphics.getRenderableCount();
}

std::size_t NWorld::getTickableCount()
{
    return instance().mTickables.size();
}

sf::Vector2f NWorld::getPointerPositionScreen(int touchIndex)
{
    return getWindow().getPointerPosition(touchIndex);
}

sf::Vector2f NWorld::getPointerPositionView(int touchIndex)
{
    return getWindow().getPointerPositionView(getActiveView(),touchIndex);
}

ah::ResourceManager& NWorld::getResources()
{
    return ah::Application::getResources();
}

ah::Window& NWorld::getWindow()
{
    return ah::Application::getWindow();
}

ah::ValueContainer& NWorld::getValues()
{
    return ah::Application::getValues();
}

std::string NWorld::setTimer(sf::Time duration, NTimer::Callback callback)
{
    std::string handle = std::to_string(++instance().mTimerHandleCounter);
    instance().mTimers[handle].setCallback(callback);
    instance().mTimers[handle].reset(duration);
    return handle;
}

std::string NWorld::startTimer()
{
    std::string handle = std::to_string(++instance().mTimerHandleCounter);
    instance().mTimers[handle].reset(sf::Time::Zero);
    return handle;
}

sf::Time NWorld::getTimerElapsed(std::string const& handle)
{
    if (contains(instance().mTimers,handle))
    {
        return instance().mTimers[handle].getElapsedTime();
    }
    return sf::Time::Zero;
}

sf::Time NWorld::getTimerRemaining(std::string const& handle)
{
    if (contains(instance().mTimers,handle))
    {
        return instance().mTimers[handle].getRemaining();
    }
    return sf::Time::Zero;
}

sf::Time NWorld::getTimerDuration(std::string const& handle)
{
    if (contains(instance().mTimers,handle))
    {
        return instance().mTimers[handle].getDuration();
    }
    return sf::Time::Zero;
}

void NWorld::repeatTimer(std::string const& handle, bool repeat)
{
    if (contains(instance().mTimers,handle))
    {
        instance().mTimers[handle].setRepeat(repeat);
    }
}

void NWorld::playTimer(std::string const& handle)
{
    if (contains(instance().mTimers,handle))
    {
        instance().mTimers[handle].play();
    }
}

void NWorld::pauseTimer(std::string const& handle)
{
    if (contains(instance().mTimers,handle))
    {
        instance().mTimers[handle].pause();
    }
}

void NWorld::resetTimer(std::string const& handle, sf::Time newDuration)
{
    if (contains(instance().mTimers,handle))
    {
        instance().mTimers[handle].reset(newDuration);
    }
}

void NWorld::stopTimer(std::string const& handle)
{
    remove(instance().mTimers,handle);
}

void NWorld::addRenderable(NSceneComponent* renderable)
{
    mGraphics.addRenderable(renderable);
}

void NWorld::removeRenderable(NSceneComponent* renderable)
{
    mGraphics.removeRenderable(renderable);
}

void NWorld::addTickable(NTickable* tickable)
{
    add(mTickableAdditions,tickable);
}

void NWorld::removeTickable(NTickable* tickable)
{
    add(mTickableDeletions,tickable);
}

NParticleSystem::Ptr NWorld::getParticleSystem(std::string const& systemId)
{
    return instance().mGraphics.getParticleSystem(systemId);
}

void NWorld::removeParticleSystem(std::string const& systemId)
{
    instance().mGraphics.removeParticleSystem(systemId);
}

std::size_t NWorld::getParticleSystemCount()
{
    return instance().mGraphics.getParticleSystemCount();
}

void NWorld::needUpdateOrder()
{
    instance().mGraphics.needUpdateOrder();
}

NWorld::NWorld()
{
}

NWorld::~NWorld()
{
}
