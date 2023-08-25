#include "Edge.hpp"

Edge::Edge() {}

Edge::Edge(sf::Vector2f posBegin, sf::Vector2f posEnd, std::string text, sf::Font &font, sf::Color Color, bool highLight)
    : mPosBegin(sf::Vector2f(posBegin.x, posBegin.y)), mPosEnd(sf::Vector2f(posEnd.x, posEnd.y)), mColor(Color), mAngle(0.f), mHighLight(highLight), mValue(text)
{
    mLength = std::sqrt((mPosEnd.x - mPosBegin.x) * (mPosEnd.x - mPosBegin.x) + (mPosEnd.y - mPosBegin.y) * (mPosEnd.y - mPosBegin.y));
    mAngle = std::atan2(mPosEnd.y - mPosBegin.y, mPosEnd.x - mPosBegin.x) * 180.f / std::acos(-1);
    mRect.setSize(sf::Vector2f(mLength, 4.f));
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);

    // create text
    mText.setStyle(sf::Text::Bold);
    mText.setString(textIn);
    mText.setFont(font);
    mText.setCharacterSize(25);
    mText.setPosition((mPosBegin.x + mPosEnd.x) / 2 - mText.getLocalBounds().width / 2 - 2, (mPosBegin.y + mPosEnd.y) - mFontSize / 2 - 3);
    mText.setFillColor(mHighLight ? sf::Color::Black : mColor);
}

void Edge::setPosition(sf::Vector2f posBegin, sf::Vector2f posEnd)
{
    mPosBegin = sf::Vector2f(posBegin.x, posBegin.y);
    mPosEnd = sf::Vector2f(posEnd.x, posEnd.y);
    mLength = std::sqrt((mPosEnd.x - mPosBegin.x) * (mPosEnd.x - mPosBegin.x) + (mPosEnd.y - mPosBegin.y) * (mPosEnd.y - mPosBegin.y));
    mAngle = std::atan2(mPosEnd.y - mPosBegin.y, mPosEnd.x - mPosBegin.x) * 180.f / std::acos(-1);
    mRect.setSize(sf::Vector2f(mLength, 4.f));
    mText.setPosition((mPosBegin.x + mPosEnd.x) / 2 - mText.getLocalBounds().width / 2 - 2, (mPosBegin.y + mPosEnd.y) - mFontSize / 2 - 3);
}

void Edge::setPosPoint(Point begin, Point end)
{
    mPosBegin = begin.mPos;
    mPosEnd = end.mPos;
    mLength = std::sqrt((mPosEnd.x - mPosBegin.x) * (mPosEnd.x - mPosBegin.x) + (mPosEnd.y - mPosBegin.y) * (mPosEnd.y - mPosBegin.y));
    mAngle = std::atan2(mPosEnd.y - mPosBegin.y, mPosEnd.x - mPosBegin.x) * 180.f / std::acos(-1);
    mRect.setSize(sf::Vector2f(mLength, 4.f));
    mText.setPosition((mPosBegin.x + mPosEnd.x) / 2 - mText.getLocalBounds().width / 2 - 2, (mPosBegin.y + mPosEnd.y) - mFontSize / 2 - 3);
}

void Edge::setColor(sf::Color Color)
{
    mColor = Color;
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);
    mText.setFillColor(mHighLight ? sf::Color::Black : mColor);
}

void Edge::setHighLight(bool highLight)
{
    mHighLight = highLight;
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);
    mText.setFillColor(mHighLight ? sf::Color::Black : mColor);
}

void Edge::draw(sf::RenderWindow &mWindow)
{
    sf::Transform transform;
    transform.translate(mPosBegin);
    transform.rotate(mAngle);
    mWindow.draw(mRect, transform);
    mWindow.draw(mText);
}
