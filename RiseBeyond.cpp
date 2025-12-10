#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <ctime>

using namespace sf;

class UserWindow : public RenderWindow
{

public:
    Texture backgroundTexture;
    Sprite backgroundSprite;

    UserWindow()
    {
        setSize(Vector2u(1920, 1080));
        backgroundTexture.loadFromFile("images/background.png");
        backgroundSprite.setTexture(backgroundTexture);
        setTitle("Rise Beyond");
    }

    void drawBackground()
    {
        RenderWindow::draw(backgroundSprite);
    }
};

class Circle : public CircleShape
{
public:
    Circle(int radius, float x, float y)
    {
        setRadius(radius);
        setPosition(Vector2f(x / 2 - 10, y / 2 - 20));
    }
};

class ShapeGenerate
{
public:
    RectangleShape rectangles[20];
    ConvexShape a;

    ShapeGenerate()
    {
        a.setPointCount(3);
        a.setPoint(0, Vector2f(10, 10));
        a.setPoint(1, Vector2f(40, 50));
        a.setPoint(2, Vector2f(45, 35));
        srand(time(0));
        for (int i = 0; i < 20; i++)
        {
            if (i < 5)
            {
                rectangles[i].setSize(Vector2f(50, 50));
            }
            else if (i > 4 && i < 10)
            {
                rectangles[i].setSize(Vector2f(75, 75));
            }
            else if (i > 9 && i < 15)
            {
                rectangles[i].setSize(Vector2f(90, 90));
            }
            else
            {
                rectangles[i].setSize(Vector2f(120, 120));
            }
            rectangles[i].setFillColor(Color ::Red);
            rectangles[i].setPosition(Vector2f(i * 100, -rand() % 500));
        }
    }
};

struct Textures
{
    Texture Background;
    Texture GameOver;
    Texture balloon;
    Texture invertBaloon;
} textures;

enum GameState
{
    waiting,
    started,
    gameover
};

struct game
{
    GameState gamestate = started;
} game;

struct sprites
{
    Sprite image;
} home, balloon, gameOver;

int main()
{
    RenderWindow window(VideoMode::getDesktopMode(), "Rise Beyond");
    Circle circle(15, window.getSize().x, window.getSize().y);
    ShapeGenerate s1;
    Text t;
    Font f;
    // f.loadFromFile
    // t.setFont();

    textures.Background.loadFromFile("images/B.png");
    textures.GameOver.loadFromFile("./images/gameover.png");
    textures.balloon.loadFromFile("images/balloon.png");
    textures.Background.setSmooth(true);

    home.image.setTexture(textures.Background);
    home.image.setScale(window.getSize().x / home.image.getLocalBounds().width, window.getSize().y / home.image.getLocalBounds().height);

    gameOver.image.setTexture(textures.GameOver);
    // gameOver.image.setScale(window.getSize().x / gameOver.image.getLocalBounds().width, window.getSize().y / gameOver.image.getLocalBounds().height);
    gameOver.image.setPosition(window.getSize().x / 2, window.getSize().y / 2);
    balloon.image.setTexture(textures.balloon);
    balloon.image.setPosition(window.getSize().x / 3 + 60, window.getSize().y / 2 + 20);

    sf::FloatRect Balloon = balloon.image.getGlobalBounds();
                std::cout << "Balloon GlobalBounds:" << std::endl;
                std::cout << "Left: " << Balloon.left << std::endl;
                std::cout << "Top: " << Balloon.top << std::endl;
                std::cout << "Width: " << Balloon.width << std::endl;
                std::cout << "Height: " << Balloon.height << std::endl;
    while (window.isOpen())
    {

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
        }
        if (game.gamestate == started)
        {
            circle.setPosition(Mouse::getPosition().x - 14, Mouse::getPosition().y - 90);
            window.clear();
            window.draw(home.image);
            for (int j = 0; j < 20; j++)
            {

                window.draw(s1.rectangles[j]);
                s1.rectangles[j].move(0, 0.2);
            }

            window.draw(balloon.image);

            window.draw(circle);
            for (int x = 0; x < 20; x++)
            {
                sf::FloatRect rectBounds = s1.rectangles[x].getGlobalBounds();
                std::cout << "Balloon GlobalBounds:" << std::endl;
                std::cout << "Left: " << rectBounds.left << std::endl;
                std::cout << "Top: " << rectBounds.top << std::endl;
                std::cout << "Width: " << rectBounds.width << std::endl;
                std::cout << "Height: " << rectBounds.height << std::endl;
                
                if (balloon.image.getGlobalBounds().intersects(s1.rectangles[x].getGlobalBounds()))
                    game.gamestate = gameover;
            }
            window.display();

            if (game.gamestate == gameover)
            {

                // game.gamestate = waiting;
                // window.draw(gameOver.image);
                // window.display();
            }
        }
    }
    return 0;
}