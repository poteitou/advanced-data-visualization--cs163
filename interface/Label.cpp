#include "Label.hpp"

Label::Label() {}

Label::Label(sf::Vector2f size, sf::Vector2f pos, std::string textIn, std::string textOut, sf::Font &font, bool highLight, sf::Color Color, float appearTime) : mSize(size), mPos(pos), mAppear(false), mAppearTime(appearTime), mDefaultAppear(appearTime), mHighLight(highLight), mColor(Color)
{
    mFontSize = 25;
    // create rectangle
    mRect.setOrigin(sf::Vector2f(0.f, 0.f));
    mRect.setSize(mSize);
    mRect.setPosition(mPos);
    mRect.setFillColor(mHighLight ? mColor : sf::Color::White);
    mRect.setOutlineThickness(2.f);
    mRect.setOutlineColor(mColor);

    // create text
    mTextIn.setString(textIn);
    mTextIn.setFont(font);
    mTextOut.setString(textOut);
    mTextOut.setFont(font);

    mTextIn.setCharacterSize(mFontSize);
    mTextIn.setPosition(mPos.x + (mSize.x - mTextIn.getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2);
    mTextIn.setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);

    mTextOut.setCharacterSize(mFontSize);
    mTextOut.setPosition(mPos.x + (mSize.x - mTextOut.getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2 + 50.f);
    mTextOut.setFillColor(mHighLight ? mColor : sf::Color::Black);
}

void Label::setText(std::string textIn, std::string textOut)
{
    mTextIn.setString(textIn);
    mTextOut.setString(textOut);
}

void Label::setColor(sf::Color Color)
{
    mColor = Color;
    mTextIn.setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
    mTextOut.setFillColor(mHighLight ? mColor : sf::Color::Black);
    mRect.setFillColor(mHighLight ? mColor : sf::Color::White);
}

void Label::setPosition(sf::Vector2f pos)
{
    mPos = pos;
    mRect.setPosition(mPos);
    mTextIn.setPosition(mPos.x + (mSize.x - mTextIn.getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2);
    mTextOut.setPosition(mPos.x + (mSize.x - mTextOut.getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2 + 50.f);
}

// void Label::reset()
// {
//     mAppearTime = mDefaultAppear;
//     mAppear = false;
// }

// bool Label::appear(float limit, float dt)
// {
//     mAppearTime += limit * dt;
//     if (mAppearTime >= limit)
//     {
//         mAppearTime = limit;
//         mAppear = true;
//     }
//     return mAppear;
// }

void Label::draw(sf::RenderWindow &mWindow)
{
    mWindow.draw(mRect);
    mWindow.draw(mTextIn);
    mWindow.draw(mTextOut);
}

