#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include "../interface/Button.hpp"
#include "../interface/ButtonImg.hpp"
#include "../interface/InputBar.hpp"
#include "../interface/Point.hpp"
#include "../interface/Edge.hpp"
#include <queue>
#include <vector>
#include <string.h>
#include <fstream>
#include <ctime>
#include <random>
#include <chrono>
#include <cstdlib>
#include <utility>
#include <iostream>
#include <cmath>

struct Graph
{
    Graph(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode);
    
    int mVertex, mEdge;
    std::vector<std::pair<int, int> > mAdj[10];
    int lab[10];
    struct Tree
    {
        std::vector<Point> mPoint;
        std::vector<Edge> mEdge;
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

    void destroy();
    void reset(Tree &tree);
    int addPoint(Tree &tree, int id, bool highLight);
    int addEdge(Tree &tree, int id1, int id2, int w, bool highLight);
    int Rand(int MAX);
    void randomize();
    void setColor();
    void update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt);
    void updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateConnected(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateMst(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateDijkstra(bool mousePress, sf::Vector2i mousePosition, char &keyPress);

    void init(std::string fileName);
    void connected(std::string key);
    int findLab(int u);
    bool join(int u, int v);
    void mst();
    void dijkstra(std::string key);
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
    bool firstTime, firstTimeSpeed;
};

#endif // GRAPH_HPP
