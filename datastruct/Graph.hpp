#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <SFML/Graphics.hpp>
#include "../interface/Button.hpp"
#include "../interface/ButtonImg.hpp"
#include "../interface/InputBar.hpp"
#include "../interface/Point.hpp"
#include "../interface/Edge.hpp"
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
    // void updateConnected(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    // void updateMst(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    // void updateDijkstra(bool mousePress, sf::Vector2i mousePosition, char &keyPress);

    // Node* connected(Node* node, std::string key);
    void init(std::string fileName);
    // Node* connected(Step &step, Node* root, std::string key, float x, float y, float distance);
    // void finalConnected(std::string key);
    // Node* minValueNode(Step &step, Node* node, float x, float y, float distance);
    // Node* mst(Step &step, Node* root, std::string key, float x, float y, float distance);
    // void finalMst(std::string key);
    // void dijkstra(Step &step, Node* root, std::string key, float x, float y, float distance);
    // void finalDijkstra(std::string key);
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
