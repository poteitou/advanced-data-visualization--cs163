#ifndef TRIE_HPP
#define TRIE_HPP

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

struct Trie
{
    Trie(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode);
    struct Node
    {
        Node* child[26];
        std::string key;
        bool isEndOfWord;
        int height, numChild;
    };
    Node *mRoot;
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

    int height(Node *node);
    Node* newNode();
    Node* copy(Node* root);
    void destroy(Node* &root);
    void destroyNode(Tree &tree, Node* &root, float x, float y, float distance);
    void beautify(Tree &tree, Node *root, float x, float y, float distance);
    void reset(Tree &tree, Node *root);
    void resetSub(Tree &tree, Node *root, float x, float y, float distance);

    int findPoint(Tree &tree, float x, float y);
    int addPoint(Tree &tree, float x, float y, std::string key, bool highLight);
    int findLine(Tree &tree, float x, float y, float u, float v);
    int addLine(Tree &tree, float x, float y, float u, float v, bool highLight);

    int Rand(int MAX);
    void randomize();
    void setColor();
    void update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt);
    void updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateInsert(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress);

    void* insert(Node* root, std::string key);
    bool canInsert(std::string key);
    Node *rightRotate(Step &step, Node *Y, float x, float y, float distance);
    Node *leftRotate(Step &step, Node *X, float x, float y, float distance);
    Node* init(Step &step, Node* root, std::string key, float x, float y, float distance);
    void finalInit(std::string fileName);
    Node* insert(Step &step, Node* root, std::string key, float x, float y, float distance);
    void finalInsert(std::string key);
    Node* minValueNode(Step &step, Node* node, float x, float y, float distance);
    Node* remove(Step &step, Node* root, std::string key, float x, float y, float distance);
    void finalRemove(std::string key);
    void search(Step &step, Node* root, std::string key, float x, float y, float distance);
    void finalSearch(std::string key);
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

#endif // TRIE_HPP
