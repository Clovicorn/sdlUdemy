#ifndef APP_H
#define APP_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "../input/inputController.hpp"

// #include "../utils/vec2d.hpp"

#include "../games/tetris/tetris.hpp"
// #include "../games/game.hpp"

// #include "../graphics/color.hpp"
#include "../graphics/screen.hpp"

#include "../scenes/arcadeScene.hpp"
// #include "../scenes/scene.hpp"
#include "../scenes/gameScene.hpp"

class App
{
public:
    static App &Singleton();
    bool Init(uint32_t width, uint32_t height, uint32_t mag);
    void Run();
    void SetFPS(float fps);

    void PushScene(std::unique_ptr<Scene> scene);
    void PopScene();
    Scene *CurrentScene();

    inline uint32_t Width() { return mScreen.Width(); }
    inline uint32_t Height() { return mScreen.Height(); }
    static const std::string &GetBasePath();

private:
    float mFPS = 30.0f;
    float mDT = 1 / mFPS * 1000;
    Screen mScreen;
    SDL_Window *mWindow;
    std::vector<std::unique_ptr<Scene>> mScenes;
    InputController mInputController;
};

#endif /* APP_H */