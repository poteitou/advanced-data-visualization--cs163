#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <SFML/Graphics.hpp>
#include "../interface/Button.hpp"
#include "../interface/ButtonImg.hpp"
#include "../interface/InputBar.hpp"
#include "../interface/Label.hpp"
#include "../interface/Arrow.hpp"
#include "../interface/Point.hpp"
#include "../interface/Line.hpp"
#include <vector>
#include <string.h>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <utility>

struct HashTable
{
    HashTable(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode);
    struct Bucket
    {
        Label mLabel;
        Arrow mArrow;
        std::vector<Point> mPoint;
        std::vector<Line> mLine;
        void draw(sf::RenderWindow &mWindow);
    };
    Bucket mRealBucket[5];
    void reset(Bucket (&bucket)[5]);
    void beautify(Bucket (&bucket)[5]);

    void addPoint(Bucket &bucket, int index, int pos, std::string element, bool highLight);
    void addLine(Bucket &bucket, int index, int pos, bool highLight);

    int Rand(int MAX);
    void randomize();
    void update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt);
    void updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateInsert(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress);
    void init(std::string fileName);
    void insert(std::string element);
    void remove(std::string element);
    void search(std::string element);
    // void setColor();
    void draw();

    sf::RenderWindow &mWindow;
    sf::Font &mFont, &mFontCode;
    struct Step
    {
        int cntCode;
        float mTime;
        Bucket mBucket[5];
        std::vector<sf::Text> mText;

        void draw(sf::RenderWindow &mWindow);
    };

    std::vector<Step> mStep;
    std::vector<Button> mButton;
    std::vector<ButtonImg> mButtonImg;
    std::vector<InputBar> mInputBar;
    sf::Texture mTexture;
    sf::Sprite mSpriteSpeed;
    std::vector<sf::Text> mNoteText, mRealText;

    int step;
    int cntNote;
    int mType;
    int mSmallType;
    int mSpeed;
    float mDt;
    // bool nosuchfile;
    bool firstTime, firstTimeSpeed;
    int mRun;
    // std::pair<sf::Color, sf::Color> pallete[3];
    int color;
};

#endif // HASHTABLE_HPP
