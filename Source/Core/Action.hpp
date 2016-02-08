#ifndef NACTION_HPP
#define NACTION_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

class NAction
{
    public:
        enum Type
        {
            Realtime = 1,
            Pressed = 1 << 1,
            Released = 1 << 2
        };

        NAction();
        NAction(sf::Mouse::Button button, int type = Type::Realtime | Type::Pressed);
        NAction(sf::Keyboard::Key key, int type = Type::Realtime | Type::Pressed);
        NAction(sf::Event::EventType const& type);

        void setMouseButton(sf::Mouse::Button button, int type = Type::Realtime | Type::Pressed);
        sf::Mouse::Button getMouseButton() const;

        void setKeyboardKey(sf::Keyboard::Key key, int type = Type::Realtime | Type::Pressed);
        sf::Keyboard::Key getKeyboardKey() const;

        void setEventType(sf::Event::EventType const& event);
        sf::Event::EventType getEventType() const;

        void setType(int type);
        int getType() const;

        bool isMouseAction() const;
        bool isKeyboardAction() const;

        bool test() const;

        bool operator==(sf::Event const& event) const;
        bool operator==(NAction const& action) const;

        // TODO : Static functions to convert keys/buttons to strings

    protected:
        sf::Event mEvent;
        int mType;
};

#endif // NACTION_HPP
