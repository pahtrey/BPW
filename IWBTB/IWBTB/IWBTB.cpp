// IWBTB.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Configuration.h"
#include "iostream"

using namespace sf;

float mapOffsetX = MAP_ELEMENT_SIZE, mapOffsetY = WINDOW_HEIGHT / 2 - MAP_ELEMENT_SIZE * 2;

std::string mapArray[MAP_HEIGHT] = {
	"0000000000000000000000000000000000000000", // D - дверь низ
	"0                                      0", // d - дверь верх
	"0                                      0", // C - монетка
	"0                                      0", // S - звезда
	"0                                      0", // 0 - пустота
	"0    F                                 0", // F - флаг
	"0LBBBBBBBBBBBBBR   LBBBBBBBBBBBBBR     0", // L - левый блок
	"0                                      0", // R - правый блок
	"0                                      0", // B - центральный блок
	"0      LBBBBBBBBBBBBBB    LBBBBBBBBBBBR0", // 
	"0LBR                                   0", //
	"0                                      0", //
	"0      LBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBR0", //
	"0LBR                                   0", //
	"0             CCC                      0", //
	"0LBBBBBBBBBBBBBBBBBBR   LBBBBBBBBBR    0",
	"0                         B            0",
	"0LBBBBBR                  B            0",
	"0                         B            0",
	"0                   LBBBBBR            0",
	"0   S       LR                         0",
	"0                     LR       LBR     0",
	"0                                   S  0",
	"0LBBBBBBBBBBBBR      LBBBBBBBBBBBBBBBBR0",
	"0 d                                    0",
	"0 D                               CC   0",
	"0LBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBR0",
};

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
		body = FloatRect(3 * MAP_ELEMENT_SIZE, 25 * MAP_ELEMENT_SIZE, CHARACTER_WIDTH, CHARACTER_HEIGHT);

		onGround = true;

		x = y = 0.1;
		frame = 0;
	}

	void SetDefaultSkin()
	{
		skin.setTextureRect(IntRect(0, 0, CHARACTER_WIDTH, CHARACTER_HEIGHT));
	}

	void update(float time)
	{
		body.left += x * time;
		
		Collision(0);

		if (!onGround)
		{
			y = y + 0.0005 * time;
		}

		body.top += y * time;
		onGround = false;

		Collision(1);

		frame += 0.005 * time;
		if (frame > 1)
		{
			frame -= 1;
		}

		if (x > 0)
		{
			skin.setTextureRect(IntRect(CHARACTER_WIDTH * (int)frame, CHARACTER_HEIGHT, CHARACTER_WIDTH, CHARACTER_HEIGHT));
		}
		else if (x < 0)
		{
			skin.setTextureRect(IntRect(CHARACTER_WIDTH * (int)frame + CHARACTER_WIDTH, CHARACTER_HEIGHT, -CHARACTER_WIDTH, CHARACTER_HEIGHT));
		}

		skin.setPosition(body.left - mapOffsetX, body.top - mapOffsetY);

		x = 0;
	}

	void Collision(int dir)
	{
		for (int i = body.top / MAP_ELEMENT_SIZE; i < (body.top + body.height) / MAP_ELEMENT_SIZE; i++)
		{
			for (int j = body.left / MAP_ELEMENT_SIZE; j < (body.left + body.width) / MAP_ELEMENT_SIZE; j++)
			{
				if (mapArray[i][j] == 'B' || mapArray[i][j] == 'L' || mapArray[i][j] == 'R' || mapArray[i][j] == '0')
				{
					if (x > 0 && dir == 0)
					{
						body.left = j * MAP_ELEMENT_SIZE - body.width;
					}

					if (x < 0 && dir == 0)
					{
						body.left = j * MAP_ELEMENT_SIZE + MAP_ELEMENT_SIZE;
					}

					if (y > 0 && dir == 1)
					{
						body.top = i * MAP_ELEMENT_SIZE - body.height;
						y = 0;
						onGround = true;
					}

					if (y < 0 && dir == 1)
					{
						body.top = i * MAP_ELEMENT_SIZE + MAP_ELEMENT_SIZE;
						y = 0;
					}
				}
			}
		}
	}
};


int main()
{
	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);

	Texture texture;
	texture.loadFromFile("resources/sprite.png");

	CCharacter character(texture);

	Clock clock;
	RectangleShape map(Vector2f(MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
	map.setTexture(& texture);

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
			character.x = -0.2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			character.x = 0.2;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (character.onGround)
			{
				character.y = -0.5;
				character.onGround = false;
			}
		}


		character.update(time);

		if ((character.body.left > WINDOW_WIDTH / 2 + MAP_ELEMENT_SIZE)
			&& (character.body.left < ((MAP_WIDTH * MAP_ELEMENT_SIZE) - (WINDOW_WIDTH / 2) - MAP_ELEMENT_SIZE * 2)))
		{
			mapOffsetX = character.body.left - WINDOW_WIDTH / 2; 
		}

		if ((character.body.top > WINDOW_HEIGHT / 2 + MAP_ELEMENT_SIZE)
			&& (character.body.top < ((MAP_HEIGHT * MAP_ELEMENT_SIZE) - (WINDOW_HEIGHT / 2))))
		{
			mapOffsetY = character.body.top - WINDOW_HEIGHT / 2;
		}

		window.clear(Color::White);

		for (int i = 0; i < MAP_HEIGHT; i++)
		{
			for (int j = 0; j < MAP_WIDTH - 1; j++)
			{
				if (mapArray[i][j] == 'B')
				{
					map.setTextureRect(IntRect(103, 40, MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
				}

				if (mapArray[i][j] == 'L')
				{
					map.setTextureRect(IntRect(63, 80, MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
				}

				if (mapArray[i][j] == 'R')
				{
					map.setTextureRect(IntRect(63, 0, MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
				}

				if (mapArray[i][j] == 'S')
				{
					map.setTextureRect(IntRect(103, 0, MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
				}

				if (mapArray[i][j] == 'C')
				{
					map.setTextureRect(IntRect(103, 80, MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
				}

				if (mapArray[i][j] == 'd')
				{
					map.setTextureRect(IntRect(143, 80, MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
				}

				if (mapArray[i][j] == 'D')
				{
					map.setTextureRect(IntRect(183, 80, MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
				}

				if (mapArray[i][j] == 'F')
				{
					map.setTextureRect(IntRect(183, 0, MAP_ELEMENT_SIZE, MAP_ELEMENT_SIZE));
				}

				if (mapArray[i][j] == '0')
				{
					map.setTextureRect(IntRect(0, 0, 0, 0));
				}

				if (mapArray[i][j] == ' ')
				{
					continue;
				}

				map.setPosition(MAP_ELEMENT_SIZE * j - mapOffsetX, MAP_ELEMENT_SIZE * i - mapOffsetY);
				window.draw(map);
			}
		}

		window.draw(character.skin);
		window.display();
	}

    return 0;
}