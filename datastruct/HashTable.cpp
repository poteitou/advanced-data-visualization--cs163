#include "HashTable.hpp"

HashTable::HashTable(sf::RenderWindow &window, sf::Font &font) : mWindow(window), mFont(font), mType(0), mSmallType(0)
{
    mButton.resize(12);
    mInputBar.resize(10);
    mButtonImg.resize(10);

    /*
    mDefaultText.resize(20);
    for (int i = 0; i < 10; i++)
    {
        mDefaultText[i].setFont(mFont);
        mDefaultText[i].setFillColor(sf::Color::Black);
    } */

    /* mDefaultText[0].setString("HASH TABLE");
    mDefaultText[1].setString("Maximum capacity: 9");
    mDefaultText[2].setString("Value range: 0..99");
    mDefaultText[3].setString("Color tone:"); */

    /* // Init randomize, data file
    mDefaultText[6].setString("Error: No such file or directory!");
    mDefaultText[9].setString("Error: Index out of range or reaching capacity!");

    mDefaultText[0].setCharacterSize(45);
    mDefaultText[1].setCharacterSize(25);
    mDefaultText[2].setCharacterSize(25);
    mDefaultText[3].setCharacterSize(25);
    mDefaultText[6].setCharacterSize(25);
    mDefaultText[9].setCharacterSize(25);

    mDefaultText[0].setPosition(600, 40);
    mDefaultText[1].setPosition(1050, 420);
    mDefaultText[2].setPosition(1050, 470);
    mDefaultText[3].setPosition(1050, 600);

    mDefaultText[6].setFillColor(sf::Color::Red);
    mDefaultText[6].setPosition(350, 630 + 50 + 15);
    mDefaultText[9].setFillColor(sf::Color::Red);
    mDefaultText[9].setPosition(350, 630 + 50 + 15); */

    std::string nameButton[] = {"Init", "Insert", "Remove", "Search", "From File", "Randomize", "OK", "OK", "OK", "OK"};
    for (int i = 0; i < 4; i++) // Init, Insert, Remove, Search
        mButton[i] = Button(sf::Vector2f(100, 50), sf::Vector2f(100, 100 + i * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);
    
    
    for (int i = 4; i < 6; i++) // From File + Randomize
        mButton[i] = Button(sf::Vector2f(150, 50), sf::Vector2f(225 + (i - 4) * 175, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);
    
    // Init bar + OK
    mInputBar[0] = InputBar(sf::Vector2f(350, 50), sf::Vector2f(225, 100 + 55), mFont, "datafile.data", 2);
    mInputBar[1] = InputBar(sf::Vector2f(425, 50), sf::Vector2f(225, 100 + 55), mFont, std::to_string(Rand(99)), 0);
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

    std::string nameImg[] = {"begin", "prev", "play", "next", "end", "minus", "plus", "pause"};
    for (int i = 0; i < 5; i++)
        mButtonImg[i] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(100 + i * 55, 350), nameImg[i] + ".png", nameImg[i] + "Hover.png");
    mButtonImg[7] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(100 + 2 * 55, 350), nameImg[7] + ".png", nameImg[7] + "Hover.png");

    mButtonImg[5] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(115 + 6 * 55, 350), nameImg[5] + ".png", nameImg[5] + "Hover.png");
    mButtonImg[6] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(115 + 9 * 55 - 5, 350), nameImg[6] + ".png", nameImg[6] + "Hover.png");

    // speed image
    mTexture.loadFromFile("resources/images/speed" + std::to_string(1) + ".png");
    mSpriteSpeed.setTexture(mTexture, true);
    mSpriteSpeed.setPosition(sf::Vector2f(115 + 7 * 55, 350));
    /*   
    pallete[0] = {sf::Color(255, 200, 200), sf::Color(255, 95, 95)};
    pallete[1] = {sf::Color(180, 255, 215), sf::Color(30, 190, 90)};
    pallete[2] = {sf::Color(180, 255, 255), sf::Color(0, 180, 240)};

    for (int i = 8; i < 11; i++)
        mButton[i] = Button(sf::Vector2f(50, 50), sf::Vector2f(1200 + (i - 8) * 70, 590), pallete[i - 8].first, pallete[i - 8].second, nameButton[i], mFont, 22);

    mButton[11] = Button(sf::Vector2f(75, 50), sf::Vector2f(750, 630 + 5), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[11], mFont, 22);

    std::string nameBOnce[] = {"1x", "2x", "4x", "8x"};
    for (int i = 0; i < 4; i++)
        mBOnce[i] = Button(sf::Vector2f(100, 50), sf::Vector2f(350 + i * 150, 475), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameBOnce[i], mFont, 22);
    */

    for (int i = 0; i < 2; i++)
    {
        mRect[i].setOrigin(sf::Vector2f(0.f, 0.f));
        mRect[i].setFillColor(sf::Color::Transparent);
        mRect[i].setOutlineThickness(2.f);
        mRect[i].setOutlineColor(sf::Color::Black);
    }
    mRect[0].setSize(sf::Vector2f(800, 600));
    mRect[0].setPosition(sf::Vector2f(700, 100));

    mRect[1].setSize(sf::Vector2f(500, 300));
    mRect[1].setPosition(sf::Vector2f(100, 500));
    firstTime = true;
    step = -1;
    mSpeed = 0;
    /*

    array = new std::string[9];
    head = nullptr;
    size = 0;
    firstStep = true;
    mRun = -1; // no mode:-1       step:0      once:1
    color = 0; */

    reset(mRealBucket);
}

void HashTable::reset(Bucket (&bucket)[5])
{
    for (int i = 0; i < 5; i++)
    {
        bucket[i].mLabel = Label(sf::Vector2f(100, 50), sf::Vector2f(800, 175 + i * 100), std::to_string(i), mFont, false, sf::Color(50, 140, 200));
        bucket[i].mPoint.clear();
        bucket[i].mLine.clear();
    }
}

void HashTable::beautify(Bucket (&bucket)[5])
{
    for (int i = 0; i < 5; i++)
    {
        bucket[i].mLabel = Label(sf::Vector2f(100, 50), sf::Vector2f(800, 175 + i * 100), std::to_string(i), mFont, false, sf::Color(50, 140, 200));
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
    bucket.mPoint.push_back(Point(25, sf::Vector2f(975 + pos * 100, 200 + index * 100), element, mFont, highLight, sf::Color(50, 140, 200)));
}

void HashTable::addLine(Bucket &bucket, int index, int pos, bool highLight)
{
    if (pos == -1) pos = bucket.mLine.size();
    if (bucket.mPoint.empty())
    {
        bucket.mArrow = Arrow(sf::Vector2f(800 + 100, 175 + index * 100 + 25), sf::Color(50, 140, 200), highLight);
        return;
    }
    bucket.mLine.push_back(Line(sf::Vector2f(1075 + pos * 100 - 100, 200 + index * 100), sf::Vector2f(1075 + pos * 100, 200 + index * 100), sf::Color(50, 140, 200), highLight));
}

void HashTable::Step::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < 5; i++)
        mBucket[i].draw(mWindow);
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
        temp += value + ' ';
    }
    mInputBar[1].mValue = temp;
    mInputBar[1].mText.setString(temp);
    outFile.close();
}

void HashTable::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt)
{
    mDt = dt;
    for (int i = 0; i < 4; i++)
        mButton[i].setMouseOver(mousePosition);
    /* for (int i = 8; i < 11; i++)
    {
        if (mButton[i].setMouseOver(mousePosition) && mousePress)
        {
            color = i - 8;
            setColor();
        }
    }
    mButton[8 + color].mHovered = true;
    */
    for (int i = 0; i < 4; i++)
        if (mousePress && mButton[i].mHovered)
        {
            mType = i + 1;
            mSmallType = 0;
            firstTime = true;
            // nosuchfile = false;
            // if (i == 3)
            //     nosuchfile = false;
            std::ofstream outFile("data/randomize.data");
            outFile << mInputBar[1].mValue;
            outFile.close();
            mInputBar[2].reset(std::to_string(Rand(99)));
            mInputBar[3].reset(std::to_string(Rand(99)));
            mInputBar[4].reset(std::to_string(Rand(99)));
        }
    mSpeed = 1;
    for (int i = 0; i < 7; i++)
        mButtonImg[i].setMouseOver(mousePosition);
    /*
    if (mRun == 1 && mousePress && mButton[5].mHovered)
    {
        mRun = 0;
        mButton[5].mHovered = true;
        for (int i = 0; i < 4; i++) mBOnce[i].mHovered = false;
        for (int i = 0; i < 3; i++)
            mBStep[i].setMouseOver(mousePosition);
        mSpeed = 0;
        step = 0;
        for (int i = 0; i < mDataNode.size(); i++)
        {
            for (int j = 0; j < mDataNode[i].size(); j++)
                mDataNode[i][j].reset();
        }
    }
    else if (mRun == 0) // Run step-by-step
    {
        mButton[5].mHovered = true;

        if (mBStep[0].setMouseOver(mousePosition) && mousePress)
        {
            if (step > 0 && firstStep) 
            {
                --step;
                for (int i = 0; i < mDataNode[step].size(); i++)
                    mDataNode[step][i].reset();
            }
            firstStep = false;
        }
        else if (mBStep[1].setMouseOver(mousePosition) && mousePress)
        {
            if (step + 1 < (int)mDataNode.size() && firstStep) 
            {
                ++step;
                for (int i = 0; i < mDataNode[step].size(); i++)
                    mDataNode[step][i].reset();
            }
            firstStep = false;
        }
        else if (mBStep[2].setMouseOver(mousePosition) && mousePress)
        {
            if (firstStep) 
            {
                step = (int)mDataNode.size() - 1;
                for (int i = 0; i < mDataNode[step].size(); i++)
                    mDataNode[step][i].reset();
            }
            firstStep = false;
        }
        else firstStep = true;
    }
    if ((mRun == 0 && mousePress && mButton[6].mHovered) || mRun == 1) // Run at-once
    {
        mRun = 1;
        mButton[6].mHovered = true;
        for (int i = 0; i < 4; i++)
        {
            if (mSpeed == 0) mSpeed = 1; // auto 1x mSpeed
            if (mBOnce[i].setMouseOver(mousePosition) && mousePress)
            {
                mSpeed = 1 << i;
                mBOnce[i].mHovered = true;
                for (int i = 0; i < mDataNode.size(); i++)
                {
                    for (int j = 0; j < mDataNode[i].size(); j++)
                        mDataNode[i][j].reset();
                }
            }
            if (mSpeed == (1 << i)) mBOnce[i].mHovered = true;
        }
    }

    if (mousePress && mButton[7].mHovered)
    {
        size = 0;
        firstTime = firstStep = true;
        mRun = step = -1;
        mSpeed = mType = mData = 0;
        color = 0;
        mButton[7].reset();
        mDataNode.clear();
        Node *tmp;
        while (head != nullptr)
        {
            tmp = head;
            head = head->next;
            remove tmp;
        }
        return;
    }
    */

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
    // case 5: // Update
    //     updateModify(mousePress, mousePosition, keyPress);
    //     break;
    default:
        break;
    }
    /*

    if (mRun == 1)
    {
        bool drawn = false;
        for (int i = 0; i < mDataNode.size(); i++)
        {
            for (int j = 0; j < mDataNode[i].size(); j++)
            {
                if (!mDataNode[i][j].appear(100.f, mSpeed * dt))
                {
                    step = i;
                    drawn = true;
                }
            }
            if (drawn) break;
        }
        if (drawn == false)
            step = (int)mDataNode.size() - 1;
    } */
}

void HashTable::updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    mButton[0].mHovered = true;
    if (mButton[4].setMouseOver(mousePosition) && mousePress) // From File
    {
        mInputBar[0].reset("datafile.data");
        mSmallType = 1;
        // nosuchfile = false;
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
        {
            // nosuchfile = false;
            init("data/" + mInputBar[0].mValue);
        }
        else firstTime = true;
        break;
    case 2: // Randomize
        mButton[5].mHovered = true;
        mInputBar[1].update(mousePress, mousePosition, keyPress, 26);
        if (mButton[6].setMouseOver(mousePosition) && mousePress)
            init("data/randomize.data");
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

    // nosuchfile = false;
    mInputBar[2].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[7].setMouseOver(mousePosition) && mousePress && mInputBar[2].mValue != "")
        insert(mInputBar[2].mValue);
    else firstTime = true;
}

void HashTable::updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[2].mHovered = true;

    // nosuchfile = false;
    mInputBar[3].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[8].setMouseOver(mousePosition) && mousePress && mInputBar[3].mValue != "")
        remove(mInputBar[3].mValue);
    else firstTime = true;
}

void HashTable::updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[3].mHovered = true;

    // nosuchfile = false;
    mInputBar[4].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[9].setMouseOver(mousePosition) && mousePress && mInputBar[4].mValue != "")
        search(mInputBar[4].mValue);
    else firstTime = true;
}

/*
void HashTable::updateModify(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    mButton[3].mHovered = true;

    char tempkeyPress = keyPress;
    mInputBar[3].update(mousePress, mousePosition, keyPress, 1);
    mInputBar[3].update(mousePress, mousePosition, tempkeyPress, 2);
    if (mButton[11].setMouseOver(mousePosition) && mousePress && mInputBar[3].mValue != "" && mInputBar[3].mValue != "")
        modify(stoi(mInputBar[3].mValue), mInputBar[3].mValue);
    else firstTime = true;
}
*/

/*
void HashTable::setPos(std::vector<DataNode> &temp, int id, float start, Node* tmp)
{
    if (tmp == nullptr)
        return;
    for (int i = id; i < size; i++)
    {
        temp[i] = DataNode(sf::Vector2f(start + i * 100, 150), sf::Vector2f(start + (i > 0 ? i - 1 : i) * 100, 150), sf::Vector2f(start + (i < size - 1 ? i + 1 : i) * 100, 150), tmp->data, i == 0 ? "head-0" : std::to_string(i), mFont, sf::Color::Black, sf::Color::Black, pallete[color].first, sf::Color::Black, 100.f, false, tmp->next != nullptr);
        tmp = tmp->next;
    }
}
*/

void HashTable::init(std::string filename)
{
    std::ifstream inFile(filename);
    if (!inFile)
    {
        // nosuchfile = true;
        return;
    }
    // nosuchfile = false;

    if (firstTime == false) return;
    firstTime = false;
    step = 0;
    mRun = 1;
    
    reset(mRealBucket);
    mStep.clear();
    Step tmpStep;
    for (int i = 0; i < 5; i++)
    {
        tmpStep.mBucket[i] = mRealBucket[i];
        tmpStep.mTime = 0;
    }
    mStep.push_back(tmpStep);

    std::string element;
    while (inFile >> element)
    {
        int index = stoi(element) % 5;
        if (mRealBucket[index].mPoint.size() == 5)
        {
            // noti
            // nosuchfile = true;
            continue;
        }
        // nosuchfile = false;
        tmpStep.mBucket[index].mLabel.setHighLight(true);
        mStep.push_back(tmpStep);

        addLine(tmpStep.mBucket[index], index, -1, true);
        addLine(mRealBucket[index], index, -1, false);
        addPoint(tmpStep.mBucket[index], index, -1, element, true);
        addPoint(mRealBucket[index], index, -1, element, false);
        mStep.push_back(tmpStep);
    } 
    for (int i = 0; i < 5; i++)
    {
        tmpStep.mBucket[i] = mRealBucket[i];
        tmpStep.mTime = 0;
    }
    mStep.push_back(tmpStep);
    
    inFile.close();
}

void HashTable::insert(std::string element)
{
    if (firstTime == false) return;
    firstTime = false;
    mStep.clear();
    Step tmpStep;
    for (int i = 0; i < 5; i++)
    {
        tmpStep.mBucket[i] = mRealBucket[i];
        tmpStep.mTime = 0;
    }
    mStep.push_back(tmpStep);
    int index = stoi(element) % 5;
    if (mRealBucket[index].mPoint.size() == 5)
    {
        // noti
        // nosuchfile = true;
        return;
    }
    // nosuchfile = false;
    step = 0;
    mRun = 1;

    tmpStep.mBucket[index].mLabel.setHighLight(true);
    mStep.push_back(tmpStep);

    addLine(tmpStep.mBucket[index], index, -1, true);
    addLine(mRealBucket[index], index, -1, false);
    addPoint(tmpStep.mBucket[index], index, -1, element, true);
    addPoint(mRealBucket[index], index, -1, element, false);
    mStep.push_back(tmpStep);

    for (int i = 0; i < 5; i++)
    {
        tmpStep.mBucket[i] = mRealBucket[i];
        tmpStep.mTime = 0;
    }
    mStep.push_back(tmpStep);
}

void HashTable::remove(std::string element)
{
    if (firstTime == false) return;
    firstTime = false;
    mStep.clear();
    Step tmpStep;
    for (int i = 0; i < 5; i++)
    {
        tmpStep.mBucket[i] = mRealBucket[i];
        tmpStep.mTime = 0;
    }
    mStep.push_back(tmpStep);
    int index = stoi(element) % 5;
    if (mRealBucket[index].mPoint.size() == 5)
    {
        // noti
        // nosuchfile = true;
        return;
    }
    // nosuchfile = false;
    step = 0;
    mRun = 1;

    tmpStep.mBucket[index].mLabel.setHighLight(true);
    mStep.push_back(tmpStep);

    for (int i = 0; i < tmpStep.mBucket[index].mPoint.size(); i++)
    {
        if (i == 0)
            tmpStep.mBucket[index].mArrow.setHighLight(true);
        else 
            tmpStep.mBucket[index].mLine[i - 1].setHighLight(true);
        tmpStep.mBucket[index].mPoint[i].setHighLight(true);
        mStep.push_back(tmpStep);
        if (tmpStep.mBucket[index].mPoint[i].mValue == element) 
        {
            mRealBucket[index].mPoint.erase(mRealBucket[index].mPoint.begin() + i);
            if (i) mRealBucket[index].mLine.erase(mRealBucket[index].mLine.begin() + i - 1);
            break;
        }
    }

    beautify(mRealBucket);
    for (int i = 0; i < 5; i++)
    {
        tmpStep.mBucket[i] = mRealBucket[i];
        tmpStep.mTime = 0;
    }
    mStep.push_back(tmpStep);
}
/*

void HashTable::modify(int index, std::string element)
{
    if (firstTime == false) return;

    firstTime = false;
    if (mDataNode.empty() || index >= size)
    {
        nosuchfile = true;
        return;
    }
    nosuchfile = false;
    
    std::vector<DataNode> temp(size);
    Node *tmp = head;
    setPos(temp, 0, 350, tmp);
    mDataNode.clear();
    mDataNode.push_back(temp);

    mRun = 1;
    step = 0; // activate
    tmp = head;
    temp[0].mAppear = false;
    temp[0].mAppearTime = temp[0].mDefaultAppear = 0.f;

    for (int i = 0; i <= index; i++)
    {
        if (i > 0)
        {
            temp[i - 1].setColor(sf::Color::Black, sf::Color::Black, pallete[color].first, sf::Color::Black);
        }
        temp[i].setColor(sf::Color::White, pallete[color].second, pallete[color].second, sf::Color::Black);
        mDataNode.push_back(temp);

        if (i < index)
        {
            temp[i].setColor(sf::Color::White, pallete[color].second, pallete[color].second, pallete[color].second);
            mDataNode.push_back(temp);
            tmp = tmp->next;
        }
    }
    tmp->data = element;
    tmp = head;
    setPos(temp, 0, 350, tmp);
    mDataNode.push_back(temp);
}
*/

void HashTable::search(std::string element) 
{
    if (firstTime == false) return;
    firstTime = false;
    mStep.clear();
    Step tmpStep;
    for (int i = 0; i < 5; i++)
    {
        tmpStep.mBucket[i] = mRealBucket[i];
        tmpStep.mTime = 0;
    }
    mStep.push_back(tmpStep);
    int index = stoi(element) % 5;
    if (mRealBucket[index].mPoint.size() == 5)
    {
        // noti
        // nosuchfile = true;
        return;
    }
    // nosuchfile = false;
    step = 0;
    mRun = 1;

    tmpStep.mBucket[index].mLabel.setHighLight(true);
    mStep.push_back(tmpStep);

    for (int i = 0; i < tmpStep.mBucket[index].mPoint.size(); i++)
    {
        if (i == 0)
            tmpStep.mBucket[index].mArrow.setHighLight(true);
        else 
            tmpStep.mBucket[index].mLine[i - 1].setHighLight(true);
        tmpStep.mBucket[index].mPoint[i].setHighLight(true);
        mStep.push_back(tmpStep);
        if (tmpStep.mBucket[index].mPoint[i].mValue == element) 
        {
            for (int j = 0; j < 5; j++)
            {
                tmpStep.mBucket[j] = mRealBucket[j];
                tmpStep.mTime = 0;
            }
            tmpStep.mBucket[index].mPoint[i].setHighLight(true);
            mStep.push_back(tmpStep);
            return;
        }
    }

    for (int i = 0; i < 5; i++)
    {
        tmpStep.mBucket[i] = mRealBucket[i];
        tmpStep.mTime = 0;
    }
    mStep.push_back(tmpStep);
}

// void HashTable::setColor()
// {
//     for (int i = 0; i < mDataNode.size(); i++)
//     {
//         for (int j = 0; j < mDataNode[i].size(); j++) if (mDataNode[i][j].mColor != sf::Color::White)
//         {
//             if (mDataNode[i][j].mInColor == sf::Color::Black)
//             {
//                 mDataNode[i][j].setColor(sf::Color::Black, sf::Color::Black, pallete[color].first, sf::Color::Black);
//             }
//             else 
//             {
//                 bool ok = mDataNode[i][j].mArrColor != sf::Color::Black;
//                 mDataNode[i][j].setColor(sf::Color::White, pallete[color].second, pallete[color].second, ok ? pallete[color].second : sf::Color::Black);
//             }
//         }
//     }
// }

void HashTable::draw()
{
    // ButtonImg tmp = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(100 + i * 55, 350), "begin" + ".png", "begin" + "Hover.png");
    mWindow.draw(mRect[0]);
    mWindow.draw(mRect[1]);
    // for (int i = 0; i < 4; i++)
    //     mWindow.draw(mDefaultText[i]);
    for (int i = 0; i < 4; i++)
        mButton[i].draw(mWindow);
    for (int i = 0; i < 7; i++)
        mButtonImg[i].draw(mWindow);
    mWindow.draw(mSpriteSpeed);
    // if (mRun == 0)
    // {
    //     for (int i = 0; i < 3; i++)
    //         mBStep[i].draw(mWindow);
    // }
    // if (mRun == 1)
    // {
    //     for (int i = 0; i < 4; i++)
    //         mBOnce[i].draw(mWindow);
    // }
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
            // if (nosuchfile)
            //     mWindow.draw(mDefaultText[6]);
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
        // if (nosuchfile) mWindow.draw(mDefaultText[9]);
        break;
    case 3: // Remove
        mInputBar[3].draw(mWindow);
        mButton[8].draw(mWindow);
        // if (nosuchfile) mWindow.draw(mDefaultText[9]);
        break;
    case 4: // Search
        mInputBar[4].draw(mWindow);
        mButton[9].draw(mWindow);
        // if (nosuchfile) mWindow.draw(mDefaultText[9]);
        break;
    /*
    case 5: // Update
        mInputBar[3].draw(mWindow);
        mInputBar[3].draw(mWindow);
        mButton[11].draw(mWindow);
        if (nosuchfile) mWindow.draw(mDefaultText[9]);
        break;
    */
    default:
        break;
    }

    if (mRun != -1 && step != -1)
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
            mStep[step].draw(mWindow);
    }
}
