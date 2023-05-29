#include "titleScreen.hpp"
#include "../app/app.hpp"
#include "../graphics/screen.hpp"
#include "../shapes/aaRectangle.hpp"
#include "../utils/vec2d.hpp"

TitleScreen::TitleScreen() : mScreenWidth(0), mScreenHeight(0), mTimeElapsed(0), mShowMsgLoop(0), mMsgPaused(false), mShowQuitMsg(false)
{
}

void TitleScreen::Init(const std::string &gameName)
{
    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();
    mFont = App::Singleton().GetFont();
    mGameName = gameName;
}

void TitleScreen::Draw(Screen &screen)
{
    screen.SetRenderColor(Color::Black());
    AARectangle rect(Vec2D::Zero, mScreenWidth, mScreenHeight / 2);

    Vec2D pos(mFont.GetDrawPosition(mGameName, rect, BFXA_CENTER, BFYA_CENTER));
    screen.Draw(mFont, mGameName, pos, Color::Red());
    if (!mMsgPaused)
    {
        AARectangle rect2(Vec2D(0, mScreenHeight / 2), mScreenWidth, mScreenHeight / 2);
        if (mShowQuitMsg)
        {

            Vec2D quitPos(mFont.GetDrawPosition(mQuitText, rect2, BFXA_CENTER, BFYA_CENTER));
            screen.Draw(mFont, mQuitText, quitPos);
        }
        else
        {

            Vec2D playPos(mFont.GetDrawPosition(mSpaceText, rect2, BFXA_CENTER, BFYA_CENTER));
            screen.Draw(mFont, mSpaceText, playPos);
        }
    }
}

bool TitleScreen::Update(uint32_t dt)
{
    if (mTimeElapsed == 45 && !mMsgPaused)
    {
        mShowQuitMsg = !mShowQuitMsg;
        mMsgPaused = true;
        mTimeElapsed = 0;
        if (mShowMsgLoop == 4)
        {
            Reset();
            return false;
        }
        else
        {
            mShowMsgLoop++;
        }
    }
    else if (mTimeElapsed == 20 && mMsgPaused)
    {
        mMsgPaused = false;
        mTimeElapsed = 0;
    }
    else
    {
        mTimeElapsed += 1;
    }

    return true;
}

void TitleScreen::Reset()
{
    mTimeElapsed = 0;
    mShowMsgLoop = 0;
    mMsgPaused = false;
    mShowQuitMsg = false;
}