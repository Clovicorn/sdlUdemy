#include "gameScene.hpp"
#include "../games/game.hpp"

GameScene::GameScene(std::unique_ptr<Game> ptrGame) : mGame(std::move(ptrGame))
{
}

void GameScene::Init()
{
    mGame->Init(mGameController);
    mName = mGame->GetName();
}

void GameScene::Draw(Screen &screen)
{
    mGame->Draw(screen);
}

void GameScene::Update(uint32_t dt)
{
    mGame->Update(dt);
}

const std::string &GameScene::GetSceneName()
{
    return mName;
}