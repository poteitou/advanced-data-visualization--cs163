#include "Trie.hpp"

Trie::Trie(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode) : mWindow(window), mFont(font), mFontCode(fontCode), mType(0), mSmallType(0)
{
    mButton.resize(10);
    mInputBar.resize(5);
    mButtonImg.resize(12);
    mRealText.resize(12);
    mNoteText.resize(3);

    for (int i = 0; i < 12; i++)
    {
        mRealText[i].setCharacterSize(18);
        mRealText[i].setFont(mFontCode);
        mRealText[i].setFillColor(sf::Color::Black);
        mRealText[i].setPosition(120, 525 + i * 28 - 18 / 2);
    }
    for (int i = 0; i < 3; i++)
    {
        mNoteText[i].setFont(mFont);
        mNoteText[i].setFillColor(sf::Color::Black);
        mNoteText[i].setCharacterSize(20);
    }

    std::ifstream inNote("pseudo/trie/trie.note");
    std::string tmp;
    cntNote = 0;
    while (getline(inNote, tmp))
    {
        mNoteText[cntNote].setPosition(720, 760 + cntNote * 35 - 20 / 2);
        mNoteText[cntNote++].setString(tmp);
    }
    inNote.close();

    std::string nameButton[] = {"Init", "Insert", "Delete", "Search", "From File", "Randomize", "OK", "OK", "OK", "OK"};
    for (int i = 0; i < 4; i++) // Init, Insert, Remove, Search
        mButton[i] = Button(sf::Vector2f(100, 50), sf::Vector2f(100, 100 + i * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);

    for (int i = 4; i < 6; i++) // From File + Randomize
        mButton[i] = Button(sf::Vector2f(150, 50), sf::Vector2f(225 + (i - 4) * 175, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);

    // Init bar + OK
    mInputBar[0] = InputBar(sf::Vector2f(350, 50), sf::Vector2f(225, 175), mFont, "sample.data", 2);
    mInputBar[1] = InputBar(sf::Vector2f(425, 50), sf::Vector2f(225, 175), mFont, randString(0), 3);
    mButton[6] = Button(sf::Vector2f(75, 50), sf::Vector2f(575, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[6], mFont, 22);

    // Insert bar + OK
    mInputBar[2] = InputBar(sf::Vector2f(150, 50), sf::Vector2f(225, 100 + 55), mFont, randString(0), 3);
    mButton[7] = Button(sf::Vector2f(75, 50), sf::Vector2f(400, 100 + 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[7], mFont, 22);

    // Remove bar + OK
    mInputBar[3] = InputBar(sf::Vector2f(150, 50), sf::Vector2f(225, 100 + 2 * 55), mFont, randString(0), 3);
    mButton[8] = Button(sf::Vector2f(75, 50), sf::Vector2f(400, 100 + 2 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[8], mFont, 22);

    // Search bar + OK
    mInputBar[4] = InputBar(sf::Vector2f(150, 50), sf::Vector2f(225, 100 + 3 * 55), mFont, randString(0), 3);
    mButton[9] = Button(sf::Vector2f(75, 50), sf::Vector2f(400, 100 + 3 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[9], mFont, 22);

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
    mRoot = NULL;
}

Trie::Node* Trie::newNode()
{
    Node* node = new Node();
	node->isEndOfWord = false;
    node->numChild = 0;
    node->key = "";

	for (int i = 0; i < 26; i++)
		node->child[i] = NULL;
    
	return node;
}

Trie::Node* Trie::copy(Node* root)
{
    if (root == NULL) return NULL;
    Node* node = newNode();
    node->isEndOfWord = root->isEndOfWord;
    node->numChild = root->numChild;
    node->key = root->key;
    for (int i = 0; i < 26; i++)
        node->child[i] = copy(root->child[i]);
    return node;
}

bool Trie::isEmpty(Node* root)
{
    for (int i = 0; i < 26; i++)
        if (root->child[i]) return false;
    return true;
}

void Trie::destroy(Node* &root)
{
    if (root)
    {
        for (int i = 0; i < 26; i++)
            destroy(root->child[i]);
        delete root;
    }
    root = NULL;
}

void Trie::destroyNode(Tree &tree, Node* &root, float x = 1100, float y = 175, float distance = 800)
{
    if (root)
    {
        tree.mPoint.erase(tree.mPoint.begin() + addPoint(tree, x, y, root->key, false));

        for (int i = 0, j = 0; i < 26; i++)
            if (root->child[i])
            {
                tree.mLine.erase(tree.mLine.begin() + addLine(tree, x, y, x - distance / 2 + j * distance / root->numChild + distance / root->numChild / 2, y + 80, false));
                destroyNode(tree, root->child[i], x - distance / 2 + j * distance / root->numChild + distance / root->numChild / 2, y + 80, distance / root->numChild);
                j++;
            }
    }
}

void Trie::beautify(Tree &tree, Node *root, float x = 1100, float y = 175, float distance = 800)
{
    if (root)
    {
        tree.mPoint.push_back(Point(23, sf::Vector2f(x, y), root->key, mFont, false, pallete[mColor]));
        for (int i = 0, j = 0; i < 26; i++)
            if (root->child[i])
            {
                tree.mLine.push_back(Line(sf::Vector2f(x, y), sf::Vector2f(x - distance / 2 + j * distance / root->numChild + distance / root->numChild / 2, y + 80), pallete[mColor], false));
                beautify(tree, root->child[i], x - distance / 2 + j * distance / root->numChild + distance / root->numChild / 2, y + 80, distance / root->numChild);
                j++;
            }
    }
}

void Trie::reset(Tree &tree, Node *root)
{
    tree.mPoint.clear();
    tree.mLine.clear();
    beautify(tree, root);
}

void Trie::resetSub(Tree &tree, Node *root, float x = 1100, float y = 175, float distance = 800)
{
    destroyNode(tree, root, x, y, distance);
    beautify(tree, root, x, y, distance);
}

void Trie::Tree::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < mLine.size(); i++)
        mLine[i].draw(mWindow);
    for (int i = 0; i < mPoint.size(); i++)
        mPoint[i].draw(mWindow);
}

int Trie::findPoint(Tree &tree, float x, float y)
{
    for (int i = 0; i < tree.mPoint.size(); i++)
        if (tree.mPoint[i].mPos.x == x && tree.mPoint[i].mPos.y == y) return i;
    return -1;
}

int Trie::addPoint(Tree &tree, float x, float y, std::string key, bool highLight)
{
    for (int i = 0; i < tree.mPoint.size(); i++)
    {
        if (tree.mPoint[i].mPos.x == x && tree.mPoint[i].mPos.y == y)
        {
            tree.mPoint[i].mValue = key;
            tree.mPoint[i].setHighLight(highLight);
            return i;
        }
    }
    tree.mPoint.push_back(Point(23, sf::Vector2f(x, y), key, mFont, highLight, pallete[mColor]));
    return tree.mPoint.size() - 1;
}

int Trie::findLine(Tree &tree, float x, float y, float u, float v)
{
    for (int i = 0; i < tree.mLine.size(); i++)
    {
        if (tree.mLine[i].mPosBegin == sf::Vector2f(x, y) && tree.mLine[i].mPosEnd == sf::Vector2f(u, v)) return i;
        else if (tree.mLine[i].mPosBegin == sf::Vector2f(u, v) && tree.mLine[i].mPosEnd == sf::Vector2f(x, y)) return i;
    }
    return -1;
}

int Trie::addLine(Tree &tree, float x, float y, float u, float v, bool highLight)
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

void Trie::Step::draw(sf::RenderWindow &mWindow)
{
    mTree.draw(mWindow);
    for (int i = 0; i < cntCode; i++)
        mWindow.draw(mText[i]);
}

int Trie::Rand(int MAX)
{
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return rng() % MAX;
}

std::string Trie::randString(int size = 0)
{
    if (!size) size = Rand(6) + 1;
    std::string res = "";
    for (int i = 0; i < size; i++)
        res += char(Rand(26) + 97);
    return res;
}

void Trie::randomize()
{
    std::ofstream outFile("data/randomize.data");

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int randSize = rng() % 13 + 1;
    std::string temp = "";
    int remain = 26;
    for (int i = 0; i < randSize; i++)
    {
        std::string value = randString(remain - (randSize - i - 1) * 2 > 6 ? 0 : remain - (randSize - i - 1) * 2);
        outFile << value;
        temp += value;
        if (i < randSize - 1)
        {
            temp += ' ';
            outFile << ' ';
        }
        remain -= (value.size() + 1);
    }
    mInputBar[1].mValue = temp;
    mInputBar[1].mText.setString(temp);
    outFile.close();
}

void Trie::setColor()
{
    for (int i = 0; i < mStep.size(); i++)
    {
        for (int id = 0; id < mStep[i].mTree.mLine.size(); id++)
        {
            if (mStep[i].mTree.mLine[id].mColor != sf::Color::Black)
                mStep[i].mTree.mLine[id].setColor(pallete[mColor]);
        }
        for (int id = 0; id < mStep[i].mTree.mPoint.size(); id++)
        {
            if (mStep[i].mTree.mPoint[id].mColor != sf::Color::Black)
                mStep[i].mTree.mPoint[id].setColor(pallete[mColor]);
        }
    }
}

void Trie::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt)
{
    mDt = dt;
    for (int i = 0; i < 4; i++)
        mButton[i].setMouseOver(mousePosition);
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
            mInputBar[2].reset(randString(0));
            mInputBar[3].reset(randString(0));
            mInputBar[4].reset(randString(0));
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

    if (mousePress && mButtonImg[11].mHovered)
    {
        firstTime = firstTimeSpeed = true;
        step = -1;
        mRun = mSpeed = 1;
        mType = mSmallType = mData = 0;
        mColor = 0;
        mStep.clear();
        destroy(mRoot);
        mButtonImg[11].mHovered = false;
        return;
    }

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

void Trie::updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    mButton[0].mHovered = true;
    if (mButton[4].setMouseOver(mousePosition) && mousePress) // From File
    {
        mInputBar[0].reset("sample.data");
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
        else
            firstTime = true;
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
        else
            firstTime = true;
        break;
    default:
        break;
    }
}

void Trie::updateInsert(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[1].mHovered = true;

    mInputBar[2].update(mousePress, mousePosition, keyPress, 6);
    if (mButton[7].setMouseOver(mousePosition) && mousePress && mInputBar[2].mValue != "")
        insert(mInputBar[2].mValue);
    else
        firstTime = true;
}

void Trie::updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[2].mHovered = true;

    mInputBar[3].update(mousePress, mousePosition, keyPress, 6);
    if (mButton[8].setMouseOver(mousePosition) && mousePress && mInputBar[3].mValue != "")
        finalRemove(mInputBar[3].mValue);
    else
        firstTime = true;
}

void Trie::updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[3].mHovered = true;

    mInputBar[4].update(mousePress, mousePosition, keyPress, 6);
    if (mButton[9].setMouseOver(mousePosition) && mousePress && mInputBar[4].mValue != "")
        search(mInputBar[4].mValue);
    else
        firstTime = true;
}

bool Trie::insert(Node* root, std::string key)
{
    Node* pTemp = root;

    float distance = 800;
    if ((int)key.size() > 6) return false;
	for (int i = 0; i < key.size(); i++) 
    {
		int index = key[i] - 'a';
		if (!pTemp->child[index])
		{
            pTemp->child[index] = newNode();
            pTemp->numChild++;
        }
        if (distance / (pTemp->numChild) < 50) return false;
        distance /= (pTemp->numChild);
		pTemp = pTemp->child[index];
        pTemp->key = key[i];
	}

	// mark last node as leaf
	pTemp->isEndOfWord = true;
    return true;
}

bool Trie::canInsert(std::string key)
{
    Node* root = copy(mRoot);
    bool res = insert(root, key);
    destroy(root);
    return res;
}

void Trie::init(std::string filename)
{
    std::ifstream inFile(filename), inCode("pseudo/trie/init.pseudo");
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

    destroy(mRoot);
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
    reset(tmpStep.mTree, mRoot);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));

    std::string key;
    if (!mRoot) mRoot = newNode();
    while (inFile >> key)
    {
        if (canInsert(key) == false) continue;
        
        int x = 1100, y = 175, distance = 800;
        Node* pTemp = mRoot;
        addPoint(tmpStep.mTree, x, y, pTemp->key, true);
        mStep.push_back(tmpStep);
        for (int i = 0; i < key.size(); i++) 
        {
            int index = key[i] - 'a';
            if (!pTemp->child[index])
            {
                pTemp->child[index] = newNode();
                pTemp->numChild++;
                reset(tmpStep.mTree, mRoot);
                addPoint(tmpStep.mTree, x, y, pTemp->key, true);
                int Cnt = -1;
                for (int j = 0; j <= index; j++)
                    if (pTemp->child[j]) Cnt++;
                addLine(tmpStep.mTree, x, y, x - distance / 2 + Cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2, y + 80, true);
                addPoint(tmpStep.mTree, x - distance / 2 + Cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2, y + 80, "", true);
                mStep.push_back(tmpStep);
            }
            int cnt = -1;
            for (int j = 0; j <= index; j++)
                if (pTemp->child[j]) cnt++;
            reset(tmpStep.mTree, mRoot);
            addPoint(tmpStep.mTree, x, y, pTemp->key, true);
            addLine(tmpStep.mTree, x, y, x - distance / 2 + cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2, y + 80, true);
            x = x - distance / 2 + cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2;
            y = y + 80;
            distance = distance / (pTemp->numChild);
            pTemp = pTemp->child[index];
            pTemp->key = key[i];
            addPoint(tmpStep.mTree, x, y, pTemp->key, true);
            mStep.push_back(tmpStep);
        }
        pTemp->isEndOfWord = true;
        reset(tmpStep.mTree, mRoot);
        addPoint(tmpStep.mTree, x, y, pTemp->key, true);
        mStep.push_back(tmpStep);

        reset(tmpStep.mTree, mRoot);
        mStep.push_back(tmpStep);
    }

    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inFile.close();
    inCode.close();
}

void Trie::insert(std::string key)
{
    std::ifstream inCode("pseudo/trie/insert.pseudo");
    if (firstTime == false)
    {
        inCode.close();
        return;
    }
    firstTime = false;

    mStep.clear();
    Step tmpStep;
    if (!mRoot) mRoot = newNode();

    int cnt = 0;
    std::string tmp;
    while (getline(inCode, tmp))
    {
        mRealText[cnt].setString(tmp);
        mRealText[cnt++].setFillColor(sf::Color::Black);
    }

    tmpStep.cntCode = cnt;
    reset(tmpStep.mTree, mRoot);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;
    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    if (canInsert(key) == false)
    {
        mStep.push_back(tmpStep);
        tmpStep.mText = mRealText;
        mStep.push_back(tmpStep);
        inCode.close();
        return;
    }

    int x = 1100, y = 175, distance = 800;
    Node* pTemp = mRoot;
    tmpStep.mText = mRealText;
    tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
    addPoint(tmpStep.mTree, x, y, pTemp->key, true);
    mStep.push_back(tmpStep);
	for (int i = 0; i < key.size(); i++) 
    {
        tmpStep.mText = mRealText;
        tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
        tmpStep.mText[4].setFillColor(sf::Color(230, 100, 140));
		int index = key[i] - 'a';
		if (!pTemp->child[index])
		{
            tmpStep.mText[5].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[6].setFillColor(sf::Color(230, 100, 140));
            pTemp->child[index] = newNode();
            pTemp->numChild++;
            reset(tmpStep.mTree, mRoot);
            addPoint(tmpStep.mTree, x, y, pTemp->key, true);
            int Cnt = -1;
            for (int j = 0; j <= index; j++)
                if (pTemp->child[j]) Cnt++;
            addLine(tmpStep.mTree, x, y, x - distance / 2 + Cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2, y + 80, true);
            addPoint(tmpStep.mTree, x - distance / 2 + Cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2, y + 80, "", true);
            mStep.push_back(tmpStep);
        }
        tmpStep.mText[5].setFillColor(sf::Color::Black);
        tmpStep.mText[6].setFillColor(sf::Color::Black);
        int cnt = -1;
        for (int j = 0; j <= index; j++)
            if (pTemp->child[j]) cnt++;
        reset(tmpStep.mTree, mRoot);
        addPoint(tmpStep.mTree, x, y, pTemp->key, true);
        addLine(tmpStep.mTree, x, y, x - distance / 2 + cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2, y + 80, true);
        x = x - distance / 2 + cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2;
        y = y + 80;
        distance = distance / (pTemp->numChild);
		pTemp = pTemp->child[index];
        pTemp->key = key[i];
        addPoint(tmpStep.mTree, x, y, pTemp->key, true);
        tmpStep.mText[7].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
	}
	pTemp->isEndOfWord = true;
    reset(tmpStep.mTree, mRoot);
    addPoint(tmpStep.mTree, x, y, pTemp->key, true);
    tmpStep.mText = mRealText;
    tmpStep.mText[8].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

bool Trie::search(Node* root, std::string key)
{
	Node* pTemp = root;

	for (int i = 0; i < key.length(); i++) 
    {
		int index = key[i] - 'a';
		if (!pTemp->child[index]) return false;
		pTemp = pTemp->child[index];
	}

	return (pTemp != NULL && pTemp->isEndOfWord);
}

Trie::Node* Trie::remove(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 800, int depth = 0)
{
    reset(step.mTree, mRoot);
	if (!root) 
    {
        step.mText = mRealText;
        step.mText[0].setFillColor(sf::Color(230, 100, 140));
        step.mText[1].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
        return nullptr;
    }
    addPoint(step.mTree, x, y, root->key, true);
	if (depth == key.size()) 
    {
		if (root->isEndOfWord)
			root->isEndOfWord = false;

		if (isEmpty(root)) 
        {
			delete (root);
			root = NULL;
		}

        step.mText = mRealText;
        step.mText[0].setFillColor(sf::Color(230, 100, 140));
        for (int i = 2; i < 6; i++)
            step.mText[i].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
		return root;
	}

    int cnt = 0;
    for (int i = 0; i < 26; i++)
        if (root->child[i]) cnt++;
	int index = key[depth] - 'a';
    step.mText = mRealText;
    step.mText[0].setFillColor(sf::Color(230, 100, 140));
    for (int i = 6; i < 8; i++)
        step.mText[i].setFillColor(sf::Color(230, 100, 140));
    addLine(step.mTree, x, y, x - distance / 2 + cnt * distance / root->numChild + distance / root->numChild / 2, y + 80, true);
    mStep.push_back(step);
	root->child[index] = remove(step, root->child[index], key, x - distance / 2 + cnt * distance / root->numChild + distance / root->numChild / 2, y + 80, distance / root->numChild, depth + 1);

    reset(step.mTree, mRoot);
    addPoint(step.mTree, x, y, root->key, true);
	if (isEmpty(root) && root->isEndOfWord == false) 
    {
        step.mText = mRealText;
        step.mText[0].setFillColor(sf::Color(230, 100, 140));
        step.mText[8].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
		delete (root);
		root = NULL;
	}

    step.mText = mRealText;
    step.mText[0].setFillColor(sf::Color(230, 100, 140));
    step.mText[9].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(step);
	return root;
}

void Trie::finalRemove(std::string key)
{
    std::ifstream inCode("pseudo/trie/remove.pseudo");
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
    reset(tmpStep.mTree, mRoot);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    if (search(mRoot, key))
        remove(tmpStep, mRoot, key, 1100, 175, 800, 0);

    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void Trie::search(std::string key)
{
    std::ifstream inCode("pseudo/trie/search.pseudo");
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
    reset(tmpStep.mTree, mRoot);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    int x = 1100, y = 175, distance = 800;
    Node* pTemp = mRoot;
    tmpStep.mText = mRealText;
    tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
    addPoint(tmpStep.mTree, x, y, pTemp->key, true);
    mStep.push_back(tmpStep);
	for (int i = 0; i < key.size(); i++) 
    {
        tmpStep.mText = mRealText;
        tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
        tmpStep.mText[4].setFillColor(sf::Color(230, 100, 140));
		int index = key[i] - 'a';
		if (!pTemp->child[index]) 
        {
            tmpStep.mText[5].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[6].setFillColor(sf::Color(230, 100, 140));
            reset(tmpStep.mTree, mRoot);
            mStep.push_back(tmpStep);
            inCode.close();
            return;
        }
        tmpStep.mText[5].setFillColor(sf::Color::Black);
        tmpStep.mText[6].setFillColor(sf::Color::Black);
        int cnt = -1;
        for (int j = 0; j <= index; j++)
            if (pTemp->child[j]) cnt++;
        reset(tmpStep.mTree, mRoot);
        addPoint(tmpStep.mTree, x, y, pTemp->key, true);
        addLine(tmpStep.mTree, x, y, x - distance / 2 + cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2, y + 80, true);
        x = x - distance / 2 + cnt * distance / pTemp->numChild + distance / pTemp->numChild / 2;
        y = y + 80;
        distance = distance / (pTemp->numChild);
		pTemp = pTemp->child[index];
        pTemp->key = key[i];
        addPoint(tmpStep.mTree, x, y, pTemp->key, true);
        tmpStep.mText[7].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
	}

	if (pTemp != NULL && pTemp->isEndOfWord)
    {
        reset(tmpStep.mTree, mRoot);
        addPoint(tmpStep.mTree, x, y, pTemp->key, true);
        tmpStep.mText = mRealText;
        tmpStep.mText[8].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
    }
    else
    {
        reset(tmpStep.mTree, mRoot);
        tmpStep.mText = mRealText;
        tmpStep.mText[9].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(tmpStep);
    }
    inCode.close();
}

void Trie::draw()
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
