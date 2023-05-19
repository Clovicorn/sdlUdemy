#include "highScores.hpp"
#include <algorithm>
#include <functional>
#include "../graphics/bitmapFont.hpp"
#include "../graphics/screen.hpp"
#include "../utils/fileCommandLoader.hpp"
#include "../shapes/aaRectangle.hpp"
#include "../app/app.hpp"

HighScores::HighScores()
{
}

HighScores::~HighScores()
{
}

void HighScores::Draw(Screen &screen)
{
    if (mScoreState == SCORE_SHOW)
    {
        BitmapFont &font = App::Singleton().GetFont();
        unsigned int height_11 = App::Singleton().Height() / 11;
        AARectangle rect(Vec2D::Zero, App::Singleton().Width(), height_11);
        Vec2D pos = font.GetDrawPosition(std::string("High Scores"), rect, BFXA_CENTER, BFYA_CENTER);
        screen.Draw(font, std::string("High Scores"), pos, Color::Red());
        unsigned int height_12 = (App::Singleton().Height() - height_11) / 11;
        rect = {Vec2D(60, height_11 + 10), App::Singleton().Height(), height_12};
        for (size_t i = 0; i < mScores.size(); i++)
        {
            std::string nameAndScore = mScores[i].name + "    " + to_string(mScores[i].score);
            pos = font.GetDrawPosition(nameAndScore, rect, BFXA_LEFT, BFYA_CENTER);
            screen.Draw(font, nameAndScore, pos, Color::Cyan());
            rect.MoveBy(Vec2D(0, height_12));
        }
    }
}

void HighScores::Init(const std::string &pathToFile)
{
    mScoreState = SCORE_SHOW;
    LoadScoreFile(pathToFile);
}

void HighScores::Update(uint32_t dt)
{
}

bool HighScores::CheckScore(int score)
{
    for (auto &nameScore : mScores)
    {
        if (score >= nameScore.score)
        {
            return true;
        }
    }
    return false;
}

void HighScores::LoadScoreFile(const std::string &filePath)
{
    FileCommandLoader loader;

    Command nameCommand;
    nameCommand.command = "name";
    nameCommand.parseFunc = [this](ParseParams params)
    {
        NameScore newNameScore;
        newNameScore.name = FileCommandLoader::ReadString(params);
        mScores.push_back(newNameScore);
    };

    Command scoreCommand;
    scoreCommand.command = "score";
    scoreCommand.parseFunc = [this](ParseParams params)
    {
        mScores.back().score = FileCommandLoader::ReadInt(params);
    };

    loader.AddCommand(nameCommand);
    loader.AddCommand(scoreCommand);

    loader.LoadFile(filePath);
}

bool compareScore(NameScore s1, NameScore s2)
{
    return (s1.score > s2.score);
}

void HighScores::AddScore(const NameScore &name)
{
    mScores.back() = name;

    std::sort(mScores.begin(), mScores.end(), compareScore);
}
