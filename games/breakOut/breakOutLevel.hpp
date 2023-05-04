#pragma once

#include <stdint.h>
#include <vector>

#include "ball.hpp"
#include "block.hpp"
#include "../../shapes/aaRectangle.hpp"
#include "../../graphics/screen.hpp"

class BreakOutLevel
{
public:
    BreakOutLevel();
    void Draw(Screen &screen);
    void Init(const AARectangle &boundary);
    void Load(const std::vector<Block> &blocks);
    void Update(uint32_t dt, Ball &ball);

private:
    void CreateDefaultLevel(const AARectangle &boundary);
    std::vector<Block> mBlocks;
};