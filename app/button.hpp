#ifndef APP_BUTTON_H
#define APP_BUTTON_H

#include <functional>
#include <string>

#include "../shapes/aaRectangle.hpp"
#include "../graphics/bitmapFont.hpp"
#include "../graphics/color.hpp"

class Screen;

class Button
{
public:
    using ButtonAction = std::function<void(void)>;
    Button();
    Button(BitmapFont &bitmapFont, const Color &textColor, const Color &highlightColor = Color::White());
    void Init(const AARectangle &bBox);
    void Draw(Screen &screen);
    void ExecuteAction();

    inline const void SetButtonText(const std::string &string) { mText = string; }
    inline std::string &GetButtonText() { return mText; }
    inline void SetHighlighted(bool state) { mIsHighlighted = state; }
    inline bool IsHighlighted() { return mIsHighlighted; }
    inline void SetButtonAction(Button::ButtonAction action) { mAction = action; }

private:
    BitmapFont &mBitmapFont;
    AARectangle mBBox;
    std::string mText;

    bool mIsHighlighted = false;
    ButtonAction mAction;
    Color mTextColor;
    Color mHighlightColor;
};

#endif /* APP_BUTTON_H */