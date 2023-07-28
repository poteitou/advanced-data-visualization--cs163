#include "ButtonImg.hpp"

ButtonImg::ButtonImg() {}

ButtonImg::ButtonImg(sf::Vector2f size, sf::Vector2f position, std::string file, std::string hoverFile)
    : mFile(file), mHoverFile(hoverFile), mHovered(false)
{
    mTexture.loadFromFile("resources/images/" + mFile);
    mSprite.setTexture(mTexture, true);
    mSprite.setPosition(position);
}

void ButtonImg::draw(sf::RenderWindow &mWindow)
{
    if (mHovered)
    {
        mTexture.loadFromFile("resources/images/" + mHoverFile);
        mSprite.setTexture(mTexture, true);
    }
    else
    {
        mTexture.loadFromFile("resources/images/" + mFile);
        mSprite.setTexture(mTexture, true);
    }

    mWindow.draw(mSprite);
}

bool ButtonImg::setMouseOver(sf::Vector2i mousePosition)
{
    sf::FloatRect bounds = mSprite.getGlobalBounds();

    if (bounds.contains(static_cast<sf::Vector2f>(mousePosition)))
    {
        mHovered = true;
        return true;
    }
    else
    {
        mHovered = false;
        return false;
    }
}

void ButtonImg::reset()
{
    mHovered = false;
}

