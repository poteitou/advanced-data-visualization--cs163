#include "InputBar.hpp"

InputBar::InputBar() {}

InputBar::InputBar(sf::Vector2f size, sf::Vector2f pos, sf::Font &font, std::string defaultText, int type)
    : mSize(size), mPos(pos), mValue(defaultText), mHovered(false), mSelected(false), mType(type)
{
    mFontSize = 26;
    mRect.setPosition(mPos);
    mRect.setSize(mSize);
    mDefaultColor = sf::Color::White;
    mHoveredColor = sf::Color(200, 200, 200);
    mSelectedColor = sf::Color(0, 0, 0);
    mRect.setFillColor(mDefaultColor);
    mRect.setOutlineThickness(2.f);
    mRect.setOutlineColor(sf::Color::Black);

    mText.setFont(font);
    mText.setString(mValue);
    mText.setCharacterSize(mFontSize);
    mText.setPosition(mPos.x + (mSize.x - mText.getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2);
    mText.setFillColor(sf::Color::Black);
}

void InputBar::update(bool mousePress, sf::Vector2i mousePosition, char &keyPress, int capacity)
{
    sf::FloatRect bounds = mRect.getGlobalBounds();
    if (mousePress)
    {
        if (bounds.contains(static_cast<sf::Vector2f>(mousePosition)))
        {
            mSelected = true;
            mRect.setFillColor(mSelectedColor);
            mText.setFillColor(sf::Color::White);
        }
        else
        {
            mSelected = false;
            mHovered = false;
            mRect.setFillColor(mDefaultColor);
            mText.setFillColor(sf::Color::Black);
        }
        return;
    }
    if (!mSelected && bounds.contains(static_cast<sf::Vector2f>(mousePosition)))
    {
        mHovered = true;
        mRect.setFillColor(mHoveredColor);
        mText.setFillColor(sf::Color::Black);
    }
    else if (!mSelected)
    {
        mHovered = false;
        mRect.setFillColor(mDefaultColor);
        mText.setFillColor(sf::Color::Black);
    }

    if (keyPress == '$' || !mSelected)
    {
        keyPress = '$';
        return;
    }
    if (keyPress == '@')
    {
        if (!mValue.empty())
        {
            mValue.pop_back();
            mText.setString(mValue);
        }
    }
    else if ((int)mValue.size() < capacity)
    {
        if (keyPress == ' ' && (mType >= 2 || capacity <= 10 || mValue.empty() || mValue.back() == ' '))
        {
            // Do not allow the first character to be a space or 2 spaces, space in filename mode, trie mode, space in 2-digit mode
            keyPress = '$';
            return;
        }
        if (keyPress == '.' && mType != 2)
        {
            // '.' in !filename mode
            keyPress = '$';
            return;
        }
        if (mType == 0 && !(('0' <= keyPress && keyPress <= '9') || keyPress == ' '))
        {
            // only digit in digit mode
            keyPress = '$';
            return;
        }
        if (mType == 3 && !(('a' <= keyPress && keyPress <= 'z') || keyPress == ' '))
        {
            // only lowercase in trie mode
            keyPress = '$';
            return;
        }
        int mSize = (int)mValue.size();
        if (mType == 0 && keyPress != ' ' && mSize >= 2 && mValue[mSize - 1] != ' ' && mValue[mSize - 2] != ' ')
        {
            // Do not allow 3-digit numbers
            keyPress = '$';
            return;
        }
        mValue += keyPress;
        mText.setString(mValue);
    }

    keyPress = '$';
}

void InputBar::draw(sf::RenderWindow &mWindow)
{
    mWindow.draw(mRect);
    mText.setPosition(mPos.x + (mSize.x - mText.getLocalBounds().width) / 2, mPos.y + (mSize.y - mFontSize) / 2);
    mWindow.draw(mText);
}

void InputBar::reset(std::string defaultText)
{
    mValue = defaultText;
    mText.setString(mValue);
}