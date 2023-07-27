#include "Arrow.hpp"

Arrow::Arrow() {}

Arrow::Arrow(sf::Vector2f posBegin, sf::Color Color, bool highLight)
    : mPosBegin(sf::Vector2f(posBegin.x, posBegin.y)), mPosEnd(sf::Vector2f(posBegin.x + 50.f, posBegin.y)), mColor(Color), mAngle(0.f), mTriangleSize(12.f), mHighLight(highLight)
{
    mLength = std::sqrt((mPosEnd.x - mPosBegin.x) * (mPosEnd.x - mPosBegin.x) + (mPosEnd.y - mPosBegin.y) * (mPosEnd.y - mPosBegin.y));
    mAngle = std::atan2(mPosEnd.y - mPosBegin.y, mPosEnd.x - mPosBegin.x) * 180.f / std::acos(-1);
    mRect.setSize(sf::Vector2f(mLength - mTriangleSize, 4.f));
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);

    mTriangle.setPointCount(3);
    mTriangle.setPoint(0, sf::Vector2f(mLength - mTriangleSize, -mTriangleSize / 2 + 2));
    mTriangle.setPoint(1, sf::Vector2f(mLength, 2));
    mTriangle.setPoint(2, sf::Vector2f(mLength - mTriangleSize, mTriangleSize / 2 + 2));
    mTriangle.setFillColor(mHighLight ? mColor : sf::Color::Black);
}

void Arrow::setPosition(sf::Vector2f posBegin)
{
    mPosBegin = sf::Vector2f(posBegin.x, posBegin.y);
    mPosEnd = sf::Vector2f(posBegin.x + 50.f, posBegin.y);
    mLength = std::sqrt((mPosEnd.x - mPosBegin.x) * (mPosEnd.x - mPosBegin.x) + (mPosEnd.y - mPosBegin.y) * (mPosEnd.y - mPosBegin.y));
    mAngle = std::atan2(mPosEnd.y - mPosBegin.y, mPosEnd.x - mPosBegin.x) * 180.f / std::acos(-1);
    mRect.setSize(sf::Vector2f(mLength - mTriangleSize, 4.f));
    mTriangle.setPoint(0, sf::Vector2f(mLength - mTriangleSize, -mTriangleSize / 2 + 2));
    mTriangle.setPoint(1, sf::Vector2f(mLength, 2));
    mTriangle.setPoint(2, sf::Vector2f(mLength - mTriangleSize, mTriangleSize / 2 + 2));
}

void Arrow::setColor(sf::Color Color)
{
    mColor = Color;
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);
    mTriangle.setFillColor(mHighLight ? mColor : sf::Color::Black);
}

void Arrow::setHighLight(bool highLight)
{
    mHighLight = highLight;
    mRect.setFillColor(mHighLight ? mColor : sf::Color::Black);
    mTriangle.setFillColor(mHighLight ? mColor : sf::Color::Black);
}

void Arrow::draw(sf::RenderWindow &mWindow)
{
    sf::Transform transform;
    transform.translate(mPosBegin);
    transform.rotate(mAngle);
    mWindow.draw(mRect, transform);
    mWindow.draw(mTriangle, transform);
}
