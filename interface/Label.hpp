#ifndef LABEL_HPP
#define LABEL_HPP

#include <SFML/Graphics.hpp>

struct Label
{
    Label();
    Label(sf::Vector2f size, sf::Vector2f pos, std::string textIn, sf::Font &font, bool highLight, sf::Color Color, float appearTime);
    void setColor(sf::Color Color);
    void setHighLight(bool highLight);
    void setPosition(sf::Vector2f pos);
    // void reset();
    // bool appear(float limit, float dt);
    void draw(sf::RenderWindow &mWindow);

    sf::Vector2f mSize, mPos;
    sf::RectangleShape mRect;
    sf::Text mTextIn;

    int mFontSize;
    float mAppearTime;
    bool mAppear;
    bool mHighLight;

    float mDefaultAppear;
    sf::Color mColor;
};

#endif // LABEL_HPP

