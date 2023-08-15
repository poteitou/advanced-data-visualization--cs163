#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <SFML/Graphics.hpp>
#include "Line.hpp"

struct Block
{
    Block();
    Block(int size, sf::Vector2f pos, std::string textIn1, std::string textIn2, std::string textIn3, sf::Font &font, bool highLight, sf::Color Color);
    void setColor(sf::Color Color);
    void setHighLight(bool highLight);
    void setPosition(sf::Vector2f pos);
    Line getLine(Block block1, Block block2, int kind, sf::Color Color, bool highLight);
    void setText(std::string text1, std::string text2, std::string text3);
    void draw(sf::RenderWindow &mWindow);

    sf::Vector2f mPos;
    sf::RectangleShape mRect[3];
    sf::Text mTextIn[3];
    sf::Color mColor;

    std::string mValue[3];
    int mSize;
    int mFontSize;
    bool mHighLight;
};

#endif // BLOCK_HPP

