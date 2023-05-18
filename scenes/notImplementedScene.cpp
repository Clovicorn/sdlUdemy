#include "notImplementedScene.hpp"

#include "../app/app.hpp"
#include "../graphics/bitmapFont.hpp"
#include "../graphics/color.hpp"
#include "../graphics/screen.hpp"
#include "../shapes/aaRectangle.hpp"

void NotImplementedScene::Init()
{
    ButtonAction escapeAction;
    escapeAction.Key = GameController::Cancel();
    escapeAction.Action = [](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            App::Singleton().PopScene();
        }
    };
    mGameController.AddInputActionForKey(escapeAction);
}

void NotImplementedScene::Draw(Screen &screen)
{
    uint32_t width = App::Singleton().Width();
    uint32_t height = App::Singleton().Height();
    std::string notYet = "Not Implemented yet.";
    std::string pressEsc = "press Escape to quit.";
    AARectangle rect1(Vec2D::Zero, width, height / 2);
    AARectangle rect2(Vec2D(0, height / 2), width, height / 2);
    BitmapFont &font = App::Singleton().GetFont();
    Vec2D pos = font.GetDrawPosition(notYet, rect1, BFXA_CENTER, BFYA_CENTER);
    screen.Draw(font, notYet, pos, Color::Red());
    if (!mIsPaused)
    {
        pos = font.GetDrawPosition(pressEsc, rect2, BFXA_CENTER, BFYA_CENTER);
        screen.Draw(font, pressEsc, pos);
    }
}

void NotImplementedScene::Update(uint32_t dt)
{
    if (mTimeElapsed == 45 && !mIsPaused)
    {
        mTimeElapsed = 0;
        mIsPaused = true;
    }
    else if (mTimeElapsed == 20 && mIsPaused)
    {
        mTimeElapsed = 0;
        mIsPaused = false;
    }
    else
    {
        mTimeElapsed++;
    }
}

std::string &NotImplementedScene::GetSceneName()
{
    return mSceneName;
}
