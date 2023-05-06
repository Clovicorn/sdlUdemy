#pragma once

#include <string>
#include <vector>

#include "../../graphics/screen.hpp"
#include "../../utils/fileCommandLoader.hpp"

struct NameScore
{
    std::string name;
    int score;
};

class HighScores
{

public:
    HighScores();
    ~HighScores();
    void Draw(Screen &screen);
    void Init(const std::string &pathToFile);
    void Update(uint32_t dt);
    void CheckScore(int score, const std::string &name);

private:
    void LoadScoreFile(const std::string &filePath);
    void AddScore(const NameScore &name);
    std::string mPathAndFileName;
    std::vector<NameScore> mScores;
};