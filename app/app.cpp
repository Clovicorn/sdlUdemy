#include "app.hpp"

App &App::Singleton()
{
    static App theApp;
    return theApp;
}

bool App::Init(uint32_t width, uint32_t height, uint32_t mag)
{
    mWindow = mScreen.Init(width, height, mag);
    if (mWindow)
    {
        SetFPS(mFPS);
        std::unique_ptr<ArcadeScene>
            arcadeScene = std::make_unique<ArcadeScene>();
        PushScene(std::move(arcadeScene));

        // temp setup
        std::unique_ptr<BreakOut> breakOutGame = std::make_unique<BreakOut>();
        std::unique_ptr<GameScene> breakOutScene = std::make_unique<GameScene>(std::move(breakOutGame));
        PushScene(std::move(breakOutScene));
    }

    return mWindow != nullptr;
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
