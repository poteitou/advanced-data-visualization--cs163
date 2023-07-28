#include "Point.hpp"

Point::Point() {}

Point::Point(float radius, sf::Vector2f pos, std::string textIn, sf::Font &font, bool highLight, sf::Color Color) : mRadius(radius), mPos(pos), mHighLight(highLight), mColor(Color), mValue(textIn)
{
    mFontSize = 25;
    // create rectangle
    mCir.setOrigin(sf::Vector2f(mRadius, mRadius));
    mCir.setRadius(mRadius);
    mCir.setPosition(mPos);
    mCir.setFillColor(mHighLight ? mColor : sf::Color::White);
    mCir.setOutlineThickness(3.f);
    mCir.setOutlineColor(mColor);

    // create text
    mTextIn.setString(textIn);
    mTextIn.setFont(font);

    mTextIn.setCharacterSize(mFontSize);
    mTextIn.setPosition(mPos.x - mTextIn.getLocalBounds().width / 2 - 2, mPos.y - mFontSize / 2 - 3);
    mTextIn.setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
}

void Point::setColor(sf::Color Color)
{
    mColor = Color;
    mTextIn.setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
    mCir.setFillColor(mHighLight ? mColor : sf::Color::White);
}

void Point::setHighLight(bool highLight)
{
    mHighLight = highLight;
    mTextIn.setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
    mCir.setFillColor(mHighLight ? mColor : sf::Color::White);
}

void Point::setPosition(sf::Vector2f pos)
{
    mPos = pos;
    mCir.setPosition(mPos);
    mTextIn.setPosition(mPos.x - mTextIn.getLocalBounds().width / 2 - 2, mPos.y - mFontSize / 2 - 3);
}

void Point::draw(sf::RenderWindow &mWindow)
{
    mWindow.draw(mCir);
    mWindow.draw(mTextIn);
}

