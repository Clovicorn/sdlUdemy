#ifndef HIGHSCORES_H
#define HIGHSCORES_H

#include <string>
#include <vector>

class Screen;
enum scoreState
{
    SCORE_SHOW = 0,
    SCORE_UPDATE
};

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
    bool Update(uint32_t dt);
    bool CheckScore(int score);
    void SetPreviousLetter();
    void SetNextLetter();
    void AcceptName(int score);
    void MoveLeft();
    void MoveRight();

    inline const std::vector<NameScore> &GetHighScores() { return mScores; }
    inline void SetScoreState(scoreState state) { mScoreState = state; }
    inline const scoreState GetScoreState() { return mScoreState; }

private:
    void LoadScoreFile(const std::string &filePath);
    void SaveScores();
    void AddScore(const NameScore &name);
    int mTimeElapsed;
    std::string mPathAndFileName;
    std::vector<NameScore> mScores;
    scoreState mScoreState;
    int mCurInitial;
    int mInitials[3] = {0};
};

#endif /* HIGHSCORES_H */