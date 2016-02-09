#ifndef NCAMERAMANAGER_HPP
#define NCAMERAMANAGER_HPP

#include "CameraComponent.hpp"
#include "../Utils/Array.hpp"

class NCameraManager
{
    public:
        NCameraManager();
        ~NCameraManager();

        void addCamera(NCameraComponent* camera);
        void removeCamera(NCameraComponent* camera);

        sf::View getActiveView() const;

    protected:
        NArray<NCameraComponent*> mCameras;
        int mActive;
};

#endif // NCAMERAMANAGER_HPP
