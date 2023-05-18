#include "highScores.hpp"
#include "../../graphics/screen.hpp"
#include "../../utils/fileCommandLoader.hpp"

HighScores::HighScores()
{
}

HighScores::~HighScores()
{
}

void HighScores::Draw(Screen &screen)
{
}

void HighScores::Init(const std::string &pathToFile)
{
    LoadScoreFile(pathToFile);
}

void HighScores::Update(uint32_t dt)
{
}

void HighScores::CheckScore(int score, const std::string &name)
{
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

void HighScores::AddScore(const NameScore &name)
{
}
