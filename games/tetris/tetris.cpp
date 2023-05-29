#include "tetris.hpp"

#include <algorithm>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include "../../app/app.hpp"
#include "../../input/gameController.hpp"

Tetris::~Tetris()
{
    App::Singleton().SetRendererClearColor(Color::Black());
}
void Tetris::Draw(Screen &screen)
{
    if (mGameState == TETRIS_GAME_OVER)
    {
        AARectangle rect(Vec2D::Zero, mScreenWidth, mScreenHeight);
        std::string gameOver = "Game Over!";
        Vec2D pos(mFont.GetDrawPosition(gameOver, rect, BFXA_CENTER, BFYA_CENTER));
        screen.Draw(mFont, gameOver, pos);
    }
    if (mGameState == TETRIS_TITLE)
    {
        mTitleScreen.Draw(screen);
    }
    if (mGameState == TETRIS_SCORES)
    {
        mHighScores.Draw(screen);
    }

    if (mGameState == TETRIS_PLAYING)
    {
        AARectangle scoreRect(Vec2D(mNextShapeBorder.GetTopLeft().GetX(), mNextShapeBorder.GetTopLeft().GetY() + 150), mNextShapeBorder.GetWidth(), 20);
        Vec2D nextPos(mNextShapeBorder.GetTopLeft().GetX() + 20, mNextShapeBorder.GetTopLeft().GetY() - 10);
        Vec2D scorePos(scoreRect.GetTopLeft().GetX() + 15, scoreRect.GetTopLeft().GetY() - 10);
        screen.Draw(mBorder, Color::White(), true, Color::Black());
        screen.Draw(mNextShapeBorder, Color::White(), true, Color::Black());
        std::string scoreText = to_string(mScore);
        screen.Draw(scoreRect, Color::White(), true, Color::Black());
        Vec2D scoreTextPos = mFont.GetDrawPosition(scoreText, scoreRect, BFXA_CENTER, BFYA_CENTER);
        screen.Draw(mFont, std::string("Next:"), nextPos, Color::White());
        screen.Draw(mFont, std::string("Score"), scorePos, Color::White());
        screen.Draw(mFont, scoreText, scoreTextPos, Color::White());
        for (auto &block : mCurrentShape.GetBlocks())
        {
            if (block.GetAARectangle().GetTopLeft().GetY() > mBorder.GetTopLeft().GetY())
                block.Draw(screen);
        }
        mNextShape.Draw(screen);

        for (auto &block : mBlocks)
        {
            if (block.GetShouldDraw())
            {
                block.Draw(screen);
            }
        }
    }
}

void Tetris::Init(GameController &controller)
{
    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();
    mFont = App::Singleton().GetFont();
    mHighScores.Init(App::Singleton().GetBasePath() + mHighScoresFile);
    CreateControls(controller);
    mTitleScreen.Init(mGameName);

    // border_width = 10

    int borderTopX = (mScreenWidth - BORDER_WIDTH) - (mBlockSize * mPlayingWidthSquares) - (mPlayingWidthSquares + 1);

    int borderTopY = (mScreenHeight - BORDER_WIDTH) - (mBlockSize * mPlayingHeightSquares) - (mPlayingHeightSquares + 1);
    unsigned int borderWidth = (mBlockSize * mPlayingWidthSquares) + (mPlayingWidthSquares) + 1;
    unsigned int borderHeight = (mBlockSize * mPlayingHeightSquares) + (mPlayingHeightSquares) + 1;
    mBorder = {Vec2D(borderTopX, borderTopY), borderWidth, borderHeight};
    int nextBorderTopX = BORDER_WIDTH / 2;
    mNextShapeBorder = {Vec2D(nextBorderTopX, borderTopY + (mBlockSize * 2)), (mBlockSize * 6), (mBlockSize * 4)};
    ResetCurrentShape();
}

void Tetris::Update(uint32_t dt)
{
    if (mGameState == TETRIS_GAME_OVER)
    {
        if (mTimeElapsed == 120)
        {
            mGameState = TETRIS_TITLE;
            mTimeElapsed = 0;
        }
        else
        {
            mTimeElapsed += 1;
        }
    }
    if (mGameState == TETRIS_TITLE)
    {
        bool showTitle = mTitleScreen.Update(dt);
        if (!showTitle)
        {
            mGameState = TETRIS_SCORES;
        }
    }
    if (mGameState == TETRIS_SCORES)
    {
        bool showScores = mHighScores.Update(dt);
        if (!showScores)
        {
            mGameState = TETRIS_TITLE;
        }
    }
    if (mGameState == TETRIS_PLAYING)
    {
        if (mAmountBetweenUpdate >= mSpeed)
        {

            mAmountBetweenUpdate = 0;
            IsGameOver();
            UpdateBoard(dt);
        }
        else
        {
            mAmountBetweenUpdate++;
        }
    }
}

void Tetris::UpdateBoard(unsigned int dt)
{
    if (!CheckForCollision(BOTTOM_BORDER))
    {
        if (mCurrentShape.GetCanMove())
        {
            mCurrentShape.Update(dt);
        }
    }
    else
    {
        DeleteCompleteRows();
    }
}

void Tetris::DeleteCompleteRows()
{
    int rowsDelAmount = 0;
    std::vector<int> rowsDeleted;
    for (int i = 0; i < mPlayingHeightSquares; i++)
    {

        if (rows[i] == mPlayingWidthSquares)
        {
            rowsDeleted.push_back(i);
            int y = (i * (mBlockSize + 1)) + mBorder.GetTopLeft().GetY() + 1;

            for (auto &block : mBlocks)
            {
                if (block.GetAARectangle().GetTopLeft().GetY() == y)
                {
                    block.SetShouldDraw(false);
                }
                else if (block.GetAARectangle().GetTopLeft().GetY() < y)
                {
                    Vec2D move(0, mBlockSize + 1);
                    block.MoveBy(move);
                }
            }
            rows[i] = 0;
            rowsDelAmount++;
        }
    }
    if (rowsDeleted.size() > 0)
    {
        for (int i = 0; i < rowsDeleted.size(); i++)
        {
            for (int x = rowsDeleted[i]; x >= 0; x--)
            {
                if (x >= 1)
                {
                    if (rows[x] == 0 && rows[x - 1] > 0)
                    {
                        rows[x] = rows[x - 1];
                        rows[x - 1] = 0;

                        x++;
                    }
                }
            }
        }
    }

    mBlocks.erase(std::remove_if(mBlocks.begin(), mBlocks.end(), [](TetrisBlock &block)
                                 { if(!block.GetShouldDraw()){
                                    return true;} return false; }),
                  mBlocks.end());
    if (rowsDelAmount > 0)
    {
        for (int i = 0; i < mPlayingWidthSquares; i++)
        {
            if (columns[i] > 0)
            {
                columns[i] -= rowsDelAmount;
            }
        }
        if (mTotalRowsCompleted % mSpeedUp == 0 && mSpeed >= mMaxSpeed)
        {
            mSpeed -= 1;
        }
        UpdateScore(rowsDelAmount);
    }
}

void Tetris::UpdateScore(int amount)
{
    if (amount == 4)
    {
        mScore += 1000;
    }
    else
    {
        mScore += (amount * 100);
    }
}

std::string Tetris::GetName()
{

    return mGameName;
}

void Tetris::CreateControls(GameController &controller)
{
    controller.ClearAll();

    ButtonAction upKeyAction;
    upKeyAction.Key = GameController::Up();
    upKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == TETRIS_PLAYING)
            {
                mCurrentShape.Rotate();
                for (int i = 0; i < mCurrentShape.GetBlocks().size(); i++)
                {
                    if (mCurrentShape.GetBlocks()[i].GetAARectangle().GetBottomRight().GetX() > mBorder.GetBottomRight().GetX())
                    {

                        mCurrentShape.MoveLeft();
                        i = -1;
                        continue;
                    }
                    if (mCurrentShape.GetBlocks()[i].GetAARectangle().GetTopLeft().GetX() < mBorder.GetTopLeft().GetX())
                    {
                        mCurrentShape.MoveRight();
                        i = -1;
                        continue;
                    }
                }
            }
            if (mGameState == TETRIS_SCORES && mHighScores.GetScoreState() == SCORE_UPDATE)
            {
                mHighScores.SetPreviousLetter();
            }
        }
    };

    ButtonAction rightKeyAction;
    rightKeyAction.Key = GameController::Right();
    rightKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (mGameState == TETRIS_PLAYING)
        {
            if (GameController::IsPressed(state))
            {

                if (!CheckForCollision(RIGHT_BORDER))
                {
                    mCurrentShape.MoveRight();
                }
            }
        }
        if (mGameState == TETRIS_SCORES && mHighScores.GetScoreState() == SCORE_UPDATE)
        {
            mHighScores.MoveRight();
        }
    };
    ButtonAction downKeyAction;
    downKeyAction.Key = GameController::Down();
    downKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (mGameState == TETRIS_PLAYING)
        {
            if (GameController::IsPressed(state))
            {
                if (!CheckForCollision(BOTTOM_BORDER))
                {
                    mCurrentShape.Update(0);
                    mAmountBetweenUpdate = 0;
                }
                else
                {
                    DeleteCompleteRows();
                }
            }
        }
        if (mGameState == TETRIS_SCORES && mHighScores.GetScoreState() == SCORE_UPDATE)
        {
            mHighScores.SetNextLetter();
        }
    };

    ButtonAction leftKeyAction;
    leftKeyAction.Key = GameController::Left();
    leftKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (mGameState == TETRIS_PLAYING)
        {
            if (GameController::IsPressed(state))
            {
                if (!CheckForCollision(LEFT_BORDER))
                {
                    mCurrentShape.MoveLeft();
                }
            }
        }
        if (mGameState == TETRIS_SCORES && mHighScores.GetScoreState() == SCORE_UPDATE)
        {
            mHighScores.MoveLeft();
        }
    };

    ButtonAction spaceKeyAction;
    spaceKeyAction.Key = GameController::Action();
    spaceKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == TETRIS_TITLE)
            {
                StartGame();
            }
            if (mGameState == TETRIS_SCORES && mHighScores.GetScoreState() == SCORE_UPDATE)
            {
                mHighScores.AcceptName(mScore);
            }
        }
    };

    ButtonAction escapeKeyAction;
    escapeKeyAction.Key = GameController::Cancel();
    escapeKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == TETRIS_PLAYING)
            {
                mGameState = TETRIS_PAUSED;
            }

            else if (mGameState == TETRIS_PAUSED)
            {
                mGameState = TETRIS_PLAYING;
            }
            if (mGameState == TETRIS_TITLE)
            {
                App::Singleton().PopScene();
            }
        }
    };
    controller.AddInputActionForKey(upKeyAction);
    controller.AddInputActionForKey(rightKeyAction);
    controller.AddInputActionForKey(downKeyAction);
    controller.AddInputActionForKey(leftKeyAction);

    controller.AddInputActionForKey(spaceKeyAction);
    controller.AddInputActionForKey(escapeKeyAction);
}

void Tetris::ResetCurrentShape()
{

    int startX = mBorder.GetTopLeft().GetX() + ((mBlockSize + 1) * 4) + 1;
    mCurrentShape.Init(mNextShape.GetShapeType(), mBlockSize, startX, mBorder.GetTopLeft().GetY() + 1);
    mCurrentShape.SetCanMove(true);
    std::srand(int(time(0)));
    int randomNum = std::rand() % NUM_SHAPES;
    mNextShape.Init((ShapeType)randomNum, mBlockSize, mNextShapeBorder.GetTopLeft().GetX() + mBlockSize, mNextShapeBorder.GetTopLeft().GetY() + mBlockSize);
}

bool Tetris::CheckForCollision(BoardSides side)
{
    int sidePoint = 0;

    if (side == LEFT_BORDER)
    {
        for (auto &block : mCurrentShape.GetBlocks())
        {
            sidePoint = mBorder.GetTopLeft().GetX();
            if (block.GetAARectangle().GetTopLeft().GetX() < sidePoint + mBlockSize)
            {
                return true;
            }
            else
            {
                if (mBlocks.size() > 0)
                {
                    for (auto &vectorBlock : mBlocks)
                    {
                        AARectangle rect = block.GetAARectangle();
                        Vec2D move(mBlockSize, 0);
                        move.SetX(-move.GetX() / 2);
                        rect.MoveBy(move);
                        if (rect.Intersects(vectorBlock.GetAARectangle()))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if (side == RIGHT_BORDER)
    {
        for (auto &block : mCurrentShape.GetBlocks())
        {
            sidePoint = mBorder.GetBottomRight().GetX();
            if (block.GetAARectangle().GetBottomRight().GetX() >= sidePoint - mBlockSize)
            {
                return true;
            }
            else
            {
                if (mBlocks.size() > 0)
                {
                    for (auto &vectorBlock : mBlocks)
                    {
                        AARectangle rect = block.GetAARectangle();
                        rect.MoveBy(Vec2D(mBlockSize / 2, 0));
                        if (rect.Intersects(vectorBlock.GetAARectangle()))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    else if (side == BOTTOM_BORDER)
    {
        sidePoint = mBorder.GetBottomRight().GetY();
        bool hasCollided = false;
        for (auto &block : mCurrentShape.GetBlocks())
        {

            AARectangle rect = block.GetAARectangle();
            rect.MoveBy(Vec2D(0, mBlockSize / 2));
            if (mBlocks.size() > 0)
            {
                for (auto &vectorBlock : mBlocks)
                {

                    if (rect.Intersects(vectorBlock.GetAARectangle()))
                    {

                        hasCollided = true;
                    }
                }
            }
            if (rect.GetBottomRight().GetY() >= sidePoint && !hasCollided)
            {
                hasCollided = true;
            }
        }
        if (hasCollided)
        {
            for (auto &block : mCurrentShape.GetBlocks())
            {
                TetrisBlock blockToAdd(block.GetAARectangle(), block.GetOutlineColor(), Color::White());

                mBlocks.push_back(blockToAdd);
                mBlocks.back().SetShouldDraw(true);

                float x = (blockToAdd.GetAARectangle().GetTopLeft().GetX() - mBorder.GetTopLeft().GetX()) / (mBlockSize + 1);
                float y = (blockToAdd.GetAARectangle().GetTopLeft().GetY() - mBorder.GetTopLeft().GetY()) / (mBlockSize + 1);

                x = std::floor(x);
                y = std::floor(y);

                rows[(int)y] += 1;
                columns[(int)x] += 1;
            }
            ResetCurrentShape();
            return true;
        }
    }

    return false;
}

void Tetris::IsGameOver()
{
    if (mGameState == TETRIS_PLAYING)
    {
        int minX = mBorder.GetTopLeft().GetX() + (mBlockSize * 4) + 1;
        int maxX = mBorder.GetBottomRight().GetX() - (mBlockSize * 4) - 1;
        int minY = mBorder.GetTopLeft().GetY() + 1;
        if (rows[0] > 0)
        {

            if (mBlocks.size() > 0)
            {
                for (auto &block : mBlocks)
                {

                    if (block.GetAARectangle().GetTopLeft().GetY() <= minY && (minX <= block.GetAARectangle().GetTopLeft().GetX() <= maxX))
                    {
                        // mBlocks.clear();
                        bool isScoreHighScore = mHighScores.CheckScore(mScore);
                        if (isScoreHighScore)
                        {
                            mHighScores.SetScoreState(SCORE_UPDATE);
                            mGameState = TETRIS_SCORES;
                        }
                        else
                        {
                            mGameState = TETRIS_GAME_OVER;
                        }

                        break;
                    }
                }
            }
        }
    }
}

void Tetris::StartGame()
{
    if (mGameState == TETRIS_TITLE)
    {
        Color renderColor(100, 100, 100, 255);
        App::Singleton().SetRendererClearColor(renderColor);
        mGameState = TETRIS_PLAYING;
        mBlocks.clear();
        for (int i = 0; i < mPlayingWidthSquares; i++)
        {
            columns[i] = 0;
        }
        for (int i = 0; i < mPlayingHeightSquares; i++)
        {
            rows[i] = 0;
        }
        mSpeed = STARTSPEED;
        mAmountBetweenUpdate = 0;
        mTotalRowsCompleted = 0;
        std::srand(int(time(0)));
        int randomNum = std::rand() % NUM_SHAPES;
        mNextShape.Init((ShapeType)randomNum, mBlockSize, mNextShapeBorder.GetTopLeft().GetX() + mBlockSize, mNextShapeBorder.GetTopLeft().GetY() + mBlockSize);
        SDL_Delay(1000);
        ResetCurrentShape();
    }
}