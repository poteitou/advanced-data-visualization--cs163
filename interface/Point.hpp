#ifndef POINT_HPP
#define POINT_HPP

#include <SFML/Graphics.hpp>

struct Point
{
    Point();
    Point(float radius, sf::Vector2f pos, std::string textIn, sf::Font &font, bool highLight, sf::Color Color, float appearTime);
    void setColor(sf::Color Color);
    void setHighLight(bool highLight);
    void setPosition(sf::Vector2f pos);
    // void reset();
    // bool appear(float limit, float dt);
    void draw(sf::RenderWindow &mWindow);

    float mRadius;
    sf::Vector2f mPos;
    sf::CircleShape mCir;
    sf::Text mTextIn;

    int mFontSize;
    float mAppearTime;
    bool mAppear;
    bool mHighLight;

    float mDefaultAppear;
    sf::Color mColor;
};

#endif // POINT_HPP

