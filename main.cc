#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include "MusicAnalyzer.h"

#include <math.h>
#define PI 3.14159265


int main()
{
   // Create the main window
    sf::RenderWindow window(sf::VideoMode(1900, 1000), "SFML window");

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("appleberry_with_cyrillic.ttf"))
        return EXIT_FAILURE;

    // Create a graphical text to display
    sf::Text text("Hello SFML", font, 30);
	text.setPosition(100,100);

    // Limit the framerate to 60 frames per second (this step is optional)
    window.setFramerateLimit(60);

	if (!MusicAnalyzer::isAvailable())
	{
		std::cout << "No recording device\n" ;
	    return 0;
	}

	MusicAnalyzer recorder;
	recorder.start();

	sf::Clock clock;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
		if(recorder.vaildData)
		{
		    // Clear screen
		    window.clear();
			recorder.draw(window);
			sf::Time time1 = clock.getElapsedTime();
			clock.restart();
		    // SHOW samples per sec
		    std::stringstream ss;
		    ss <<  1/time1.asSeconds() << " sps";
		    text.setString(ss.str());
			// Update the canvas
			window.draw(text);
		    // Update the window
		    window.display();
		}
    }
	recorder.stop();
    return 0;
}
