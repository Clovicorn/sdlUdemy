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
    // CreateDefaultLevel(boundary);
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

    const int NUM_BLOCKS_ACROSS = (((int)boundary.GetWidth() - ((BLOCK_WIDTH))) / BLOCK_WIDTH);
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

// Static Methods
std::vector<BreakOutLevel> BreakOutLevel::LoadLevelsFromFile(const std::string &filePath, int screenWidth, int screenHeight)
{
    std::vector<BreakOutLevel> levels;
    std::vector<LayoutBlock> layoutBlocks;
    std::vector<Block> levelBlocks;

    int width = 0;
    int height = 0;

    FileCommandLoader loader;

    Command levelCommand;
    levelCommand.command = "level";
    levelCommand.parseFunc = [&](ParseParams params)
    {
        if (levels.size() > 0)
        {
            levels.back().Load(levelBlocks);
        }
        layoutBlocks.clear();
        levelBlocks.clear();
        width = 0;
        height = 0;

        BreakOutLevel level;

        level.Init(AARectangle(Vec2D::Zero, screenWidth, screenHeight));
        levels.push_back(level);
    };

    loader.AddCommand(levelCommand);

    Command blockCommand;
    blockCommand.command = "block";
    blockCommand.parseFunc = [&](ParseParams params)
    {
        LayoutBlock lb;
        layoutBlocks.push_back(lb);
    };

    loader.AddCommand(blockCommand);

    Command symbolCommand;
    symbolCommand.command = "symbol";
    symbolCommand.parseFunc = [&](ParseParams params)
    {
        layoutBlocks.back().symbol = FileCommandLoader::ReadChar(params);
    };
    loader.AddCommand(symbolCommand);

    Command fillcolorCommand;
    fillcolorCommand.command = "fillcolor";
    fillcolorCommand.parseFunc = [&](ParseParams params)
    {
        layoutBlocks.back().color = FileCommandLoader::ReadColor(params);
    };
    loader.AddCommand(fillcolorCommand);

    Command hpCommand;
    hpCommand.command = "hp";
    hpCommand.parseFunc = [&](ParseParams params)
    {
        layoutBlocks.back().hp = FileCommandLoader::ReadInt(params);
    };

    loader.AddCommand(hpCommand);

    Command widthCommand;
    widthCommand.command = "width";
    widthCommand.parseFunc = [&](ParseParams params)
    {
        width = FileCommandLoader::ReadInt(params);
    };
    loader.AddCommand(widthCommand);

    Command heightCommand;
    heightCommand.command = "height";
    heightCommand.parseFunc = [&](ParseParams params)
    {
        height = FileCommandLoader::ReadInt(params);
    };
    loader.AddCommand(heightCommand);

    Command layoutCommand;
    layoutCommand.commandType = COMMAND_MULTI_LINE;
    layoutCommand.command = "layout";
    layoutCommand.parseFunc = [&](ParseParams params)
    {
        float startX = (screenWidth - BLOCK_WIDTH * width) / 2.0f;
        AARectangle blockRect(Vec2D(startX, (params.lineNum + 1) * BLOCK_HEIGHT), BLOCK_WIDTH, BLOCK_HEIGHT);

        for (int c = 0; c < params.line.length(); c++)
        {
            if (params.line[c] != '-')
            {
                LayoutBlock thisBlockLayout = FindLayoutBlockForSymbol(layoutBlocks, params.line[c]);
                Block b;
                b.Init(blockRect, thisBlockLayout.hp, Color::Black(), thisBlockLayout.color);
                levelBlocks.push_back(b);
            }
            blockRect.MoveBy(Vec2D(BLOCK_WIDTH, 0));
        }
    };
    loader.AddCommand(layoutCommand);

    loader.LoadFile(filePath);

    if (levels.size() > 0)
    {
        levels.back().Load(levelBlocks);
    }

    return levels;
}