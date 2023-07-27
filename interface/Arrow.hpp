#ifndef ARROW_HPP
#define ARROW_HPP

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <math.h>

struct Arrow
{
    Arrow();
    Arrow(sf::Vector2f posBegin, sf::Color Color, bool highLight);
    void setPosition(sf::Vector2f posBegin);
    void setColor(sf::Color Color);
    void setHighLight(bool highLight);
    void draw(sf::RenderWindow &mWindow);

    sf::RectangleShape mRect;
    sf::ConvexShape mTriangle;
    sf::Vector2f mPosBegin, mPosEnd;
    sf::Color mColor;
    float mLength;
    float mAngle;
    float mTriangleSize;
    bool mHighLight;
};

#endif // ARROW_HPP

