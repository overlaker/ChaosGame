#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    int NPointsGen = 10;

    // Create a video mode object
    VideoMode vm(1900, 1000);

    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game - Sierpi?ski triangle", Style::Default);
    vector<Vector2f> vertices;
    vector<Vector2f> points;

    sf::Font font;
    sf::Text hintText;
    if (!font.loadFromFile("KOMIKAP_.ttf"))
    {
        cout << "Failed to load Font file!!" << endl;
    }
    else
    {
        hintText.setFont(font);
        //hintText.setString("Hello world");
        hintText.setCharacterSize(24); // in pixels, not points!
        hintText.setFillColor(sf::Color::White);
        //hintText.setStyle(sf::Text::Bold | sf::Text::Underlined);
    }

    while (window.isOpen())
    {
        /** Hint the user **/
        if (vertices.size() < 3)
        {
            hintText.setString(" Click on any 3 Points on the screen to create the vertices for the triangle...");
        }
        else if (points.size() == 0)
        {
            hintText.setString(" Click one more time for the Starting Point...");
        }
        else hintText.setString("");

        /*
        ****************************************
        Handle the players input
        ****************************************
        */
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                // Quit the game when the window is closed
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    if (vertices.size() < 3)
                    {
                        std::cout << "the left button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        std::cout << "the left button was pressed for the 4th time!!" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        /*
        ****************************************
        Update
        ****************************************
        */
        if (points.size() > 0)
        {
            //** generate more point(s) **
            for (int i = 0; i < NPointsGen; i++)
            {
                //(1) select random vertex
                Vector2f vtx = vertices[rand() % 3];

                //(2) calculate midpoint between random vertex and the last point in the vector
                Vector2f last = points.at(points.size() - 1);
                Vector2f npt;
                npt.x = (vtx.x + last.x) / 2.0;
                npt.y = (vtx.y + last.y) / 2.0;

                //(3) push back the newly generated coord.
                points.push_back(npt);
            }
        }

        /*
        ****************************************
        Draw
        ****************************************
        */
        window.clear();

        if (hintText.getString().getSize() > 0) window.draw(hintText);

        for (unsigned long i = 0; i < vertices.size(); i++)
        {
            RectangleShape rect(Vector2f(4, 4));
            rect.setPosition(Vector2f(vertices[i].x - 2, vertices[i].y - 2));
            rect.setFillColor(Color::Green);
            window.draw(rect);
        }

        //** Draw points **
        for (unsigned long i = 0; i < points.size(); i++)
        {
            RectangleShape rect(Vector2f(2, 2));
            rect.setPosition(Vector2f(points[i].x - 1, points[i].y - 1));
            rect.setFillColor(Color::Yellow);
            window.draw(rect);
        }

        window.display();
    }
    //End while loop#
}