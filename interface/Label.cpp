#include "Label.hpp"

Label::Label() {}

Label::Label(sf::Vector2f size, sf::Vector2f pos, std::string textIn, sf::Font &font, bool highLight, sf::Color Color) : mSize(size), mPos(pos), mHighLight(highLight), mColor(Color)
{
    mFontSize = 25;
    // create rectangle
    mRect.setOrigin(sf::Vector2f(0.f, 0.f));
    mRect.setSize(mSize);
    mRect.setPosition(mPos);
    mRect.setFillColor(mHighLight ? mColor : sf::Color::White);
    mRect.setOutlineThickness(3.f);
    mRect.setOutlineColor(mColor);

    // create text
    mTextIn.setString(textIn);
    mTextIn.setFont(font);

    mTextIn.setCharacterSize(mFontSize);
    mTextIn.setPosition(mPos.x + (mSize.x - mTextIn.getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2);
    mTextIn.setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
}

void Label::setColor(sf::Color Color)
{
    mColor = Color;
    mTextIn.setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
    mRect.setFillColor(mHighLight ? mColor : sf::Color::White);
    mRect.setOutlineColor(mColor);
}

void Label::setHighLight(bool highLight)
{
    mHighLight = highLight;
    mTextIn.setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
    mRect.setFillColor(mHighLight ? mColor : sf::Color::White);
}

void Label::setPosition(sf::Vector2f pos)
{
    mPos = pos;
    mRect.setPosition(mPos);
    mTextIn.setPosition(mPos.x + (mSize.x - mTextIn.getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2);
}

void Label::draw(sf::RenderWindow &mWindow)
{
    mWindow.draw(mRect);
    mWindow.draw(mTextIn);
}

