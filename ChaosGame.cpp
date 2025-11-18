#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    // Points to generate in one frame/loop
    int NPointsGen = 50;

    // Number of vertices, max vertices
    int NVertices = 3;      //default, but will be decided later...
    int MaxVertices = 8;    //upper limit of vertices...
    bool EndClickInput = false;

    // Create a video mode object
    VideoMode vm(1900, 1000);

    // Create and open a window for the game
    RenderWindow window(vm, "Chaos Game - Sierpinski triangle +", Style::Default);
    vector<Vector2f> vertices;
    vector<Vector2f> points;

    // Prepare for the Font object with styles
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
        if (vertices.size() < MaxVertices && !EndClickInput)
        {
            hintText.setString("Left Click on at least 3 up to " + to_string(MaxVertices) + " Points on the screen to create the vertices; Right click to end.");
        }
        else if (points.size() == 0)
        {
            hintText.setString("Left Click one more time for the Starting Point...");
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
                    if (vertices.size() < MaxVertices && !EndClickInput)
                    {
                        std::cout << "the left button was pressed" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;
                        vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else if (points.size() == 0)
                    {
                        ///fourth click
                        std::cout << "the left button was pressed for the start point!!" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                        ///push back to points vector
                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right && !EndClickInput)
                {
                    int n = vertices.size();
                    if (n >= 3 && n <= MaxVertices)
                    {
                        std::cout << "the right button was pressed ~" << std::endl;
                        EndClickInput = true;
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
                Vector2f vtx = vertices[rand() % vertices.size()];

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