#include "Heap.hpp"

Heap::Heap(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode) : mWindow(window), mFont(font), mFontCode(fontCode), mType(0), mSmallType(0)
{
    mButton.resize(13);
    mInputBar.resize(3);
    mButtonImg.resize(12);
    mRealText.resize(9);
    mNoteText.resize(4);

    for (int i = 0; i < 9; i++)
    {
        mRealText[i].setCharacterSize(19);
        mRealText[i].setFont(mFontCode);
        mRealText[i].setFillColor(sf::Color::Black);
        mRealText[i].setPosition(120, 580 + i * 35 - 19 / 2);
    }
    for (int i = 1; i < 4; i++)
    {
        mNoteText[i].setFont(mFont);
        mNoteText[i].setFillColor(sf::Color::Black);
        mNoteText[i].setCharacterSize(20);
    }
    mNoteText[0].setFont(mFont);
    mNoteText[0].setStyle(sf::Text::Bold);
    mNoteText[0].setFillColor(sf::Color(230, 100, 140));
    mNoteText[0].setCharacterSize(30);
    mNoteText[0].setPosition(720, 130 - 30 / 2);
    mNoteText[0].setString("");

    std::ifstream inNote("pseudo/heap/heap.note");
    std::string tmp;
    cntNote = 1;
    while (getline(inNote, tmp))
    {
        mNoteText[cntNote].setPosition(720, 760 + (cntNote - 1) * 35 - 20 / 2);
        mNoteText[cntNote++].setString(tmp);
    }
    inNote.close();

    std::string nameButton[] = {"Init", "Push", "Pop", "Top", "From File", "Randomize", "OK", "OK", "OK", "OK", "Size", "OK", "Change Type"};
    for (int i = 0; i < 4; i++) // Init, Push, Pop, GetTop, GetSize
        mButton[i] = Button(sf::Vector2f(100, 50), sf::Vector2f(100, 100 + i * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);
    mButton[10] = Button(sf::Vector2f(100, 50), sf::Vector2f(100, 100 + 4 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[10], mFont, 22);

    for (int i = 4; i < 6; i++) // From File + Randomize
        mButton[i] = Button(sf::Vector2f(150, 50), sf::Vector2f(225 + (i - 4) * 175, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);

    // Init bar + OK
    mInputBar[0] = InputBar(sf::Vector2f(350, 50), sf::Vector2f(225, 175), mFont, "datafile.data", 2);
    mInputBar[1] = InputBar(sf::Vector2f(425, 50), sf::Vector2f(225, 175), mFont, std::to_string(Rand(99)), 0);
    mButton[6] = Button(sf::Vector2f(75, 50), sf::Vector2f(575, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[6], mFont, 22);

    // Push bar + OK
    mInputBar[2] = InputBar(sf::Vector2f(100, 50), sf::Vector2f(225, 100 + 55), mFont, std::to_string(Rand(99)), 0);
    mButton[7] = Button(sf::Vector2f(75, 50), sf::Vector2f(350, 100 + 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[7], mFont, 22);

    // Pop bar + OK
    mButton[8] = Button(sf::Vector2f(75, 50), sf::Vector2f(225, 100 + 2 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[8], mFont, 22);

    // GetTop bar + OK
    mButton[9] = Button(sf::Vector2f(75, 50), sf::Vector2f(225, 100 + 3 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[9], mFont, 22);

    // GetSize bar + OK
    mButton[11] = Button(sf::Vector2f(75, 50), sf::Vector2f(225, 100 + 4 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[11], mFont, 22);

    // ChangeType bar + OK
    mButton[12] = Button(sf::Vector2f(210, 50), sf::Vector2f(115 + 6 * 55, 100 + 4 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[12], mFont, 22);

    // Play button
    std::string nameImg[] = {"begin", "prev", "play", "next", "end", "minus", "plus", "pause", "blue", "purple", "pink", "home"};
    for (int i = 0; i < 5; i++)
        mButtonImg[i] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(100 + i * 55, 405), nameImg[i] + ".png", nameImg[i] + "Hover.png");

    mButtonImg[5] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(115 + 6 * 55, 405), nameImg[5] + ".png", nameImg[5] + "Hover.png");
    mButtonImg[6] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(115 + 9 * 55 - 5, 405), nameImg[6] + ".png", nameImg[6] + "Hover.png");
    mButtonImg[7] = ButtonImg(sf::Vector2f(50, 50), sf::Vector2f(100 + 2 * 55, 405), nameImg[7] + ".png", nameImg[7] + "Hover.png");

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
    mSpriteSpeed.setPosition(sf::Vector2f(115 + 7 * 55, 405));

    firstTime = firstTimeSpeed = firstTimeChange = true;
    step = -1;
    mSpeed = mRun = 1; // pause: 0   play: 1
    mColor = 0;
    mArr.clear();
    mMaxHeap = false;
}

bool Heap::isLess(std::string a, std::string b, bool maxHeap)
{
    if (maxHeap)
        return stoi(a) > stoi(b);
    return stoi(a) < stoi(b);
}

void Heap::destroyNode(Tree &tree, int id = 0, float x = 1100, float y = 175, float distance = 200)
{
    if (id < (int)mArr.size())
    {
        tree.mPoint.erase(tree.mPoint.begin() + addPoint(tree, x, y, mArr[id], false));
        if (id * 2 + 1 < (int)mArr.size())
        {
            tree.mLine.erase(tree.mLine.begin() + addLine(tree, x, y, x - distance, y + 100, true));
            destroyNode(tree, id * 2 + 1, x - distance, y + 100, distance / 2);
        }
        if (id * 2 + 2 < (int)mArr.size())
        {
            tree.mLine.erase(tree.mLine.begin() + addLine(tree, x, y, x + distance, y + 100, true));
            destroyNode(tree, id * 2 + 2, x + distance, y + 100, distance / 2);
        }
    }
}

void Heap::beautify(Tree &tree, int id = 0, float x = 1100, float y = 175, float distance = 200)
{
    if (id < (int)mArr.size())
    {
        tree.mPoint.push_back(Point(23, sf::Vector2f(x, y), mArr[id], mFont, false, pallete[mColor]));
        if (id * 2 + 1 < (int)mArr.size())
        {
            tree.mLine.push_back(Line(sf::Vector2f(x, y), sf::Vector2f(x - distance, y + 100), pallete[mColor], true));
            beautify(tree, id * 2 + 1, x - distance, y + 100, distance / 2);
        }
        if (id * 2 + 2 < (int)mArr.size())
        {
            tree.mLine.push_back(Line(sf::Vector2f(x, y), sf::Vector2f(x + distance, y + 100), pallete[mColor], true));
            beautify(tree, id * 2 + 2, x + distance, y + 100, distance / 2);
        }
    }
}

void Heap::reset(Tree &tree, int id = 0)
{
    tree.mPoint.clear();
    tree.mLine.clear();
    beautify(tree, id);
}

void Heap::resetSub(Tree &tree, int id = 0, float x = 1100, float y = 175, float distance = 200)
{
    destroyNode(tree, id, x, y, distance);
    beautify(tree, id, x, y, distance);
}

void Heap::Tree::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < mLine.size(); i++)
        mLine[i].draw(mWindow);
    for (int i = 0; i < mPoint.size(); i++)
        mPoint[i].draw(mWindow);
}

int Heap::findPoint(Tree &tree, std::string key)
{
    for (int i = 0; i < tree.mPoint.size(); i++)
        if (tree.mPoint[i].mValue == key) return i;
    return -1;
}

int Heap::addPoint(Tree &tree, float x, float y, std::string key, bool highLight)
{
    for (int i = 0; i < tree.mPoint.size(); i++)
    {
        if (tree.mPoint[i].mValue == key)
        {
            tree.mPoint[i].setHighLight(highLight);
            return i;
        }
    }
    tree.mPoint.push_back(Point(23, sf::Vector2f(x, y), key, mFont, highLight, pallete[mColor]));
    return tree.mPoint.size() - 1;
}

int Heap::addLine(Tree &tree, float x, float y, float u, float v, bool highLight)
{
    for (int i = 0; i < tree.mLine.size(); i++)
    {
        if (tree.mLine[i].mPosBegin == sf::Vector2f(x, y) && tree.mLine[i].mPosEnd == sf::Vector2f(u, v))
        {
            tree.mLine[i].setHighLight(highLight);
            return i;
        }
        else if (tree.mLine[i].mPosBegin == sf::Vector2f(u, v) && tree.mLine[i].mPosEnd == sf::Vector2f(x, y))
        {
            tree.mLine[i].setHighLight(highLight);
            return i;
        }
    }
    tree.mLine.push_back(Line(sf::Vector2f(x, y), sf::Vector2f(u, v), pallete[mColor], highLight));
    return tree.mLine.size() - 1;
}

void Heap::Step::draw(sf::RenderWindow &mWindow)
{
    mTree.draw(mWindow);
    for (int i = 0; i < cntCode; i++)
        mWindow.draw(mText[i]);
}

int Heap::Rand(int MAX)
{
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return rng() % MAX;
}

void Heap::randomize()
{
    std::ofstream outFile("data/randomize.data");

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int randSize = rng() % 9 + 1;
    std::string temp = "";
    for (int i = 0; i < randSize; i++)
    {
        std::string value = std::to_string(rng() % 100);
        outFile << value << ' ';
        temp += value;
        if (i < randSize - 1)
            temp += ' ';
    }
    mInputBar[1].mValue = temp;
    mInputBar[1].mText.setString(temp);
    outFile.close();
}

void Heap::setColor()
{
    for (int i = 0; i < mStep.size(); i++)
    {
        for (int id = 0; id < mStep[i].mTree.mLine.size(); id++)
            mStep[i].mTree.mLine[id].setColor(pallete[mColor]);
        for (int id = 0; id < mStep[i].mTree.mPoint.size(); id++)
        {
            if (mStep[i].mTree.mPoint[id].mColor != sf::Color::Black)
                mStep[i].mTree.mPoint[id].setColor(pallete[mColor]);
        }
    }
}

void Heap::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt)
{
    mDt = dt;
    for (int i = 0; i < 4; i++)
        mButton[i].setMouseOver(mousePosition);
    mButton[10].setMouseOver(mousePosition);
    mButton[12].setMouseOver(mousePosition);
    for (int i = 0; i < 7; i++)
        mButtonImg[i].setMouseOver(mousePosition);
    if (mRun == 0)
        mButtonImg[7].setMouseOver(mousePosition);
    for (int i = 8; i < 11; i++)
        if (mButtonImg[i].setMouseOver(mousePosition) && mousePress)
            mColor = i - 8;
    mButtonImg[8 + mColor].mHovered = true;
    mButtonImg[11].setMouseOver(mousePosition);

    for (int i = 0; i < 4; i++)
        if (mousePress && mButton[i].mHovered)
        {
            mType = i + 1;
            mSmallType = 0;
            firstTime = true;
            mInputBar[2].reset(std::to_string(Rand(99)));
        }
    if (mousePress && mButton[10].mHovered)
    {
        mType = 4 + 1;
        mSmallType = 0;
        firstTime = true;
        mInputBar[2].reset(std::to_string(Rand(99)));
    }

    if (mousePress && mButton[12].mHovered)
    {
        mType = 5 + 1;
        mSmallType = 0;
        mInputBar[2].reset(std::to_string(Rand(99)));
        mNoteText[0].setString("");
        changeType();
    }
    else
        firstTimeChange = true;

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
    mSpriteSpeed.setPosition(sf::Vector2f(115 + 7 * 55, 405));

    if (mousePress && mButtonImg[11].mHovered)
    {
        firstTime = firstTimeSpeed = firstTimeChange = true;
        step = -1;
        mRun = mSpeed = 1;
        mType = mSmallType = mData = 0;
        mColor = 0;
        mArr.clear();
        mNoteText[0].setString("");
        mMaxHeap = false;
        mStep.clear();
        mButtonImg[11].mHovered = false;
        return;
    }

    switch (mType)
    {
    case 1: // Init
        updateInit(mousePress, mousePosition, keyPress);
        break;
    case 2: // Push
        updatePush(mousePress, mousePosition, keyPress);
        break;
    case 3: // Pop
        updatePop(mousePress, mousePosition, keyPress);
        break;
    case 4: // GetTop
        updateGetTop(mousePress, mousePosition, keyPress);
        break;
    case 5: // GetSize
        updateGetSize(mousePress, mousePosition, keyPress);
        break;
    case 6: // ChangeType
        break;
    default:
        break;
    }
}

void Heap::updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
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
        {
            mNoteText[0].setString("");
            init("data/" + mInputBar[0].mValue);
        }
        else
            firstTime = true;
        break;
    case 2: // Randomize
        mButton[5].mHovered = true;
        mInputBar[1].update(mousePress, mousePosition, keyPress, 26);
        if (mButton[6].setMouseOver(mousePosition) && mousePress)
        {
            mNoteText[0].setString("");
            std::ofstream outFile("data/randomize.data");
            outFile << mInputBar[1].mValue;
            outFile.close();
            init("data/randomize.data");
        }
        else
            firstTime = true;
        break;
    default:
        break;
    }
}

void Heap::updatePush(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[1].mHovered = true;

    mInputBar[2].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[7].setMouseOver(mousePosition) && mousePress && mInputBar[2].mValue != "")
    {
        mNoteText[0].setString("");
        push(mInputBar[2].mValue);
    }
    else
        firstTime = true;
}

void Heap::updatePop(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[2].mHovered = true;

    if (mButton[8].setMouseOver(mousePosition) && mousePress)
    {
        mNoteText[0].setString("");
        pop();
    }
    else
        firstTime = true;
}

void Heap::updateGetTop(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[3].mHovered = true;

    if (mButton[9].setMouseOver(mousePosition) && mousePress)
    {
        mNoteText[0].setString("");
        getTop();
    }
    else
        firstTime = true;
}

void Heap::updateGetSize(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[10].mHovered = true;

    if (mButton[11].setMouseOver(mousePosition) && mousePress) getSize();
    else
        firstTime = true;
}

void Heap::heapify(Step &step, int i)
{
    int smallest = i; // Initialize smallest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
 
    // If left child is larger than root
    if (l < (int)mArr.size() && isLess(mArr[l], mArr[smallest], mMaxHeap))
        smallest = l;
 
    // If right child is larger than smallest so far
    if (r < (int)mArr.size() && isLess(mArr[r], mArr[smallest], mMaxHeap))
        smallest = r;
    
    reset(step.mTree, 0);
    int id1 = findPoint(step.mTree, mArr[i]);
    step.mTree.mPoint[id1].setHighLight(true);
    mStep.push_back(step);
    int id2 = findPoint(step.mTree, mArr[smallest]);
    step.mTree.mPoint[id2].setHighLight(true);
    if (id1 != id2) mStep.push_back(step);

    // If smallest is not root
    if (smallest != i) 
    {
        swap(mArr[i], mArr[smallest]);
        reset(step.mTree, 0);
        id1 = findPoint(step.mTree, mArr[i]);
        step.mTree.mPoint[id1].setHighLight(true);
        id2 = findPoint(step.mTree, mArr[smallest]);
        step.mTree.mPoint[id2].setHighLight(true);
        mStep.push_back(step);
        heapify(step, smallest);
    }
}

void Heap::init(std::string filename)
{
    std::ifstream inFile(filename), inCode("pseudo/heap/init.pseudo");
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
    
    mArr.clear();
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
    reset(tmpStep.mTree, 0);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));

    std::string key;
    while (inFile >> key)
    {
        if (std::find(mArr.begin(), mArr.end(), key) != mArr.end() || (int)mArr.size() >= 31) continue;
        mArr.push_back(key);
    }
    reset(tmpStep.mTree, 0);
    mStep.push_back(tmpStep);


    tmpStep.mText = mRealText;
    tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
    for (int i = (int)mArr.size() / 2 - 1; i >= 0; i--)
        heapify(tmpStep, i);

    reset(tmpStep.mTree, 0);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inFile.close();
    inCode.close();
}

void Heap::push(std::string key)
{
    std::ifstream inCode("pseudo/heap/push.pseudo");
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
    reset(tmpStep.mTree, 0);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    if (std::find(mArr.begin(), mArr.end(), key) != mArr.end() || (int)mArr.size() >= 31)
    {
        mStep.push_back(tmpStep);
        tmpStep.mText = mRealText;
        mStep.push_back(tmpStep);
        inCode.close();
        return;
    }
    mStep.push_back(tmpStep);
    tmpStep.mText = mRealText;
    tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
    mArr.push_back(key);
    reset(tmpStep.mTree, 0);
    int id = findPoint(tmpStep.mTree, key);
    tmpStep.mTree.mPoint[id].setHighLight(true);
    mStep.push_back(tmpStep);
    
    int i = (int)mArr.size() - 1;
    tmpStep.mText = mRealText;
    tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
    reset(tmpStep.mTree, 0);
    int x = findPoint(tmpStep.mTree, mArr[i]);
    tmpStep.mTree.mPoint[x].setHighLight(true);
    mStep.push_back(tmpStep);
    while (i != 0 && isLess(mArr[i], mArr[(i - 1) / 2], mMaxHeap))
    {
        tmpStep.mText = mRealText;
        for (int id = 4; id < 7; id++)
            tmpStep.mText[id].setFillColor(sf::Color(230, 100, 140));
        reset(tmpStep.mTree, 0);
        int id1 = findPoint(tmpStep.mTree, mArr[i]);
        tmpStep.mTree.mPoint[id1].setHighLight(true);
        int id2 = findPoint(tmpStep.mTree, mArr[(i - 1) / 2]);
        tmpStep.mTree.mPoint[id2].setHighLight(true);
        mStep.push_back(tmpStep);
        swap(mArr[i], mArr[(i - 1) / 2]);
        reset(tmpStep.mTree, 0);
        id1 = findPoint(tmpStep.mTree, mArr[i]);
        tmpStep.mTree.mPoint[id1].setHighLight(true);
        id2 = findPoint(tmpStep.mTree, mArr[(i - 1) / 2]);
        tmpStep.mTree.mPoint[id2].setHighLight(true);
        mStep.push_back(tmpStep);
        i = (i - 1) / 2;
        tmpStep.mText = mRealText;
        for (int id = 4; id < 8; id++) if (id != 6)
            tmpStep.mText[id].setFillColor(sf::Color(230, 100, 140));
        reset(tmpStep.mTree, 0);
        id1 = findPoint(tmpStep.mTree, mArr[i]);
        tmpStep.mTree.mPoint[id1].setHighLight(true);
        mStep.push_back(tmpStep);
    }

    reset(tmpStep.mTree, 0);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void Heap::pop()
{
    std::ifstream inCode("pseudo/heap/pop.pseudo");
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

    step = 0;
    mRun = 1;

    if (mArr.empty()) 
    {
        tmpStep.mText = mRealText;
        tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
        reset(tmpStep.mTree, 0);
        tmpStep.mText = mRealText;
        mStep.push_back(tmpStep);
        inCode.close();
        return;
    }
    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    reset(tmpStep.mTree, 0);
    int id1 = findPoint(tmpStep.mTree, mArr[0]);
    tmpStep.mTree.mPoint[id1].setHighLight(true);
    int id2 = findPoint(tmpStep.mTree, mArr[(int)mArr.size() - 1]);
    tmpStep.mTree.mPoint[id2].setHighLight(true);
    mStep.push_back(tmpStep);
    mArr[0] = mArr[(int)mArr.size() - 1];
    reset(tmpStep.mTree, 0);
    tmpStep.mTree.mPoint[id1].setHighLight(true);
    tmpStep.mTree.mPoint[id2].setHighLight(true);
    mStep.push_back(tmpStep);
    mArr.pop_back();
    tmpStep.mText = mRealText;
    tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
    reset(tmpStep.mTree, 0);
    mStep.push_back(tmpStep);
    if (!mArr.empty())
    {
        tmpStep.mText = mRealText;
        tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
        heapify(tmpStep, 0);
    }

    reset(tmpStep.mTree, 0);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void Heap::getTop()
{
    std::ifstream inCode("pseudo/heap/getTop.pseudo");
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

    step = 0;
    mRun = 1;

    if (mArr.empty()) 
    {
        reset(tmpStep.mTree, 0);
        tmpStep.mTime = 0;
        tmpStep.mText = mRealText;
        tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
        tmpStep.mText = mRealText;
        mStep.push_back(tmpStep);
        inCode.close();
        return;
    }
    reset(tmpStep.mTree, 0);
    int id1 = findPoint(tmpStep.mTree, mArr[0]);
    tmpStep.mTree.mPoint[id1].setHighLight(true);
    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);
    inCode.close();
}

void Heap::getSize()
{
    std::ifstream inCode("pseudo/heap/getSize.pseudo");
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

    step = 0;
    mRun = 1;

    reset(tmpStep.mTree, 0);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    std::string sizeHeap = "Size = " + std::to_string((int)mArr.size());
    mNoteText[0].setString(sizeHeap);
    mStep.push_back(tmpStep);
    inCode.close();
}

void Heap::changeType()
{
    if (firstTime == false)
        return;
    firstTime = false;

    mStep.clear();
    Step tmpStep;

    step = 0;
    mRun = 1;

    std::string tmp = "Change type of this Heap (min heap <-> max heap)";
    mRealText[0].setString(tmp);
    mRealText[0].setFillColor(sf::Color::Black);
    tmpStep.mTime = 0;
    tmpStep.cntCode = 1;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    mMaxHeap = !mMaxHeap;
    for (int i = (int)mArr.size() / 2 - 1; i >= 0; i--)
        heapify(tmpStep, i);

    reset(tmpStep.mTree, 0);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
}

void Heap::draw()
{
    sf::Text textImple;
    textImple.setCharacterSize(35);
    textImple.setString("Implementation");
    textImple.setStyle(sf::Text::Bold);
    textImple.setFont(mFont);
    textImple.setFillColor(sf::Color(230, 100, 140));
    textImple.setPosition(100 + 555 / 2 - textImple.getLocalBounds().width / 2, 505 - 35 / 2);
    mWindow.draw(textImple);

    for (int i = 0; i < cntNote; i++)
        mWindow.draw(mNoteText[i]);
    for (int i = 0; i < 4; i++)
        mButton[i].draw(mWindow);
    mButton[10].draw(mWindow);
    mButton[12].draw(mWindow);
    for (int i = 0; i < 7; i++)
        mButtonImg[i].draw(mWindow);
    if (mRun == 0)
        mButtonImg[7].draw(mWindow);
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
    case 2: // Push
        mInputBar[2].draw(mWindow);
        mButton[7].draw(mWindow);
        break;
    case 3: // Pop
        mButton[8].draw(mWindow);
        break;
    case 4: // GetTop
        mButton[9].draw(mWindow);
        break;
    case 5: // GetSize
        mButton[11].draw(mWindow);
        break;
    case 6: // ChangeType
        mButton[12].draw(mWindow);
        break;
    default:
        break;
    }
    setColor();
    if (mRun == 1 && !mStep.empty())
    {
        while (step < mStep.size() - 1)
        {
            mStep[step].draw(mWindow);
            mStep[step].mTime += 100 * mSpeed * mDt;
            if (mStep[step].mTime < 100)
                break;
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
