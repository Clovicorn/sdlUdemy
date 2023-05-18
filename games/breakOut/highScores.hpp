#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <string>
#include <vector>

class Screen;

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
    inline void UpdateScore() { mCurrentScore += 10; }
    inline void ResetScore() { mCurrentScore = 0; }
    inline const std::string GetScore() { return std::to_string(mCurrentScore); }

private:
    void LoadScoreFile(const std::string &filePath);
    void AddScore(const NameScore &name);
    std::string mPathAndFileName;
    std::vector<NameScore> mScores;
    int mCurrentScore = 0;
};

#endif /* HIGHSCORES_H */