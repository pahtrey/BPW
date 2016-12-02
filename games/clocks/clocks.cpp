////////////////////////////////////////////////////////////
// Headers:
// ctime for getting system time and
// cmath for sin and cos functions
////////////////////////////////////////////////////////////
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cmath>

////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main()
{
	// Define some variables and constants
	const int screenWidth = 800;
	const int screenHeight = 600;
	const double PI = 3.1415927;
	const int clockCircleSize = 250;
	const int clockCircleThickness = 2;
	int x, y;
	double angle = 0.0;

	// Set multisampling level
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Create the window of the application
	sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "SFML Analog Clock", sf::Style::Close, settings);

	// Define windowCenter which gets the center of the window here, right after creating window
	sf::Vector2f windowCenter = sf::Vector2f(window.getSize().x / 2.0f, window.getSize().y / 2.0f);

	// Create a list for clock's dots
	sf::CircleShape hourDot[60];
	sf::RectangleShape dot[60];
	sf::Text clockFace[60];

	//Create text
	sf::Font font;
	if (!font.loadFromFile("resources/arial.ttf"))
	{
		return EXIT_FAILURE;
	}

	// Create dots and place them to very right positions
	for (int i = 0; i < 60; i++)
	{
		x = (clockCircleSize - 10) * cos(angle);
		y = (clockCircleSize - 10) * sin(angle);

		if (i % 5 == 0) {
			hourDot[i] = sf::CircleShape(3);
			clockFace[i].setString(std::to_string(i));
		}
		else
			dot[i] = sf::RectangleShape(sf::Vector2f(1, 8));

		hourDot[i].setFillColor(sf::Color::Black);
		hourDot[i].setOrigin(hourDot[i].getGlobalBounds().width / 2, hourDot[i].getGlobalBounds().height / 2);
		hourDot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		clockFace[i].setFont(font);
		clockFace[i].setFillColor(sf::Color::Black);
		clockFace[i].setCharacterSize(24);
		clockFace[i].setOrigin(clockFace[i].getGlobalBounds().width / 2, clockFace[i].getGlobalBounds().height / 2);
		clockFace[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		dot[i].setFillColor(sf::Color::Black);
		dot[i].setOrigin(dot[i].getGlobalBounds().width / 2, dot[i].getGlobalBounds().height / 2);
		dot[i].setPosition(x + window.getSize().x / 2, y + window.getSize().y / 2);

		dot[i].setRotation(i * 6 + 90);

		angle = angle + ((2 * PI) / 60);
	}

	// Create outline of the clock
	sf::CircleShape clockCircle(clockCircleSize);

	clockCircle.setPointCount(100);
	clockCircle.setOutlineThickness(clockCircleThickness);
	clockCircle.setOutlineColor(sf::Color::Black);
	clockCircle.setOrigin(clockCircle.getGlobalBounds().width / 2, clockCircle.getGlobalBounds().height / 2);
	clockCircle.setPosition(window.getSize().x / 2 + clockCircleThickness, window.getSize().y / 2 + clockCircleThickness);

	// Crate another circle for center
	sf::CircleShape centerCircle(10);

	centerCircle.setPointCount(100);
	centerCircle.setFillColor(sf::Color::Red);
	centerCircle.setOrigin(centerCircle.getGlobalBounds().width / 2, centerCircle.getGlobalBounds().height / 2);
	centerCircle.setPosition(windowCenter);

	// Create hour, minute, and seconds hands
	sf::RectangleShape hourHand(sf::Vector2f(5, 180));
	sf::RectangleShape minuteHand(sf::Vector2f(3, 240));
	sf::RectangleShape secondsHand(sf::Vector2f(2, 250));

	hourHand.setFillColor(sf::Color::Black);
	minuteHand.setFillColor(sf::Color::Black);
	secondsHand.setFillColor(sf::Color::Red);

	hourHand.setOrigin(hourHand.getGlobalBounds().width / 2, hourHand.getGlobalBounds().height - 25);
	minuteHand.setOrigin(minuteHand.getGlobalBounds().width / 2, minuteHand.getGlobalBounds().height - 25);
	secondsHand.setOrigin(secondsHand.getGlobalBounds().width / 2, secondsHand.getGlobalBounds().height - 25);

	hourHand.setPosition(windowCenter);
	minuteHand.setPosition(windowCenter);
	secondsHand.setPosition(windowCenter);

	// Create sound effect
	sf::Music clockTick;
	if (!clockTick.openFromFile("resources/clock-1.wav"))
		return EXIT_FAILURE;
	clockTick.setLoop(true);
	clockTick.play();

	// Use a part of SFML logo as clock brand
	sf::Texture clockBrand;
	if (!clockBrand.loadFromFile("resources/clock-brand.png"))
	{
		return EXIT_FAILURE;
	}
	sf::Sprite clockBrandSprite;
	clockBrandSprite.setTexture(clockBrand);
	clockBrandSprite.setOrigin(clockBrandSprite.getTextureRect().left + clockBrandSprite.getTextureRect().width / 2.0f,
		clockBrandSprite.getTextureRect().top + clockBrandSprite.getTextureRect().height / 2.0f);

	clockBrandSprite.setPosition(window.getSize().x / 2, window.getSize().y - 100);

	// Create clock background
	sf::Texture clockImage;
	if (!clockImage.loadFromFile("resources/clock-image.jpg"))
	{
		return EXIT_FAILURE;
	}

	clockCircle.setTexture(&clockImage);
	clockCircle.setTextureRect(sf::IntRect(40, 0, 500, 500));

	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Window closed: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Get system time
		std::time_t currentTime = std::time(NULL);

		struct tm * ptm = localtime(&currentTime);

		hourHand.setRotation(ptm->tm_hour * 30 + (ptm->tm_min / 2));
		minuteHand.setRotation(ptm->tm_min * 6 + (ptm->tm_sec / 12));
		secondsHand.setRotation(ptm->tm_sec * 6);

		// Clear the window
		window.clear(sf::Color::White);

		// Draw all parts of clock
		window.draw(clockCircle);

		for (int i = 0; i < 60; i++)
		{
			window.draw(dot[i]);
			window.draw(hourDot[i]);
		}

		for (int i = 1; i < 60; i++)
		{
			window.draw(clockFace[i]);
		}

		window.draw(clockBrandSprite);
		window.draw(hourHand);
		window.draw(minuteHand);
		window.draw(secondsHand);
		window.draw(centerCircle);

		// Display things on screen
		window.display();
	}

	return EXIT_SUCCESS;
}