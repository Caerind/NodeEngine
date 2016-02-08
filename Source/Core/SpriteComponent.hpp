#ifndef NSPRITECOMPONENT_HPP
#define NSPRITECOMPONENT_HPP

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "SceneComponent.hpp"

class NSpriteComponent : public NSceneComponent
{
    public:
        NSpriteComponent();

        void setTexture(sf::Texture& texture);
        void setTextureRect(sf::IntRect const& rect);

        void render(sf::RenderTarget& target);

    private:
        sf::Sprite mSprite;
};

#endif // NSPRITECOMPONENT_HPP
