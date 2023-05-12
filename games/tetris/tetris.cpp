#include "tetris.hpp"

void Tetris::Draw(Screen &screen)
{
    screen.Draw(mBorder, Color::White(), true, Color::Black());
    screen.Draw(mNextShapeBorder, Color::White(), true, Color::Black());
    if (mGameState == TETRIS_PLAYING)
    {
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
    CreateControls(controller);

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
    if (mGameState == TETRIS_PLAYING)
    {
        if (mAmountBetweenUpdate >= 60)
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

        if (rows[i] == 10)
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
    std::cout << "Score is: " << mScore << std::endl;
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

                if (!CheckForCollision(RIGHT_BORDER))
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
                else
                {
                    DeleteCompleteRows();
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
                if (!CheckForCollision(LEFT_BORDER))
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
                StartGame();
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
// TODO Figure what just fucking blew up and is now
//  crashing the fucking game!

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
                        std::cout << "Game over." << std::endl;
                        // mBlocks.clear();
                        mGameState = TETRIS_NOT_STARTED;
                        break;
                    }
                }
            }
        }
    }
}

void Tetris::StartGame()
{
    if (mGameState == TETRIS_NOT_STARTED)
    {
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
        std::srand(int(time(0)));
        int randomNum = std::rand() % NUM_SHAPES;
        mNextShape.Init((ShapeType)randomNum, mBlockSize, mNextShapeBorder.GetTopLeft().GetX() + mBlockSize, mNextShapeBorder.GetTopLeft().GetY() + mBlockSize);
        SDL_Delay(1000);
        ResetCurrentShape();
    }
}