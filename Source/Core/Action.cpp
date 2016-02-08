#include "Action.hpp"

NAction::NAction()
{
}

NAction::NAction(sf::Mouse::Button button, int type)
{
    setMouseButton(button,type);
}

NAction::NAction(sf::Keyboard::Key key, int type)
{
    setKeyboardKey(key,type);
}

NAction::NAction(sf::Event::EventType const& type)
{
    setEventType(type);
}

void NAction::setMouseButton(sf::Mouse::Button button, int type)
{
    mEvent.mouseButton.button = button;
    mEvent.type = sf::Event::MouseButtonPressed;
    if (mType & Type::Released)
    {
        mEvent.type = sf::Event::MouseButtonReleased;
    }
    mType = type;
}

sf::Mouse::Button NAction::getMouseButton() const
{
    if (isMouseAction())
    {
        return mEvent.mouseButton.button;
    }
    else
    {
        return sf::Mouse::ButtonCount;
    }
}

void NAction::setKeyboardKey(sf::Keyboard::Key key, int type)
{
    mEvent.key.code = key;
    mEvent.type = sf::Event::KeyPressed;
    if (mType & Type::Released)
    {
        mEvent.type = sf::Event::KeyReleased;
    }
    mType = type;
}

sf::Keyboard::Key NAction::getKeyboardKey() const
{
    if (isKeyboardAction())
    {
        return mEvent.key.code;
    }
    return sf::Keyboard::Unknown;
}

void NAction::setEventType(sf::Event::EventType const& event)
{
    mEvent.type = event;
    mType = Type::Pressed;
}

sf::Event::EventType NAction::getEventType() const
{
    return mEvent.type;
}

void NAction::setType(int type)
{
    mType = type;
}

int NAction::getType() const
{
    return mType;
}

bool NAction::isMouseAction() const
{
    return (mEvent.type == sf::Event::MouseButtonPressed || mEvent.type == sf::Event::MouseButtonReleased);
}

bool NAction::isKeyboardAction() const
{
    return (mEvent.type == sf::Event::KeyPressed || mEvent.type == sf::Event::KeyReleased);
}

bool NAction::test() const
{
    if (mType & Type::Realtime)
    {
        // Keyboard
        if ((mEvent.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(mEvent.key.code))
        || (mEvent.type == sf::Event::KeyReleased && !sf::Keyboard::isKeyPressed(mEvent.key.code)))
        {
            return true;
        }
        // Mouse
        if ((mEvent.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(mEvent.mouseButton.button))
        || (mEvent.type == sf::Event::MouseButtonReleased && !sf::Mouse::isButtonPressed(mEvent.mouseButton.button)))
        {
            return true;
        }
    }
    return false;
}

bool NAction::operator==(sf::Event const& event) const
{
    if (mEvent.type == event.type)
    {
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            return (mEvent.key.code == event.key.code);
        }
        else if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
        {
            return (mEvent.mouseButton.button == event.mouseButton.button);
        }
        return true;
    }
    return false;
}

bool NAction::operator==(NAction const& action) const
{
    return (mType == action.mType && action == mEvent);
}
