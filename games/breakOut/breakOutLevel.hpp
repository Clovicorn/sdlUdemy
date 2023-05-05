#pragma once

#include <stdint.h>
#include <vector>

#include "ball.hpp"
#include "block.hpp"
#include "layoutBlock.hpp"

#include "../../graphics/screen.hpp"
#include "../../shapes/aaRectangle.hpp"
#include "../../utils/fileCommandLoader.hpp"

class BreakOutLevel
{
public:
    BreakOutLevel();
    void Draw(Screen &screen);
    void Init(const AARectangle &boundary);
    void Load(const std::vector<Block> &blocks);
    void Update(uint32_t dt, Ball &ball);

    static std::vector<BreakOutLevel> LoadLevelsFromFile(const std::string &filePath, int screenWidth, int screenHeight);

private:
    void CreateDefaultLevel(const AARectangle &boundary);
    std::vector<Block> mBlocks;

    static const int BLOCK_WIDTH = 16;
    static const int BLOCK_HEIGHT = 8;
};