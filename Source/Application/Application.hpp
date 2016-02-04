#ifndef AH_APPLICATION_HPP
#define AH_APPLICATION_HPP

#include "StateManager.hpp"
#include "Window.hpp"
#include "AudioManager.hpp"
#include "ResourceManager.hpp"
#include "LangManager.hpp"
#include "../Utils/Log.hpp"

namespace ah
{

class Application
{
    public:
        static Application& instance();

        static void run();

        static StateManager& getStates();
        static Window& getWindow();
        static AudioManager& getAudio();
        static ResourceManager& getResources();
        static LangManager& getLang();

    private:
        Application();
        ~Application();

        static Application mInstance;

        StateManager mStates;
        Window mWindow;
        AudioManager mAudio;
        ResourceManager mResources;
        LangManager mLang;
};

} // namespace ah

#endif // AH_APPLICATION_HPP
