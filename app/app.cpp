#include "app.hpp"

#include "../scenes/arcadeScene.hpp"
#include "../games/tetris/tetris.hpp"
#include "../scenes/gameScene.hpp"

App &App::Singleton()
{
    static App theApp;
    return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
    if (!mFont.Load("ArcadeFont"))
    {
        std::cout << "Failed to load font" << std::endl;
        return false;
    }
    mWindow = mScreen.Init(width, height, mag);
    if (mWindow)
    {
        SetFPS(mFPS);
        std::unique_ptr<ArcadeScene>
            arcadeScene = std::make_unique<ArcadeScene>();
        PushScene(std::move(arcadeScene));
        /* Temp Section*/
        std::unique_ptr<Tetris> tetris = std::make_unique<Tetris>();
        std::unique_ptr<GameScene> tetrisGame = std::make_unique<GameScene>(std::move(tetris));
        PushScene(std::move(tetrisGame));

        /* */
    }

    return mWindow != nullptr;
}

void App::SetRendererClearColor(const Color &color)
{
    mScreen.SetRenderColor(color);
}

void App::SetFPS(float fps)
{
    mFPS = fps;
    mDT = 1 / mFPS * 1000;
}

void App::PushScene(std::unique_ptr<Scene> scene)
{
    if (scene)
    {
        scene->Init();
        mInputController.SetGameController(scene->GetGameController());
        mScenes.emplace_back(std::move(scene));
        SDL_SetWindowTitle(mWindow, CurrentScene()->GetSceneName().c_str());
    }
}

void App::PopScene()
{
    if (mScenes.size() > 1)
    {
        mScenes.pop_back();
    }
    if (CurrentScene())
    {
        SDL_SetWindowTitle(mWindow, CurrentScene()->GetSceneName().c_str());
        mInputController.SetGameController(CurrentScene()->GetGameController());
    }
}

Scene *App::CurrentScene()
{
    if (mScenes.empty())
    {
        return nullptr;
    }
    return mScenes.back().get();
}

void App::Run()
{

    uint32_t lastTick = SDL_GetTicks();
    uint32_t currentTick = lastTick;

    uint32_t accumulator = 0;

    bool running = true;
    mInputController.Init([&running](uint32_t dt, InputState state)
                          { running = false; });
    while (running)
    {
        currentTick = SDL_GetTicks();
        uint32_t frameTime = currentTick - lastTick;

        if (frameTime > 300)
        {
            frameTime = 300;
        }
        accumulator += frameTime;

        // get input
        mInputController.Update(mDT);
        // updat area
        Scene *currentScene = App::CurrentScene();
        if (currentScene)
        {
            while (accumulator >= mDT)
            {

                currentScene->Update(mDT);
                accumulator -= int(mDT);
            }

            currentScene->Draw(mScreen);
        }

        mScreen.SwapScreen();
        lastTick = currentTick;
    }
}

const std::string &App::GetBasePath()
{
    static std::string basePath = SDL_GetBasePath();
    return basePath;
}