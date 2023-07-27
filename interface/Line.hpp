#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include <algorithm>
#include <math.h>

struct Line
{
    Line();
    Line(sf::Vector2f posBegin, sf::Vector2f posEnd, sf::Color Color, bool highLight);
    void setPosition(sf::Vector2f posBegin, sf::Vector2f posEnd);
    void setPosPoint(Point begin, Point end);
    void setColor(sf::Color Color);
    void setHighLight(bool highLight);
    void draw(sf::RenderWindow &mWindow);

    sf::RectangleShape mRect;
    sf::Vector2f mPosBegin, mPosEnd;
    sf::Color mColor;
    float mLength;
    float mAngle;
    bool mHighLight;
};

#endif // LINE_HPP

