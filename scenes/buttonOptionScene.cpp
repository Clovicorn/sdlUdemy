#include "buttonOptionScene.hpp"
#include "../app/app.hpp"
#include "../graphics/screen.hpp"
#include "../graphics/bitmapFont.hpp"
#include "../utils/utils.hpp"

ButtonOptionScene::ButtonOptionScene()
{
}

ButtonOptionScene::ButtonOptionScene(const std::vector<std::string> &buttonText, const Color &color) : mHighlightedOption(0)
{
    mBitmapFont = App::Singleton().GetFont();
    for (size_t i = 0; i < buttonText.size(); i++)
    {
        Button b(mBitmapFont, color);
        b.SetButtonText(buttonText[i]);
        mButtons.push_back(b);
    }
    if (mButtons.size() > 0)
    {
        mButtons[mHighlightedOption].SetHighlighted(true);
    }
}

void ButtonOptionScene::Draw(Screen &screen)
{
    HighlightCurrentButton();
    for (auto &button : mButtons)
    {
        button.Draw(screen);
    }
}

void ButtonOptionScene::Init()
{
    CreateControls();
    uint32_t width = App::Singleton().Width();
    uint32_t height = App::Singleton().Height();

    Size fontSize = mBitmapFont.GetSizeOf(mButtons[0].GetButtonText());
    const int BUTTON_PAD = 10;
    unsigned int buttonHeight = fontSize.height + BUTTON_PAD * 2;
    uint32_t maxButtonWidth = fontSize.width;

    for (auto &button : mButtons)
    {
        Size s = mBitmapFont.GetSizeOf(button.GetButtonText());
        if (s.width > maxButtonWidth)
        {
            maxButtonWidth = s.width;
        }
    }
    maxButtonWidth += BUTTON_PAD * 2;
    uint32_t yPad = 1;
    uint32_t yOffset = ((buttonHeight + yPad) * static_cast<uint32_t>(mButtons.size())) / 2;

    for (auto &button : mButtons)
    {
        AARectangle rect(Vec2D((width / 2) - (maxButtonWidth / 2), yOffset), maxButtonWidth, buttonHeight);
        button.Init(rect);
        yOffset += buttonHeight + yPad;
    }

    mButtons[mHighlightedOption].SetHighlighted(true);
}

void ButtonOptionScene::Update(uint32_t dt)
{
    // Nothing to update
}

void ButtonOptionScene::SetPreviousButton()
{
    mHighlightedOption--;
    if (mHighlightedOption < 0)
    {
        mHighlightedOption = static_cast<int>(mButtons.size()) - 1;
    }
    HighlightCurrentButton();
}

void ButtonOptionScene::SetNextButton()
{
    mHighlightedOption = (mHighlightedOption + 1) % mButtons.size();
    HighlightCurrentButton();
}

void ButtonOptionScene::ExecuteCurrentButtonAction()
{
    mButtons[mHighlightedOption].ExecuteAction();
}

void ButtonOptionScene::HighlightCurrentButton()
{
    for (auto &button : mButtons)
    {
        button.SetHighlighted(false);
    }
    mButtons[mHighlightedOption].SetHighlighted(true);
}

void ButtonOptionScene::CreateControls()
{
    ButtonAction upAction;
    upAction.Key = GameController::Up();
    upAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            SetPreviousButton();
        }
    };

    ButtonAction downAction;
    downAction.Key = GameController::Down();
    downAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            SetNextButton();
        }
    };

    ButtonAction actionAction;
    actionAction.Key = GameController::Action();
    actionAction.Action = [this](uint32_t dt, InputState state)
    {
        if (GameController::IsPressed(state))
        {
            ExecuteCurrentButtonAction();
        }
    };

    mGameController.AddInputActionForKey(upAction);
    mGameController.AddInputActionForKey(downAction);
    mGameController.AddInputActionForKey(actionAction);
}

void ButtonOptionScene::SetButtonActions(const std::vector<Button::ButtonAction> &actions)
{
    if (actions.size() == mButtons.size())
    {
        for (size_t i = 0; i < mButtons.size(); i++)
        {
            mButtons[i].SetButtonAction(actions[i]);
        }
    }
    else
    {
        std::cout << "actions size != to mButtons size." << std::endl;
    }
}