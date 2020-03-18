#include "Clouds.h"


Clouds::Clouds(int t_width, int t_height) :
	MIN_RAD{25},
	MAX_RAD{75},
	m_width{t_width},
	m_height{t_height}
{
	initArray();
}

///////////////////////////////////////////////////////////////

void Clouds::initArray()
{
	for (CloudPiece& c : m_cloudArray)
	{
		// Random radius between min and max
		float radius = static_cast<float>((rand() % (MAX_RAD - MIN_RAD)) + MIN_RAD);
		c.rad = radius;

		// Random position within bounds, with an overdraw of 50 pixels added on either side to prevent gaps at edge
		c.shape.setPosition({ static_cast<float>(rand() % (m_width + 100) - 50), static_cast<float>(rand() % m_height) - 50});

		// Random shade of grey
		int colorOffset = rand() % 64;
		c.shape.setFillColor(sf::Color( 64 + colorOffset, 64 + colorOffset, 64 + colorOffset, 255 ));

		c.growing = rand() % 2;
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

		// random between 0.00 and 0.25
		float deltaRad{ (rand() % 20) / 100.0f };
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