#include "Menu.hpp"

Menu::Menu(sf::RenderWindow &window, sf::Font &font)
    : mWindow(window), mFont(font)
{
    mButton.resize(7);
    mButton[0] = Button(sf::Vector2f(300, 100), sf::Vector2f(300, 400), sf::Color(160, 220, 255), sf::Color(50, 140, 200), "Hash Table", mFont, 35);
    mButton[1] = Button(sf::Vector2f(300, 100), sf::Vector2f(650, 400), sf::Color(160, 220, 255), sf::Color(50, 140, 200), "AVL Tree", mFont, 35);
    mButton[2] = Button(sf::Vector2f(300, 100), sf::Vector2f(1000, 400), sf::Color(160, 220, 255), sf::Color(50, 140, 200), "2-3-4 Tree", mFont, 35);
    mButton[3] = Button(sf::Vector2f(300, 100), sf::Vector2f(300, 550), sf::Color(160, 220, 255), sf::Color(50, 140, 200), "Heap", mFont, 35);
    mButton[4] = Button(sf::Vector2f(300, 100), sf::Vector2f(650, 550), sf::Color(160, 220, 255), sf::Color(50, 140, 200), "Trie", mFont, 35);
    mButton[5] = Button(sf::Vector2f(300, 100), sf::Vector2f(1000, 550), sf::Color(160, 220, 255), sf::Color(50, 140, 200), "Graph", mFont, 35);
    mButton[6] = Button(sf::Vector2f(300, 100), sf::Vector2f(650, 700), sf::Color(160, 220, 255), sf::Color(50, 140, 200), "About", mFont, 35);
}

void Menu::update(bool mousePress, sf::Vector2i mousePosition, int &mData)
{
    for (int i = 0; i < 7; i++)
    {
        if (mButton[i].setMouseOver(mousePosition) && mousePress)
        {
            mData = i + 1;
            mButton[i].mHovered = false;
        }
    }
}

void Menu::draw()
{
    sf::Font mFont1;
    mFont1.loadFromFile("resources/fonts/title.ttf");
    sf::Text text1;
    text1.setString("Data Structure");
    text1.setCharacterSize(110);
    text1.setPosition(300, 100);
    text1.setFont(mFont1);
    text1.setFillColor(sf::Color(230, 100, 140));

    sf::Font mFont2;
    mFont2.loadFromFile("resources/fonts/baloon.otf");
    sf::Text text2;
    text2.setString("visualization");
    text2.setCharacterSize(80);
    text2.setPosition(520, 220);
    text2.setFont(mFont2);
    text2.setFillColor(sf::Color::Black);
    mWindow.draw(text1);
    mWindow.draw(text2);
    for (int i = 0; i < 7; i++)
        mButton[i].draw(mWindow);
}

