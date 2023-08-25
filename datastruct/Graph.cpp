#include "Graph.hpp"

Graph::Graph(sf::RenderWindow &window, sf::Font &font, sf::Font &fontCode) : mWindow(window), mFont(font), mFontCode(fontCode), mType(0), mSmallType(0)
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

    std::ifstream inNote("pseudo/graph/graph.note");
    std::string tmp;
    cntNote = 0;
    while (getline(inNote, tmp))
    {
        mNoteText[cntNote].setPosition(720, 760 + cntNote * 35 - 20 / 2);
        mNoteText[cntNote++].setString(tmp);
    }
    inNote.close();

    std::string nameButton[] = {"Init", "Connected", "MST", "Dijkstra", "From File", "Randomize", "OK", "OK", "OK", "OK"};
    for (int i = 0; i < 4; i++) // Init, Connected, Mst, Dijkstra
        mButton[i] = Button(sf::Vector2f(100, 50), sf::Vector2f(100, 100 + i * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);

    for (int i = 4; i < 6; i++) // From File + Randomize
        mButton[i] = Button(sf::Vector2f(150, 50), sf::Vector2f(225 + (i - 4) * 175, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[i], mFont, 22);

    // Init bar + OK
    mInputBar[0] = InputBar(sf::Vector2f(350, 50), sf::Vector2f(225, 175), mFont, "example.data", 2);
    mButton[6] = Button(sf::Vector2f(75, 50), sf::Vector2f(575, 100), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[6], mFont, 22);

    // Connected bar + OK
    mInputBar[2] = InputBar(sf::Vector2f(100, 50), sf::Vector2f(225, 100 + 55), mFont, std::to_string(Rand(99)), 0);
    mButton[7] = Button(sf::Vector2f(75, 50), sf::Vector2f(350, 100 + 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[7], mFont, 22);

    // Mst bar + OK
    mInputBar[3] = InputBar(sf::Vector2f(100, 50), sf::Vector2f(225, 100 + 2 * 55), mFont, std::to_string(Rand(99)), 0);
    mButton[8] = Button(sf::Vector2f(75, 50), sf::Vector2f(350, 100 + 2 * 55), sf::Color(160, 220, 255), sf::Color(50, 140, 200), nameButton[8], mFont, 22);

    // Dijkstra bar + OK
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
    mVertex = mEdge = 0;
}

void Graph::destroy()
{
    mVertex = mEdge = 0;
    for (int i = 0; i < 10; i++)
        mAdj[i].clear();
}

void Graph::reset(Tree &tree)
{
    tree.mPoint.clear();
    tree.mEdge.clear();
    float PI = std::acos(-1);
    float R = 300;
    for (int i = 0; i < mVertex; i++)
    {
        float x = 1100 + R * std::sin(i * 2 * PI / mVertex);
        float y = 400 + R * (1 - std::cos(i * 2 * PI / mVertex));
        tree.mPoint.push_back(Point(25, sf::Vector2f(x, y), std::to_string(i), mFont, false, pallete[mColor]));
        for (int j = 0; j < mAdj[i].size(); j++)
        {
            int u = i;
            int v = mAdj[i][j].second;
            int w = mAdj[i][j].first;
            float x1 = 1100 + R * std::sin(u * 2 * PI / mVertex);
            float y1 = 400 + R * (1 - std::cos(u * 2 * PI / mVertex));
            float x2 = 1100 + R * std::sin(v * 2 * PI / mVertex);
            float y2 = 400 + R * (1 - std::cos(v * 2 * PI / mVertex));
            tree.mEdge.push_back(Edge(sf::Vector2f(x1, y1), sf::Vector2f(x2, y2), std::to_string(w), mFont, pallete[mColor], false));
        }
    }
}

void Graph::Tree::draw(sf::RenderWindow &mWindow)
{
    for (int i = 0; i < mEdge.size(); i++)
        mEdge[i].draw(mWindow);
    for (int i = 0; i < mPoint.size(); i++)
        mPoint[i].draw(mWindow);
}

int Graph::addPoint(Tree &tree, int id, bool highLight)
{
    float PI = std::acos(-1);
    float R = 300;
    float x = 1100 + R * std::sin(id * 2 * PI / mVertex);
    float y = 400 + R * (1 - std::cos(id * 2 * PI / mVertex));
    std::string key = std::to_string(id);
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

int Graph::addEdge(Tree &tree, int id1, int id2, int w, bool highLight)
{
    float PI = std::acos(-1);
    float R = 300;
    float x = 1100 + R * std::sin(id1 * 2 * PI / mVertex);
    float y = 400 + R * (1 - std::cos(id1 * 2 * PI / mVertex));
    float u = 1100 + R * std::sin(id2 * 2 * PI / mVertex);
    float v = 400 + R * (1 - std::cos(id2 * 2 * PI / mVertex));
    for (int i = 0; i < tree.mEdge.size(); i++)
    {
        if (tree.mEdge[i].mPosBegin == sf::Vector2f(x, y) && tree.mEdge[i].mPosEnd == sf::Vector2f(u, v))
        {
            tree.mEdge[i].mValue = std::to_string(w);
            tree.mEdge[i].setHighLight(highLight);
            return i;
        }
        else if (tree.mEdge[i].mPosBegin == sf::Vector2f(u, v) && tree.mEdge[i].mPosEnd == sf::Vector2f(x, y))
        {
            tree.mEdge[i].mValue = std::to_string(w);
            tree.mEdge[i].setHighLight(highLight);
            return i;
        }
    }
    tree.mEdge.push_back(Edge(sf::Vector2f(x, y), sf::Vector2f(u, v), std::to_string(w), mFont, pallete[mColor], highLight));
    return tree.mEdge.size() - 1;
}

void Graph::Step::draw(sf::RenderWindow &mWindow)
{
    mTree.draw(mWindow);
    for (int i = 0; i < cntCode; i++)
        mWindow.draw(mText[i]);
}

int Graph::Rand(int MAX)
{
    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    return rng() % MAX;
}

void Graph::randomize()
{
    std::ofstream outFile("data/randomize.data");

    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
    int n = Rand(10) + 1, m = Rand(20) + 1;
    outFile << n << ' ' << m << '\n';
    for (int i = 0; i < m; i++)
    {
        int u = Rand(n), v = Rand(n), w = Rand(100);
        outFile << u << ' ' << v << ' ' << w << '\n';
    }
    outFile.close();
}

void Graph::setColor()
{
    for (int i = 0; i < mStep.size(); i++)
    {
        for (int id = 0; id < mStep[i].mTree.mEdge.size(); id++)
        {
            if (mStep[i].mTree.mEdge[id].mColor != sf::Color::Black)
                mStep[i].mTree.mEdge[id].setColor(pallete[mColor]);
        }
        for (int id = 0; id < mStep[i].mTree.mPoint.size(); id++)
        {
            if (mStep[i].mTree.mPoint[id].mColor != sf::Color::Black)
                mStep[i].mTree.mPoint[id].setColor(pallete[mColor]);
        }
    }
}

void Graph::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int &mData, float dt)
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
        destroy();
        mButtonImg[11].mHovered = false;
        return;
    }

    switch (mType)
    {
    case 1: // Init
        updateInit(mousePress, mousePosition, keyPress);
        break;
    case 2: // Connected
        // updateConnected(mousePress, mousePosition, keyPress);
        break;
    case 3: // Mst
        // updateMst(mousePress, mousePosition, keyPress);
        break;
    case 4: // Dijkstra
        // updateDijkstra(mousePress, mousePosition, keyPress);
        break;
    default:
        break;
    }
}

void Graph::updateInit(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    mButton[0].mHovered = true;
    if (mButton[4].setMouseOver(mousePosition) && mousePress) // From File
    {
        mInputBar[0].reset("example.data");
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
        if (mButton[6].setMouseOver(mousePosition) && mousePress)
        {
            init("data/randomize.data");
        }
        else
            firstTime = true;
        break;
    default:
        break;
    }
}

/*
void Graph::updateConnected(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[1].mHovered = true;

    mInputBar[2].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[7].setMouseOver(mousePosition) && mousePress && mInputBar[2].mValue != "")
        finalConnected(mInputBar[2].mValue);
    else
        firstTime = true;
}

void Graph::updateMst(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[2].mHovered = true;

    mInputBar[3].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[8].setMouseOver(mousePosition) && mousePress && mInputBar[3].mValue != "")
        finalMst(mInputBar[3].mValue);
    else
        firstTime = true;
}

void Graph::updateDijkstra(bool mousePress, sf::Vector2i mousePosition, char &keyPress)
{
    char tempkeyPress;
    mButton[3].mHovered = true;

    mInputBar[4].update(mousePress, mousePosition, keyPress, 2);
    if (mButton[9].setMouseOver(mousePosition) && mousePress && mInputBar[4].mValue != "")
        finalDijkstra(mInputBar[4].mValue);
    else
        firstTime = true;
}

Graph::Node* Graph::connected(Node *root, std::string key)
{
    if (root == NULL)
        return newNode(key);
    if (key < root->key)
        root->left = connected(root->left, key);
    else if (key > root->key)
        root->right = connected(root->right, key);
    else
        return root;

    root->height = 1 + std::max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
    if (balance > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

*/

void Graph::init(std::string filename)
{
    std::ifstream inFile(filename), inCode("pseudo/graph/init.pseudo");
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

    destroy();
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
    reset(tmpStep.mTree);
    tmpStep.mTime = 0;

    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    inFile >> mVertex >> mEdge;

    for (int i = 0; i < mEdge; i++)
    {
        tmpStep.mText = mRealText;
        for (int j = 0; j < 5; j++)
            tmpStep.mText[j].setFillColor(sf::Color(230, 100, 140));
        int u, v, w;
        inFile >> u >> v >> w;
        if (mVertex > 10 || !(0 <= u && u < mVertex) || !(0 <= v && v < mVertex) || u == v || !(0 < w && w <= 99)) continue;
        mAdj[u].push_back(std::make_pair(v, w));
        mAdj[v].push_back(std::make_pair(u, w));
        reset(tmpStep.mTree);
        addPoint(tmpStep.mTree, u, true);
        addPoint(tmpStep.mTree, v, true);
        addEdge(tmpStep.mTree, u, v, w, true);
        mStep.push_back(tmpStep);
    }
    if (mVertex > 10)
    {
        inFile.close();
        inCode.close();
        return;
    }

    reset(tmpStep.mTree);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inFile.close();
    inCode.close();
}

/*
Graph::Node* Graph::connected(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 200)
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
        addEdge(step.mTree, x, y, x - distance, y + 100, true);
        root->left = connected(step, root->left, key, x - distance, y + 100, distance / 2);
    }
    else if (stoi(key) > stoi(root->key))
    {
        addEdge(step.mTree, x, y, x + distance, y + 100, true);
        root->right = connected(step, root->right, key, x + distance, y + 100, distance / 2);
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
        root->left = leftRotate(step, root->left, x - distance, y + 100, distance / 2);
        resetSub(step.mTree, root->left, x - distance, y + 100, distance / 2);
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
        root->right = rightRotate(step, root->right, x + distance, y + 100, distance / 2);
        resetSub(step.mTree, root->right, x + distance, y + 100, distance / 2);
        step.mText = mRealText;
        step.mText[8].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
        return leftRotate(step, root, x, y, distance);
    }
 
    return root;
}

void Graph::finalConnected(std::string key)
{
    std::ifstream inCode("pseudo/graph/connected.pseudo");
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
    reset(tmpStep.mTree);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    if (canConnected(key) == false)
    {
        mStep.push_back(tmpStep);
        tmpStep.mText = mRealText;
        mStep.push_back(tmpStep);
        inCode.close();
        return;
    }
    mRoot = connected(tmpStep, mRoot, key);

    reset(tmpStep.mTree);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

Graph::Node* Graph::mst(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 200)
{
    if (root == NULL) return root;
    addPoint(step.mTree, x, y, root->key, true);
    mStep.push_back(step);

    if (stoi(key) < stoi(root->key))
    {
        if (root->left) addEdge(step.mTree, x, y, x - distance, y + 100, true);
        root->left = mst(step, root->left, key, x - distance, y + 100, distance / 2);
    }
    else if (stoi(key) > stoi(root->key))
    {
        if (root->right) addEdge(step.mTree, x, y, x + distance, y + 100, true);
        root->right = mst(step, root->right, key, x + distance, y + 100, distance / 2);
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
                step.mTree.mEdge.erase(step.mTree.mEdge.begin() + addEdge(step.mTree, x - distance * 2, y - 100, x, y, true));
                step.mTree.mEdge.erase(step.mTree.mEdge.begin() + addEdge(step.mTree, x + distance * 2, y - 100, x, y, true));
            }
            else // One child case
            {
                step.mTree.mEdge.erase(step.mTree.mEdge.begin() + addEdge(step.mTree, x, y, x - distance, y + 100, true));
                step.mTree.mEdge.erase(step.mTree.mEdge.begin() + addEdge(step.mTree, x, y, x + distance, y + 100, true));
                *root = *temp; // Copy the contents of the non-empty child
            }
            step.mTree.mPoint.erase(step.mTree.mPoint.begin() + findPoint(step.mTree, key));
            delete temp;
            temp = NULL;
        }
        else
        {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            addEdge(step.mTree, x, y, x + distance, y + 100, true);
            mStep.push_back(step);
            Node* temp = minValueNode(step, root->right, x + distance, y + 100, distance / 2);
            mStep.push_back(step);
 
            // Copy the inorder successor's data to this node
            resetSub(step.mTree, root, x, y, distance);
            int id = findPoint(step.mTree, root->key);
            // root->key = temp->key;
            step.mTree.mPoint[id] = Point(23, sf::Vector2f(x, y), root->key, mFont, true, pallete[mColor]);
            mStep.push_back(step);
 
            // Delete the inorder successor
            if (root->right) addEdge(step.mTree, x, y, x + distance, y + 100, true);
            root->right = mst(step, root->right, temp->key, x + distance, y + 100, distance / 2);
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
        root->left = leftRotate(step, root->left, x - distance, y + 100, distance / 2);
        resetSub(step.mTree, root->left, x - distance, y + 100, distance / 2);
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
        root->right = rightRotate(step, root->right, x + distance, y + 100, distance / 2);
        resetSub(step.mTree, root->right, x + distance, y + 100, distance / 2);
        step.mText = mRealText;
        step.mText[8].setFillColor(sf::Color(230, 100, 140));
        mStep.push_back(step);
        return leftRotate(step, root, x, y, distance);
    }
 
    return root;
}

void Graph::finalMst(std::string key)
{
    std::ifstream inCode("pseudo/graph/mst.pseudo");
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
    reset(tmpStep.mTree);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    mRoot = mst(tmpStep, mRoot, key);

    reset(tmpStep.mTree);
    tmpStep.mText = mRealText;
    mStep.push_back(tmpStep);
    inCode.close();
}

void Graph::dijkstra(Step &step, Node* root, std::string key, float x = 1100, float y = 175, float distance = 200)
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
        if (root->left) addEdge(step.mTree, x, y, x - distance, y + 100, true);
        dijkstra(step, root->left, key, x - distance, y + 100, distance / 2);
    }
    else if (stoi(key) > stoi(root->key))
    {
        step.mText = mRealText;
        step.mText[5].setFillColor(sf::Color(230, 100, 140));
        if (root->right) addEdge(step.mTree, x, y, x + distance, y + 100, true);
        dijkstra(step, root->right, key, x + distance, y + 100, distance / 2);
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

void Graph::finalDijkstra(std::string key)
{
    std::ifstream inCode("pseudo/graph/dijkstra.pseudo");
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
    reset(tmpStep.mTree);
    tmpStep.mTime = 0;
    tmpStep.mText = mRealText;
    tmpStep.mText[0].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    step = 0;
    mRun = 1;

    tmpStep.mText = mRealText;
    tmpStep.mText[1].setFillColor(sf::Color(230, 100, 140));
    mStep.push_back(tmpStep);

    dijkstra(tmpStep, mRoot, key);
    inCode.close();
}

*/ 
void Graph::draw()
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
            mButton[6].draw(mWindow);
            break;
        default:
            break;
        }
        break;
    case 2: // Connected
        mInputBar[2].draw(mWindow);
        mButton[7].draw(mWindow);
        break;
    case 3: // Mst
        mInputBar[3].draw(mWindow);
        mButton[8].draw(mWindow);
        break;
    case 4: // Dijkstra
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
