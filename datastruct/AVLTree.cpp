#include "AVLTree.hpp"

AVLTree::AVLTree(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode) : mWindow(window), mFont(font), mFontCode(fontCode), mType(0), mSmallType(0)
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
    mRoot = NULL;
}

int AVLTree::height(Node *root)
{
    if (root == NULL) return 0;
    return root->height;
}

int AVLTree::getBalance(Node *root)
{
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}

AVLTree::Node* AVLTree::newNode(std::string key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // leaf;
    return node;
}

void AVLTree::destroy(Node* &root)
{
    if (root)
    {
        destroy(root->left);
        destroy(root->right);
        delete root;
    }
    root = NULL;
}

void AVLTree::reset()
{
    destroy(mRoot);
    mRealTree.mPoint.clear();
    mRealTree.mLine.clear();
}

void AVLTree::preOrder(Node *root)
{
    if (root != NULL)
    {
        // cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void AVLTree::beautify(Tree &tree, Node *root, bool highLight = false, int index = 0, float x = 1100, float y = 175, float distance = 200)
{
    if (root !=  NULL)
    {
        tree.mPoint.push_back(Point(23, sf::Vector2f(x, y), root->key, mFont, highLight, pallete[mColor]));
        if (root->left)
            tree.mLine.push_back(Line(sf::Vector2f(x, y), sf::Vector2f(x - distance, y + 100.f), pallete[mColor], highLight));
        if (root->right)
            tree.mLine.push_back(Line(sf::Vector2f(x, y), sf::Vector2f(x + distance, y + 100.f), pallete[mColor], highLight));
        beautify(tree, root->left, highLight, index * 2 + 1, x - distance, y + 100.f, distance / 2);
        beautify(tree, root->right, highLight, index * 2 + 2, x + distance, y + 100.f, distance / 2);
    }
}

void AVLTree::Tree::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < mLine.size(); i++)
        mLine[i].draw(mWindow);
    for (int i = 0; i < mPoint.size(); i++)
        mPoint[i].draw(mWindow);
}

int AVLTree::getIndex(Node *root, int indexRoot, std::string key)
{
    if (root == NULL)
        return indexRoot;
    if (stoi(key) < stoi(root->key))
        return getIndex(root->left, indexRoot * 2 + 1, key);
    else if (stoi(key) > stoi(root->key))
        return getIndex(root->right, indexRoot * 2 + 2, key);
    return indexRoot;
}

void AVLTree::addPoint(Tree &tree, float x, float y, std::string key, bool highLight)
{
    tree.mPoint.push_back(Point(23, sf::Vector2f(x, y), key, mFont, highLight, pallete[mColor]));
}

void AVLTree::addLine(Tree &tree, float x, float y, float u, float v, bool highLight)
{
    tree.mLine.push_back(Line(sf::Vector2f(x, y), sf::Vector2f(u, v), pallete[mColor], highLight));
}

void AVLTree::Step::draw(sf::RenderWindow &mWindow)
{
    mTree.draw(mWindow);
    for (int i = 0; i < cntCode; i++)
        mWindow.draw(mText[i]);
}

int AVLTree::Rand(int MAX)
{
    srand(time(NULL));
    return rand() % MAX;
}

void AVLTree::randomize()
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

/* 
void AVLTree::setColor()
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
 */

void AVLTree::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt)
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
        reset();
        mButtonImg[11].mHovered = false;
        return;
    }

    switch (mType)
    {
    case 1: // Init
        // updateInit(mousePress, mousePosition, keyPress);
        break;
    case 2: // Insert
        updateInsert(mousePress, mousePosition, keyPress);
        break;
    case 3: // Remove
        // updateRemove(mousePress, mousePosition, keyPress);
        break;
    case 4: // Search
        // updateSearch(mousePress, mousePosition, keyPress);
        break;
    default:
        break;
    }
}

/* 
void AVLTree::updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
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
 */

void AVLTree::updateInsert(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[1].mHovered = true;

    mInputBar[2].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[7].setMouseOver(mousePosition) && mousePress && mInputBar[2].mValue != "")
        finalInsert(mInputBar[2].mValue);
    else
        firstTime = true;
}

/*
     y                               x
    / \     Right Rotation          / \
   x   T3   - - - - - - - >        T1  y 
  / \       < - - - - - - -           / \
 T1  T2     Left Rotation           T2  T3  
*/

/* 

Node* AVLTree::rightRotate(Node *y)
{
	Node *x = y->left;
	Node *T2 = x->right;

	// Perform rotation
	x->right = y;
	y->left = T2;

	// Update heights
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;

	// Return new root
	return x;
}

Node* AVLTree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}
 */

/* 
void AVLTree::updateRemove(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[2].mHovered = true;

    mInputBar[3].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[8].setMouseOver(mousePosition) && mousePress && mInputBar[3].mValue != "")
        remove(mInputBar[3].mValue);
    else
        firstTime = true;
}

void AVLTree::updateSearch(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[3].mHovered = true;

    mInputBar[4].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[9].setMouseOver(mousePosition) && mousePress && mInputBar[4].mValue != "")
        search(mInputBar[4].mValue);
    else
        firstTime = true;
}

void AVLTree::init(std::string filename)
{
    std::ifstream inFile(filename), inCode("pseudo/hashtable/init.pseudo");
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
 */

AVLTree::Node* AVLTree::insert(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 200)
{
    /* 1. Perform the normal BST insertion */
    if (root == NULL)
    {
        addPoint(step.mTree, x, y, key, true);
        addPoint(mRealTree, x, y, key, false);
        mStep.push_back(step);
        return newNode(key);
    }

    for (int i = 0; i < step.mTree.mPoint.size(); i++)
    {
        if (step.mTree.mPoint[i].mValue == root->key)
            step.mTree.mPoint[i].setHighLight(true);
    }
    mStep.push_back(step);

    if (stoi(key) < stoi(root->key))
    {
        addLine(mRealTree, x, y, x - distance, y + 100, false);
        addLine(step.mTree, x, y, x - distance, y + 100, true);
        root->left = insert(step, root->left, key, x - distance, y + 100, distance / 2);
    }
    else if (stoi(key) > stoi(root->key))
    {
        addLine(mRealTree, x, y, x + distance, y + 100, false);
        addLine(step.mTree, x, y, x + distance, y + 100, true);
        root->right = insert(step, root->right, key, x + distance, y + 100, distance / 2);
    }
    else // Equal keys are not allowed in BST
    {
        return root;
    }

    /* 2. Update height of this ancestor root */
    // root->height = std::max(height(root->left), height(root->right)) + 1;

    // /* 3. Get the balance factor of this ancestor
    //     root to check whether this root became
    //     unbalanced */
    // int balance = getBalance(root);
    // for (int i = 0; i < step.mTree.mPoint.size(); i++)
    // {
    //     if (step.mTree.mPoint[i].mValue == root->key)
    //         step.mTree.mPoint[i].setHighLight(true);
    // }
    // mStep.push_back(step);

/*
    // Left Left Problem
    if (balance > 1 && key < root->left->key)
    {
        
        return rightRotate(root);
    }
    // Right Right Problem
    if (balance < -1 && key > root->right->key)
    {
        return leftRotate(root);
    }

    // Left Right Problem
    if (balance > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        print all tree
        return rightRotate(root);
    }

    // Right Left Problem
    if (balance < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        print all tree
        return leftRotate(root);
    }
 */
    /* return the (unchanged) root pointer */

    // beautify(mRealTree, mRoot);
    // mStep.push_back(step);
    return root;
}

void AVLTree::finalInsert(std::string key)
{
    // std::ifstream inCode("pseudo/avltree/insert.pseudo");
    if (firstTime == false)
    {
        // inCode.close();
        return;
    }
    firstTime = false;

    mStep.clear();
    Step tmpStep;

    int cnt = 0;
    // std::string tmp;
    // while (getline(inCode, tmp))
    // {
    //     mRealText[cnt].setString(tmp);
    //     mRealText[cnt++].setFillColor(sf::Color::Black);
    // }

    tmpStep.cntCode = cnt;
    tmpStep.mTree = mRealTree;
    tmpStep.mTime = 0;
    // tmpStep.mText = mRealText;
    // tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    mRoot = insert(tmpStep, mRoot, key);

    beautify(mRealTree, mRoot);
    tmpStep.mTree = mRealTree;
    // tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    // inCode.close();
}

/* 
void AVLTree::remove(std::string element)
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
            mRealBucket[index].mPoint.erase(mRealBucket[index].mPoint.begin() + i);
            mRealBucket[index].mLine.pop_back();
            break;
        }
    }

    beautify(mRealTree, mRoot);
    for (int i = 0; i < 5; i++)
        tmpStep.mBucket[i] = mRealBucket[i];
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void AVLTree::search(std::string element)
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
 */

void AVLTree::draw()
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
    beautify(mRealTree, mRoot);
    // setColor();
    if (mRun == 1 && !mStep.empty())
    {
        while (step < mStep.size() - 1)
        {
            mStep[step].draw(mWindow);
            mStep[step].mTime += 100.f * mSpeed * mDt;
            if (mStep[step].mTime < 100.f)
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