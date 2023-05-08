#include "tetris.hpp"

void Tetris::Init(GameController &controller)
{
    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();
    CreateControls(controller);

    int borderTopX = (mScreenWidth - BORDER_WIDTH) - (mBlockSize * mPlayingWidthSquares);
    int borderTopY = mScreenHeight - ((mPlayingHeightSquares * mBlockSize) + BORDER_WIDTH);
    mBorder = {Vec2D(borderTopX, borderTopY), (mPlayingWidthSquares * mBlockSize) + 4, (mPlayingHeightSquares * mBlockSize) + 8};
    mCurrentShape.Init(LINE_SHAPE, mBlockSize, borderTopX + (mBlockSize * 4) + 1, borderTopY + 1);
}

void Tetris::Update(uint32_t dt)
{
    if (mGameState == TETRIS_PLAYING)
    {
        if (mAmountBetweenUpdate >= 60)
        {
            bool hasCollided = false;
            mAmountBetweenUpdate = 0;
            // TODO Create Collision Detection Here
            if (!CheckForCollision(BOTTOM_BORDER))
            {
                mCurrentShape.Update(dt);
            }
        }
        else
        {
            mAmountBetweenUpdate++;
        }
    }
}

void Tetris::Draw(Screen &screen)
{
    screen.Draw(mBorder, Color::White(), true, Color::Black());
    if (mGameState == TETRIS_PLAYING)
    {
        mCurrentShape.Draw(screen);
    }
}

std::string Tetris::GetName()
{
    std::string name = "Tetris";
    return name;
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
                if (mCurrentShape.GetBlocks()[3].GetAARectangle().GetCenterPoint().GetY() > mBorder.GetTopLeft().GetY() + (mBlockSize * 3))
                {
                    mCurrentShape.Rotate();
                }
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
                bool hasCollided = CheckForCollision(RIGHT_BORDER);
                if (!hasCollided)
                {
                    mCurrentShape.MoveRight();
                }
            }
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
            }
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
                bool hasCollided = CheckForCollision(LEFT_BORDER);
                if (!hasCollided)
                {
                    mCurrentShape.MoveLeft();
                }
            }
        }
    };

    ButtonAction spaceKeyAction;
    spaceKeyAction.Key = GameController::Action();
    spaceKeyAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            if (mGameState == TETRIS_NOT_STARTED)
            {
                std::cout << "Starting Game" << std::endl;
                mGameState = TETRIS_PLAYING;
            }
            else if (mGameState == TETRIS_PLAYING)
            {
                if (mCurrentShape.GetBlocks()[3].GetAARectangle().GetCenterPoint().GetY() + mBlockSize > mBorder.GetTopLeft().GetY() + (mBlockSize * 3))
                {
                    mCurrentShape.Rotate();
                }
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
                // std::cout << "Set game state: " << mGameState << std::endl;
            }

            else if (mGameState == TETRIS_PAUSED)
            {
                mGameState = TETRIS_PLAYING;
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
}

void Tetris::UpdateBoard()
{
}

bool Tetris::CheckForCollision(BoardSides side)
{
    int sidePoint = 0;

    for (auto &block : mCurrentShape.GetBlocks())
    {
        if (side == LEFT_BORDER)
        {
            sidePoint = mBorder.GetTopLeft().GetX();
            if (block.GetAARectangle().GetTopLeft().GetX() <= sidePoint + mBlockSize)
            {
                return true;
            }
        }
        else if (side == RIGHT_BORDER)
        {
            sidePoint = mBorder.GetBottomRight().GetX();
            if (block.GetAARectangle().GetBottomRight().GetX() >= sidePoint - mBlockSize)
            {
                return true;
            }
        }
        else if (side == BOTTOM_BORDER)
        {
            sidePoint = mBorder.GetBottomRight().GetY();
            if (block.GetAARectangle().GetBottomRight().GetY() >= sidePoint - mBlockSize)
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    return false;
}