#ifndef BREAKOUT_LEVEL_H
#define BREAKOUT_LEVEL_H

#include <stdint.h>
#include <vector>

#include "block.hpp"
#include "../../shapes/aaRectangle.hpp"

class Screen;
class Ball;
class LayoutBlock;
class HighScore;

class BreakOutLevel
{
public:
    BreakOutLevel();
    void Draw(Screen &screen);
    void Init(const AARectangle &boundary);
    void Load(const std::vector<Block> &blocks);
    void Update(uint32_t dt, Ball &ball);
    bool IsLevelComplete();

    static std::vector<BreakOutLevel> LoadLevelsFromFile(const std::string &filePath, int screenWidth, int screenHeight);

private:
    void CreateDefaultLevel(const AARectangle &boundary);
    std::vector<Block> mBlocks;
    const int UNBREAKABLE = -1;
    static const int BLOCK_WIDTH = 16;
    static const int BLOCK_HEIGHT = 8;
};

#endif /* BREAKOUT_LEVEL_H */