#include <iostream>
#include <sstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int main()
{
    // Global Var.
    int NPointsGen = 1000;    // Points to generate in one frame/loop
    float MagicRatios[] = { 0.5, 0.5, 0.618, 0.6667, 0.692, 0.707, 0.742, 0.764 };  //3~10 vertices
    long unsigned int MaxVertices = 8;    //upper limit of vertices...
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
                        ///pick start point
                        std::cout << "the left button was pressed for the start point!!" << std::endl;
                        std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                        std::cout << "mouse y: " << event.mouseButton.y << std::endl;

                        points.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
                    }
                    else
                    {
                        std::cout << "Total points: " << points.size() << endl;
                    }
                }
                else if (event.mouseButton.button == sf::Mouse::Right && !EndClickInput)
                {
                    long unsigned int n = vertices.size();
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
            float ratio = MagicRatios[vertices.size() - 3];
            int lastIdx = -1;
            // generate NPointsGen points
            for (int i = 0; i < NPointsGen; i++)
            {
                //(1) select random vertex
                int idx = rand() % vertices.size();
                //Avoid the same vertex twice in a row for rectangle (only!)
                while (idx == lastIdx && vertices.size() == 4)
                {
                    idx = rand() % vertices.size();
                }
                Vector2f vtx = vertices[idx];
                lastIdx = idx;

                //(2) calculate midpoint between random vertex and the last point in the vector
                Vector2f last = points.at(points.size() - 1);
                Vector2f npt;
                npt.x = last.x + ratio * (vtx.x - last.x);
                npt.y = last.y + ratio * (vtx.y - last.y);

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
