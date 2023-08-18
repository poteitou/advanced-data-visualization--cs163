#include "Tree234.hpp"

Tree234::Tree234(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode) : mWindow(window), mFont(font), mFontCode(fontCode), mType(0), mSmallType(0)
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

    std::ifstream inNote("pseudo/tree234/tree234.note");
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
    mRoot = nullptr;
}

int Tree234::num(std::string key)
{
    if (key == "") return -1;
    return stoi(key);
}

int Tree234::Node::num(std::string key)
{
    if (key == "") return -1;
    return stoi(key);
}

Tree234::Node::Node()
{
    for (int i = 0; i < 3; i++)
    {
        keys[i] = "";
        child[i] = nullptr;
    }
    child[3] = nullptr;
    parent = nullptr;
    numKeys = 0;
}

void Tree234::destroy(Node *&root)
{
    if (root)
    {
        for (int i = 0; i <= root->numKeys; i++)
            destroy(root->child[i]);
        delete root;
    }
    root = nullptr;
}

Block Tree234::createBlock(Node* root, float size = 50.f, int id = -1, float x = 1100, float y = 225, float distance = 800, bool highLight = false)
{
    if (id == -1)
    {
        if (root->numKeys == 0)
            return Block(size, sf::Vector2f(x, y), "", "", "", mFont, highLight, pallete[mColor]);
        else if (root->numKeys == 1)
            return Block(size, sf::Vector2f(x, y), "", root->keys[0], "", mFont, highLight, pallete[mColor]);
        else if (root->numKeys == 2)
            return Block(size, sf::Vector2f(x, y), root->keys[0], "", root->keys[1], mFont, highLight, pallete[mColor]);
        else if (root->numKeys == 3)
            return Block(size, sf::Vector2f(x, y), root->keys[0], root->keys[1], root->keys[2], mFont, highLight, pallete[mColor]);
    }
    if (root->numKeys == 1)
        return createBlock(root->child[id], std::min(distance / 2 / 3 - 2, 50.f), -1, x - distance / 4 + id * distance / 2, y + 150, distance / 2, highLight);
    else if (root->numKeys == 2)
        return createBlock(root->child[id], std::min(distance / 3 / 3 - 2, 50.f), -1, x - distance / 3 + id * distance / 3, y + 150, distance / 3, highLight);
    else // if (root->numKeys == 3)
        return createBlock(root->child[id], std::min(distance / 4 / 3 - 2, 50.f), -1, x - distance / 8 * 3 + id * distance / 4, y + 150, distance / 4, highLight);
}

Line Tree234::createLine(Node* root, int id, float x = 1100, float y = 225, float distance = 800, bool highLight = false)
{
    if (root->numKeys == 1)
        return Line(sf::Vector2f(x, y), sf::Vector2f(x - distance / 4 + id * distance / 2, y + 150), pallete[mColor], highLight);
    else if (root->numKeys == 2)
        return Line(sf::Vector2f(x, y), sf::Vector2f(x - distance / 3 + id * distance / 3, y + 150), pallete[mColor], highLight);
    else // if (root->numKeys == 3)
        return Line(sf::Vector2f(x, y), sf::Vector2f(x - distance / 8 * 3 + id * distance / 4, y + 150), pallete[mColor], highLight);
}

void Tree234::beautify(Tree &tree, Node *root, int id = -1, float x = 1100, float y = 225, float distance = 800)
{
    if (root)
    {
        if (id == -1)
            tree.mBlock.push_back(createBlock(root, 50.f, id, x, y, distance));
        for (int i = 0; i <= root->numKeys; i++)
        {
            if (root->child[i] && root->child[i]->numKeys)
            {
                tree.mLine.push_back(createLine(root, i, x, y, distance));
                Block temp = createBlock(root, 50.f, i, x, y, distance, false);
                tree.mBlock.push_back(temp);
                beautify(tree, root->child[i], i, temp.mPos.x, temp.mPos.y, distance / (root->numKeys + 1));
            }
        }
    }
}

void Tree234::reset(Tree &tree, Node *root)
{
    tree.mBlock.clear();
    tree.mLine.clear();
    beautify(tree, root);
}

void Tree234::Tree::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < mLine.size(); i++)
        mLine[i].draw(mWindow);
    for (int i = 0; i < mBlock.size(); i++)
        mBlock[i].draw(mWindow);
}

void Tree234::Step::draw(sf::RenderWindow &mWindow)
{
    mTree.draw(mWindow);
    for (int i = 0; i < cntCode; i++)
        mWindow.draw(mText[i]);
}

int Tree234::Rand(int MAX)
{
    srand(time(nullptr));
    return rand() % MAX;
}

void Tree234::randomize()
{
    std::ofstream outFile("data/randomize.data");

    srand(time(nullptr));
    int randSize = rand() % 9 + 1;
    std::string temp = "";
    for (int i = 0; i < randSize; i++)
    {
        std::string value = std::to_string(rand() % 100);
        outFile << value << ' ';
        temp += value;
        if (i < randSize - 1)
            temp += ' ';
    }
    mInputBar[1].mValue = temp;
    mInputBar[1].mText.setString(temp);
    outFile.close();
}

void Tree234::setColor()
{
    for (int i = 0; i < mStep.size(); i++)
    {
        for (int id = 0; id < mStep[i].mTree.mLine.size(); id++)
        {
            if (mStep[i].mTree.mLine[id].mColor != sf::Color::Black)
                mStep[i].mTree.mLine[id].setColor(pallete[mColor]);
        }
        for (int id = 0; id < mStep[i].mTree.mBlock.size(); id++)
        {
            if (mStep[i].mTree.mBlock[id].mColor != sf::Color::Black)
                mStep[i].mTree.mBlock[id].setColor(pallete[mColor]);
        }
    }
}

void Tree234::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt)
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

    if (mousePress && mButtonImg[11].mHovered)
    {
        firstTime = firstTimeSpeed = true;
        step = -1;
        mRun = mSpeed = 1;
        mType = mSmallType = mData = 0;
        mColor = 0;
        mStep.clear();
        destroy(mRoot);
        mKeys.clear();
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

void Tree234::updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
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

void Tree234::updateInsert(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[1].mHovered = true;

    mInputBar[2].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[7].setMouseOver(mousePosition) && mousePress && mInputBar[2].mValue != "")
        insert(mInputBar[2].mValue);
    else
        firstTime = true;
}

void Tree234::updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[2].mHovered = true;

    mInputBar[3].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[8].setMouseOver(mousePosition) && mousePress && mInputBar[3].mValue != "")
        finalRemove(mInputBar[3].mValue);
    else
        firstTime = true;
}

void Tree234::updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[3].mHovered = true;

    mInputBar[4].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[9].setMouseOver(mousePosition) && mousePress && mInputBar[4].mValue != "")
        search(mInputBar[4].mValue);
    else
        firstTime = true;
}

bool Tree234::Node::isFull()
{
    return numKeys == 3;
}

bool Tree234::Node::isLeaf()
{
    return child[0] == nullptr;
}

int Tree234::Node::findKey(std::string key)
{
    for (int i = 0; i < numKeys; i++)
        if (num(key) == num(keys[i]))
            return i;
    return -1;
}

int Tree234::Node::insertKey(std::string key)
{
    for (int j = 2; j >= 0; j--)
    {
        if (keys[j] == "")
            continue;
        if (num(key) < num(keys[j]))
        {
            keys[j + 1] = keys[j];
        }
        else if (num(key) > num(keys[j]))
        {
            keys[j + 1] = key;
            numKeys++;
            return j + 1;
        }
        else
        {
            return -1;
        }
    }
    keys[0] = key;
    numKeys++;
    return 0;
}

std::string Tree234::Node::removeKey()
{
    std::string temp = keys[numKeys - 1];
    keys[numKeys - 1] = "";
    numKeys--;
    return temp;
}

void Tree234::Node::removeKeyAtIndex(int index)
{
    for (int i = index; i < numKeys - 1; i++)
        keys[i] = keys[i + 1];
    keys[numKeys - 1] = "";
    numKeys--;
}

void Tree234::Node::connectChild(int index, Node* nodeChild)
{
    child[index] = nodeChild;
    if (nodeChild)
        nodeChild->parent = this;
}

Tree234::Node* Tree234::Node::disconnectChild(int index)
{
    Node* temp = child[index];
    if (temp)
    {
        temp->parent = nullptr;
        child[index] = nullptr;
    }
    return temp;
}

int Tree234::getNextChild(Node* node, std::string key)
{
    int j;
    for (j = 0; j < node->numKeys; j++)
    {
        if (num(key) < num(node->keys[j]))
            return j;
    }
    return j;
}

int Tree234::getIndexInPar(Node *node)
{
    Node *parent = node->parent;
    int index = 0;
    for (int i = 0; i <= parent->numKeys; i++)
        if (parent->child[i] == node)
            return i;
    return -1;
}

std::string Tree234::successor(std::string key, Node *node)
{
    if (node->isLeaf())
    {
        for (int j = 0; j < node->numKeys; j++)
        {
            if (num(node->keys[j]) > num(key))
                return node->keys[j];
        }
        return "";
    }
    for (int j = 0; j < node->numKeys; j++)
    {
        if (num(key) < num(node->keys[j]))
        {
            std::string succ = successor(key, node->child[j]);
            if (succ != "")
                return succ;
            return node->keys[j];
        }
    }
    return successor(key, node->child[node->numKeys]);
}


bool Tree234::swapSuccessor(std::string key, Node* &node, std::string value)
{
    if (node->isLeaf())
    {
        for (int j = 0; j < node->numKeys; j++)
        {
            if (num(node->keys[j]) > num(key))
            {
                node->keys[j] = value;
                return true;
            }
        }
        return false;
    }
    for (int j = 0; j < node->numKeys; j++)
    {
        if (num(key) < num(node->keys[j]))
        {
            if (swapSuccessor(key, node->child[j], value))
                return true;
            node->keys[j] = value;
            return true;
        }
    }
    return swapSuccessor(key, node->child[node->numKeys], value);
}

void Tree234::split(Node* &root, Node* node)
{
    Node* parent;
    int itemIndex;
    std::string itemC = node->removeKey();
    std::string itemB = node->removeKey();
    Node* child2 = node->disconnectChild(2);
    Node* child3 = node->disconnectChild(3);

    Node* newRight = new Node();
    if (node == root)
    {
        root = new Node();
        parent = root;
        root->connectChild(0, node);
    }
    else
    {
        parent = node->parent;
    }
    itemIndex = parent->insertKey(itemB);
    int n = parent->numKeys;
    for (int j = n - 1; j > itemIndex; j--)
    {
        Node* temp = parent->disconnectChild(j);
        parent->connectChild(j + 1, temp);
    }
    newRight->insertKey(itemC);
    newRight->connectChild(0, child2);
    newRight->connectChild(1, child3);
    parent->connectChild(itemIndex + 1, newRight);
}

bool Tree234::rotate(Node* &node)
{
    Node* parent = node->parent;
    int index = getIndexInPar(node);
    if (index > 0)
    {
        Node* left = parent->child[index - 1];
        if (left->numKeys > 1)
        {
            std::string smallestKeyInRoot = parent->keys[0];
            parent->removeKeyAtIndex(0);
            std::string highestKeyInSibling = left->keys[left->numKeys - 1];
            Node* child = left->disconnectChild(left->numKeys);
            left->removeKeyAtIndex(left->numKeys - 1);
            node->insertKey(smallestKeyInRoot);
            parent->insertKey(highestKeyInSibling);
            node->connectChild(0, child);
            return true;
        }
    }
    if (index < parent->numKeys)
    {
        Node* right = parent->child[index + 1];
        if (right->numKeys > 1)
        {
            std::string highestKeyInRoot = parent->keys[parent->numKeys - 1];
            parent->removeKeyAtIndex(parent->numKeys - 1);
            std::string smallestKeyInSibling = right->keys[0];
            Node* child = right->disconnectChild(0);
            right->removeKeyAtIndex(0);
            node->insertKey(highestKeyInRoot);
            parent->insertKey(smallestKeyInSibling);
            node->connectChild(node->numKeys, child);
            return true;
        }
    }
    return false;
}

bool Tree234::merge(Node* &node)
{
    Node* parent = node->parent;
    if (parent->parent == nullptr)
        return false;
    int index = getIndexInPar(node);

    if (index < parent->numKeys)
    {
        Node* right = parent->child[index + 1];

        Node* newNode = new Node();
        std::string parentKey = parent->removeKey();
        std::string nodeKey = node->keys[0];
        std::string siblingKey = right->keys[0];
        newNode->insertKey(parentKey);
        newNode->insertKey(nodeKey);
        newNode->insertKey(siblingKey);

        parent->disconnectChild(index);
        parent->disconnectChild(index + 1);
        parent->connectChild(index, newNode);
        newNode->connectChild(0, node->child[0]);
        newNode->connectChild(1, node->child[1]);
        newNode->connectChild(2, right->child[0]);
        newNode->connectChild(3, right->child[1]);
    }
    else
    {
        Node* left = parent->child[index - 1];
        Node* newNode = new Node();
        std::string parentKey = parent->removeKey();
        std::string nodeKey = node->keys[0];
        std::string siblingKey = left->keys[0];
        newNode->insertKey(parentKey);
        newNode->insertKey(nodeKey);
        newNode->insertKey(siblingKey);

        parent->disconnectChild(index);
        parent->disconnectChild(index - 1);
        parent->connectChild(index - 1, newNode);
        newNode->connectChild(0, left->child[0]);
        newNode->connectChild(1, left->child[1]);
        newNode->connectChild(2, node->child[0]);
        newNode->connectChild(3, node->child[1]);
    }
    return true;
}

void Tree234::shrink(Node* &root, Node* &node)
{
    Node* parent = node->parent;
    int index = getIndexInPar(node);

    Node* sibling;
    if (index == 0) sibling = parent->child[1];
    else sibling = parent->child[0];
    Node* newRoot = new Node();

    std::string parentKey = parent->keys[0];
    std::string siblingKey = sibling->keys[0];
    std::string nodeKey = node->keys[0];
    newRoot->insertKey(parentKey);
    newRoot->insertKey(siblingKey);
    newRoot->insertKey(nodeKey);

    if (index == 0)
    {
        newRoot->connectChild(0, node->child[0]);
        newRoot->connectChild(1, node->child[1]);
        newRoot->connectChild(2, sibling->child[0]);
        newRoot->connectChild(3, sibling->child[1]);
    }
    else
    {
        newRoot->connectChild(0, sibling->child[0]);
        newRoot->connectChild(1, sibling->child[1]);
        newRoot->connectChild(2, node->child[0]);
        newRoot->connectChild(3, node->child[1]);
    }
    root = newRoot;
}

int Tree234::height(Node* root)
{
    if (root == nullptr)
        return 0;
    int h = 1;
    for (int i = 0; i <= root->numKeys; i++)
        h = std::max(h, 1 + height(root->child[i]));
    return h;
}

Tree234::Node* Tree234::copy(Node *root)
{
    if (root == nullptr)
        return nullptr;
    Node *temp = new Node();
    for (int i = 0; i < 3; i++)
        temp->keys[i] = root->keys[i];
    for (int i = 0; i < 4; i++)
    {
        temp->child[i] = copy(root->child[i]);
        if (temp->child[i])
            temp->child[i]->parent = temp;
    }
    temp->numKeys = root->numKeys;
    return temp;
}

bool Tree234::canInsert(std::string key)
{
    if (!mRoot)
        return true;
    for (std::string x : mKeys)
        if (key == x) return false;
    Node* root = copy(mRoot);
    Node* cur = root;
    while (true)
    {
        if (cur->isFull())
        {
            split(root, cur);
            cur = cur->parent;
            int j = getNextChild(cur, key);
            cur = cur->child[j];
        }
        else if (cur->isLeaf())
        {
            break;
        }
        else
        {
            int j = getNextChild(cur, key);
            cur = cur->child[j];
        }
    }
    cur->insertKey(key);
    if (height(root) <= 3)
    {
        destroy(root);
        return true;
    }
    destroy(root);
    return false;
}

void Tree234::init(std::string filename)
{
    std::ifstream inFile(filename), inCode("pseudo/tree234/init.pseudo");
    if (!inFile)
        return;

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
    mKeys.clear();
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
    while (inFile >> key)
    {
        if (canInsert(key) == false)
            continue;
        mKeys.push_back(key);
        if (!mRoot) mRoot = new Node();
        Node *cur = mRoot;
        int id = -1;
        float x = 1100, y = 225, distance = 800, X = 1100, Y = 225, DISTANCE = 800;
        tmpStep.mTree.mBlock.push_back(createBlock(cur, 50.f, id, x, y, distance, true));
        mStep.push_back(tmpStep);

        while (true)
        {   
            if (cur->isFull())
            {
                reset(tmpStep.mTree, mRoot);
                tmpStep.mTree.mBlock.push_back(createBlock(id == -1 ? cur : cur->parent, 50.f, id, X, Y, DISTANCE, true));
                mStep.push_back(tmpStep);
                split(mRoot, cur);

                cur = cur->parent;
                int j = getNextChild(cur, key);
                id = j;
                Block temp = createBlock(cur, 50.f, id, X, Y, DISTANCE, true);
                x = temp.mPos.x, y = temp.mPos.y;
                distance = DISTANCE / (cur->numKeys + 1);
                cur = cur->child[j];
                reset(tmpStep.mTree, mRoot);
                tmpStep.mTree.mBlock.push_back(temp);
                mStep.push_back(tmpStep);
            }
            else if (cur->isLeaf())
            {
                mStep.push_back(tmpStep);
                cur->insertKey(key);
                reset(tmpStep.mTree, mRoot);
                tmpStep.mTree.mBlock.push_back(createBlock(id == -1 ? cur : cur->parent, 50.f, id, X, Y, DISTANCE, true));
                mStep.push_back(tmpStep);
                break;
            }
            else
            {
                int j = getNextChild(cur, key);
                id = j;
                Block temp = createBlock(cur, 50.f, id, x, y, distance, true);
                X = x, Y = y;
                DISTANCE = distance;
                x = temp.mPos.x, y = temp.mPos.y;
                distance = DISTANCE / (cur->numKeys + 1);
                cur = cur->child[j];
                reset(tmpStep.mTree, mRoot);
                tmpStep.mTree.mBlock.push_back(temp);
                mStep.push_back(tmpStep);
            }
        }
        reset(tmpStep.mTree, mRoot);
        mStep.push_back(tmpStep);
    }

    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inFile.close();
    inCode.close();
}

void Tree234::insert(std::string key)
{
    std::ifstream inCode("pseudo/tree234/insert.pseudo");
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

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);
    if (canInsert(key) == false)
    {
        tmpStep.mText = mRealText;
        mStep.push_back(tmpStep);
        inCode.close();
        return;
    }
    mKeys.push_back(key);
    if (!mRoot) mRoot = new Node();
    Node *cur = mRoot;
    int id = -1;
    float x = 1100, y = 225, distance = 800, X = 1100, Y = 225, DISTANCE = 800;
    tmpStep.mText = mRealText;
    tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
    tmpStep.mTree.mBlock.push_back(createBlock(cur, 50.f, id, x, y, distance, true));
    mStep.push_back(tmpStep);

    while (true)
    {   
        tmpStep.mText = mRealText;
        tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
        if (cur->isFull())
        {
            tmpStep.mText[4].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[5].setFillColor(sf::Color(230, 100, 140));
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(createBlock(id == -1 ? cur : cur->parent, 50.f, id, X, Y, DISTANCE, true));
            mStep.push_back(tmpStep);
            split(mRoot, cur);

            cur = cur->parent;
            int j = getNextChild(cur, key);
            id = j;
            Block temp = createBlock(cur, 50.f, id, X, Y, DISTANCE, true);
            x = temp.mPos.x, y = temp.mPos.y;
            distance = DISTANCE / (cur->numKeys + 1);
            cur = cur->child[j];
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(temp);
            mStep.push_back(tmpStep);
        }
        else if (cur->isLeaf())
        {
            tmpStep.mText = mRealText;
            tmpStep.mText[8].setFillColor(sf::Color(230, 100, 140));
            mStep.push_back(tmpStep);
            cur->insertKey(key);
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(createBlock(id == -1 ? cur : cur->parent, 50.f, id, X, Y, DISTANCE, true));
            mStep.push_back(tmpStep);
            break;
        }
        else
        {
            tmpStep.mText[6].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[7].setFillColor(sf::Color(230, 100, 140));
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(createBlock(id == -1 ? cur : cur->parent, 50.f, id, X, Y, DISTANCE, true));
            mStep.push_back(tmpStep);
            int j = getNextChild(cur, key);
            id = j;
            Block temp = createBlock(cur, 50.f, id, x, y, distance, true);
            X = x, Y = y;
            DISTANCE = distance;
            x = temp.mPos.x, y = temp.mPos.y;
            distance = DISTANCE / (cur->numKeys + 1);
            cur = cur->child[j];
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(temp);
            mStep.push_back(tmpStep);
        }
    }
    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void Tree234::remove(Step &step, Node* &root, std::string key, float x = 1100, float y = 225, float distance = 800)
{
    if (root->isLeaf())
    {
        int index = root->findKey(key);
        root->removeKeyAtIndex(index);
    }
    else
    {
        if (root->numKeys == 1 && root->parent != nullptr)
        {
            if (rotate(root));
            else if (merge(root));
            else shrink(mRoot, root);
        }
        for (int j = 0; j < root->numKeys; j++)
        {
            std::string temp = root->keys[j];
            if (num(temp) == num(key))
            {
                std::string nxt = successor(key, root);
                if (nxt == "")
                {
                    root->removeKeyAtIndex(j);
                    root->disconnectChild(j + 1);
                    return;
                }
                else
                {
                    swapSuccessor(key, root, temp);
                    root->keys[j] = nxt;
                }
            }
            else if (num(temp) > num(key))
            {
                return remove(step, root->child[j], key);
            }
        }
        return remove(step, root->child[root->numKeys], key);
    }
}

void Tree234::finalRemove(std::string key)
{
    std::ifstream inCode("pseudo/tree234/remove.pseudo");
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

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    for (std::string x : mKeys)
    {
        if (key == x)
        {
            remove(tmpStep, mRoot, key);
            break;
        }
    }
    mKeys.erase(std::find(mKeys.begin(), mKeys.end(), key));

    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void Tree234::search(std::string key)
{
    std::ifstream inCode("pseudo/tree234/search.pseudo");
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

    if (!mRoot)
    {
        tmpStep.mText = mRealText;
        mStep.push_back(tmpStep);
        return;
    }
    Node* cur = mRoot;
    int id = -1;
    float x = 1100, y = 225, distance = 800, X = 1100, Y = 225, DISTANCE = 800;
    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    tmpStep.mTree.mBlock.push_back(createBlock(cur, 50.f, id, x, y, distance, true));
    mStep.push_back(tmpStep);
    while(true)
    {
        tmpStep.mText = mRealText;
        tmpStep.mText[2].setFillColor(sf::Color(230, 100, 140));
        int index = cur->findKey(key);
        if (index != -1) 
        {
            tmpStep.mText[3].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[4].setFillColor(sf::Color(230, 100, 140));
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(createBlock(id == -1 ? cur : cur->parent, 50.f, id, X, Y, DISTANCE, true));
            mStep.push_back(tmpStep);
            break;
        }
        else if (!cur->isLeaf())
        {
            tmpStep.mText[5].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[6].setFillColor(sf::Color(230, 100, 140));
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(createBlock(id == -1 ? cur : cur->parent, 50.f, id, X, Y, DISTANCE, true));
            mStep.push_back(tmpStep);
            int j = getNextChild(cur, key);
            id = j;
            Block temp = createBlock(cur, 50.f, id, x, y, distance, true);
            X = x, Y = y;
            DISTANCE = distance;
            x = temp.mPos.x, y = temp.mPos.y;
            distance = DISTANCE / (cur->numKeys + 1);
            cur = cur->child[j];
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(temp);
            mStep.push_back(tmpStep);
        }
        else
        {
            tmpStep.mText[7].setFillColor(sf::Color(230, 100, 140));
            tmpStep.mText[8].setFillColor(sf::Color(230, 100, 140));
            reset(tmpStep.mTree, mRoot);
            tmpStep.mTree.mBlock.push_back(createBlock(id == -1 ? cur : cur->parent, 50.f, id, X, Y, DISTANCE, true));
            mStep.push_back(tmpStep);
            reset(tmpStep.mTree, mRoot);
            mStep.push_back(tmpStep);
            break;
        }
    }
    inCode.close();
}

void Tree234::draw()
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
