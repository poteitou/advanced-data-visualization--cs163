#include "Screen.hpp"

Screen::Screen(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode)
    : mWindow(window), mFont(font), mFontCode(fontCode), mData(0), mMenu(mWindow, mFont), mHashTable(mWindow, mFont, mFontCode)
{
    
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
    // case 2: // Dynamic array
    //     mDynamicArray.update(mousePress, mousePosition, keyPress, mData, dt);
    //     break;
    // case 3: // 234 tree
    //     mSinglyLinkedList.update(mousePress, mousePosition, keyPress, mData, dt);
    //     break;
    // case 4: // Doubly linked list
    //     mDoublyLinkedList.update(mousePress, mousePosition, keyPress, mData, dt);
    //     break;
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
    sf::Font mFont1;
    mFont1.loadFromFile("resources/fonts/childtitle.ttf");
    sf::Text textTitle;
    textTitle.setCharacterSize(130);
    textTitle.setFont(mFont1);
    textTitle.setFillColor(sf::Color(230, 100, 140));
    switch(mData)
    {
    case 0: // Menu
        mMenu.draw();
        break;
    case 1: // Hash table
        textTitle.setString("Hash table");
        mHashTable.draw();
        break;
    // case 2: // Dynamic array
    //     mDynamicArray.draw();
    //     break;
    // case 3: // 234 tree
    //     mSinglyLinkedList.draw();
    //     break;
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
    sf::Text textOperation;
    textOperation.setCharacterSize(35);
    textOperation.setString("Operations");
    textOperation.setFont(mFont);
    textOperation.setFillColor(sf::Color(230, 100, 140));
    textOperation.setPosition(100 + 555 / 2 - textOperation.getLocalBounds().width / 2, 50 - 35 / 2);
    if (mData > 0) 
    {
        textTitle.setPosition(800 + 350 - textTitle.getLocalBounds().width / 2, 50 - 130 / 2);
        mWindow.draw(textOperation);
        mWindow.draw(textTitle);
    }
}

