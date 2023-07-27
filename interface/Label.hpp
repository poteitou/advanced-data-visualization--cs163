#ifndef LABEL_HPP
#define LABEL_HPP

#include <SFML/Graphics.hpp>

struct Label
{
    Label();
    Label(sf::Vector2f size, sf::Vector2f pos, std::string textIn, sf::Font &font, bool highLight, sf::Color Color);
    void setColor(sf::Color Color);
    void setHighLight(bool highLight);
    void setPosition(sf::Vector2f pos);
    void draw(sf::RenderWindow &mWindow);

    sf::Vector2f mSize, mPos;
    sf::RectangleShape mRect;
    sf::Text mTextIn;
    sf::Color mColor;

    int mFontSize;
    bool mHighLight;
};

#endif // LABEL_HPP

