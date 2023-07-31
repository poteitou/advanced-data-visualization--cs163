#include "HashTable.hpp"

HashTable::HashTable(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode) : mWindow(window), mFont(font), mFontCode(fontCode), mType(0), mSmallType(0)
{
    mButton.resize(10);
    mInputBar.resize(5);
    mButtonImg.resize(12);
    mRealText.resize(9);
    mNoteText.resize(3);

    for (int i = 0; i < 9; i++)
    {
        mRealText[i].setCharacterSize(19);
        mRealText[i].setFont(mFontCode);
        mRealText[i].setFillColor(sf::Color::Black);
        mRealText[i].setPosition(120, 525 + i * 35 - 19 / 2);
    }
    for (int i = 0; i < 3; i++)
    {
        mNoteText[i].setFont(mFont);
        mNoteText[i].setFillColor(sf::Color::Black);
        mNoteText[i].setCharacterSize(20);
    }

    std::ifstream inNote("pseudo/hashtable/hashtable.note");
    std::string tmp;
    cntNote = 0;
    while (getline(inNote, tmp))
    {
        mNoteText[cntNote].setPosition(720, 760 + cntNote * 35 - 20 / 2);
        mNoteText[cntNote++].setString(tmp);
    }
    inNote.close();

    std::string nameButton[] = {"Init", "Insert", "Remove", "Search", "From File", "Randomize", "OK", "OK", "OK", "OK"};
    for (int i = 0; i < 4; i++) // Init, Insert, Remove, Search
        mButton[i] = Button(sf::Vector2f(100, 50), sf::Vector2f(100, 100 + i * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);
    
    
    for (int i = 4; i < 6; i++) // From File + Randomize
        mButton[i] = Button(sf::Vector2f(150, 50), sf::Vector2f(225 + (i - 4) * 175, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);
    
    // Init bar + OK
    mInputBar[0] = InputBar(sf::Vector2f(350, 50), sf::Vector2f(225, 175), mFont, "datafile.data", 2);
    mInputBar[1] = InputBar(sf::Vector2f(425, 50), sf::Vector2f(225, 175), mFont, std::to_string(Rand(99)), 0);
    mButton[6] = Button(sf::Vector2f(75, 50), sf::Vector2f(575, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[6], mFont, 22);

    // Insert bar + OK
    mInputBar[2] = InputBar(sf::Vector2f(100, 50), sf::Vector2f(225, 100 + 55), mFont, std::to_string(Rand(99)), 0);
    mButton[7] = Button(sf::Vector2f(75, 50), sf::Vector2f(350, 100 + 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[7], mFont, 22);

    // Remove bar + OK
    mInputBar[3] = InputBar(sf::Vector2f(100, 50), sf::Vector2f(225, 100 + 2 * 55), mFont, std::to_string(Rand(99)), 0);
    mButton[8] = Button(sf::Vector2f(75, 50), sf::Vector2f(350, 100 + 2 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[8], mFont, 22);

    // Search bar + OK
    mInputBar[4] = InputBar(sf::Vector2f(100, 50), sf::Vector2f(225, 100 + 3 * 55), mFont, std::to_string(Rand(99)), 0);
    mButton[9] = Button(sf::Vector2f(75, 50), sf::Vector2f(350, 100 + 3 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[9], mFont, 22);

    // Play button
    std::string nameImg[] = {"begin", "prev", "play", "next", "end", "minus", "plus", "pause", "blue", "purple", "pink", "home"};
    for (int i = 0; i < 5; i++)
        mButtonImg[i] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(100 + i * 55, 350), nameImg[i] + ".png", nameImg[i] + "Hover.png");

    mButtonImg[5] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(115 + 6 * 55, 350), nameImg[5] + ".png", nameImg[5] + "Hover.png");
    mButtonImg[6] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(115 + 9 * 55 - 5, 350), nameImg[6] + ".png", nameImg[6] + "Hover.png");
    mButtonImg[7] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(100 + 2 * 55, 350), nameImg[7] + ".png", nameImg[7] + "Hover.png");

    // Color button
    pallete[0] = sf::Color(50, 140, 200);
    pallete[1] = sf::Color(170, 100, 220);
    pallete[2] = sf::Color(230, 100, 140);
    for (int i = 8; i < 11; i++)
        mButtonImg[i] = ButtonImg(sf::Vector2f(49, 49), sf::Vector2f(1343 + (i - 8) * 54, 745), nameImg[i] + ".png", nameImg[i] + "Hover.png");

    // Home button
    mButtonImg[11] = ButtonImg(sf::Vector2f(157, 50), sf::Vector2f(1343, 800), nameImg[11] + ".png", nameImg[11] + "Hover.png");

    // speed image
    mTexture.loadFromFile("resources/images/speed" + std::to_string(1) + ".png");
    mSpriteSpeed.setTexture(mTexture, true);
    mSpriteSpeed.setPosition(sf::Vector2f(115 + 7 * 55, 350));

    firstTime = firstTimeSpeed = true;
    step = -1;
    mSpeed = mRun = 1; // pause: 0   play: 1
    mColor = 0;
    reset(mRealBucket);
}

void HashTable::reset(Bucket (&bucket)[5])
{
    for (int i = 0; i < 5; i++)
    {
        bucket[i].mLabel = Label(sf::Vector2f(100, 50), sf::Vector2f(800, 175 + i * 100), std::to_string(i), mFont, false, pallete[mColor]);
        bucket[i].mPoint.clear();
        bucket[i].mLine.clear();
    }
}

void HashTable::beautify(Bucket (&bucket)[5])
{
    for (int i = 0; i < 5; i++)
    {
        bucket[i].mLabel = Label(sf::Vector2f(100, 50), sf::Vector2f(800, 175 + i * 100), std::to_string(i), mFont, false, pallete[mColor]);
        for (int j = 0; j < bucket[i].mPoint.size(); j++)
            bucket[i].mPoint[j].setPosition(sf::Vector2f(975 + j * 100, 200 + i * 100));
        for (int j = 0; j < bucket[i].mLine.size(); j++)
            bucket[i].mLine[j].setPosition(sf::Vector2f(1075 + j * 100 - 100, 200 + i * 100), sf::Vector2f(1075 + j * 100, 200 + i * 100));
    }
}

void HashTable::Bucket::draw(sf::RenderWindow &mWindow)
{
    if (!mPoint.empty()) mArrow.draw(mWindow);
    mLabel.draw(mWindow);
    for (int i = 0; i < mLine.size(); i++)
        mLine[i].draw(mWindow);
    for (int i = 0; i < mPoint.size(); i++)
        mPoint[i].draw(mWindow);
}

void HashTable::addPoint(Bucket &bucket, int index, int pos, std::string element, bool highLight)
{
    if (pos == -1) pos = bucket.mPoint.size();
    bucket.mPoint.push_back(Point(25, sf::Vector2f(975 + pos * 100, 200 + index * 100), element, mFont, highLight, pallete[mColor]));
}

void HashTable::addLine(Bucket &bucket, int index, int pos, bool highLight)
{
    if (pos == -1) pos = bucket.mLine.size();
    if (bucket.mPoint.empty())
    {
        bucket.mArrow = Arrow(sf::Vector2f(800 + 100, 175 + index * 100 + 25), pallete[mColor], highLight);
        return;
    }
    bucket.mLine.push_back(Line(sf::Vector2f(1075 + pos * 100 - 100, 200 + index * 100), sf::Vector2f(1075 + pos * 100, 200 + index * 100), pallete[mColor], highLight));
}

void HashTable::Step::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < 5; i++)
        mBucket[i].draw(mWindow);
    for (int i = 0; i < cntCode; i++)
        mWindow.draw(mText[i]);
}

int HashTable::Rand(int MAX)
{
    srand(time(NULL));
    return rand() % MAX;
}

void HashTable::randomize()
{
    std::ofstream outFile("data/randomize.data");

    srand(time(NULL));
    int randSize = rand() % 9 + 1;
    std::string temp = "";
    for (int i = 0; i < randSize; i++)
    {
        std::string value = std::to_string(rand() % 100);
        outFile << value << ' ';
        temp += value;
        if (i < randSize - 1) temp += ' ';
    }
    mInputBar[1].mValue = temp;
    mInputBar[1].mText.setString(temp);
    outFile.close();
}

void HashTable::setColor()
{
    for (int i = 0; i < mStep.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (!mStep[i].mBucket[j].mPoint.empty()) 
            {
                if (mStep[i].mBucket[j].mArrow.mColor != sf::Color::Black)
                    mStep[i].mBucket[j].mArrow.setColor(pallete[mColor]);
            }
            if (mStep[i].mBucket[j].mLabel.mColor != sf::Color::Black)
                mStep[i].mBucket[j].mLabel.setColor(pallete[mColor]);
            for (int id = 0; id < mStep[i].mBucket[j].mLine.size(); id++)
            {
                if (mStep[i].mBucket[j].mLine[id].mColor != sf::Color::Black)
                    mStep[i].mBucket[j].mLine[id].setColor(pallete[mColor]);
            }
            for (int id = 0; id < mStep[i].mBucket[j].mPoint.size(); id++)
            {
                if (mStep[i].mBucket[j].mPoint[id].mColor != sf::Color::Black)
                    mStep[i].mBucket[j].mPoint[id].setColor(pallete[mColor]); 
            }
        }
    }
}

void HashTable::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt)
{
    mDt = dt;
    for (int i = 0; i < 4; i++)
        mButton[i].setMouseOver(mousePosition);
     for (int i = 0; i < 7; i++)
        mButtonImg[i].setMouseOver(mousePosition);
    if (mRun == 0)
        mButtonImg[7].setMouseOver(mousePosition);
    for (int i = 8; i < 11; i++)
        if (mButtonImg[i].setMouseOver(mousePosition) && mousePress) mColor = i - 8;
    mButtonImg[8 + mColor].mHovered = true;
    mButtonImg[11].setMouseOver(mousePosition);
    
    for (int i = 0; i < 4; i++)
        if (mousePress && mButton[i].mHovered)
        {
            mType = i + 1;
            mSmallType = 0;
            firstTime = true;
            mInputBar[2].reset(std::to_string(Rand(99)));
            mInputBar[3].reset(std::to_string(Rand(99)));
            mInputBar[4].reset(std::to_string(Rand(99)));
        }
    
    if (mousePress && mButtonImg[5].mHovered)
    {
        if (firstTimeSpeed)
        {
            mSpeed = std::max(1, mSpeed / 2);
            firstTimeSpeed = false;
        }
    }
    else if (mousePress && mButtonImg[6].mHovered)
    {
        if (firstTimeSpeed)
        {
            mSpeed = std::min(8, mSpeed * 2);
            firstTimeSpeed = false;
        }
    }
    else if (mRun == 1 && mousePress && mButtonImg[2].mHovered) // pause
    {
        if (firstTimeSpeed)
        {
            mRun = 0;
            mButtonImg[7].setMouseOver(mousePosition);
            firstTimeSpeed = false;
        }
    }
    else if (mRun == 0 && mousePress && mButtonImg[7].mHovered) // play
    {
        if (firstTimeSpeed)
        {
            mRun = 1;
            firstTimeSpeed = false;
        }
    }
    else if (mousePress && mButtonImg[0].mHovered) 
    {
        if (firstTimeSpeed)
        {
            step = 0;
            firstTimeSpeed = false;
        }
    }
    else if (mousePress && mButtonImg[1].mHovered) 
    {
        if (firstTimeSpeed)
        {
            step = std::max(0, step - 1);
            firstTimeSpeed = false;
        }
    }
    else if (mousePress && mButtonImg[3].mHovered) 
    {
        if (firstTimeSpeed)
        {
            step = std::min((int)mStep.size() - 1, step + 1);
            firstTimeSpeed = false;
        }
    }
    else if (mousePress && mButtonImg[4].mHovered) 
    {
        if (firstTimeSpeed)
        {
            step = (int)mStep.size() - 1;
            firstTimeSpeed = false;
        }
    }
    else
        firstTimeSpeed = true;

    mTexture.loadFromFile("resources/images/speed" + std::to_string(mSpeed) + ".png");
    mSpriteSpeed.setTexture(mTexture, true);
    mSpriteSpeed.setPosition(sf::Vector2f(115 + 7 * 55, 350));

    // if (mousePress && mButtonImg[11].mHovered)
    // {
    //     firstTime = firstTimeSpeed = true;
    //     step = -1;
    //     mRun = mSpeed = 1;
    //     mType = mSmallType = mData = 0;
    //     mColor = 0;
    //     mStep.clear();
    //     reset(mRealBucket);
    //     mButtonImg[11].mHovered = false;
    //     return;
    // }

    switch (mType)
    {
    case 1: // Init
        updateInit(mousePress, mousePosition, keyPress);
        break;
    case 2: // Insert
        updateInsert(mousePress, mousePosition, keyPress);
        break;
    case 3: // Remove
        updateRemove(mousePress, mousePosition, keyPress);
        break;
    case 4: // Search
        updateSearch(mousePress, mousePosition, keyPress);
        break;
    default:
        break;
    }
}

void HashTable::updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    mButton[0].mHovered = true;
    if (mButton[4].setMouseOver(mousePosition) && mousePress) // From File
    {
        mInputBar[0].reset("datafile.data");
        mSmallType = 1;
        firstTime = true;
    }
    else if (mButton[5].setMouseOver(mousePosition) && mousePress) // Randomize
    {
        mSmallType = 2;
        randomize();
        firstTime = true;
    }
    switch (mSmallType)
    {
    case 1: // From File
        mButton[4].mHovered = true;
        mInputBar[0].update(mousePress, mousePosition, keyPress, 20);
        if (mButton[6].setMouseOver(mousePosition) && mousePress)
            init("data/" + mInputBar[0].mValue);
        else firstTime = true;
        break;
    case 2: // Randomize
        mButton[5].mHovered = true;
        mInputBar[1].update(mousePress, mousePosition, keyPress, 26);
        if (mButton[6].setMouseOver(mousePosition) && mousePress)
        {
            std::ofstream outFile("data/randomize.data");
            outFile << mInputBar[1].mValue;
            outFile.close();
            init("data/randomize.data");
        }
        else firstTime = true;
        break;
    default:
        break;
    }
}

void HashTable::updateInsert(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[1].mHovered = true;

    mInputBar[2].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[7].setMouseOver(mousePosition) && mousePress && mInputBar[2].mValue != "")
        insert(mInputBar[2].mValue);
    else firstTime = true;
}

void HashTable::updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[2].mHovered = true;

    mInputBar[3].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[8].setMouseOver(mousePosition) && mousePress && mInputBar[3].mValue != "")
        remove(mInputBar[3].mValue);
    else firstTime = true;
}

void HashTable::updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[3].mHovered = true;

    mInputBar[4].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[9].setMouseOver(mousePosition) && mousePress && mInputBar[4].mValue != "")
        search(mInputBar[4].mValue);
    else firstTime = true;
}

void HashTable::init(std::string filename)
{
    std::ifstream inFile(filename), inCode("pseudo/hashtable/init.pseudo");
    if (!inFile) return;

    if (firstTime == false) 
    {
        inFile.close();
        inCode.close();
        return;
    }
    firstTime = false;
    step = 0;
    mRun = 1;
    
    reset(mRealBucket);
    mStep.clear();
    Step tmpStep;

    int cnt = 0;
    std::string tmp;
    while (getline(inCode, tmp))
    {
        mRealText[cnt].setString(tmp);
        mRealText[cnt++].setFillColor(sf::Color::Black);
    }

    tmpStep.cntCode = cnt;
    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));

    std::string element;
    while (inFile >> element)
    {
        int index = stoi(element) % 5;
        if (mRealBucket[index].mPoint.size() == 5)
            continue;
        tmpStep.mBucket[index].mLabel.setHighLight(true);
        mStep.push_back(tmpStep);

        addLine(tmpStep.mBucket[index], index, -1, true);
        addLine(mRealBucket[index], index, -1, false);
        addPoint(tmpStep.mBucket[index], index, -1, element, true);
        addPoint(mRealBucket[index], index, -1, element, false);
        mStep.push_back(tmpStep);
    } 
    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    
    inFile.close();
    inCode.close();
}

void HashTable::insert(std::string element)
{
    std::ifstream inCode("pseudo/hashtable/insert.pseudo");
    if (firstTime == false) 
    {
        inCode.close();
        return;
    }
    firstTime = false;

    mStep.clear();
    Step tmpStep;

    int cnt = 0;
    std::string tmp;
    while (getline(inCode, tmp))
    {
        mRealText[cnt].setString(tmp);
        mRealText[cnt++].setFillColor(sf::Color::Black);
    }

    tmpStep.cntCode = cnt;
    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    int index = stoi(element) % 5;
    tmpStep.mBucket[index].mLabel.setHighLight(true);
    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    if (mRealBucket[index].mPoint.size() == 5)
    {
        tmpStep.mText = mRealText;
        tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
    }
    else
    {
        tmpStep.mText = mRealText;
        tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
        addLine(tmpStep.mBucket[index], index, -1, true);
        addLine(mRealBucket[index], index, -1, false);
        addPoint(tmpStep.mBucket[index], index, -1, element, true);
        addPoint(mRealBucket[index], index, -1, element, false);
        mStep.push_back(tmpStep);
    }

    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void HashTable::remove(std::string element)
{
    std::ifstream inCode("pseudo/hashtable/remove.pseudo");
    if (firstTime == false) 
    {
        inCode.close();
        return;
    }
    firstTime = false;

    mStep.clear();
    Step tmpStep;

    int cnt = 0;
    std::string tmp;
    while (getline(inCode, tmp))
    {
        mRealText[cnt].setString(tmp);
        mRealText[cnt++].setFillColor(sf::Color::Black);
    }

    tmpStep.cntCode = cnt;
    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    int index = stoi(element) % 5;
    tmpStep.mBucket[index].mLabel.setHighLight(true);
    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    for (int i = 0; i < tmpStep.mBucket[index].mPoint.size(); i++)
    {
        if (i == 0)
            tmpStep.mBucket[index].mArrow.setHighLight(true);
        else 
            tmpStep.mBucket[index].mLine[i - 1].setHighLight(true);

        tmpStep.mBucket[index].mPoint[i].setHighLight(true);
        tmpStep.mText = mRealText;
        tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
        if (tmpStep.mBucket[index].mPoint[i].mValue == element) 
        {
            tmpStep.mText = mRealText;
            tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[4].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[5].setFillColor(sf::Color(230, 100, 140));
            mStep.push_back(tmpStep);
            mRealBucket[index].mPoint.erase(mRealBucket[index].mPoint.begin() + i);mRealBucket[index].mLine.pop_back();
            break;
        }
    }

    beautify(mRealBucket);
    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void HashTable::search(std::string element) 
{
    std::ifstream inCode("pseudo/hashtable/search.pseudo");
    if (firstTime == false) 
    {
        inCode.close();
        return;
    }
    firstTime = false;

    mStep.clear();
    Step tmpStep;

    int cnt = 0;
    std::string tmp;
    while (getline(inCode, tmp))
    {
        mRealText[cnt].setString(tmp);
        mRealText[cnt++].setFillColor(sf::Color::Black);
    }

    tmpStep.cntCode = cnt;
    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    int index = stoi(element) % 5;
    tmpStep.mBucket[index].mLabel.setHighLight(true);
    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    for (int i = 0; i < tmpStep.mBucket[index].mPoint.size(); i++)
    {
        if (i == 0)
            tmpStep.mBucket[index].mArrow.setHighLight(true);
        else 
            tmpStep.mBucket[index].mLine[i - 1].setHighLight(true);

        tmpStep.mBucket[index].mPoint[i].setHighLight(true);
        tmpStep.mText = mRealText;
        tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
        if (tmpStep.mBucket[index].mPoint[i].mValue == element) 
        {
            for (int j = 0; j < 5; j++)
                tmpStep.mBucket[j] = mRealBucket[j];
            tmpStep.mBucket[index].mPoint[i].setHighLight(true);
            tmpStep.mText = mRealText;
            tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[4].setFillColor(sf::Color(230, 100, 140));
            mStep.push_back(tmpStep);
            return;
        }
    }

    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mText = mRealText;
    tmpStep.mText[5].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);
    inCode.close();
}

void HashTable::draw()
{
    sf::Text textImple;
    textImple.setCharacterSize(35);
    textImple.setString("Implementation");
    textImple.setStyle(sf::Text::Bold);
    textImple.setFont(mFont);
    textImple.setFillColor(sf::Color(230, 100, 140));
    textImple.setPosition(100 + 555 / 2 - textImple.getLocalBounds().width / 2, 450 - 35 / 2);
    mWindow.draw(textImple);

    for (int i = 0; i < cntNote; i++)
        mWindow.draw(mNoteText[i]);
    for (int i = 0; i < 4; i++)
        mButton[i].draw(mWindow);
    for (int i = 0; i < 7; i++)
        mButtonImg[i].draw(mWindow);
    if (mRun == 0) mButtonImg[7].draw(mWindow);
    for (int i = 8; i <= 11; i++)
        mButtonImg[i].draw(mWindow);
    mWindow.draw(mSpriteSpeed);
    switch (mType)
    {
    case 1: // Init
        for (int i = 4; i < 6; i++)
            mButton[i].draw(mWindow);
        switch (mSmallType)
        {
        case 1: // From File
            mInputBar[0].draw(mWindow);
            mButton[6].draw(mWindow);
            break;
        case 2: // Randomize
            mInputBar[1].draw(mWindow);
            mButton[6].draw(mWindow);
            break;
        default:
            break;
        }
        break;
    case 2: // Insert
        mInputBar[2].draw(mWindow);
        mButton[7].draw(mWindow);
        break;
    case 3: // Remove
        mInputBar[3].draw(mWindow);
        mButton[8].draw(mWindow);
        break;
    case 4: // Search
        mInputBar[4].draw(mWindow);
        mButton[9].draw(mWindow);
        break;
    default:
        break;
    }
    beautify(mRealBucket);
    setColor();
    if (mRun == 1 && !mStep.empty())
    {
        while (step < mStep.size() - 1)
        {
            mStep[step].draw(mWindow);
            mStep[step].mTime += 100.f * mSpeed * mDt;
            if (mStep[step].mTime < 100.f) break;
            else 
            {
                mStep[step].mTime = 0;
                ++step;
            }
        }
        if (step == mStep.size() - 1)
        {
            mRun = 0;
            mStep[step].draw(mWindow);
        }
    }
    else if (mRun == 0 && !mStep.empty())
    {
        mStep[step].draw(mWindow);
    }

}
