#ifndef NCOMPONENT_HPP
#define NCOMPONENT_HPP

#include "../Utils/Array.hpp"
#include "../Utils/Pugixml.hpp"

#include "Tickable.hpp"
#include "Transformable.hpp"

class NComponent : public NTickable, public NTransformable
{
    public:
        NComponent();

        void attachComponent(NComponent* component);
        void detachComponent(NComponent* component);

        float getFinalZ() const;
        NVector getFinalPosition() const;
        NVector getActorPosition() const;
        NVector getActorScale() const;
        float getActorRotation() const;
        sf::Transform getFinalTransform() const;

        void setActorPosition(NVector const& position);
        void setActorScale(NVector const& scale);
        void setActorRotation(float rotation);

        virtual void save(pugi::xml_node& node);

    protected:
        NArray<NComponent*> mComponents;
        NComponent* mParent;
};

#endif // NCOMPONENT_HPP
