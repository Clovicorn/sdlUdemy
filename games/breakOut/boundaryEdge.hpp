#pragma once

#include "../../utils/vec2d.hpp"
#include "../../shapes/line2D.hpp"

enum EDGE_TYPE
{
    TOP = 0,
    RIGHT,
    BOTTOM,
    LEFT,
    NUM_EDGES
};

struct BoundaryEdge
{
    Vec2D normal;
    Line2D edge;
};

static const Vec2D UP_DIR = {0, -1};
static const Vec2D RIGHT_DIR = {1, 0};
static const Vec2D BOTTOM_DIR = {0, 1};
static const Vec2D LEFT_DIR = {-1, 0};