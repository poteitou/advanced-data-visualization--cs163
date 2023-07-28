#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>

struct Point
{
    Point();
    Point(float radius, sf::Vector2f pos, std::string textIn, sf::Font &font, bool highLight, sf::Color Color);
    void setColor(sf::Color Color);
    void setHighLight(bool highLight);
    void setPosition(sf::Vector2f pos);
    void draw(sf::RenderWindow &mWindow);

    float mRadius;
    sf::Vector2f mPos;
    sf::CircleShape mCir;
    sf::Text mTextIn;
    sf::Color mColor;

    std::string mValue;
    int mFontSize;
    bool mHighLight;
};

#endif // POINT_HPP

