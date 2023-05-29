#ifndef GAMES_TITLE_H
#define GAMES_TITLE_H

#include <stdint.h>
#include <string>
#include "../graphics/bitmapFont.hpp"

class Screen;

class TitleScreen
{
public:
    TitleScreen();
    void Init(const std::string &gameName);
    void Draw(Screen &screen);
    bool Update(uint32_t dt);

private:
    void Reset();

    BitmapFont mFont;
    uint32_t mScreenWidth;
    uint32_t mScreenHeight;
    int mTimeElapsed;
    int mShowMsgLoop;

    bool mMsgPaused;
    bool mShowQuitMsg;

    std::string mGameName;
    std::string mQuitText = "Press Escape to quit.";
    std::string mSpaceText = "Press Space to play.";
};

#endif /* GAMES_TITLE_H */