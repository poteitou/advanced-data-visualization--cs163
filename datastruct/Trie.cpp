#include "Trie.hpp"

Trie::Trie(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode) : mWindow(window), mFont(font), mFontCode(fontCode), mType(0), mSmallType(0)
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

    std::ifstream inNote("pseudo/avltree/avltree.note");
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
    mRoot = NULL;
}

int Trie::height(Node *root)
{
    if (root == NULL) return 0;
    return root->height;
}

Trie::Node* Trie::newNode()
{
    Node* node = new Node();
	node->isEndOfWord = false;
    node->height = 1;
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
    node->height = root->height;
    node->numChild = root->numChild;
    node->key = root->key;
    for (int i = 0; i < 26; i++)
        node->child[i] = copy(root->child[i]);
    return node;
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
                tree.mLine.erase(tree.mLine.begin() + addLine(tree, x, y, x - distance + j * distance / numChild + distance / numChild / 2, y + 50, false));
                destroyNode(tree, root->child[i], x - distance + j * distance / numChild + distance / numChild / 2, y + 50, distance / 2);
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
                tree.mLine.push_back(Line(sf::Vector2f(x, y), sf::Vector2f(x - distance + j * distance / numChild + distance / numChild / 2, y + 50), pallete[mColor], false));
                beautify(tree, root->child[i], x - distance + j * distance / numChild + distance / numChild / 2, y + 50, distance / 2);
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
    srand(time(NULL));
    return rand() % MAX;
}

void Trie::randomize()
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
        if (i < randSize - 1)
            temp += ' ';
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
            finalInit("data/" + mInputBar[0].mValue);
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
            finalInit("data/randomize.data");
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

    mInputBar[2].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[7].setMouseOver(mousePosition) && mousePress && mInputBar[2].mValue != "")
        finalInsert(mInputBar[2].mValue);
    else
        firstTime = true;
}

void Trie::updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[2].mHovered = true;

    mInputBar[3].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[8].setMouseOver(mousePosition) && mousePress && mInputBar[3].mValue != "")
        finalRemove(mInputBar[3].mValue);
    else
        firstTime = true;
}

void Trie::updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[3].mHovered = true;

    mInputBar[4].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[9].setMouseOver(mousePosition) && mousePress && mInputBar[4].mValue != "")
        finalSearch(mInputBar[4].mValue);
    else
        firstTime = true;
}

Trie::Node* Trie::rightRotate(Node *Y)
{
    Node *X = Y->left;
    Node *T2 = X->right;

    X->right = Y;
    Y->left = T2;

    Y->height = std::max(height(Y->left), height(Y->right)) + 1;
    X->height = std::max(height(X->left), height(X->right)) + 1;

    return X;
}

Trie::Node* Trie::leftRotate(Node *X)
{
    Node *Y = X->right;
    Node *T2 = Y->left;

    Y->left = X;
    X->right = T2;

    X->height = std::max(height(X->left), height(X->right)) + 1;
    Y->height = std::max(height(Y->left), height(Y->right)) + 1;

    return Y;
}

void::Node* Trie::insert(Node* root, std::string key)
{
    struct Node* pTemp = root;

	for (int i = 0; i < key.length(); i++) {
		int index = key[i] - 'a';
		if (!pTemp->child[index])
			pTemp->child[index] = newNode();

		pTemp = pTemp->child[index];
	}

	// mark last node as leaf
	pTemp->isEndOfWord = true;
}

bool Trie::canInsert(std::string key)
{
    Node* root = copy(mRoot);
    root = insert(root, key);
    bool res = root->height <= 10;
    destroy(root);
    return res;
}

Trie::Node* Trie::init(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 800)
{
    if (root == NULL)
    {
        addPoint(step.mTree, x, y, key, true);
        mStep.push_back(step);
        return newNode(key);
    }

    addPoint(step.mTree, x, y, root->key, true);
    mStep.push_back(step);

    if (stoi(key) < stoi(root->key))
    {
        addLine(step.mTree, x, y, x - distance, y + 50, true);
        root->left = insert(step, root->left, key, x - distance, y + 50, distance / 2);
    }
    else if (stoi(key) > stoi(root->key))
    {
        addLine(step.mTree, x, y, x + distance, y + 50, true);
        root->right = insert(step, root->right, key, x + distance, y + 50, distance / 2);
    }
    else return root;

    root->height = std::max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    resetSub(step.mTree, root, x, y, distance);
    addPoint(step.mTree, x, y, root->key, true);
    mStep.push_back(step);

    if (balance > 1 && key < root->left->key)
        return rightRotate(step, root, x, y, distance);
    if (balance < -1 && key > root->right->key)
        return leftRotate(step, root, x, y, distance);
    if (balance > 1 && key > root->left->key)
    {
        root->left = leftRotate(step, root->left, x - distance, y + 50, distance / 2);
        resetSub(step.mTree, root->left, x - distance, y + 50, distance / 2);
        mStep.push_back(step);
        return rightRotate(step, root, x, y, distance);
    }
    if (balance < -1 && key < root->right->key)
    {
        root->right = rightRotate(step, root->right, x + distance, y + 50, distance / 2);
        resetSub(step.mTree, root->right, x + distance, y + 50, distance / 2);
        mStep.push_back(step);
        return leftRotate(step, root, x, y, distance);
    }
 
    return root;
}

void Trie::finalInit(std::string filename)
{
    std::ifstream inFile(filename), inCode("pseudo/avltree/init.pseudo");
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
    while (inFile >> key)
    {
        if (canInsert(key) == false) continue;
        mRoot = init(tmpStep, mRoot, key);
        reset(tmpStep.mTree, mRoot);
        mStep.push_back(tmpStep);
    }

    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inFile.close();
    inCode.close();
}

Trie::Node* Trie::insert(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 800)
{
    if (root == NULL)
    {
        addPoint(step.mTree, x, y, key, true);
        mStep.push_back(step);
        return newNode(key);
    }
    addPoint(step.mTree, x, y, root->key, true);
    mStep.push_back(step);

    if (stoi(key) < stoi(root->key))
    {
        addLine(step.mTree, x, y, x - distance, y + 50, true);
        root->left = insert(step, root->left, key, x - distance, y + 50, distance / 2);
    }
    else if (stoi(key) > stoi(root->key))
    {
        addLine(step.mTree, x, y, x + distance, y + 50, true);
        root->right = insert(step, root->right, key, x + distance, y + 50, distance / 2);
    }
    else // Equal keys are not allowed in BST
    {
        return root;
    }

    root->height = std::max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    resetSub(step.mTree, root, x, y, distance);
    addPoint(step.mTree, x, y, root->key, true);
    step.mText = mRealText;
    step.mText[2].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(step);

    // Left Left Problem
    if (balance > 1 && key < root->left->key)
    {
        step.mText = mRealText;
        step.mText[3].setFillColor(sf::Color(230, 100, 140));
        return rightRotate(step, root, x, y, distance);
    }
    // Right Right Problem
    if (balance < -1 && key > root->right->key)
    {
        step.mText = mRealText;
        step.mText[4].setFillColor(sf::Color(230, 100, 140));
        return leftRotate(step, root, x, y, distance);
    }

    // Left Right Problem
    if (balance > 1 && key > root->left->key)
    {
        step.mText = mRealText;
        step.mText[5].setFillColor(sf::Color(230, 100, 140));
        root->left = leftRotate(step, root->left, x - distance, y + 50, distance / 2);
        resetSub(step.mTree, root->left, x - distance, y + 50, distance / 2);
        step.mText = mRealText;
        step.mText[6].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
        return rightRotate(step, root, x, y, distance);
    }

    // Right Left Problem
    if (balance < -1 && key < root->right->key)
    {
        step.mText = mRealText;
        step.mText[7].setFillColor(sf::Color(230, 100, 140));
        root->right = rightRotate(step, root->right, x + distance, y + 50, distance / 2);
        resetSub(step.mTree, root->right, x + distance, y + 50, distance / 2);
        step.mText = mRealText;
        step.mText[8].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
        return leftRotate(step, root, x, y, distance);
    }
 
    return root;
}

void Trie::finalInsert(std::string key)
{
    std::ifstream inCode("pseudo/avltree/insert.pseudo");
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
    if (canInsert(key) == false)
    {
        mStep.push_back(tmpStep);
        tmpStep.mText = mRealText;
        mStep.push_back(tmpStep);
        inCode.close();
        return;
    }
    mRoot = insert(tmpStep, mRoot, key);

    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

Trie::Node* Trie::minValueNode(Step &step, Node* node, float x, float y, float distance)
{
    if (node->left == NULL)
    {
        addPoint(step.mTree, x, y, node->key, true);
        mStep.push_back(step);
        return node;
    }
    addPoint(step.mTree, x, y, node->key, true);
    addLine(step.mTree, x, y, x - distance, y + 50, true);
    mStep.push_back(step);
    return minValueNode(step, node->left, x - distance, y + 50, distance / 2);
}

Trie::Node* Trie::remove(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 800)
{
    if (root == NULL) return root;
    addPoint(step.mTree, x, y, root->key, true);
    mStep.push_back(step);

    if (stoi(key) < stoi(root->key))
    {
        if (root->left) addLine(step.mTree, x, y, x - distance, y + 50, true);
        root->left = remove(step, root->left, key, x - distance, y + 50, distance / 2);
    }
    else if (stoi(key) > stoi(root->key))
    {
        if (root->right) addLine(step.mTree, x, y, x + distance, y + 50, true);
        root->right = remove(step, root->right, key, x + distance, y + 50, distance / 2);
    }
    else
    {
        // node with only one child or no child
        if((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
                step.mTree.mLine.erase(step.mTree.mLine.begin() + addLine(step.mTree, x - distance * 2, y - 50, x, y, true));
                step.mTree.mLine.erase(step.mTree.mLine.begin() + addLine(step.mTree, x + distance * 2, y - 50, x, y, true));
            }
            else // One child case
            {
                step.mTree.mLine.erase(step.mTree.mLine.begin() + addLine(step.mTree, x, y, x - distance, y + 50, true));
                step.mTree.mLine.erase(step.mTree.mLine.begin() + addLine(step.mTree, x, y, x + distance, y + 50, true));
                *root = *temp; // Copy the contents of the non-empty child
            }
            step.mTree.mPoint.erase(step.mTree.mPoint.begin() + findPoint(step.mTree, x, y));
            delete temp;
            temp = NULL;
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            addLine(step.mTree, x, y, x + distance, y + 50, true);
            mStep.push_back(step);
            Node* temp = minValueNode(step, root->right, x + distance, y + 50, distance / 2);
            mStep.push_back(step);
 
            // Copy the inorder successor's data to this node
            resetSub(step.mTree, root, x, y, distance);
            int id = findPoint(step.mTree, x, y);
            // root->key = temp->key;
            step.mTree.mPoint[id] = Point(23, sf::Vector2f(x, y), root->key, mFont, true, pallete[mColor]);
            mStep.push_back(step);
 
            // Delete the inorder successor
            if (root->right) addLine(step.mTree, x, y, x + distance, y + 50, true);
            root->right = remove(step, root->right, temp->key, x + distance, y + 50, distance / 2);
            root->key = temp->key;
        }
    }
 
    // If the tree had only one node then return
    if (root == NULL) return root;
 
    root->height = std::max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    resetSub(step.mTree, root, x, y, distance);
    addPoint(step.mTree, x, y, root->key, true);
    step.mText = mRealText;
    step.mText[2].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(step);
 
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
    {
        step.mText = mRealText;
        step.mText[3].setFillColor(sf::Color(230, 100, 140));
        return rightRotate(step, root, x, y, distance);
    }
 
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
    {
        step.mText = mRealText;
        step.mText[4].setFillColor(sf::Color(230, 100, 140));
        return leftRotate(step, root, x, y, distance);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        step.mText = mRealText;
        step.mText[5].setFillColor(sf::Color(230, 100, 140));
        root->left = leftRotate(step, root->left, x - distance, y + 50, distance / 2);
        resetSub(step.mTree, root->left, x - distance, y + 50, distance / 2);
        step.mText = mRealText;
        step.mText[6].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
        return rightRotate(step, root, x, y, distance);
    }
 
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        step.mText = mRealText;
        step.mText[7].setFillColor(sf::Color(230, 100, 140));
        root->right = rightRotate(step, root->right, x + distance, y + 50, distance / 2);
        resetSub(step.mTree, root->right, x + distance, y + 50, distance / 2);
        step.mText = mRealText;
        step.mText[8].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
        return leftRotate(step, root, x, y, distance);
    }
 
    return root;
}

void Trie::finalRemove(std::string key)
{
    std::ifstream inCode("pseudo/avltree/remove.pseudo");
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

    mRoot = remove(tmpStep, mRoot, key);

    reset(tmpStep.mTree, mRoot);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void Trie::search(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 800)
{
    if (root == NULL) 
    {
        step.mText = mRealText;
        step.mText[2].setFillColor(sf::Color(230, 100, 140));
        reset(step.mTree, mRoot);
        mStep.push_back(step);
        return;
    }
    addPoint(step.mTree, x, y, root->key, true);
    mStep.push_back(step);

    if (stoi(key) < stoi(root->key))
    {
        step.mText = mRealText;
        step.mText[4].setFillColor(sf::Color(230, 100, 140));
        if (root->left) addLine(step.mTree, x, y, x - distance, y + 50, true);
        search(step, root->left, key, x - distance, y + 50, distance / 2);
    }
    else if (stoi(key) > stoi(root->key))
    {
        step.mText = mRealText;
        step.mText[5].setFillColor(sf::Color(230, 100, 140));
        if (root->right) addLine(step.mTree, x, y, x + distance, y + 50, true);
        search(step, root->right, key, x + distance, y + 50, distance / 2);
    }
    else
    {
        step.mText = mRealText;
        step.mText[3].setFillColor(sf::Color(230, 100, 140));
        reset(step.mTree, mRoot);
        addPoint(step.mTree, x, y, root->key, true);
        mStep.push_back(step);
        return;
    }
}

void Trie::finalSearch(std::string key)
{
    std::ifstream inCode("pseudo/avltree/search.pseudo");
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

    search(tmpStep, mRoot, key);
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
