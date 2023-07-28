#ifndef BUTTONIMG_HPP
#define BUTTONIMG_HPP

#include <SFML/Graphics.hpp>

struct ButtonImg
{
    ButtonImg();
    ButtonImg(sf::Vector2f size, sf::Vector2f position, std::string file, std::string hoverFile);

    void draw(sf::RenderWindow &mWindow);
    bool setMouseOver(sf::Vector2i mousePosition);
    void reset();

    sf::Texture mTexture;
    sf::Sprite mSprite;
    std::string mFile;
    std::string mHoverFile;
    bool mHovered;
};

#endif // BUTTONIMG_HPP

