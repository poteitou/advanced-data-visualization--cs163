#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "../datastruct/HashTable.hpp"
// #include "../datastruct/DynamicArray.hpp"
// #include "../datastruct/SinglyLinkedList.hpp"
// #include "../datastruct/DoublyLinkedList.hpp"
// #include "../datastruct/CircularLinkedList.hpp"
// #include "../datastruct/Stack.hpp"
// #include "../datastruct/Queue.hpp"

struct Screen
{
    Screen(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode);
    void update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, float dt);
    void draw();

    sf::RenderWindow &mWindow;
    sf::Font &mFont, &mFontCode;
    Menu mMenu;
    HashTable mHashTable;
    // DynamicArray mDynamicArray;
    // SinglyLinkedList mSinglyLinkedList;
    // DoublyLinkedList mDoublyLinkedList;
    // CircularLinkedList mCircularLinkedList;
    // Stack mStack;
    // Queue mQueue;
    int mData;
};

#endif // SCREEN_HPP