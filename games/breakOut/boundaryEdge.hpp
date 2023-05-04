#pragma once

#include "../../utils/vec2d.hpp"
#include "../../shapes/line2D.hpp"

static const Vec2D UP_DIR = {0, -1};
static const Vec2D RIGHT_DIR = {1, 0};
static const Vec2D DOWN_DIR = {0, 1};
static const Vec2D LEFT_DIR = {-1, 0};

enum EdgeType
{
    TOP_EDGE = 0,
    RIGHT_EDGE,
    BOTTOM_EDGE,
    LEFT_EDGE,
    NUM_EDGES
};

struct BoundaryEdge
{
    Vec2D normal;
    Line2D edge;
};
