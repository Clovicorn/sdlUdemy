#include "button.hpp"
#include "../graphics/screen.hpp"

Button::Button(BitmapFont &bitmapFont, const Color &textColor, const Color &highlightColor) : mBitmapFont(bitmapFont), mTextColor(textColor), mHighlightColor(highlightColor), mAction(NULL), mText("")
{
}

void Button::Init(const AARectangle &bBox)
{
    mBBox = bBox;
}

void Button::Draw(Screen &screen)
{
    Vec2D pos = mBitmapFont.GetDrawPosition(mText, mBBox, BFXA_CENTER, BFYA_CENTER);
    if (IsHighlighted())
    {
        screen.Draw(mBitmapFont, mText, pos, mTextColor);
    }
    else
    {
        screen.Draw(mBitmapFont, mText, pos);
    }
}

void Button::ExecuteAction()
{
    if (mAction)
    {
        mAction();
    }
}
