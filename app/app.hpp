#ifndef APP_H
#define APP_H

#include <stdint.h>
#include <SDL2/SDL.h>
#include <memory>
#include <vector>

#include "../input/inputController.hpp"
#include "../graphics/bitmapFont.hpp"
#include "../graphics/screen.hpp"

class Scene;

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
    void SetRendererClearColor(const Color &color);

    inline uint32_t Width() { return mScreen.Width(); }
    inline uint32_t Height() { return mScreen.Height(); }
    static const std::string &GetBasePath();
    inline BitmapFont &GetFont() { return mFont; }

private:
    float mFPS = 30.0f;
    float mDT = 1 / mFPS * 1000;
    Screen mScreen;
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer = nullptr;
    std::vector<std::unique_ptr<Scene>> mScenes;
    InputController mInputController;
    BitmapFont mFont;
};

#endif /* APP_H */