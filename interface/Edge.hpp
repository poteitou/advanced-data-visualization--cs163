#ifndef EDGE_HPP
#define EDGE_HPP

#include <SFML/Graphics.hpp>
#include "Point.hpp"
#include <algorithm>
#include <math.h>

struct Edge
{
    Edge();
    Edge(sf::Vector2f posBegin, sf::Vector2f posEnd, std::string text, sf::Font &font, sf::Color Color, bool highLight);
    void setPosition(sf::Vector2f posBegin, sf::Vector2f posEnd);
    void setPosPoint(Point begin, Point end);
    void setColor(sf::Color Color);
    void setHighLight(bool highLight);
    void draw(sf::RenderWindow &mWindow);

    sf::RectangleShape mRect;
    sf::Vector2f mPosBegin, mPosEnd;
    sf::Color mColor;
    sf::Text mText;
    std::string mValue;
    float mLength;
    float mAngle;
    bool mHighLight;
};

#endif // EDGE_HPP

