#ifndef APP_BUTTONOPTIONSCENE_H
#define APP_BUTTONOPTIONSCENE_H

#include <string>
#include <vector>

#include "scene.hpp"
#include "../app/button.hpp"

class Screen;

class ButtonOptionScene : public Scene
{
public:
    ButtonOptionScene();
    ButtonOptionScene(const std::vector<std::string> &optionNames, const Color &color);
    virtual void Init() override;
    virtual void Draw(Screen &screen) override;
    virtual void Update(uint32_t dt) override;
    void SetButtonActions(const std::vector<Button::ButtonAction> &actions);

private:
    void SetPreviousButton();
    void SetNextButton();
    void ExecuteCurrentButtonAction();
    void HighlightCurrentButton();
    void CreateControls();
    int mHighlightedOption;
    BitmapFont mBitmapFont;
    std::vector<Button> mButtons;
    std::string mSceneName = "";
};

#endif /* APP_BUTTONOPTIONSCENE_H */