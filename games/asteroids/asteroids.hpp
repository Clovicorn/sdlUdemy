#ifndef ASTEROIDS_ASTEROIDS_H
#define ASTEROIDS_ASTEROIDS_H

#include <string>
#include <vector>

#include "ship.hpp"
#include "rock.hpp"

#include "../game.hpp"
#include "../highScores.hpp"
#include "../titleScreen.hpp"
#include "../../graphics/spriteSheet.hpp"
#include "../../graphics/animationPlayer.hpp"
#include "../../graphics/bitmapFont.hpp"

class Screen;

enum AsteroidsState
{
    ASTEROIDS_TITLE = 0,
    ASTEROIDS_SCORE,
    ASTEROIDS_COUNTDOWN,
    ASTEROIDS_PLAYING,
    ASTEROIDS_GAMEOVER,
};

class Asteroids : public Game
{
public:
    Asteroids();
    virtual void Init(GameController &controller) override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen &screen) override;
    virtual std::string GetName() override;

private:
    void CreateControls(GameController &controller);
    void SwapState();
    void ResetCurrentGame();
    void LostLife();

    std::string mGameName = "Asteroids";
    std::string mHighScoresFile = "assets/Asteroids/AsteroidsHighScores.txt";
    std::string mAnimationsFile = "assets/Asteroids/AsteroidsAnimations.txt";
    std::string mSpriteSheetFile = "/Asteroids/AsteroidsSprites";

    const int COUNTDOWN_FADE = 4;
    int mCountDown;
    int mTimeElapsed;
    int mLives;
    unsigned int mScreenWidth;
    unsigned int mScreenHeight;

    bool mShowShip;
    bool mShowExplosion;
    bool mExplosionShown;
    bool mStartGame;

    AsteroidsState mGameState;
    AnimationPlayer mAnimationPlayer;
    BitmapFont mFont;
    TitleScreen mTitleScreen;
    HighScores mHighScores;
    SpriteSheet mSpriteSheet;
    Ship mShip;
    std::vector<Rock> mRocks;
};

#endif /* ASTEROIDS_ASTEROIDS_H */