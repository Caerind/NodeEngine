#ifndef NWORLD_HPP
#define NWORLD_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>

#include "Renderable.hpp"
#include "Tickable.hpp"
#include "Actor.hpp"
#include "Action.hpp"

#include "../Utils/Array.hpp"

class NWorld
{
    public:
        static NWorld& instance();

        // Add an event to the list
        static void addEvent(sf::Event const& event);

        // Test if an event exist
        //static bool testEvent(sf::Event const& event);
        static bool testAction(NAction const& action);

        // Tick the world
        static void tick(sf::Time dt);

        // Render the world
        static void render(sf::RenderTarget& target);

        // Update the world : use temp array and then clear them
        static void update();

        // Add an actor
        static void addActor(NActor* actor);

        // Remove an actor
        static void removeActor(NActor* actor);

        /* These following arent static cause they shouldn't be use directly */
        void addRenderable(NRenderable* renderable);
        void removeRenderable(NRenderable* renderable);
        void addTickable(NTickable* tickable);
        void removeTickable(NTickable* tickable);

    private:
        NWorld();
        ~NWorld();

        static NWorld mInstance;

    private:
        NArray<sf::Event> mEvents;

        NArray<NActor*> mActors;
        NArray<NActor*> mActorsAdditions;
        NArray<NActor*> mActorsDeletions;

        NArray<NRenderable*> mRenderables;
        NArray<NRenderable*> mRenderablesAdditions;
        NArray<NRenderable*> mRenderablesDeletions;

        NArray<NTickable*> mTickables;
        NArray<NTickable*> mTickablesAdditions;
        NArray<NTickable*> mTickablesDeletions;
};

#endif // NWORLD_HPP
