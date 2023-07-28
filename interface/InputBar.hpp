#ifndef INPUTBAR_HPP
#define INPUTBAR_HPP

#include <SFML/Graphics.hpp>
#include <string.h>

struct InputBar
{
    InputBar();
    InputBar(sf::Vector2f size, sf::Vector2f pos, sf::Font &font, std::string defaultText, int type);

    void update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int capacity);
    void draw(sf::RenderWindow &mWindow);
    void reset(std::string defaultText);

    sf::Vector2f mSize, mPos;
    sf::RectangleShape mRect;
    sf::Text mText;
    std::string mValue;
    sf::Color mDefaultColor;
    sf::Color mHoveredColor;
    sf::Color mSelectedColor;
    int mType; // 0: number, 1: digit, 2: filename
    bool mHovered;
    bool mSelected;
    int mFontSize;
};

#endif
