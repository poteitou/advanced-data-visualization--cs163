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
#include <cstdlib>
#include <utility>
#include <iostream>

struct Tree234
{
    Tree234(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode);
    struct Node
    {
        std::string keys[3];
        Node* parent;
        Node* child[4];
        int numKeys; 
        int numKeyChild;

        Node();
        int num(std::string key);
        bool isFull();
        bool isLeaf();
        int findKey(std::string key);
        void updateParNumKeyChild(int count);
        int insertKey(std::string key);
        std::string removeKey();
        void connectChild(int index, Node* nodeChild);
        Node* disconnectChild(int index);
    };
    Node* mRoot;
    std::vector<std::string> mKeys;

    int num(std::string key);
    int getNextChild(Node* node, std::string key);
    void split(Node* &root, Node* node);
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
    // void updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress);

    // void insertInLeaf(Node* leaf, std::string key);
    // Node* rightRotate(Node* Y);
    // Node* leftRotate(Node* X);
    bool canInsert(std::string key);
    /* Node* rightRotate(Step &step, Node* Y, float x, float y, float distance);
    Node* leftRotate(Step &step, Node* X, float x, float y, float distance);
    */
    void init(std::string fileName);
    void insert(std::string key);
    /* Node* minValueNode(Step &step, Node* node, float x, float y, float distance);
    Node* remove(Step &step, Node* root, std::string key, float x, float y, float distance);
    void finalRemove(std::string key);
     */
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
