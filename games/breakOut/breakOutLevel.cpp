#include "breakOutLevel.hpp"

BreakOutLevel::BreakOutLevel()
{
}

void BreakOutLevel::Draw(Screen &screen)
{
    for (auto &block : mBlocks)
    {
        if (!block.IsDestroyed())
        {
            block.Draw(screen);
        }
    }
}

void BreakOutLevel::Init(const AARectangle &boundary)
{
    CreateDefaultLevel(boundary);
}

void BreakOutLevel::Load(const std::vector<Block> &blocks)
{
    mBlocks.clear();
    mBlocks = blocks;
}

void BreakOutLevel::Update(uint32_t dt, Ball &ball)
{
    std::vector<Block> collidedBlocks;
    BoundaryEdge edgeToBounceOff;
    Block *ptrBlockToBounceOff = nullptr;

    float largestMag = -1.0f;

    for (auto &block : mBlocks)
    {
        BoundaryEdge edge;
        if (!block.IsDestroyed() &&
            block.HasCollided(ball.GetBoundingRect(), edge))
        {
            collidedBlocks.push_back(block);

            float mag = block.GetCollisionOffset(ball.GetBoundingRect()).Mag();

            if (mag > largestMag)
            {
                edgeToBounceOff = edge;
                ptrBlockToBounceOff = &block;
            }
        }
    }
    if (ptrBlockToBounceOff != nullptr)
    {
        ptrBlockToBounceOff->Bounce(ball, edgeToBounceOff);
        ptrBlockToBounceOff->ReduceHP();
    }
    for (auto &block : collidedBlocks)
    {
        BoundaryEdge edge;
        if (block.HasCollided(ball.GetBoundingRect(), edge))
        {
            Vec2D p;
            ball.MakeFlushWithEdge(edge, p, true);
        }
    }
}

// Private methods below

void BreakOutLevel::CreateDefaultLevel(const AARectangle &boundary)
{
    mBlocks.clear();
    const int BLOCK_WIDTH = 30;
    const int BLOCK_HEIGHT = 15;
    const int NUM_BLOCKS_ACROSS = (((int)boundary.GetWidth() - ((2 * BLOCK_WIDTH))) / BLOCK_WIDTH);
    std::cout << NUM_BLOCKS_ACROSS << std::endl;
    const int NUM_BLOCK_ROWS = 6;
    float startX = ((int)boundary.GetWidth() - (NUM_BLOCKS_ACROSS * (BLOCK_WIDTH + 1))) / 2;

    Color colors[NUM_BLOCK_ROWS];
    colors[0] = Color::Red();
    colors[1] = Color::Pink();
    colors[2] = Color::Magenta();
    colors[3] = Color::Cyan();
    colors[4] = Color::Orange();
    colors[5] = Color::Yellow();

    for (int r = 0; r < NUM_BLOCK_ROWS; ++r)
    {
        AARectangle blockRect = {Vec2D(startX, BLOCK_HEIGHT * (r + 1)), BLOCK_WIDTH, BLOCK_HEIGHT};

        for (int c = 0; c < NUM_BLOCKS_ACROSS; ++c)
        {
            Block b;
            b.Init(blockRect, 1, Color::Black(), colors[r]);
            mBlocks.push_back(b);
            blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    }
}
