#include "Screen.hpp"

Screen::Screen(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode)
    : mWindow(window), mFont(font), mFontCode(fontCode), mData(0), mMenu(mWindow, mFont), mHashTable(mWindow, mFont, mFontCode), mAVLTree(mWindow, mFont, mFontCode), mTree234(mWindow, mFont, mFontCode)
{
    mFont1.loadFromFile("resources/fonts/childtitle.ttf");
    textTitle.setFont(mFont1);
    textTitle.setCharacterSize(130);
    textTitle.setFillColor(sf::Color(230, 100, 140));

    textOperation.setCharacterSize(35);
    textOperation.setString("Operations");
    textOperation.setStyle(sf::Text::Bold);
    textOperation.setFont(mFont);
    textOperation.setFillColor(sf::Color(230, 100, 140));
    textOperation.setPosition(100 + 555 / 2 - textOperation.getLocalBounds().width / 2, 50 - 35 / 2);

    for (int i = 0; i < 3; i++)
    {
        mRect[i].setOrigin(sf::Vector2f(0.f, 0.f));
        mRect[i].setOutlineThickness(2.f);
        mRect[i].setOutlineColor(sf::Color(50, 140, 200));
    }
    mRect[0].setSize(sf::Vector2f(800, 600));
    mRect[0].setPosition(sf::Vector2f(700, 100));
    mRect[0].setFillColor(sf::Color::Transparent);

    mRect[1].setSize(sf::Vector2f(555, 350));
    mRect[1].setPosition(sf::Vector2f(100, 500));
    mRect[1].setFillColor(sf::Color::White);

    mRect[2].setSize(sf::Vector2f(600, 105));
    mRect[2].setPosition(sf::Vector2f(700, 745));
    mRect[2].setFillColor(sf::Color::White);
}

void Screen::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, float dt)
{
    switch(mData)
    {
    case 0: // Menu
        mMenu.update(mousePress, mousePosition, mData);
        break;
    case 1: // Hash table
        mHashTable.update(mousePress, mousePosition, keyPress, mData, dt);
        break;
    case 2: // AVL tree
        mAVLTree.update(mousePress, mousePosition, keyPress, mData, dt);
        break;
    case 3: // 234 tree
        mTree234.update(mousePress, mousePosition, keyPress, mData, dt);
        break;
    // case 4: // Doubly linked list
    //     mDoublyLinkedList.update(mousePress, mousePosition, keyPress, mData, dt);
    //     brea0k;
    // case 5: // Circular linked list
    //     mCircularLinkedList.update(mousePress, mousePosition, keyPress, mData, dt);
    //     break;
    // case 6: // Stack
    //     mStack.update(mousePress, mousePosition, keyPress, mData, dt);
    //     break;
    // case 7: // Queue
    //     mQueue.update(mousePress, mousePosition, keyPress, mData, dt);
    //     break;
    default:
        break;
    }
}

void Screen::draw()
{
    if (mData != 0) for (int i = 0; i < 3; i++) mWindow.draw(mRect[i]);
    switch(mData)
    {
    case 0: // Menu
        mMenu.draw();
        break;
    case 1: // Hash table
        textTitle.setString("Hash table");
        mHashTable.draw();
        break;
    case 2: // AVL Tree
        textTitle.setString("AVL tree");
        mAVLTree.draw();
        break;
    case 3: // 234 tree
        textTitle.setString("2-3-4 tree");
        mTree234.draw();
        break;
    // case 4: // Doubly linked list
    //     mDoublyLinkedList.draw();
    //     break;
    // case 5: // Circular linked list
    //     mCircularLinkedList.draw();
    //     break;
    // case 6: // Stack
    //     mStack.draw();
    //     break;
    // case 7: // Queue
    //     mQueue.draw();
    //     break;
    default:
        break;
    }
    if (mData > 0) 
    {
        textTitle.setPosition(800 + 350 - textTitle.getLocalBounds().width / 2, 50 - 130 / 2);
        mWindow.draw(textOperation);
        mWindow.draw(textTitle);
    }
}

