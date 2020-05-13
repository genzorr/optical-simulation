#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>
#include "CircleDifr.h"
#include "GapDifr.h"
#include "Edge.h"

int main()
{
	std::string difrType;
	std::cin >> difrType;
	std::transform(difrType.begin(), difrType.end(), difrType.begin(), tolower);
	int grow = 1;
	double lamda = 0.760;
	double screenDistance = 20;
	double electrofield = 63;
	sf::RenderWindow window(sf::VideoMode(WINDOWSIZE, WINDOWSIZE), "My window");
	if(difrType == "circle")
	{
		double radius = 10;
		window.setFramerateLimit(30);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Request for closing the window
				if (event.type == sf::Event::Closed)
					window.close();

			}
			sf::Image image;
			double parametr = sqrt(lamda * screenDistance) / radius;
			if (parametr < 0.35)
			{
				Geometric field(lamda, radius, screenDistance, electrofield);
				Draw(field, image);
			}
			else if (parametr < 0.45)
			{
				SemiGeom field(lamda, radius, screenDistance, electrofield);
				Draw(field, image);
			}
			else
			{
				NonGeom field(lamda, radius, screenDistance, electrofield);
				Draw(field, image);
			}

			sf::Texture texture;
			texture.loadFromImage(image);

			sf::Sprite sprite(texture);

			if (screenDistance < 4)
			{
				grow = 1;
			}
			else if (screenDistance > 60)
			{
				grow = -1;
			}

			screenDistance += grow * INCREMENT;
			std::cout << screenDistance << std::endl;

			window.clear(sf::Color::Black);
			window.draw(sprite);
			window.display();
		}
	}
	else if (difrType == "gap")
	{
		double width = 20;
		window.setFramerateLimit(30);
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Request for closing the window
				if (event.type == sf::Event::Closed)
					window.close();

			}
			sf::Image image;
			double parametr = sqrt(lamda * screenDistance) / width;
			if (parametr < 0.25)
			{
				GapGeometric field(lamda, width, screenDistance, electrofield);
				Draw(field, image);
				std::cout << "GEOM" << std::endl;
			}
			else if (parametr < 0.45)
			{
				GapGeomFrenel field(lamda, width, screenDistance, electrofield);
				Draw(field, image);
				std::cout << "GF" << std::endl;
			}
			else if (parametr < 0.6)
			{
				GapFrenel field(lamda, width, screenDistance, electrofield);
				Draw(field, image);
				std::cout << "F1" << std::endl;
			}
			else if (parametr < 0.7)
			{
				GapFrenelFraungof field(lamda, width, screenDistance, electrofield);
				Draw(field, image);
				std::cout << "FF" << std::endl;
			}
			else
			{
				GapFraungof field(lamda, width, screenDistance, electrofield);
				Draw(field, image);
				std::cout << "F2" << std::endl;
			}

			sf::Texture texture;
			texture.loadFromImage(image);

			sf::Sprite sprite(texture);

			/*if (screenDistance < 50)
			{
				grow = 1;
			}
			else if (screenDistance > 500)
			{
				grow = -1;
			}*/

			screenDistance += grow * INCREMENT;
			//std::cout << screenDistance << std::endl;

			window.clear(sf::Color::Black);
			window.draw(sprite);
			window.display();
		}
	}
	else if (difrType == "edge")
	{
		window.setFramerateLimit(30);

		sf::Image image;
		//double parametr = sqrt(lamda * screenDistance) / width;

		EdgeDifractionFrenel field(lamda, screenDistance, electrofield);
		Draw(field, image);

		while (window.isOpen())
		{
			//std::cout << screenDistance << std::endl;
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Request for closing the window
				if (event.type == sf::Event::Closed)
					window.close();

			}
			sf::Texture texture;
			texture.loadFromImage(image);

			sf::Sprite sprite(texture);

			//screenDistance += grow * INCREMENT;
			//std::cout << screenDistance << std::endl;


			window.clear(sf::Color::Black);
			window.draw(sprite);
			window.display();

		}
	}
	return 0;
}

