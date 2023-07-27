#include "Line.hpp"

Line::Line() {}

Line::Line(sf::Vector2f posBegin, sf::Vector2f posEnd, sf::Color Color, bool highLight)
    : mPosBegin(sf::Vector2f(posBegin.x, posBegin.y)), mPosEnd(sf::Vector2f(posEnd.x, posEnd.y)), mColor(Color), mAngle(0.f), mHighLight(highLight)
{
    mLength = std::sqrt((mPosEnd.x - mPosBegin.x) * (mPosEnd.x - mPosBegin.x) + (mPosEnd.y - mPosBegin.y) * (mPosEnd.y - mPosBegin.y));
    mAngle = std::atan2(mPosEnd.y - mPosBegin.y, mPosEnd.x - mPosBegin.x) * 180.f / std::acos(-1);
    mRect.setSize(sf::Vector2f(mLength, 4.f));
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);
}

void Line::setPosition(sf::Vector2f posBegin, sf::Vector2f posEnd)
{
    mPosBegin = sf::Vector2f(posBegin.x, posBegin.y);
    mPosEnd = sf::Vector2f(posEnd.x, posEnd.y);
    mLength = std::sqrt((mPosEnd.x - mPosBegin.x) * (mPosEnd.x - mPosBegin.x) + (mPosEnd.y - mPosBegin.y) * (mPosEnd.y - mPosBegin.y));
    mAngle = std::atan2(mPosEnd.y - mPosBegin.y, mPosEnd.x - mPosBegin.x) * 180.f / std::acos(-1);
    mRect.setSize(sf::Vector2f(mLength, 4.f));
}

void Line::setPosPoint(Point begin, Point end)
{
    mPosBegin = begin.mPos;
    mPosEnd = end.mPos;
    mLength = std::sqrt((mPosEnd.x - mPosBegin.x) * (mPosEnd.x - mPosBegin.x) + (mPosEnd.y - mPosBegin.y) * (mPosEnd.y - mPosBegin.y));
    mAngle = std::atan2(mPosEnd.y - mPosBegin.y, mPosEnd.x - mPosBegin.x) * 180.f / std::acos(-1);
    mRect.setSize(sf::Vector2f(mLength, 4.f));
}

void Line::setColor(sf::Color Color)
{
    mColor = Color;
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);
}

void Line::setHighLight(bool highLight)
{
    mHighLight = highLight;
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);
}

void Line::draw(sf::RenderWindow &mWindow)
{
    sf::Transform transform;
    transform.translate(mPosBegin);
    transform.rotate(mAngle);
    mWindow.draw(mRect, transform);
}
