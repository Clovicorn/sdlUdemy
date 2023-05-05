#include "layoutBlock.hpp"

LayoutBlock FindLayoutBlockForSymbol(const std::vector<LayoutBlock> &blocks, char symbol)
{
    for (size_t i = 0; i < blocks.size(); i++)
    {
        if (blocks[i].symbol == symbol)
        {
            return blocks[i];
        }
    }
    return LayoutBlock();
}