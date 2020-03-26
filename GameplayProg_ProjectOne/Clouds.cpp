#include "Clouds.h"


Clouds::Clouds(int t_width, int t_height) :
	MIN_RAD{75},
	MAX_RAD{150},
	m_width{t_width},
	m_height{t_height}
{
	loadTextures();
	initArray();
}

///////////////////////////////////////////////////////////////

void Clouds::loadTextures()
try
{
	if (!m_texture.loadFromFile("ASSETS\\TEXTURES\\cloud.png"))
	{
		std::string msg{ "Error loading cloud texture" };
		throw std::exception(msg.c_str());
	}
}
catch (const std::exception& e)
{
	std::cout << e.what() << std::endl;
}

///////////////////////////////////////////////////////////////

void Clouds::initArray()
{
	for (CloudPiece& c : m_cloudArray)
	{
		// Random radius between min and max
		float radius = static_cast<float>((rand() % (MAX_RAD - MIN_RAD)) + MIN_RAD);
		c.rad = radius;

		// Random position within bounds, with an overdraw of 100 pixels added on either side to prevent gaps at edge
		c.shape.setPosition({ static_cast<float>(rand() % (m_width + 200) - 150), static_cast<float>(rand() % m_height) - 100});

		// Random shade of grey
		int colorOffset = rand() % 128;
		c.shape.setFillColor(sf::Color(64 + colorOffset, 64 + colorOffset, 64 + colorOffset, 64 + colorOffset ));

		// Add a slight rotational bias to offset uniformity
		c.shape.setRotation(rand() % 10 - 5);

		// Flip a coin to decide if they're growing or shrinking
		c.growing = rand() % 2;

		c.shape.setTexture(&m_texture);
	}
}

///////////////////////////////////////////////////////////////

void Clouds::update(sf::Time t_dT)
{
	for (CloudPiece& c : m_cloudArray)
	{
		// If we hit our min or max (with a random offset), change direction
		if (c.rad >= MAX_RAD - rand() % 10)
		{
			c.growing = false;
		}
		else if (c.rad <= MIN_RAD + rand() % 10)
		{
			c.growing = true;
		}

		// random between 0.00 and 0.10
		float deltaRad{ (rand() % 10) / 100.0f };
		c.rad += (c.growing) ? deltaRad : -deltaRad;

		// Update our radius
		c.shape.setRadius(c.rad);
	}
}

///////////////////////////////////////////////////////////////

void Clouds::draw(sf::RenderTarget& t_target, sf::RenderStates t_state) const
{
	for (auto& c : m_cloudArray)
	{
		t_target.draw(c.shape);
	}
}