#ifndef HEAP_HPP
#define HEAP_HPP

#include <SFML/Graphics.hpp>
#include "../interface/Button.hpp"
#include "../interface/ButtonImg.hpp"
#include "../interface/InputBar.hpp"
#include "../interface/Point.hpp"
#include "../interface/Line.hpp"
#include <vector>
#include <string.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <utility>
#include <iostream>

struct Heap
{
    Heap(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode);
    std::vector<std::string> mArr;
    bool mMaxHeap;
    bool isLess(std::string a, std::string b, bool maxHeap);
    struct Tree
    {
        std::vector<Point> mPoint;
        std::vector<Line> mLine;
        void draw(sf::RenderWindow &mWindow);
    };

    struct Step
    {
        int cntCode;
        float mTime;
        Tree mTree;
        std::vector<sf::Text> mText;
        void draw(sf::RenderWindow &mWindow);
    };

    void destroyNode(Tree &tree, int id, float x, float y, float distance);
    void beautify(Tree &tree, int id, float x, float y, float distance);
    void reset(Tree &tree, int id);
    void resetSub(Tree &tree, int id, float x, float y, float distance);

    int findPoint(Tree &tree, std::string key);
    int addPoint(Tree &tree, float x, float y, std::string key, bool highLight);
    int addLine(Tree &tree, float x, float y, float u, float v, bool highLight);

    int Rand(int MAX);
    void randomize();
    void setColor();
    void update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt);
    void updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updatePush(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updatePop(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateGetTop(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateGetSize(bool mousePress, sf::Vector2i mousePosition, char &keyPress);

    void heapify(Step &step, int i);
    void init(std::string fileName);
    void push(std::string key);
    void pop();
    void getTop();
    void getSize();
    void changeType();
    void draw();

    sf::RenderWindow &mWindow;
    sf::Font &mFont, &mFontCode;

    std::vector<Step> mStep;
    std::vector<Button> mButton;
    std::vector<ButtonImg> mButtonImg;
    std::vector<InputBar> mInputBar;
    std::vector<sf::Text> mNoteText, mRealText;
    sf::Texture mTexture;
    sf::Sprite mSpriteSpeed;

    int step, cntNote;
    int mColor;
    sf::Color pallete[3];
    int mRun, mSpeed;
    int mType, mSmallType;
    float mDt;
    bool firstTime, firstTimeSpeed, firstTimeChange;
};

#endif // HEAP_HPP
