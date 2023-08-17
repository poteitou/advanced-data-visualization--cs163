#include "Block.hpp"

Block::Block() {}

Block::Block(int size, sf::Vector2f pos, std::string textIn1, std::string textIn2, std::string textIn3, sf::Font &font, bool highLight, sf::Color Color) : mSize(size), mPos(pos), mHighLight(highLight), mColor(Color), mValue{textIn1, textIn2, textIn3}
{
    mFontSize = mSize * 2 / 3;

    for (int i = 0; i < 3; i++)
    {
        mRect[i].setOrigin(sf::Vector2f(0.f, 0.f));
        mRect[i].setSize(sf::Vector2f(mSize, mSize));
        mRect[i].setPosition(sf::Vector2f(mPos.x - 3 * mSize / 2 + i * mSize, mPos.y));
        mRect[i].setFillColor(mHighLight ? mColor : sf::Color::White);
        mRect[i].setOutlineThickness(2.f);
        mRect[i].setOutlineColor(mColor);

        mTextIn[i].setString(mValue[i]);
        mTextIn[i].setFont(font);
        mTextIn[i].setCharacterSize(mFontSize);
        mTextIn[i].setPosition(mPos.x - 3 * mSize / 2 + i * mSize + (mSize - mTextIn[i].getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2);
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
        mRect[i].setPosition(sf::Vector2f(mPos.x + i * mSize, mPos.y));
        mTextIn[i].setPosition(mPos.x - 3 * mSize / 2 + i * mSize + (mSize - mTextIn[i].getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2);
    }
}

Line Block::getLine(Block block1, Block block2, int kind, sf::Color Color, bool highLight)
{
    if (kind == 5)
        return Line(sf::Vector2f(block1.mPos.x, block1.mPos.y + block1.mSize), sf::Vector2f(block2.mPos.x, block2.mPos.y), Color, highLight);
    return Line(sf::Vector2f(block1.mPos.x - 3 * block1.mSize / 2 + kind * block1.mSize, block1.mPos.y + block1.mSize), sf::Vector2f(block2.mPos.x, block2.mPos.y), Color, highLight);
}

void Block::setText(std::string text1, std::string text2, std::string text3)
{
    mValue[0] = text1;
    mValue[1] = text2;
    mValue[2] = text3;
    for (int i = 0; i < 3; i++)
        mTextIn[i].setString(mValue[i]);
}


void Block::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < 3; i++)
    {
        mWindow.draw(mRect[i]);
        mWindow.draw(mTextIn[i]);
    }
}

