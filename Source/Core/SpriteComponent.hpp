#ifndef NSPRITECOMPONENT_HPP
#define NSPRITECOMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "SceneComponent.hpp"

class NSpriteComponent : public NSceneComponent
{
    public:
        NSpriteComponent();

        void setOrigin(float x, float y, float z = 0.f);
        void setOrigin(NVector const& origin);
        NVector getOrigin() const;

        void setTexture(sf::Texture& texture);
        void setTextureRect(sf::IntRect const& rect);

        void render(sf::RenderTarget& target);

        bool contains(NVector const& position);

        virtual void load(pugi::xml_node& node, std::string const& name = "SpriteComponent");
        virtual void save(pugi::xml_node& node, std::string const& name = "SpriteComponent");

    private:
        sf::Sprite mSprite;
        NVector mOrigin;
};

#endif // NSPRITECOMPONENT_HPP
