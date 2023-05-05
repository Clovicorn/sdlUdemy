#pragma once

#include <vector>
#include "../../graphics/color.hpp"

struct LayoutBlock
{
    char symbol = '-';
    int hp = 0;
    Color color = Color::Black();
};

LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock> &blocks, char symbol);