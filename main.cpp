//preprocessor directives & includes
#include <iostream>
#include <SFML/Graphics.hpp>
#include <cmath>

#include "ParticleSystem.h"

//2014-10-27
//using ParticleSystem (vertices)
//By Louis Haquette

int main()
{
    srand(time(0));

    //declaration + initialisation
    unsigned int vertexCount(0);

    //ask the vertex amount to the user
    std::cout << "write the the vertex amount (unsigned integer)" << std::endl;

    std::cin >> vertexCount;

    //generate RenderWindow
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Particles");

    //generate the vertices in a ParticleSystem instance (particles)
    ParticleSystem particles(vertexCount);

    std::cout << std::endl << "done" << std::endl << std::endl;

    sf::Clock clock;

    //main loop
    while (window.isOpen())
    {
        //events
        sf::Event event;

        //events loop
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
            {
                window.close();
            }

            if (event.type == sf::Event::Resized)
            {
                //set wiewPort
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;

                    particles.setColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

                    std::cout << "R = "
                    << int(particles.getColor().r) << " ; G = "
                    << int(particles.getColor().g) << " ; B = "
                    << int(particles.getColor().b) << std::endl << std::endl;
                }
                else if (event.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;

                    particles.resetAllParticles();

                    std::cout  << "particles clear" << std::endl << std::endl;
                }
                else if (event.mouseButton.button == sf::Mouse::Middle)
                {
                    std::cout  << "the middle button was pressed" << std::endl << std::endl;

                    particles.changeColor();
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    std::cout << "the up key was pressed" << std::endl;
                    std::cout << "control: " << event.key.control << std::endl;

                    if (event.key.control)
                    {
                        particles.setSpeed(particles.getSpeed() + 10);
                    }
                    else
                    {
                        particles.setSpeed(particles.getSpeed() + 1);
                    }

                    std::cout << "speed = " << particles.getSpeed() << event.key.control << std::endl << std::endl;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    std::cout << "the down was pressed" << std::endl;
                    std::cout << "control: " << event.key.control << std::endl;

                    if (event.key.control)
                    {
                        if (!(particles.getSpeed() - 10 <= 0))
                        {
                            particles.setSpeed(particles.getSpeed() - 10);
                        }
                    }
                    else
                    {
                        if (!(particles.getSpeed() - 1 <= 0))
                        {
                            particles.setSpeed(particles.getSpeed() - 1);
                        }
                    }

                    std::cout << "speed = " << particles.getSpeed() << event.key.control << std::endl << std::endl;
                }
            }

            if (event.type == sf::Event::MouseWheelMoved)
            {
                std::cout << "wheel movement: " << event.mouseWheel.delta << std::endl;

                if (!(particles.getLifetimeS() + event.mouseWheel.delta < 1) && !(particles.getLifetimeS() + event.mouseWheel.delta > 64))
                {
                    particles.setLifetime(particles.getLifetimeS() + event.mouseWheel.delta);
                }

                std::cout  << "particle lifetime = " << particles.getLifetimeS() << " sec" << std::endl << std::endl;
            }

        }

        //particles emitter focus the mouse position
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        particles.setEmitter(window.mapPixelToCoords(mouse));

        //updates particles
        sf::Time elapsed = clock.restart();
        particles.update(elapsed);

        //drawing
        window.clear();
        window.draw(particles);
        window.display();
    }

    //main end
    return 0;
}
