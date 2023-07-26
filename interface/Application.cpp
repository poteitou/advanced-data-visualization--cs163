#include "Application.hpp"

Application::Application()
    : mWindow(sf::VideoMode(1600, 900), "Data Structure Visualization", sf::Style::Titlebar | sf::Style::Close)
{
    mFont.loadFromFile("resources/fonts/arial.ttf");
    mWindow.setVerticalSyncEnabled(true);
    // to the refresh rate of the monitor, usually around 60Hz. This can avoid graphical artifacts such as screen tearing
    mWindow.setPosition(sf::Vector2i(175, 50));

    mousePress = false;
    keyPress = '$';
}

void Application::run()
{
    sf::Clock clock;
    // Screen mScreen(mWindow, mFont);

    while (mWindow.isOpen())
    {
        float dt = clock.restart().asSeconds();
        processEvents();
        // mScreen.update(mousePress, mousePosition, keyPress, dt);
        mWindow.clear();
        // render(mScreen);
    }
}

void Application::processEvents()
{
    sf::Event event;
    char c;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::MouseButtonPressed:
            if (event.mouseButton.button == sf::Mouse::Left)
                mousePress = true;
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Left)
                mousePress = false;
            break;
        case sf::Event::MouseMoved:
            mousePosition = sf::Mouse::getPosition(mWindow);
            break;
        case sf::Event::TextEntered:
            if (event.text.unicode == 8) // Backspace
                keyPress = '@';
            else if ((event.text.unicode >= 48 && event.text.unicode <= 57) || (event.text.unicode >= 97 && event.text.unicode <= 122) || (event.text.unicode >= 65 && event.text.unicode <= 90) || event.text.unicode == 32) // 0 -> 9 or space
                keyPress = static_cast<char>(event.text.unicode);
            else
                keyPress = '$';
            break;
        case sf::Event::KeyReleased:
            keyPress = '$';
            break;
        default:
            break;
        }
    }
}

void Application::render()//Screen &mScreen)
{
    sf::Texture texture;
    texture.loadFromFile("resources/images/background.png");
    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    mWindow.draw(sprite);
    // mScreen.draw();
    mWindow.display();
}
