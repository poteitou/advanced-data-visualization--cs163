#ifndef TREE234_HPP
#define TREE234_HPP

#include <SFML/Graphics.hpp>
#include "../interface/Button.hpp"
#include "../interface/ButtonImg.hpp"
#include "../interface/InputBar.hpp"
#include "../interface/Block.hpp"
#include "../interface/Line.hpp"
#include <vector>
#include <string.h>
#include <fstream>
#include <ctime>
#include <random>
#include <chrono>
#include <cstdlib>
#include <utility>
#include <iostream>

struct Tree234
{
    Tree234(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode);
    struct Node
    {
        std::string* keys[3];
        Node* parent;
        Node* child[4];
        int numKeys; 

        Node();
        int num(std::string key);
        int num(std::string* key);
        bool isFull();
        bool isLeaf();
        int findKey(std::string key);
        int insertKey(std::string* key);
        std::string* removeKey();
        void removeKeyAtIndex(int index);
        void insertChild(int index, Node* nodeChild);
        void connectChild(int index, Node* nodeChild);
        Node* disconnectChild(int index);
    };
    Node* mRoot;
    std::vector<std::string> mKeys;

    int num(std::string key);
    int num(std::string* key);
    int getNextChild(Node* node, std::string key);
    int getIndexInPar(Node* node);
    std::string* successor(std::string key, Node *node);
    void split(Node* &root, Node* node);
    bool rotate(Node* node);
    bool merge(Node* node);
    void shrink(Node* node);
    int height(Node* node);
    Node* copy(Node* root);
    struct Tree
    {
        std::vector<Block> mBlock;
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

    void destroy(Node* &root);
    void highLigthtBlock(Tree &tree, Node* node);
    Block createBlock(Node* node, float size, int id, float x, float y, float distance, bool highLight);
    Line createLine(Node* node, int id, float x, float y, float distance, bool highLight);
    void beautify(Tree &tree, Node* root, int id, float x, float y, float distance);
    void reset(Tree &tree, Node* root);

    int Rand(int MAX);
    void randomize();
    void setColor();
    void update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt);
    void updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateInsert(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress);

    bool canInsert(std::string key);
    void init(std::string fileName);
    void insert(std::string key);
    void remove(Step &step, Node* node, std::string key);
    void finalRemove(std::string key);
    void search(std::string key);
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

#endif // TREE234_HPP
