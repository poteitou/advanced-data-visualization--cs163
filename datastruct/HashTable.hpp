#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <SFML/Graphics.hpp>
#include "../interface/Button.hpp"
#include "../interface/InputBar.hpp"
#include "../interface/Label.hpp"
#include "../interface/Arrow.hpp"
#include <vector>
#include <string.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <utility>

struct HashTable
{
    HashTable(sf::RenderWindow &window, sf::Font &font);

    std::vector<std::string> bucket[5];

    int Rand(int MAX);
    void update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt);
    void updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateInsert(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    // void updateDelete(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    // void updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress);

    // void randomize();
    // void setPos(std::vector<DataNode> &temp, int id, float start, Node* tmp);
    // void init(std::string fileName);
    void insert(std::string element);
    // void delete(std::string element);
    // void search(std::string element);

    // void setColor();
    void draw();

    struct Bucket
    {
        Label mLabel;
        Arrow mArrow;
        // vector<Point> points;
        // vector<Line> lines;
        void draw(sf::RenderWindow &mWindow);
    };

    struct Step
    {
        Bucket mBucket[5];
        // vector<Pseudo> pseudo;

        void draw(sf::RenderWindow &mWindow);
    };

    std::vector<Step> mStep;

    sf::RenderWindow &mWindow;
    sf::Font &mFont;
    std::vector<Button> mButton;
    std::vector<InputBar> mInputBar;

    // std::vector<sf::Text> mDefaultText;

    // std::vector<std::vector<DataNode>> mDataNode;
    // std::string *array;

    // int step;
    // int size;
    int mType;
    int mSmallType;
    // int speed;
    // bool nosuchfile;
    bool firstTime;
    // bool firstStep;
    // int runOption;
    // std::pair<sf::Color, sf::Color> pallete[3];
    sf::RectangleShape mRect[2];
    // int color;
};

#endif // HASHTABLE_HPP
