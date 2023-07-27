#ifndef LABEL_HPP
#define LABEL_HPP

#include <SFML/Graphics.hpp>

struct Label
{
    Label();
    Label(sf::Vector2f size, sf::Vector2f pos, std::string textIn, std::string textOut, sf::Font &font, bool highLight, sf::Color Color, float appearTime);
    void setText(std::string textIn, std::string textOut);
    void setColor(sf::Color Color);
    void setPosition(sf::Vector2f pos);
    // void reset();
    // bool appear(float limit, float dt);
    void draw(sf::RenderWindow &mWindow);

    sf::Vector2f mSize, mPos;
    sf::RectangleShape mRect;
    sf::Text mTextIn;
    sf::Text mTextOut;
    
    int mFontSize;
    float mAppearTime;
    bool mAppear;
    bool mNext;
    bool mHighLight;

    float mDefaultAppear;
    sf::Color mInColor;
    sf::Color mColor;
};

#endif

