#pragma once
#include <algorithm>
#include <cmath>
#include <string>
#include <cctype>

static const float EPSILON = 0.0001f;
const float PI = 3.14159f;
const float TWO_PI = 2.0f * PI;

bool IsEqual(float x, float y);

bool IsGreaterThanOrEqual(float x, float y);

bool IsLessThanOrEqual(float x, float y);

float MillisecondsToSeconds(unsigned int milliSeconds);

unsigned int GetIndex(unsigned int width, unsigned int row, unsigned int column);

bool StringCompare(const std::string &a, const std::string &b);