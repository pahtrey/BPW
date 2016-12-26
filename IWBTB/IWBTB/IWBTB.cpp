// IWBTB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "iostream"

using namespace sf;

int ground = WINDOW_HEIGHT - 32;

class CCharacter
{
public:
	float x, y;
	FloatRect body;
	bool onGround;
	Sprite skin;
	float frame;

	CCharacter(Texture & image)
	{
		skin.setTexture(image);
		skin.setTextureRect(IntRect(0, 0, 32, 32));
		body = FloatRect(32, 32, 32, 32);

		onGround = true;

		x = y = 0;
		frame = 0;
	}

	void SetDefaultSkin()
	{
		skin.setTextureRect(IntRect(0, 0, 32, 32));
	}

	void update(float time)
	{
		body.left += x * time;
		
		if (!onGround)
		{
			y = y + 0.0005 * time;
		}

		body.top += y * time;
		onGround = false;

		if (body.top > ground) 
		{
			body.top = ground;
			y = 0;
			onGround = true;
		}

		frame += 0.005 * time;
		if (frame > 5)
		{
			frame -= 5;
		}

		if (x > 0)
		{
			skin.setTextureRect(IntRect(32 * (int)frame, 32, 32, 32));
		}
		else if (x < 0)
		{
			skin.setTextureRect(IntRect(32 * (int)frame + 32, 32, -32, 32));
		}

		skin.setPosition(body.left, body.top);

		x = 0;
	}
};


int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

	Texture texture;
	texture.loadFromFile("resources/sprite.png");

	CCharacter character(texture);

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 500;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}

		character.SetDefaultSkin();

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			character.x = -0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			character.x = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (character.onGround)
			{
				character.y = -0.4;
				character.onGround = false;
			}
		}

		character.update(time);

		window.clear(Color::White);
		window.draw(character.skin);
		window.display();
	}

    return 0;
}