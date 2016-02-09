#include "CameraManager.hpp"
#include "../Application/Application.hpp"

NCameraManager::NCameraManager()
{
    mActive = -1;
}

NCameraManager::~NCameraManager()
{
}

void NCameraManager::addCamera(NCameraComponent* camera)
{
    mCameras.add(camera);
    if (mActive == -1 && camera != nullptr)
    {
        mActive = (int)mCameras.size() - 1;
    }
}

void NCameraManager::removeCamera(NCameraComponent* camera)
{
    mCameras.remove(camera);
}

sf::View NCameraManager::getActiveView() const
{
    if (mActive >= 0 && mActive < (int)mCameras.size())
    {
        if (mCameras[mActive] != nullptr)
        {
            return mCameras[mActive]->getView();
        }
    }
    return ah::Application::getWindow().getView();
}
