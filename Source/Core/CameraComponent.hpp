#ifndef NCAMERACOMPONENT_HPP
#define NCAMERACOMPONENT_HPP

#include "Component.hpp"
#include <SFML/Graphics/View.hpp>

class NCameraComponent : public NComponent
{
    public:
        NCameraComponent();
        ~NCameraComponent();

        sf::View getView() const;

        void tick(sf::Time dt);

    private:
        sf::View mView;
};

#endif // NCAMERACOMPONENT_HPP
