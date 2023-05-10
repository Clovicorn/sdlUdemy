#include "tetris.hpp"

void Tetris::Init(GameController &controller)
{
    mScreenWidth = App::Singleton().Width();
    mScreenHeight = App::Singleton().Height();
    CreateControls(controller);

    // border_width = 10

    int borderTopX = (mScreenWidth - BORDER_WIDTH) - (mBlockSize * mPlayingWidthSquares) - (mPlayingWidthSquares + 1);

    int borderTopY = (mScreenHeight - BORDER_WIDTH) - (mBlockSize * mPlayingHeightSquares) - (mPlayingHeightSquares + 1);

    unsigned int borderWidth = (mBlockSize * mPlayingWidthSquares) + (mPlayingWidthSquares) + 1;
    unsigned int borderHeight = (mBlockSize * mPlayingHeightSquares) + (mPlayingHeightSquares) + 1;
    mBorder = {Vec2D(borderTopX, borderTopY), borderWidth, borderHeight};

    ResetCurrentShape();
}

void Tetris::Update(uint32_t dt)
{
    if (mGameState == TETRIS_PLAYING)
    {
        if (mAmountBetweenUpdate >= 60)
        {
            bool hasCollided = false;
            mAmountBetweenUpdate = 0;
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
        for (auto &block : mCurrentShape.GetBlocks())
        {
            if (block.GetAARectangle().GetTopLeft().GetY() > mBorder.GetTopLeft().GetY())
                block.Draw(screen);
        }

        for (auto &block : mBlocks)
        {
            block.Draw(screen);
        }
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
    std::srand(int(time(0)));
    int randomNum = std::rand() % NUM_SHAPES;
    mCurrentShape.Init((ShapeType)randomNum, mBlockSize, mBorder.GetTopLeft().GetX() + 1, mBorder.GetTopLeft().GetY() + 1);
    mCurrentShape.SetCanMove(true);
}

void Tetris::UpdateBoard(AARectangle &rect, int row, int column)
{
}
// TODO create collision detection for blocks on the left
// and right of position
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
            }
        }
    }
    else if (side == BOTTOM_BORDER)
    {
        bool addTomBlocks = false;
        for (auto &block : mCurrentShape.GetBlocks())
        {
            std::vector<TetrisBlock> testBlocks;
            int currentTopX = block.GetAARectangle().GetTopLeft().GetX();
            for (auto &shouldAdd : mBlocks)
            {
                if (shouldAdd.GetAARectangle().GetTopLeft().GetX() == currentTopX)
                {
                    testBlocks.push_back(shouldAdd);
                }
            }
            if (testBlocks.size() > 0)
            {
                for (auto &testBlock : testBlocks)
                {
                    if (block.CheckForCollision(testBlock.GetAARectangle(), BOTTOM_SIDE))
                    {
                        addTomBlocks = true;
                    }
                }
            }
            if (addTomBlocks)
            {
                break;
            }
            // Did we hit bottom border
            sidePoint = mBorder.GetBottomRight().GetY();
            if (block.GetAARectangle().GetTopLeft().GetY() + mBlockSize >= sidePoint)
            {
                addTomBlocks = true;
            }
            if (addTomBlocks)
            {
                break;
            }
        }
        if (addTomBlocks)
        {
            mCurrentShape.SetCanMove(false);
            std::cout << "adding to mBlocks" << std::endl;
            for (auto &block : mCurrentShape.GetBlocks())
            {
                TetrisBlock newBlock(block.GetAARectangle(), block.GetOutlineColor(), Color::White());

                newBlock.SetCanMove(false);
                mBlocks.push_back(newBlock);
            }
            ResetCurrentShape();
            return true;
        }
    }

    return false;
}

void Tetris::DeleteCompleteRows()
{

    int rowsDeleted = 0;
    // TODO Implement checks for complete rows
    // then update score
    if (rowsDeleted > 0)
    {

        UpdateScore(rowsDeleted);
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
    std::cout << "Score is: " << mScore << std::endl;
}