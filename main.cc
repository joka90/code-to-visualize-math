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
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    // Limit the framerate to 60 frames per second (this step is optional)
    window.setFramerateLimit(60);

	if (!MusicAnalyzer::isAvailable())
	{
		std::cout << "No recording device\n" ;
	    return 0;
	}

	MusicAnalyzer recorder;
	recorder.start();

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

		    // Update the window
		    window.display();
		}
    }
	recorder.stop();
    return 0;
}
