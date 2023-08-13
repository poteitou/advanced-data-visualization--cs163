#include "Block.hpp"

Block::Block() {}

Block::Block(sf::Vector2f pos, std::string textIn1, std::string textIn2, std::string textIn3, sf::Font &font, bool highLight, sf::Color Color) : mPos(pos), mHighLight(highLight), mColor(Color), mValue{textIn1, textIn2, textIn3}
{
    mSize = 15;
    mFontSize = 10;

    for (int i = 0; i < 3; i++)
    {
        mRect[i].setOrigin(sf::Vector2f(0.f, 0.f));
        mRect[i].setSize(mSize);
        mRect[i].setPosition(Vector2f(mPos.x + i * mSize, mPos.y));
        mRect[i].setFillColor(mHighLight ? mColor : sf::Color::White);
        mRect[i].setOutlineThickness(2.f);
        mRect[i].setOutlineColor(mColor);

        mTextIn[i].setString(textIn);
        mTextIn[i].setFont(font);
        mTextIn[i].setCharacterSize(mFontSize);
        // mTextIn[i].setPosition(mPos.x + i * mSize + (mSize - mTextIn[i].getLocalBounds().width) / 2, mPos.y + (mSize - mFontSize) / 2);
        mTextIn[i].setPosition(mPos.x + i * mSize - mTextIn[i].getLocalBounds().width / 2, mPos.y - mFontSize / 2);
        mTextIn[i].setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
    }
}

void Block::setColor(sf::Color Color)
{
    mColor = Color;
    for (int i = 0; i < 3; i++)
    {
        mTextIn[i].setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
        mRect[i].setFillColor(mHighLight ? mColor : sf::Color::White);
        mRect[i].setOutlineColor(mColor);
    }
}

void Block::setHighLight(bool highLight)
{
    mHighLight = highLight;
    for (int i = 0; i < 3; i++)
    {
        mTextIn[i].setFillColor(mHighLight ? sf::Color::White : sf::Color::Black);
        mRect[i].setFillColor(mHighLight ? mColor : sf::Color::White);
    }
}

void Block::setPosition(sf::Vector2f pos)
{
    mPos = pos;
    for (int i = 0; i < 3; i++)
    {
        mRect[i].setPosition(Vector2f(mPos.x + i * mSize, mPos.y));
        mTextIn[i].setPosition(mPos.x + i * mSize - mTextIn[i].getLocalBounds().width / 2, mPos.y - mFontSize / 2);
    }
}

void Block::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < 3; i++)
    {
        mWindow.draw(mRect[i]);
        mWindow.draw(mTextIn[i]);
    }
}

